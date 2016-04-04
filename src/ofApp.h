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

    // Interpolation
    int genomeIdx;
    float counter;
    bool wandering;

    // Fixed randomness for flam3
    int seed;
    randctx rc;

    // Geneback for mutation
    int ngenebank;
    flam3_genome *genebank;

    // Base control points
    int ncps;
    flam3_genome *cps;

    // Copied into cpOrder
    int nCPsInTrack;
    flam3_genome *cpTrackOrder;
    vector<int> cpIdxTrackOrder;

    // After interpolation and to render
    flam3_genome cp, renderCp;
    int nsamples;
    double *prevFlameSamples, *currFlameSamples;

    // Interpolate between flam3 cps smoothly
    int frame, swapFrame, lastCP;
    vector<flameSeq> flameSequences;

    // Dot shader
    ofShader billboardShader;

    // To draw
    ofVboMesh lines;
    vector<pointPair> pointPairs;
    float *pointRadii, *lineWidths;
    double totDotPixels, totLinePixels;

    // Display Paremters
    int fullscreen;
    float mpx, mpy, mpxSmoothingFactor, mpySmoothingFactor;
    float audioEffectSize1, audioEffectSize2, audioEffectSize3, audioEffectSize4;
    float mmpx, mmpy;
    float baseSpeed, rmsSpeedMult;
    float wanderSpeed;
    bool pointRadiusUsesAudio;
    float frameClearSpeed;
    float particleAlpha, basePointRadius, pointRadiusAudioScale;
    float maxLineLength;

    // Audio mode
    int audioMode;
    ofSoundPlayer mySound;
    int soundStreamDevice, nChannels;
    ofSoundStream soundStream;  // for input

    // Audio analysis
    int nFftBuckets;
    float *audioInput;
    float *fftOutput;
    float audioRMS, smoothedAudioRMS, rmsMultiple;
    float audioCentroid, centroidMaxBucket;
    ofxFft *fft;
    float fftDecayRate;

    // The GUI window
    shared_ptr<GuiApp> gui;
    ofFbo visualsFbo;
    shared_ptr<ofTexture> visuals;
    ofxSyphonServer syphonServer;

    queue<int> keyPresses;
};

