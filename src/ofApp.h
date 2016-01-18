#pragma once

#include "ofMain.h"
#include "ofxFft.h"

extern "C" {
#include "flam3.h"
}

#define AUDIO_MODE_NONE     0
#define AUDIO_MODE_MIC      1
#define AUDIO_MODE_MP3      2
#define AUDIO_MODE_NOISE    3
#define N_AUDIO_MODES       4

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
    ofSoundStream soundStream;  // for input
    float* audioInput;
    float* fftOutput;
    ofxFft* fft;
    
    randctx rc;
    
    
};
