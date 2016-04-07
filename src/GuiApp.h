#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "appConstants.h"
#include "MidiController.h"

typedef struct dotsTrack {
    ofParameterGroup displayParameters;

    ofParameterGroup trackParams;
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

    ofParameterGroup speedParams;
    ofParameter<float> baseSpeed, rmsSpeedMult;

    ofParameterGroup dotParams;
    ofParameter<float> pointRadiusAudioScaleAmt;
    ofParameter<float> basePointRadius, pointRadiusAudioScale;

    ofParameterGroup lineParams;
    ofParameter<float> maxLineLength;

    ofParameterGroup audioEffectParams;
    ofParameter<float> audioEffectSize1, audioEffectSize2, audioEffectSize3, audioEffectSize4;
} dotsTrack;

typedef struct dotsAlbum {
    int albumIdx;
    vector<dotsTrack *> trackList;
} dotsAlbum;

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
    void midiToTrackParams();

    void saveClicked();
    void loadClicked();

    vector<int> getAlbumGenomeIndices();

    void advanceAlbum();
    void regressAlbum();
    void saveAlbum();
    void createAlbum();

    void regressTrack();
    void advanceTrack();
    void reloadTrack();
    void deleteTrack();
    void duplicateTrack();
    void copyTrack();

    void destAlbumIdxChanged(int & albumIdx);
    void genomeModified(int & genome);

    void loadAllParamsFromFile();
    void setupControls(int numCPs);
    void serializeCurrentAlbumToFile();

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

    ofxPanel albumGui;
    ofxGuiGroup albumControls;
    ofxButton prevAlbumBtn, nextAlbumBtn;
    ofxButton newAlbumBtn, saveAlbumBtn;
    ofxGuiGroup trackControls;
    ofxButton deleteTrackBtn, reloadTrackBtn, duplicateTrackBtn;
    ofxGuiGroup albumCopyControls;
    ofParameter<int> destAlbumIdx;
    ofParameter<int> destTrackIdx;
    ofxButton copyToAlbumBtn;

    ofxPanel analysisGui, inputGui, debugGui, metaGui, displayGui;

    // Parameters
    dotsTrack activeTrack;
    dotsTrack *currTrack;
    dotsTrack *nextTrack;
    dotsTrack defaultTrack;

    dotsTrack midiAdjust;

    // Albums and tracks
    int albumIdx, trackIdx;
    bool albumDirty;
    vector<dotsAlbum> albums;

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
    void setupDefaultParams(dotsTrack &track);
};
