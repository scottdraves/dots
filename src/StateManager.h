//
//  StateManager.hpp
//  dotsLocal
//
//  Created by Christopher Anderson on 4/9/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "appConstants.h"
#include "MidiController.h"

extern "C" {
#include "flam3.h"
}

static void copyParameters(const ofParameterGroup &from, const ofParameterGroup &to) {
    for(std::size_t i = 0; i < from.size(); i++){
        string type = from.getType(i);
        if(type == typeid(ofParameter <int32_t> ).name()){
            auto fromParam = from.getInt(i);
            auto toParam = to.getInt(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <uint32_t> ).name()){
            auto fromParam = from.get<uint32_t>(i);
            auto toParam = to.get<uint32_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <int64_t> ).name()){
            auto fromParam = from.get<int64_t>(i);
            auto toParam = to.get<int64_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <uint64_t> ).name()){
            auto fromParam = from.get<uint64_t>(i);
            auto toParam = to.get<uint64_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <int8_t> ).name()){
            auto fromParam = from.get<int8_t>(i);
            auto toParam = to.get<int8_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <uint8_t> ).name()){
            auto fromParam = from.get<uint8_t>(i);
            auto toParam = to.get<uint8_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <int16_t> ).name()){
            auto fromParam = from.get<int16_t>(i);
            auto toParam = to.get<int16_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <uint16_t> ).name()){
            auto fromParam = from.get<uint16_t>(i);
            auto toParam = to.get<uint16_t>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <float> ).name()){
            auto fromParam = from.getFloat(i);
            auto toParam = to.getFloat(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <double> ).name()){
            auto fromParam = from.get<double>(i);
            auto toParam = to.get<double>(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <bool> ).name()){
            auto fromParam = from.getBool(i);
            auto toParam = to.getBool(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <ofVec2f> ).name()){
            auto fromParam = from.getVec2f(i);
            auto toParam = to.getVec2f(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <ofVec3f> ).name()){
            auto fromParam = from.getVec3f(i);
            auto toParam = to.getVec3f(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <ofVec4f> ).name()){
            auto fromParam = from.getVec4f(i);
            auto toParam = to.getVec4f(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <ofColor> ).name()){
            auto fromParam = from.getColor(i);
            auto toParam = to.getColor(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <ofShortColor> ).name()){
            auto fromParam = from.getShortColor(i);
            auto toParam = to.getShortColor(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <ofFloatColor> ).name()){
            auto fromParam = from.getFloatColor(i);
            auto toParam = to.getFloatColor(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameter <string> ).name()){
            auto fromParam = from.getString(i);
            auto toParam = to.getString(i);
            toParam.set(fromParam.get());
        }else if(type == typeid(ofParameterGroup).name()){
            auto fromParam = from.getGroup(i);
            auto toParam = to.getGroup(i);
            copyParameters(fromParam, toParam);
        }else{
            ofLogWarning() << "ofxBaseGroup; no control for parameter of type " << type;
        }
    }
}

typedef struct DotsScene {
    int genomeId;
    flam3_genome *genome;

    ofParameterGroup displayParameters;

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

    void setupGenome(const int genomeId, flam3_genome *src) {
        this->genomeId = genomeId;

        genome = (flam3_genome *)malloc(sizeof(flam3_genome));
        memset(genome, 0, sizeof(flam3_genome));
        flam3_copy(genome, src);
    }

    void setupParams() {
        displayParameters.clear();
        audioAnalysisParameters.clear();
        drawingParams.clear();
        speedParams.clear();
        dotParams.clear();
        lineParams.clear();
        audioEffectParams.clear();

        // Audio analysis
        audioAnalysisParameters.setName("Audio Analysis");
        audioAnalysisParameters.add(fftDecayRate.set("fftDecayRate", 0.9, 0, 1));
        audioAnalysisParameters.add(centroidMaxBucket.set("centroidMax (mpx)", 0.35, 0, 1));
        audioAnalysisParameters.add(rmsMultiple.set("rmsMult (mpy)", 5, 0, 15));
        audioAnalysisParameters.add(mpxSmoothingFactor.set("mpxSmoothingFactor", 0.4, 0, 1));
        audioAnalysisParameters.add(mpySmoothingFactor.set("mpySmoothingFactor", 0.1, 0, 1));
        displayParameters.add(audioAnalysisParameters);

        // Drawing
        drawingParams.setName("Drawing");
        drawingParams.add(clearSpeed.set("clearSpeed", 50, 0, 255));
        drawingParams.add(particleAlpha.set("particleAlpha", 50, 0, 255));
        drawingParams.add(overallScale.set("overallScale", 1, 0.1, 3.0));
        drawingParams.add(saturationPct.set("saturationPct", 1, 0, 1));
        displayParameters.add(drawingParams);

        // Rotation / Interpolation speed
        speedParams.setName("Speed");
        speedParams.add(baseSpeed.set("baseSpeed", 0, 0, 10));
        speedParams.add(rmsSpeedMult.set("rmsSpeedMult", 30, 0, 100));
        displayParameters.add(speedParams);

        // Dot size
        dotParams.setName("Dots");
        dotParams.add(pointRadiusAudioScaleAmt.set("pointRadiusAudioScaleAmt", 1, 0, 1));
        dotParams.add(pointRadiusAudioScale.set("dotAudioScale", 10, 0, 50));
        dotParams.add(basePointRadius.set("baseDotRadius", 10, 0, 50));
        displayParameters.add(dotParams);

        // Line size
        lineParams.setName("Lines");
        lineParams.add(maxLineLength.set("maxLineLength", 100, 0, 3000));
        displayParameters.add(lineParams);

        // Audio effects
        audioEffectParams.setName("Audio Effect Sizes");
        audioEffectParams.add(audioEffectSize1.set("audioEffectSize1", 1, 0, 1));
        audioEffectParams.add(audioEffectSize2.set("audioEffectSize2", 1, 0, 1));
        audioEffectParams.add(audioEffectSize3.set("audioEffectSize3", 1, 0, 1));
        audioEffectParams.add(audioEffectSize4.set("audioEffectSize4", 1, 0, 1));
        displayParameters.add(audioEffectParams);
        
        displayParameters.setName("Scene");
    };

    void copyParamsTo(DotsScene &dest) {
        copyParameters(this->displayParameters, dest.displayParameters);
    }

    void copyGenomeTo(DotsScene &dest) {
        dest.setupGenome(genomeId, genome);
    }

    ~DotsScene() {
        delete genome;
    }
} DotsScene;

typedef struct DotsTrack {
    int trackId;
    vector<DotsScene *> scenes;

    int nGenomes;
    flam3_genome *genomes = NULL;

    void setGenomesFromScenes() {
        nGenomes = scenes.size();

        flam3_genome *newGenomes = (flam3_genome*)malloc(sizeof(flam3_genome) * nGenomes);
        memset(newGenomes, 0, sizeof(flam3_genome) * nGenomes);

        for (int i = 0; i < nGenomes; ++i) {
            flam3_copy(newGenomes + i, scenes[i]->genome);
            scenes[i]->genome = newGenomes + i;
        }

        if (genomes) delete genomes;
        genomes = newGenomes;
    }
} DotsTrack;

class StateManager {
public:
    void setup();
    void update();

    void flameUpdate(flam3_genome *dest, float audioRMS);

    void loadGenebanks();
    void initrc(long sed);
    int randomi(int n);

    void loadGenome(flam3_genome *dest);
    void killCurrent();
    void mateCurrent();
    void mutateCurrent();

    void midiToSceneParams(MidiController &midi);

    void genomeModified(int & genome);

    void loadAllParamsFromFile();
    void serializeCurrentTrackToFile();

    void applyParameterInterpolation(float t);

    void advanceTrack();
    void regressTrack();
    void saveTrack();
    void createTrack();
    DotsTrack& getTrack();

    void regressScene();
    void advanceScene();
    void reloadScene();
    void deleteScene();
    void duplicateScene();
    DotsScene& getScene();

    DotsScene defaultScene;
    DotsScene activeScene;
    DotsScene *currScene;
    DotsScene *nextScene;

    // Are we wandering or standing still
    bool wandering;
    float wanderSpeed;
    int lastCP;
    float wanderElapsed;
    float interpAmt;

    // Where are we
    int trackIdx, sceneIdx;
    vector<DotsTrack> tracks;

    // Geneback for mutation
    int ngenebank;
    flam3_genome *genebank;

    // Base control points
    int ncps;
    flam3_genome *cps;

    // Fixed randomness for flam3
    int seed;
    randctx rc;

    // For serialization
    ofxXmlSettings settings;
    int maxGenomeId;
    int maxTrackId;

    // Events
    ofEvent<int> onTrackChange;
    ofEvent<int> onSceneChange;

    ofEvent<int> onTrackUpdate;
    ofEvent<int> onSceneUpdate;

protected:
    int nextGenomeId() { return ++maxGenomeId; };
    int nextTrackId() { return ++maxTrackId; };
};