#include "ofApp.h"

#include "variations.h" // for prepare_precalc_flags and CMAP_SIZE

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(false);
    ofSetLogLevel(OF_LOG_VERBOSE);

    counter = 0;
    nsamples = 25000;	seed = 0;
    genomeIdx = 0;
    dotSizeUsesAudio = true;
    transp = 60;
    ofSetWindowTitle("D0TS");

    currFlameSamples = (double *)malloc(sizeof(double)*nsamples*4);
    prevFlameSamples = (double *)malloc(sizeof(double)*nsamples*4);

    parity = 0;
    framecount = 0;
    fullscreen = 1;
    momode = 1;

    // GUI-displayed
    mpx = mpy = 0.0;
    mmpx = mmpy = 0.0;

    // GUI-controlled
    baseSpeed = 0.25;
    rmsSpeedMult = 0;
    mpxSmoothingFactor = 0.4;
    mpySmoothingFactor = 0.1;
    centroidMaxBucket = 0.35;
    rmsMultiple = 5;
    wandering = false;
    frameClearSpeed = 50;
    
    ofHideCursor();
    
    visualsFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
    
    // cpv = (flam3_genome *) malloc(sizeof(flam3_genome)*2);
    {
        FILE *in;
        char *inf = "../../../data/live.flam3";
        in = fopen(inf, "rb");
        if (!in) {
            cout << "couldn't open flame3, exiting" << endl;
            std::exit(1);
        }
        cps = flam3_parse_from_file(in, inf, flam3_defaults_on, &ncps);
        for (int i = 0; i < ncps; i++) {
            cps[i].time = (double) i;
        }
        if (!cps) {
            cout << "couldn't read flame3, exiting" << endl;
            std::exit(1);
        }
    }
    {
        FILE *in;
        char *inf = "../../../data/genebank2.flam3";
        in = fopen(inf, "rb");
        if (!in) {
            cout << "couldn't open genebank, exiting" << endl;
            std::exit(1);
        }
        genebank = flam3_parse_from_file(in, inf, flam3_defaults_on, &ngenebank);
    }
    memset(&cp, 0, sizeof(flam3_genome));
    flam3_copy(&cp, &cps[genomeIdx]);
	   
    audioMode = AUDIO_MODE_MIC;
    ofSoundStreamListDevices();
    
    int bufferSize = 512;
    soundStreamDevice = 0;
    nChannels = 1;
    soundStream.setup(this, 0, nChannels, 44100, bufferSize, 4);
    soundStream.setDeviceID(soundStreamDevice);
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HANN);
    nFftBuckets = fft->getBinSize();
    
    audioInput = new float[bufferSize];
    fftOutput = new float[nFftBuckets];
    audioRMS = smoothedAudioRMS = 0;
    for (int i = 0; i < bufferSize; ++i) {
        audioInput[i] = 0;
    }
    for (int i = 0; i < nFftBuckets; ++i) {
        fftOutput[i] = 0;
    }
    
    gui->nAudioBuckets = nFftBuckets;
    gui->audioBuckets = fftOutput;

    billboardShader.setGeometryInputType(GL_LINES);
    billboardShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
    billboardShader.setGeometryOutputCount(12);
    billboardShader.load("billboardShader.vert", "billboardShader.frag", "billboardShader.geom");
    billboardShader.bindDefaults();

    float glMaxPointSize;
    glGetFloatv(GL_POINT_SIZE_MAX, &glMaxPointSize);
    cout << "GL max point radius: " << glMaxPointSize << endl;

    float lineWidthRange[2];
    glGetFloatv(GL_LINE_WIDTH_RANGE, lineWidthRange);
    cout << "GL line width range: " << lineWidthRange[0] << "-" << lineWidthRange[1] << endl;

    lines.setMode(OF_PRIMITIVE_LINES);
    lines.setUsage(GL_STREAM_DRAW);
    pointRadii = (float *)malloc(sizeof(float) * nsamples * 2);
    lineWidths = (float *)malloc(sizeof(float) * nsamples * 2);

    pointPairs.resize(nsamples);

    for (int i = 0; i < nsamples; ++i) {
        lines.addVertex(ofVec3f());
        lines.addColor(ofFloatColor());
        lines.addVertex(ofVec3f());
        lines.addColor(ofFloatColor());

        pointRadii[2*i] = 0;
        pointRadii[2*i+1] = 0;
        lineWidths[2*i] = 0;
        lineWidths[2*i+1] = 0;

        pointPairs[i].idx = i;
        pointPairs[i].pt1 = ofVec3f(0);
        pointPairs[i].pt2 = ofVec3f(0);
        pointPairs[i].ptSize = 0;
        pointPairs[i].lineWidth = 0;
    }

    int loc;
    billboardShader.printActiveAttributes();
    billboardShader.begin();
        loc = billboardShader.getAttributeLocation("pointRadius");
        lines.getVbo().setAttributeData(loc, pointRadii, 1, nsamples*2, GL_STREAM_DRAW);
        loc = billboardShader.getAttributeLocation("lineWidth");
        lines.getVbo().setAttributeData(loc, lineWidths, 1, nsamples*2, GL_STREAM_DRAW);
    billboardShader.end();

    frame = 0;
    swapFrame = 0;
    flameSequences.resize(5);
    for (int i = 0; i < flameSequences.size(); ++i) {
        flameSequences[i].frameCreated = 0;
        flameSequences[i].frameUpdated = -1;
        flameSequences[i].xform_distribution = NULL;
    }
}

void ofApp::guiUpdate() {
    // Copy data to gui
    gui->frameRate = ofGetFrameRate();
    gui->visuals = &visualsFbo.getTexture();
    gui->genomeIdx = genomeIdx;
    gui->mpx = mpx;
    gui->mpy = mpy;
    gui->audioCentroid = audioCentroid;
    gui->audioRMS = audioRMS;

    // Copy data from gui
    wandering = gui->wandering;
    dotSizeUsesAudio = gui->dotSizeUsesAudio;
    fftDecayRate = gui->fftDecayRate;
    rmsMultiple = gui->rmsMultiple;
    centroidMaxBucket = gui->centroidMaxBucket;
    mpxSmoothingFactor = gui->mpxSmoothingFactor;
    mpySmoothingFactor = gui->mpySmoothingFactor;
    baseSpeed = gui->baseSpeed;
    rmsSpeedMult = gui->rmsSpeedMult;
    frameClearSpeed = gui->clearSpeed;
    particleAlpha = gui->particleAlpha;
    basePointRadius = gui->basePointRadius;
    maxLineLength = gui->maxLineLength;

    if (audioMode != gui->audioMode) {
        audioMode = gui->audioMode;
        if (audioMode != AUDIO_MODE_MP3)
            mySound.stop();
    }

    if (soundStreamDevice != gui->soundStreamDevice) {
        soundStreamDevice = gui->soundStreamDevice;
        soundStream.close();
        soundStream.setDeviceID(soundStreamDevice);
        bool streamStarted = soundStream.setup(this, 0, nChannels, 44100, 512, 4);
        if (streamStarted) {
            cout << "Started audio stream with device " << soundStreamDevice << endl;
        } else {
            cout << "Could not start audio stream with device " << soundStreamDevice << endl;
        }
    }

    if (gui->nFlameSequences != flameSequences.size()) {
        swapFrame = frame;
        const int oldSize = flameSequences.size();

        flameSequences.resize(gui->nFlameSequences);
        for (int i = oldSize-1; i < flameSequences.size(); ++i) {
            flameSequences[i].frameCreated = frame;
            flameSequences[i].frameUpdated = -1;
            flameSequences[i].xform_distribution = NULL;
        }

        cout << "Now using " << flameSequences.size() << " flame sequences." << endl;
    }
}

void ofApp::flameUpdate() {
    initrc(seed);

    if (wandering) {
        double ispeed = 800.0;
        if (counter > (ncps * ispeed))
            counter = 0;
        for (int i = 0; i < ncps; i++) {
            cps[i].time = (double) i;
        }

        int currCP = floor(counter/ispeed);
        if (lastCP != currCP) {
            swapFrame = frame;

            lastCP = currCP;
            genomeIdx = currCP;
        }

        flam3_interpolate(cps, ncps, counter/ispeed, 0, &cp);
    } else {
        float speed = baseSpeed + smoothedAudioRMS * rmsSpeedMult;
        flam3_rotate(&cp, speed, flam3_inttype_log);
    }

    if (prepare_precalc_flags2(&cp)) {
        fprintf(stderr,"prepare xform pointers returned error: aborting.\n");
        return;
    }

    const int flameSeqIdxToUpdate = (frame-swapFrame) % flameSequences.size();
    flameSeq &seqToUpdate = flameSequences[flameSeqIdxToUpdate];
    if (seqToUpdate.xform_distribution) {
        free(seqToUpdate.xform_distribution);
    }
    seqToUpdate.frameUpdated = frame;
    seqToUpdate.xform_distribution = flam3_create_xform_distrib(&cp);

    std::swap(prevFlameSamples, currFlameSamples);
    setFlameParameters();

    const int nFlameSeqs = MIN(flameSequences.size(), (frame-swapFrame)+1);
    const int nSamplesPerSeq = nsamples / nFlameSeqs;
    for (int i = nFlameSeqs-1; i >= 0 ; --i) {
        double *flameSamples = currFlameSamples + nSamplesPerSeq * 4 * i;

        flameSamples[0] = flam3_random_isaac_11(&rc);
        flameSamples[1] = flam3_random_isaac_11(&rc);
        flameSamples[2] = flam3_random_isaac_01(&rc);
        flameSamples[3] = flam3_random_isaac_01(&rc);

        flam3_iterate(&cp,
                      nSamplesPerSeq,
                      20,
                      flameSamples,
                      flameSequences[i].xform_distribution,
                      &rc);
    }

    totDotPixels = 0;
    totLinePixels = 0;
    for (int i = 0; i < nsamples-1; i++) {
        // Radius depends on mpy
        float radius = basePointRadius * mpy;
        if (dotSizeUsesAudio) {
            int bucket = ofMap(i, 0, nsamples-1, 0, nFftBuckets/5);
            radius *= 10 * fftOutput[bucket];
        }
        // TODO: remove?
        radius = ofClamp(radius, 0, 300);

        int palleteIdx = (int)(currFlameSamples[4*i+2] * CMAP_SIZE);
        palleteIdx = ofClamp(palleteIdx, 0, CMAP_SIZE-1);
        double *cv = cp.palette[palleteIdx].color;
        ofColor color(255*cv[0],255*cv[1],255*cv[2], particleAlpha);

        pointPairs[i].pt1.x = currFlameSamples[4*i];
        pointPairs[i].pt1.y = currFlameSamples[4*i+1];
        pointPairs[i].pt2.x = prevFlameSamples[4*i];
        pointPairs[i].pt2.y = prevFlameSamples[4*i+1];

        pointPairs[i].color = color;
        pointPairs[i].ptSize = radius;
        pointPairs[i].lineWidth = ofClamp(radius/4, 0, 6);

        totDotPixels += (radius * 2) * (radius * 2);
//        totLinePixels +=  pointPairs[i].lineWidth;
    }

    ++frame;
//    parity = !parity;
}

//--------------------------------------------------------------
void ofApp::update(){
    counter += baseSpeed;
    
    // Handle our keypresses
    while (!keyPresses.empty()) {
        handleKey(keyPresses.front());
        keyPresses.pop();
    }
    
    // Handle GUI keypresses
    while (!gui->keyPresses.empty()) {
        handleKey(gui->keyPresses.front());
        gui->keyPresses.pop();
    }

    // Copy audio if needed
    if (audioMode == AUDIO_MODE_MP3) {
        float *ss = ofSoundGetSpectrum(nFftBuckets);
        memcpy(fftOutput, ss, sizeof(float) * nFftBuckets);
    } else if (audioMode == AUDIO_MODE_MIC || audioMode == AUDIO_MODE_NOISE) {
        // No action needed
    } else {
        memset(fftOutput, 0, sizeof(float) * nFftBuckets);
    }

    // Compute audio centroid
    float centroidN = 0, centroidD = 0;
    for (int i = 0; i < nFftBuckets; ++i) {
        centroidN += fftOutput[i] * i;
        centroidD += fftOutput[i];
    }
    float centroidBucket = centroidN / centroidD;
    audioCentroid = fmin(centroidBucket / nFftBuckets, 1);

    // Compute audio centroid mapping to useful space
    float centroidMapped = sqrt(ofMap(audioCentroid, 0, centroidMaxBucket, 0, 1, true)); // TODO: should we use sqrt here?

    // Compute audio RMS mapping to useful space
    float audioRMSMapped = ofClamp(audioRMS * rmsMultiple, 0.0, 1.0);

    // Note: this is very dependent on the tempo of the music.
    mpx += (centroidMapped - mpx) * mpxSmoothingFactor;
    mpy += (audioRMSMapped - mpy) * mpySmoothingFactor;

    guiUpdate();
    flameUpdate();
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    if (audioMode == AUDIO_MODE_MIC) {
        memcpy(audioInput, input, sizeof(float) * bufferSize);
    } else if (audioMode == AUDIO_MODE_NOISE) {
        for (int i = 0; i < bufferSize; i++)
            audioInput[i] = ofRandom(-1, 1);
    } else if (audioMode == AUDIO_MODE_NONE) {
        // TODO: don't overwrite constantly
        for (int i = 0; i < bufferSize; i++)
            audioInput[i] = 0;
    }

    // Only process data if we're listening
    if (audioMode == AUDIO_MODE_MIC || audioMode == AUDIO_MODE_NOISE) {
        fft->setSignal(audioInput);
        float *fftAmplitude = fft->getAmplitude();

        for (int i = 0; i < fft->getBinSize(); ++i) {
            // TODO: in theory this should be 20, but 16 seems to work better.
            float val = ofClamp(16.0 * log10(fftAmplitude[i] + 1), 0.0, 1.0);
            if (val > fftOutput[i] || fftDecayRate <= 0.01) {
                fftOutput[i] = val;
            } else {
                fftOutput[i] *= fftDecayRate;
            }
        }
        
        float newAudioRMS = 0.0;
        for (int i = 0; i < bufferSize; i++){
            float sample = input[i] * 0.5;
            newAudioRMS += sample * sample;
        }
        newAudioRMS /= bufferSize;
        newAudioRMS = sqrt(newAudioRMS);

        audioRMS = newAudioRMS;
        smoothedAudioRMS += (audioRMS - smoothedAudioRMS) * 0.3;
    }
}

void ofApp::setFlameParameters() {
    switch (genomeIdx) {
        case 0:
            cp.xform[4].var[5] = mpx;
            cp.xform[3].var[8] = mpy;
            
        case 1:
            cp.xform[5].var[1] = mpx;
            cp.xform[12].c[2][0] = mpy;
            break;
            
        case 2:
            cp.xform[8].var[1] = mpx;
            cp.xform[8].julian_power = mpy + 0.5;
            break;
        case 3:
            cp.xform[0].c[0][0] = -mpx+0.5;
            cp.xform[0].c[1][1] = -mpy+0.5;
            break;
        case 4:
            cp.xform[2].color = 0.2;
            cp.xform[2].c[2][0] = mpy;
            cp.xform[3].var[1] = -mpx;
            cp.xform[2].c[1][0] = 1/(mpx+0.1);
            break;
        case 5:
            cp.xform[0].var[VAR_DISC] = mpx;
            cp.xform[1].c[2][0] = 2*(mpx-0.5);
            cp.xform[1].c[2][1] = 2*(mpy-0.5);
            break;
        case 6:
            cp.xform[0].rectangles_x = mpx;
            cp.xform[0].rectangles_y = mpy;
            cp.xform[0].c[0][0] = mpx + 0.5;
            cp.xform[0].c[1][1] = mpy - 1.5;
            cp.xform[10].c[0][0] = mpx/2 - 1.0;
            cp.xform[10].c[1][1] = mpy/2 - 1.0;
            break;
        case 7:
            cp.xform[3].c[2][0] = mpx;
            cp.xform[3].c[2][1] = mpy;
            cp.xform[3].c[0][0] = mpx - 1.5;
            cp.xform[3].c[1][1] = mpy;
            cp.xform[3].var[0] = mpx;
            cp.xform[3].var[1] = mpy;
            break;
        case 8:
            cp.xform[0].c[2][0] = mpx - 0.5;
            cp.xform[0].c[2][1] = mpy - 0.5;
            cp.xform[1].c[0][0] = mpx - 0.5;
            cp.xform[1].c[1][1] = mpy - 0.5;
            cp.xform[2].c[2][0] = mpx - 0.5;
            cp.xform[2].c[2][1] = mpy - 0.5;
            cp.xform[4].julian_dist = 1 - mpx;
            cp.xform[5].julian_dist = 1 - mpy;
            break;
        case 9:
            cp.xform[0].var[VAR_WAVES] = mpx*2 + 0.2;
            cp.xform[1].var[VAR_DISC] = mpy*2 + 0.1;
            break;
        case 10:
            cp.xform[1].juliascope_power = 1/(mpx + 0.1);
            cp.xform[1].julian_power = 1/(mpy + 0.1);
            break;
        case 11:
            cp.xform[0].rectangles_x = mpx;
            cp.xform[0].rectangles_y = mpy;
            cp.xform[1].var[VAR_SPHERICAL] = 0.02 + mpx / 10;
            cp.xform[2].var[VAR_SPHERICAL] = 0.02 + mpy / 10;
            cp.xform[4].c[0][0] = 1.5 + mpx;
            break;
        case 12:
            cp.xform[0].c[0][0] = 1.5 + mpx;
            cp.xform[1].var[VAR_DISC] = 0.5 + mpy/3.0;
            break;
        case 13:
            cp.xform[0].c[0][0] = 0.4 + mpy;
            cp.xform[0].var[VAR_GAUSSIAN_BLUR] = 0.1 + mpx/2;
            cp.xform[1].rectangles_x = mpx;
            cp.xform[1].rectangles_y = mpy;
            cp.xform[4].curl_c2 = mpx;
            break;
        case 14:
            cp.xform[0].julian_power = 8.5 + mpx;
            cp.xform[1].c[1][1] = mpy;
            break;
        case 15:
            cp.xform[0].c[0][0] = -0.6 + mpx;
            cp.xform[0].c[1][1] = -0.5 + mpy;
            cp.xform[1].var[VAR_SINUSOIDAL] = 0.05 + mpx / 4;
            cp.xform[1].c[2][0] = - mpx;
            cp.xform[1].c[2][1] = mpy;
            cp.xform[2].julian_power = 2 * mpx + 0.5;
            cp.xform[2].julian_dist = mpy + 0.5;
            break;
        case 16:
            int b = 0;
            float lz = 0;
            for (int i = 0; i < cp.num_xforms; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 2; k++) {
                        float nz = fftOutput[(5*b++)%nFftBuckets];
                        cp.xform[i].c[j][k] = 5 * (nz - lz);
                        lz = nz;
                    }
                }
                cp.xform[i].c[2][0] += mpx;
                cp.xform[i].c[2][1] += mpy;
            }
            break;
    }

}

bool pairCompareDesc(const pointPair& firstElem, pointPair& secondElem) {
    return firstElem.ptSize > secondElem.ptSize;
}

//--------------------------------------------------------------
void ofApp::draw(){
    visualsFbo.begin();
    ofSetColor(0, frameClearSpeed);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(255, 255);
    ofEnableAlphaBlending();
    ofFill();

    const float maxDotPixels = gui->maxPixels; // 20 million
//    const float maxLinePixels = gui->maxPixels / 2.0; // 10 million
    const int nToAllowRandom = gui->pctToAllowRandom * 1000;

    // Sort big->small
    std::sort(pointPairs.begin(), pointPairs.end(), pairCompareDesc);

    // Copy data into VBOs
    int tippingPt = -1;
    double drawnSoFar = 0;
    for (int i = pointPairs.size()-1; i >= 0; --i) {
        if (drawnSoFar < maxDotPixels || (pointPairs[i].idx % 1000) < nToAllowRandom) {
            const float sizesq = (pointPairs[i].ptSize * 2) * (pointPairs[i].ptSize * 2);
            drawnSoFar += sizesq;

            lines.setVertex(2*i, pointPairs[i].pt1);
            lines.setVertex(2*i+1, pointPairs[i].pt2);
            lines.setColor(2*i, pointPairs[i].color);
            lines.setColor(2*i+1, pointPairs[i].color);
            lineWidths[2*i] = lineWidths[2*i+1] = pointPairs[i].lineWidth;
            pointRadii[2*i] = pointRadii[2*i+1] = pointPairs[i].ptSize;
        } else {
            if (tippingPt < 0) tippingPt = i;
            pointRadii[2*i] = pointRadii[2*i+1] = pointPairs[i].ptSize = 0;
            lineWidths[2*i] = lineWidths[2*i+1] = 0;
        }
    }
    gui->pctParticles = tippingPt > 0 ? (1.0 - (float)tippingPt / nsamples) : 1;

    if (gui->drawMode == 0) {
        int loc;
        billboardShader.begin();
            const int screenScale = ofGetWidth() / 1024.0 * gui->overallScale;

            billboardShader.setUniform2f("screen", ofGetWidth(), ofGetHeight());
            billboardShader.setUniform2f("cpCenter", cp.center[0], cp.center[1]);
            billboardShader.setUniform1f("screenScale", screenScale);
            billboardShader.setUniform1f("cpPixelsPerUnit", cp.pixels_per_unit);
            billboardShader.setUniform1f("maxLineLength", maxLineLength);

            loc = billboardShader.getAttributeLocation("pointRadius");
            lines.getVbo().updateAttributeData(loc, pointRadii, nsamples*2);
            loc = billboardShader.getAttributeLocation("lineWidth");
            lines.getVbo().updateAttributeData(loc, lineWidths, nsamples*2);

            lines.draw();
        billboardShader.end();
    } else if (gui->drawMode == 1) {
        // For old time's sake, here's the oF naive code

        for (int i = pointPairs.size()-1; i >= 0; --i) {
            if (pointPairs[i].ptSize > 0.01) {
                ofSetColor(pointPairs[i].color);
                if (pointPairs[i].lineWidth > 0.01) {
                    ofSetLineWidth(pointPairs[i].lineWidth);
                    ofDrawLine(pointPairs[i].pt1, pointPairs[i].pt2);
                }
                ofDrawCircle(pointPairs[i].pt1, pointPairs[i].ptSize);
                ofDrawCircle(pointPairs[i].pt2, pointPairs[i].ptSize);
            }
        }
    }

    // Force finish rendering - just for better profiling
    glFinish();

    ofClearAlpha();
    visualsFbo.end();

    ofSetColor(255);
    visualsFbo.draw(0, 0);

    // TODO: disable later
    char str[25];
    sprintf(str, "%.2f fps", ofGetFrameRate());
    ofDrawBitmapString(str, 10, 15);
}

void ofApp::handleKey(int key) {
    if (key == ' ') {
        swapFrame = frame;
        gui->wandering.set(!gui->wandering.get());
    } else if (key == OF_KEY_LEFT) {
        swapFrame = frame;
        if (--genomeIdx < 0) genomeIdx = ncps-1;
        flam3_copy(&cp, &cps[genomeIdx]);
    } else if (key == OF_KEY_RIGHT) {
        swapFrame = frame;
        if (++genomeIdx >= ncps) genomeIdx = 0;
        flam3_copy(&cp, &cps[genomeIdx]);
    } else if (key == 'd') {
        gui->dotSizeUsesAudio.set(!gui->dotSizeUsesAudio.get());
    } else if (key == 'a') {
        momode++;
    } else if (key == 's') {
        gui->audioMode.set(gui->audioMode.get() + 1);
        if (audioMode >= N_AUDIO_MODES)
            audioMode = 0;
        if (audioMode != AUDIO_MODE_MP3)
            mySound.stop();
    } else if (key == 'f') {
        ofToggleFullscreen();
        ofHideCursor();
        fullscreen = !fullscreen;
    } else if (key == OF_KEY_UP) {
        mutateCurrent();
    } else if (key == OF_KEY_DOWN) {
        killCurrent();
    } else if (key == ',') {
        gui->baseSpeed *= 0.80;
    } else if (key == '.') {
        gui->baseSpeed *= 1.2;
    } else if (key == '0') {
        mySound.setPosition(mySound.getPosition()-0.02);
        ofSoundStreamSetup(0, 1, this);
        mySound.stop();
    } else if (key == '1') {
        gui->audioMode.set(AUDIO_MODE_MP3);
        mySound.loadSound("audio/no_ordinary_window-youtube.mp3", true);
        mySound.play();
    } else if (key == '2') {
        gui->audioMode.set(AUDIO_MODE_MP3);
        mySound.loadSound("audio/01 - Steve McQueen.mp3", true);
        mySound.play();
    } else if (key == '3') {
        gui->audioMode.set(AUDIO_MODE_MP3);
        mySound.loadSound("audio/db120c10-01-Sonata No 1 in G Minor BWV 1001 Adagio.mp3", true);
        mySound.play();
    } else if (key == '4') {
        gui->audioMode.set(AUDIO_MODE_MP3);
        mySound.loadSound("audio/skrillex_bangarang.mp3", true);
        mySound.play();
    } else if (key == '9') {
        mySound.setPosition(mySound.getPosition()-0.02);
    } else if (key == '8') {
        mySound.setPosition(mySound.getPosition()+0.02);
    } else {
        // Give the GUI a chance to handle the key if we don't know what it is
        gui->handleKey(key);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keyPresses.push(key);
}

int ofApp::randomi(int n) {
    int i = flam3_random_isaac_01(&rc) * ncps;
    return i % n;
}

void ofApp::killCurrent() {
    flam3_genome result;
    initrc(time(NULL));
    if (randomi(2)) {
        int parent0 = randomi(ncps);
        int parent1 = randomi(ncps);
        flam3_cross(&cps[parent0], &cps[parent1], &result, CROSS_NOT_SPECIFIED, &rc, NULL);
    } else {
        int parent0 = randomi(ncps);
        int parent1 = randomi(ngenebank);
        flam3_cross(&cps[parent0], &genebank[parent1], &result, CROSS_NOT_SPECIFIED, &rc, NULL);
    }
    flam3_copy(&cp, &result);
    flam3_copy(&cps[genomeIdx], &result);
}

void ofApp::mateCurrent() {
    flam3_genome result;
    initrc(time(NULL));
    int parent1 = random()%ncps;
    flam3_cross(&cps[genomeIdx], &cps[parent1], &result, CROSS_NOT_SPECIFIED, &rc, NULL);
    flam3_copy(&cp, &result);
    flam3_copy(&cps[genomeIdx], &result);
}

void ofApp::mutateCurrent() {
    flam3_genome result;
    initrc(time(NULL));
    int ivars[flam3_nvariations];
    for (int i = 0; i < flam3_nvariations; i++)
        ivars[i] = i;
    
    flam3_mutate(&cps[genomeIdx], MUTATE_NOT_SPECIFIED, ivars, flam3_nvariations, 0, 0.2, &rc, NULL);
    flam3_copy(&cp, &cps[genomeIdx]);
}

void ofApp::initrc(long sed) {
    /* Set up the isaac rng */
    for (int lp = 0; lp < RANDSIZ; lp++)
        rc.randrsl[lp] = sed;
    irandinit(&rc,1);
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mmpx = x / 2500.0;
    mmpy = y / 1600.0;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    visualsFbo.allocate(w, h, GL_RGBA);
}
