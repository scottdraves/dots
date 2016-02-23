#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "appConstants.h"

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void handleKey(int key);
    
    ofParameterGroup audioAnalysisParameters;
    ofParameter<float> fftDecayRate;
    ofParameter<float> centroidMaxBucket;
    ofParameter<float> rmsMultiple;
    ofParameter<float> mpxSmoothingFactor, mpySmoothingFactor;
    
    ofParameterGroup audioInputParameters;
    ofParameter<int> audioMode;
    vector<ofSoundDevice> soundDevices;
    int nSoundDevices;
    ofParameter<int> soundStreamDevice;
    
    ofParameterGroup displayParameters;
    ofParameter<bool> wandering;
    ofParameter<float> baseSpeed, rmsSpeedMult;
    
    ofxPanel analysisGui, inputGui, displayGui;
    
    // To mirror from ofApp
    float frameRate;
    ofTexture* visuals;
    float *audioBuckets;
    int nAudioBuckets;
    float mpx, mpy;
    float audioCentroid, audioRMS;
    
    queue<int> keyPresses;
};
