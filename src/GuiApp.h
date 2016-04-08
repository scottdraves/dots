#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "appConstants.h"
#include "MidiController.h"

typedef struct DotsScene {
    ofParameterGroup displayParameters;

    ofParameterGroup sceneParams;
    ofParameter<int> genomeIdx;
    // TODO: duration?

    ofParameterGroup audioAnalysisParameters;
    ofParameter<float> fftDecayRate;
    ofParameter<float> centroidMaxBucket;
    ofParameter<float> rmsMultiple;
    ofParameter<float> mpxSmoothingFactor, mpySmoothingFactor;

    ofParameterGroup drawingParams;
    ofParameter<float> clearSpeed;
    ofParameter<float> particleAlpha;
    ofParameter<float> overallScale;
    ofParameter<float> saturationPct;

    ofParameterGroup speedParams;
    ofParameter<float> baseSpeed, rmsSpeedMult;

    ofParameterGroup dotParams;
    ofParameter<float> pointRadiusAudioScaleAmt;
    ofParameter<float> basePointRadius, pointRadiusAudioScale;

    ofParameterGroup lineParams;
    ofParameter<float> maxLineLength;

    ofParameterGroup audioEffectParams;
    ofParameter<float> audioEffectSize1, audioEffectSize2, audioEffectSize3, audioEffectSize4;
} DotsScene;

typedef struct DotsTrack {
    int trackIdx;
    vector<DotsScene *> scenes;
} DotsTrack;

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
    void midiToSceneParams();

    vector<int> getTrackGenomeIndices();

    void advanceTrack();
    void regressTrack();
    void saveTrack();
    void createTrack();

    void regressScene();
    void advanceScene();
    void reloadScene();
    void deleteScene();
    void duplicateScene();
    void copyScene();

    void destTrackIdxChanged(int & trackIdx);
    void genomeModified(int & genome);

    void loadAllParamsFromFile();
    void setupControls(int numCPs);
    void serializeCurrentTrackToFile();

    void applyParameterInterpolation(float t);

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

    ofParameterGroup metaParams;
    ofParameter<bool> wandering;
    ofParameter<float> wanderSpeed;
    ofParameter<float> genomeInterpolationAmt;

    ofxPanel trackGui;
    ofxGuiGroup trackControls;
    ofxButton prevTrackBtn, nextTrackBtn;
    ofxButton newTrackBtn, saveTrackBtn;
    ofxGuiGroup sceneControls;
    ofxButton deleteSceneBtn, reloadSceneBtn, duplicateSceneBtn;
    ofxGuiGroup sceneCopyControls;
    ofParameter<int> destTrackIdx;
    ofParameter<int> destSceneIdx;
    ofxButton copyToTrackBtn;

    ofxPanel analysisGui, inputGui, debugGui, metaGui, displayGui;

    // Parameters
    DotsScene activeScene;
    DotsScene *currScene;
    DotsScene *nextScene;
    DotsScene defaultScene;

    DotsScene midiAdjust;

    // tracks and scenes
    int trackIdx, sceneIdx;
    bool trackDirty;
    vector<DotsTrack> tracks;

    // To mirror from ofApp
    float frameRate, pctParticles;
    ofTexture* visuals;
    float *audioBuckets;
    int nAudioBuckets;
    float mpx, mpy;
    float audioCentroid, audioRMS;
    int numCPs;
    
    queue<int> keyPresses;
    MidiController midi;

private:
    void setupDefaultParams(DotsScene &track);
};
