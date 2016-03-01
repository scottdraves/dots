#include "ofApp.h"

#include "variations.h" // for prepare_precalc_flags and CMAP_SIZE

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(false);
//    ofSetFrameRate(60);

    counter = 0;
    nsamples = 25000;	seed = 0;
    genomeIdx = 0;
    gj = 0;
    transp = 60;
    ofSetWindowTitle("D0TS");
    samples= (double *) malloc(sizeof(double)*nsamples*8);
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
    wandering = 0;
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


    ofSetLogLevel(OF_LOG_VERBOSE);

    // We're going to use a shader to draw point sizes,
    // thanks openGL for making this a mess
    glEnable(GL_POINT_SIZE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glEnable(GL_PROGRAM_POINT_SIZE_ARB);
    glEnable(GL_PROGRAM_POINT_SIZE);

    simplePointShader.load("simplePointShader");
    simplePointShader.bindDefaults();

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

    pointRadii = (float *)malloc(sizeof(float) * nsamples * 2);
    lineWidths = (float *)malloc(sizeof(float) * nsamples * 2);
    shouldDrawLine = (bool *)malloc(sizeof(float) * nsamples);

    lines.setMode(OF_PRIMITIVE_LINES);
    lines.setUsage(GL_STREAM_DRAW);
    points.setMode(OF_PRIMITIVE_POINTS);
    points.setUsage(GL_STREAM_DRAW);

    for (int i = 0; i < nsamples; ++i) {
        points.addVertex(ofVec3f());
        points.addColor(ofFloatColor());
        points.addVertex(ofVec3f());
        points.addColor(ofFloatColor());

        lines.addVertex(ofVec3f());
        lines.addColor(ofFloatColor());
        lines.addVertex(ofVec3f());
        lines.addColor(ofFloatColor());

        pointRadii[2*i] = 0;
        pointRadii[2*i+1] = 0;
        lineWidths[2*i] = 0;
        lineWidths[2*i+1] = 0;

        shouldDrawLine[i] = true;
    }

    int loc;
    billboardShader.printActiveAttributes();
    billboardShader.begin();
        loc = billboardShader.getAttributeLocation("pointRadius");
        lines.getVbo().setAttributeData(loc, pointRadii, 1, nsamples*2, GL_STREAM_DRAW);
        loc = billboardShader.getAttributeLocation("lineWidth");
        lines.getVbo().setAttributeData(loc, lineWidths, 1, nsamples*2, GL_STREAM_DRAW);
    billboardShader.end();

    simplePointShader.printActiveAttributes();
    simplePointShader.begin();
        loc = simplePointShader.getAttributeLocation("pointRadius");
        points.getVbo().setAttributeData(loc, pointRadii, 1, nsamples*2, GL_STREAM_DRAW);
    simplePointShader.end();
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
    
    // Copy data to gui
    gui->frameRate = ofGetFrameRate();
    gui->visuals = &visualsFbo.getTexture();
    gui->mpx = mpx;
    gui->mpy = mpy;
    gui->audioCentroid = audioCentroid;
    gui->audioRMS = audioRMS;
    
    // Copy data from gui
    wandering = gui->wandering;
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

//--------------------------------------------------------------
void ofApp::draw(){
    visualsFbo.begin();
    ofSetColor(0, frameClearSpeed);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(255, 255);
    ofEnableAlphaBlending();
    
    float startTime = ofGetElapsedTimef();
    float *sp = fftOutput;

    if (audioMode == AUDIO_MODE_MP3) {
        float *ss = ofSoundGetSpectrum(nFftBuckets);
        memcpy(fftOutput, ss, sizeof(float) * nFftBuckets);
    } else if (audioMode == AUDIO_MODE_MIC || audioMode == AUDIO_MODE_NOISE) {
        // No action needed
    } else {
        memset(fftOutput, 0, sizeof(float) * nFftBuckets);
    }

    double t0, t1, t2;
    
    initrc(seed);
    
    if (wandering) {
        double ispeed = 800.0;
        if (counter > (ncps * ispeed))
            counter = 0;
        for (int i = 0; i < ncps; i++) {
            cps[i].time = (double) i;
        }
        cout << counter << endl;
        flam3_interpolate(cps, ncps, counter/ispeed, 0, &cp);
    } else {
        float speed = baseSpeed + smoothedAudioRMS * rmsSpeedMult;
        flam3_rotate(&cp, speed, flam3_inttype_log);
    }
    
    if (prepare_precalc_flags2(&cp)) {
        fprintf(stderr,"prepare xform pointers returned error: aborting.\n");
        return;
    }
    
    unsigned short *xform_distrib;
    xform_distrib = flam3_create_xform_distrib(&cp);
    
    double *s = samples + (parity?(4*nsamples):0);
    
    s[0] = flam3_random_isaac_11(&rc);
    s[1] = flam3_random_isaac_11(&rc);
    s[2] = flam3_random_isaac_01(&rc);
    s[3] = flam3_random_isaac_01(&rc);
    
    setFlameParameters();
    flam3_iterate(&cp, nsamples, 20, s, xform_distrib, &rc);
    
    double *s0, *s1;
    
    if (parity) {
        s0 = samples;
        s1 = samples + nsamples * 4;
    } else {
        s0 = samples + nsamples * 4;
        s1 = samples;
    }
    
    ofSetLineWidth(1);
    ofSetColor(255, 255);
    
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
    
    ofFill();
    int max_line_length = 100 + ofGetWidth()/3 * mpy;  // good parameter to vary, should be connected to screen size too.

    ofVec3f cpCenter(cp.center[0], cp.center[1], 0);
    ofVec3f screenCenter(ofGetWidth()/2.0, ofGetHeight()/2.0, 0);

    double totDotPixels = 0, totLinePixels = 0;
    for (int i = 0; i < nsamples-1; i++) {
        // Radius depends on mpy
        float radius = basePointRadius * mpy;
        if (gj % 2 == 1) {
            int bucket = ofMap(i, 0, nsamples-1, 0, nFftBuckets/5);
            radius *= 10 * sp[bucket];
        }
        // TODO: remove?
        radius = ofClamp(radius, 0, 300);

        int palleteIdx = (int)(s0[4*i+2] * CMAP_SIZE);
        palleteIdx = ofClamp(palleteIdx, 0, CMAP_SIZE-1);
        double *cv = cp.palette[palleteIdx].color;
        ofColor color(255*cv[0],255*cv[1],255*cv[2], particleAlpha);

        ofVec3f pt1(s0[4*i], s0[4*i+1], 0.0);
        ofVec3f pt2(s1[4*i], s1[4*i+1], 0.0);
        ofVec3f pt1Screen = (pt1 - cpCenter) * cp.pixels_per_unit + screenCenter;
        ofVec3f pt2Screen = (pt2 - cpCenter) * cp.pixels_per_unit + screenCenter;

        points.setVertex(2*i, pt1Screen);
        points.setVertex(2*i+1, pt2Screen);
        points.setColor(2*i, color);
        points.setColor(2*i+1, color);
        totDotPixels += radius * radius;

        pointRadii[2*i] = radius;
        pointRadii[2*i+1] = radius;

        lines.setVertex(2*i, pt1Screen);
        lines.setVertex(2*i+1, pt2Screen);
        lines.setColor(2*i, color);
        lines.setColor(2*i+1, color);

        float lineWidth = ofClamp(radius/4, 0, 2);
        lineWidths[2*i] = lineWidth;
        lineWidths[2*i+1] = lineWidth;

        float dist = pt1Screen.distance(pt2Screen);
        shouldDrawLine[i] = dist < max_line_length;
        totLinePixels += shouldDrawLine[i] ? dist * lineWidth : 0;
    }

    const float maxDotPixels = gui->maxPixels; // 20 million
    const float maxLinePixels = gui->maxPixels; // 10 million
    const int frameNum = ofGetFrameNum();
    const int random = ofRandomuf() * 100000;
    const float pctDotsToSave = ofClamp(totDotPixels, 0, maxDotPixels) / totDotPixels;
    const float pctLinesToSave = ofClamp(totLinePixels, 0, maxLinePixels) / totLinePixels;

    gui->pctParticles = pctDotsToSave;

    const vector<ofVec3f> &verts = lines.getVertices();
    const vector<ofFloatColor> &colors = lines.getColors();

    for (int i = 0; i < nsamples-1; i++) {
        // Discard a bunch of particles
        if (((i+frameNum) % 1000) > pctDotsToSave * 1000) {
            pointRadii[2*i] = 0;
            pointRadii[2*i+1] = 0;
            shouldDrawLine[i] = false;
        }

        if (shouldDrawLine[i] && ((i+frameNum) % 1000) > pctLinesToSave * 1000) {
            shouldDrawLine[i] = false;
        }

        if (!shouldDrawLine[i]) {
            lineWidths[2*i] = 0;
            lineWidths[2*i+1] = 0;
        }

        // For old time's sake, here's the oF naive code
        if (gui->drawMode == 2) {
            if (pointRadii[2*i] > 0.01) {
                ofSetColor(colors[2*i]);
                if (shouldDrawLine[2*i]) {
                    ofSetLineWidth(pointRadii[2*i]);
                    ofDrawLine(verts[2*i], verts[2*i+1]);
                }
                ofDrawCircle(verts[2*i], pointRadii[2*i]);
                ofDrawCircle(verts[2*i+1], pointRadii[2*i+1]);
            }
        }
    }


    // OLD: immediate-mode code
//    for (int i = 0; i < verts.size(); ++i) {
//        if (pointSizes[i] < 0.01) continue;
//        glColor4f(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
//
//        if (shouldDrawLine[i]) {
//            glLineWidth(ofClamp(pointSizes[i], 0, 2.0));
//            glBegin(GL_LINES);
//                glVertex3f(verts[i].x, verts[i].y, -0.1);
//                glVertex3f(prevVerts[i].x, prevVerts[i].y, -0.1);
////                glVertex2f(verts[i].x, verts[i].y);
////                glVertex2f(prevVerts[i].x, prevVerts[i].y);
//            glEnd();
//        }
//
//        glPointSize(pointSizes[i]);
//        glBegin(GL_POINTS);
//            glVertex3f(verts[i].x, verts[i].y, -0.1);
//            glVertex3f(prevVerts[i].x, prevVerts[i].y, -0.1);
//        glEnd();
//    }

    int loc;
    if (gui->drawMode == 0) {
        billboardShader.begin();
            billboardShader.setUniform2f("screen", ofGetWidth(), ofGetHeight());

            loc = billboardShader.getAttributeLocation("pointRadius");
            lines.getVbo().updateAttributeData(loc, pointRadii, nsamples*2);
            loc = billboardShader.getAttributeLocation("lineWidth");
            lines.getVbo().updateAttributeData(loc, lineWidths, nsamples*2);

            lines.draw();
        billboardShader.end();
    } else if (gui->drawMode == 1) {
        simplePointShader.begin();
            loc = simplePointShader.getAttributeLocation("pointRadius");
            points.getVbo().updateAttributeData(loc, pointRadii, nsamples*2);
            points.draw();
        simplePointShader.end();
        lines.draw();
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

    parity = !parity;
}

void ofApp::handleKey(int key) {
    if (key == ' ') {
        gui->wandering.set(!gui->wandering.get());
    } else if (key == OF_KEY_LEFT) {
        if (--genomeIdx < 0) genomeIdx = ncps-1;
        flam3_copy(&cp, &cps[genomeIdx]);
    } else if (key == OF_KEY_RIGHT) {
        if (++genomeIdx >= ncps) genomeIdx = 0;
        flam3_copy(&cp, &cps[genomeIdx]);
    } else if (key == 'd') {
        gj = (gj+1) % ncps;
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
