#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "appConstants.h"

typedef struct dotsParams {
    ofParameterGroup displayParameters;

    ofParameterGroup audioAnalysisParameters;
    ofParameter<float> fftDecayRate;
    ofParameter<float> centroidMaxBucket;
    ofParameter<float> rmsMultiple;
    ofParameter<float> mpxSmoothingFactor, mpySmoothingFactor;

    ofParameterGroup metaParams;
    ofParameter<bool> wandering;

    ofParameterGroup drawingParams;
    ofParameter<float> clearSpeed;
    ofParameter<float> particleAlpha;
    ofParameter<float> overallScale;

    ofParameterGroup speedParams;
    ofParameter<float> baseSpeed, rmsSpeedMult;

    ofParameterGroup dotParams;
    ofParameter<bool> pointRadiusUsesAudio;
    ofParameter<float> basePointRadius, pointRadiusAudioScale;

    ofParameterGroup lineParams;
    ofParameter<float> maxLineLength;

    ofParameterGroup audioEffectParams;
    ofParameter<float> audioEffectSize1, audioEffectSize2, audioEffectSize3, audioEffectSize4;
} dotsParams;

class ReplaceablePanel : public ofxPanel {
public:
    ReplaceablePanel();
    ~ReplaceablePanel();

    ReplaceablePanel * setup(const ofParameterGroup & parameters);
};

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void handleKey(int key);
    void buttonPressed(const void * sender);

    void copyGenomeParams(int idx);
    void saveClicked();
    void loadClicked();

    void setGenomeIdx(int idx);
    void loadAllParamsFromFile();
    void setupControls(int numCPs);
    void serializeCurrentParamsToFile();
    ofxXmlSettings settings;

    // Patameters that don't need to be serialized/unserialized
    ofParameterGroup audioInputParameters;
    ofParameter<int> audioMode;
    vector<ofSoundDevice> soundDevices;
    int nSoundDevices;
    ofParameter<int> soundStreamDevice;

    ofParameterGroup debugParameters;
    ofParameter<int> maxPixels, drawMode, nFlameSequences;
    ofParameter<float> pctToAllowRandom;
    ofParameter<bool> useSavedParams;

    dotsParams currParams;
    dotsParams defaultParams;
    map<int, dotsParams *> paramsMap;

    ofxPanel analysisGui, inputGui, debugGui, displayGui;
    
    // To mirror from ofApp
    int genomeIdx; // only set using setGenomeIdx()
    float frameRate, pctParticles;
    ofTexture* visuals;
    float *audioBuckets;
    int nAudioBuckets;
    float mpx, mpy;
    float audioCentroid, audioRMS;
    
    queue<int> keyPresses;

private:
    void setupDefaultParams(dotsParams &params);
};
