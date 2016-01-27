#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "fmod.h"
#include "GuiApp.h"
#include "appConstants.h"

extern "C" {
#include "flam3.h"
}

class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void audioIn(float * input, int bufferSize, int nChannels);
    
    void setFlameParameters();
    
    float curVol = 0.0;
    
    void killCurrent();
    void mateCurrent();
    void mutateCurrent();
    void initrc(long sed);
    int randomi(int n);
    
    void track(int trk, double v);
    
    
    float 	counter;
    int wandering;
    int framecount;
    int fullscreen;
    int nsamples;
    double *samples;
    int parity;
    int seed;
    int momode;
    FILE *out;
    int ncps;
    int ngenebank;
    int transp;
    flam3_genome *genebank;
    flam3_genome *cps;
    flam3_genome *cpv;
    flam3_genome cp;
    int gi, gj;
    float mpx, mpy;
    float mmpx, mmpy;
    float speed;
    
    
    float * left;
    float * right;
    
    int audioMode;
    ofSoundPlayer mySound;
    int soundStreamDevice, nChannels;
    ofSoundStream soundStream;  // for input

    int nFftBuckets;
    float* audioInput;
    float* fftOutput;
    float audioRMS, smoothedAudioRMS;
    ofxFft* fft;
    float fftDecayRate;
    
    randctx rc;
    
    // The GUI window
    shared_ptr<GuiApp> gui;
    ofFbo visualsFbo;
    shared_ptr<ofTexture> visuals;
};

