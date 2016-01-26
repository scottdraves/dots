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
    
    ofParameterGroup parameters;
    ofParameter<bool> wandering;
    ofParameter<float> fftDecayRate;
    
    ofParameter<int> audioMode;
    vector<ofSoundDevice> soundDevices;
    int nSoundDevices;
    ofParameter<int> soundStreamDevice;
    
    ofxPanel gui;
    
    // To mirror from ofApp
    float frameRate;
    ofTexture* visuals;
    float *audioBuckets;
    int nAudioBuckets;
};
