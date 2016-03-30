#pragma once

#include "ofMain.h"
#include "ofxFft.h"
#include "fmod.h"
#include "GuiApp.h"
#include "appConstants.h"
#include "ofxSyphon.h"

extern "C" {
#include "flam3.h"
}

typedef struct pointPair {
    int idx;
    ofVec3f pt1, pt2;
    float ptSize, lineWidth;
    ofFloatColor color;
} pointPair;

typedef struct flameSeq {
    long frameCreated, frameUpdated;
    unsigned short *xform_distribution;
} flameSeq;

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
    
    void killCurrent();
    void mateCurrent();
    void mutateCurrent();
    void initrc(long sed);
    int randomi(int n);

    void guiUpdate();
    void setFlameParameters();
    void flameUpdate();
    void handleKey(int key);
    
    float 	counter;
    float curVol = 0.0;
    bool wandering;
    int framecount;
    int fullscreen;
    float frameClearSpeed;
    int nsamples;

    double *prevFlameSamples, *currFlameSamples;

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
    flam3_genome cp, renderCp;

    int frame, swapFrame, lastCP;
    vector<flameSeq> flameSequences;

    int genomeIdx;

    float mpx, mpy, mpxSmoothingFactor, mpySmoothingFactor;
    float audioEffectSize1, audioEffectSize2, audioEffectSize3, audioEffectSize4;
    float mmpx, mmpy;
    float baseSpeed, rmsSpeedMult;

    ofShader billboardShader;

    ofVboMesh lines;
    vector<pointPair> pointPairs;
    float *pointRadii, *lineWidths;
    double totDotPixels, totLinePixels;

    bool pointRadiusUsesAudio;
    float particleAlpha, basePointRadius, pointRadiusAudioScale;
    float maxLineLength;

    float * left;
    float * right;
    
    int audioMode;
    ofSoundPlayer mySound;
    int soundStreamDevice, nChannels;
    ofSoundStream soundStream;  // for input

    int nFftBuckets;
    float* audioInput;
    float* fftOutput;
    float audioRMS, smoothedAudioRMS, rmsMultiple;
    float audioCentroid, centroidMaxBucket;
    ofxFft* fft;
    float fftDecayRate;
    
    randctx rc;

    ofEasyCam cam;

    // The GUI window
    shared_ptr<GuiApp> gui;
    ofFbo visualsFbo;
    shared_ptr<ofTexture> visuals;
    ofxSyphonServer syphonServer;

    queue<int> keyPresses;
};

