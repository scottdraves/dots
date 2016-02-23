#include "ofApp.h"

#include "variations.h" // for prepare_precalc_flags and CMAP_SIZE

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

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
}

//--------------------------------------------------------------
void ofApp::update(){
    counter = counter + smoothedAudioRMS;
    
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
    ofBackground(0, 255);
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
    
    int cohere = 1;
    double t0, t1, t2;
    
    initrc(seed);
    
    if (wandering) {
        double ispeed = 80.0;
        if (counter > (ncps * ispeed))
            counter = 0;
        for (int i = 0; i < ncps; i++) {
            cps[i].time = (double) i;
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

    if (1) {
        char s[25];
        sprintf(s, "gi=%d", genomeIdx);
        ofDrawBitmapString(s, 20, 100);
    }
    
    ofFill();
    double sum_w = 0.0;
    for (int i = 0; i < nsamples-1; i++) {
        int c = (int)(s0[4*i+2] * CMAP_SIZE);
        if (c < 0) c = 0;
        else if (c > (CMAP_SIZE-1)) c = CMAP_SIZE-1;
        
        double *cv = cp.palette[c].color;
        float w = 1.0 + c/32.0;
        w = (w - 1) * 3;
        
        //int zzz = flam3_random_isaac_01(&rc) < 0.0001;
        ///if (zzz) fprintf(stderr, "w=%f mpy=%f\n", w, mpy);
        int mpy_sp = mpy * nFftBuckets;
        if (mpy_sp < 0) mpy_sp = 0;
        if (mpy_sp >= nFftBuckets) mpy_sp = nFftBuckets-1;
        if (gj&1) {
            w *= 10 * (0.0 + sp[(int)(nFftBuckets/5*i/(float)nsamples)]) * (0.5 + mpy);
        } else {
            w *= 2 * mpy;
        }
        
        ///if (zzz) fprintf(stderr, "sp[]=%f w=%f mpy_sp=%d\n", sp[mpy_sp], w, mpy_sp);
        double new_transp = 60.0;
        if (0) {
            new_transp = 40.0;
            if (w < 3)
                new_transp = 255.0;
        } else if (0) {
            new_transp =  255.0 - 5*w;
        } else if (0) {
            new_transp =  255.0;
        }
        if (new_transp < 0.0)
            new_transp = 0.0;
        if (new_transp > 255.0)
            new_transp = 255.0;
        ofSetColor(255*cv[0],255*cv[1],255*cv[2], new_transp);
        
        int max_line_length = 20000 + 150000 * mpy;  // good parameter to vary, should be connected to screen size too.
        
        double a0 = s0[4*i] - cp.center[0];
        double a1 = s0[4*i+1] - cp.center[1];
        double a2 = s1[4*i] - cp.center[0];
        double a3 = s1[4*i+1] - cp.center[1];
        double mw = 100 * c;
        a0 *= cp.pixels_per_unit;
        a1 *= cp.pixels_per_unit;
        a2 *= cp.pixels_per_unit;
        a3 *= cp.pixels_per_unit;
        a0 += 720;
        a1 += 450;
        a2 += 720;
        a3 += 450;
        if (cohere) {
            // w = (w-1)*3;
            if (momode&1) {
                ofCircle(a0,a1,w);
                ofCircle(a2,a3,w);
            } else {
                float w2 = w/2;
                ofRect(a0-w2,a1-w2,w,w);
                ofRect(a2-w2,a3-w2,w,w);
            }
            if ((a0-a2)*(a0-a2) + (a1-a3)*(a1-a3) < max_line_length) {
                ofSetLineWidth(w);
                ofLine(a0, a1, a2, a3);
            }
            
        } else if (0) {
            w = (w-1)*10;
            ofCircle(a0,a1,w);
            ofCircle(a2,a3,w);
        } else {
            w = (w-1)*8;
            ofRect(a0-w/2,a1-w/2,w,w);
            ofRect(a2-w/2,a3-w/2,w,w);
        }
        
        if (!(i&63) && (ofGetElapsedTimef() - startTime) > 1/30.0)
            break;
    }
    parity = !parity;
    /*
     ofNoFill();
     ofSetLineWidth(1);
     // Curve from 2nd to 3rd point.
     ofCurve(10, 10,
     100, 10,
     100, 100,
     10, 100);
     */
        
    ofClearAlpha();
    visualsFbo.end();

    ofSetColor(255);
    visualsFbo.draw(0, 0);
}

void ofApp::handleKey(int key) {
    if (key == ' ') {
        gui->wandering.set(!gui->wandering.get());
    } else if (key == OF_KEY_LEFT) {
        if (--genomeIdx < 0) genomeIdx = ncps;
        flam3_copy(&cp, &cps[genomeIdx]);
    } else if (key == OF_KEY_RIGHT) {
        if (++genomeIdx >= ncps) genomeIdx = ncps;
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
