#include "GuiApp.h"

void copyParameters(const ofParameterGroup &from, const ofParameterGroup &to) {
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

void interpolateParameters(const ofParameterGroup &from, const ofParameterGroup &to,
                           const ofParameterGroup &ret, float t) {
    for(std::size_t i = 0; i < from.size(); i++){
        string type = from.getType(i);
        if(type == typeid(ofParameter <int32_t> ).name()){
            auto fromParam = from.getInt(i);
            auto toParam = to.getInt(i);
            auto retParam = ret.getInt(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <uint32_t> ).name()){
            auto fromParam = from.get<uint32_t>(i);
            auto toParam = to.get<uint32_t>(i);
            auto retParam = ret.get<uint32_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <int64_t> ).name()){
            auto fromParam = from.get<int64_t>(i);
            auto toParam = to.get<int64_t>(i);
            auto retParam = ret.get<int64_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <uint64_t> ).name()){
            auto fromParam = from.get<uint64_t>(i);
            auto toParam = to.get<uint64_t>(i);
            auto retParam = ret.get<uint64_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <int8_t> ).name()){
            auto fromParam = from.get<int8_t>(i);
            auto toParam = to.get<int8_t>(i);
            auto retParam = ret.get<int8_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <uint8_t> ).name()){
            auto fromParam = from.get<uint8_t>(i);
            auto toParam = to.get<uint8_t>(i);
            auto retParam = ret.get<uint8_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <int16_t> ).name()){
            auto fromParam = from.get<int16_t>(i);
            auto toParam = to.get<int16_t>(i);
            auto retParam = ret.get<int16_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <uint16_t> ).name()){
            auto fromParam = from.get<uint16_t>(i);
            auto toParam = to.get<uint16_t>(i);
            auto retParam = ret.get<uint16_t>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <float> ).name()){
            auto fromParam = from.getFloat(i);
            auto toParam = to.getFloat(i);
            auto retParam = ret.getFloat(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <double> ).name()){
            auto fromParam = from.get<double>(i);
            auto toParam = to.get<double>(i);
            auto retParam = ret.get<double>(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <bool> ).name()){
            auto fromParam = from.getBool(i);
            auto toParam = to.getBool(i);
            auto retParam = ret.get<bool>(i);
            retParam.set(t > 0.5 ? toParam.get() : fromParam.get());
        }else if(type == typeid(ofParameter <ofVec2f> ).name()){
            auto fromParam = from.getVec2f(i);
            auto toParam = to.getVec2f(i);
            auto retParam = ret.getVec2f(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <ofVec3f> ).name()){
            auto fromParam = from.getVec3f(i);
            auto toParam = to.getVec3f(i);
            auto retParam = ret.getVec3f(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <ofVec4f> ).name()){
            auto fromParam = from.getVec4f(i);
            auto toParam = to.getVec4f(i);
            auto retParam = ret.getVec4f(i);
            retParam.set((toParam.get() - fromParam.get()) * t + fromParam.get());
        }else if(type == typeid(ofParameter <ofColor> ).name()){
            auto fromParam = from.getColor(i);
            auto toParam = to.getColor(i);
            auto retParam = ret.getColor(i);
            retParam.set(fromParam.get().getLerped(toParam.get(), t));
        }else if(type == typeid(ofParameter <ofShortColor> ).name()){
            auto fromParam = from.getShortColor(i);
            auto toParam = to.getShortColor(i);
            auto retParam = ret.getShortColor(i);
            retParam.set(fromParam.get().getLerped(toParam.get(), t));
        }else if(type == typeid(ofParameter <ofFloatColor> ).name()){
            auto fromParam = from.getFloatColor(i);
            auto toParam = to.getFloatColor(i);
            auto retParam = ret.getFloatColor(i);
            retParam.set(fromParam.get().getLerped(toParam.get(), t));
        }else if(type == typeid(ofParameter <string> ).name()){
            auto fromParam = from.getString(i);
            auto toParam = to.getString(i);
            auto retParam = ret.getString(i);
            retParam.set(t > 0.5 ? toParam.get() : fromParam.get());
        }else if(type == typeid(ofParameterGroup).name()){
            auto fromParam = from.getGroup(i);
            auto toParam = to.getGroup(i);
            auto retParam = ret.getGroup(i);
            interpolateParameters(fromParam, toParam, retParam, t);
        }else{
            ofLogWarning() << "ofxBaseGroup; no control for parameter of type " << type;
        }
    }
}

template <typename ParameterType>
void setParam(ofParameter<ParameterType>& param, float t) {
    param.set(ofLerp(param.getMin(), param.getMax(), t));
}

void GuiApp::setup() {
    midi.setup();

    ofSoundStream ss;
    soundDevices = ss.getDeviceList();
    nSoundDevices = soundDevices.size();

    audioInputParameters.setName("Audio Input");
    audioInputParameters.add(audioMode.set("audioMode", AUDIO_MODE_MIC, 0, N_AUDIO_MODES-1));
    audioInputParameters.add(soundStreamDevice.set("soundStreamDevice", 0, 0, nSoundDevices-1));
    inputGui.setup(audioInputParameters);

    // Auto select loopback if available
    for (int i = 0; i < soundDevices.size(); ++i) {
        ofSoundDevice &sd = soundDevices[i];
        if (sd.name.find("Soundflower") != string::npos && sd.name.find("2ch") != string::npos) {
            soundStreamDevice.set(i);
        }
    }

    // Debug
    debugParameters.setName("Debug");
    debugParameters.add(drawMode.set("drawMode", 0, 0, 1));
    debugParameters.add(nFlameSequences.set("nFlameSequences", 5, 1, 10));
    debugParameters.add(maxPixels.set("maxPixels", 5000000, 10000, 100000000));
    debugParameters.add(pctToAllowRandom.set("pctToAllowRandom", 0.02, 0, 0.1));
    debugParameters.add(useSavedParams.set("Use saved params", true));
    debugGui.setup(debugParameters);

    // Meta
    metaParams.setName("Meta");
    metaParams.add(wandering.set("wandering", false));
    metaParams.add(wanderSpeed.set("wanderSpeed", 1, 0, 20));
    metaParams.add(genomeInterpolationAmt.set("interpolate", 0, 0, 1));
    metaGui.setup(metaParams);

    trackGui.setup("Tracks");

    trackControls.setup();
    trackControls.setName("< >");
    trackControls.add(prevTrackBtn.setup("Prev track"));
    trackControls.add(nextTrackBtn.setup("Next track"));
    trackControls.add(saveTrackBtn.setup("Save track"));
    trackControls.add(newTrackBtn.setup("New track"));
    trackGui.add(&trackControls);

    prevTrackBtn.addListener(this, &GuiApp::regressTrack);
    nextTrackBtn.addListener(this, &GuiApp::advanceTrack);
    saveTrackBtn.addListener(this, &GuiApp::saveTrack);
    newTrackBtn.addListener(this, &GuiApp::createTrack);

    sceneControls.setup();
    sceneControls.setName("Scenes");
    sceneControls.add(duplicateSceneBtn.setup("Duplicate scene"));
    sceneControls.add(reloadSceneBtn.setup("Reload scene"));
    sceneControls.add(deleteSceneBtn.setup("Remove scene"));
    trackGui.add(&sceneControls);

    duplicateSceneBtn.addListener(this, &GuiApp::duplicateScene);
    reloadSceneBtn.addListener(this, &GuiApp::reloadScene);
    deleteSceneBtn.addListener(this, &GuiApp::deleteScene);

    sceneCopyControls.setup();
    sceneCopyControls.setName("Copy");
    sceneCopyControls.add(destTrackIdx.set("destTrack", -1, 0, 0));
    sceneCopyControls.add(destSceneIdx.set("destScene", -1, 0, 0));
    sceneCopyControls.add(copyToTrackBtn.setup("Copy to track at idx"));
    trackGui.add(&sceneCopyControls);
    destTrackIdx.addListener(this, &GuiApp::destTrackIdxChanged);
    copyToTrackBtn.addListener(this, &GuiApp::copyScene);

    setupDefaultParams(defaultScene);
    setupDefaultParams(activeScene);
    copyParameters(defaultScene.displayParameters, activeScene.displayParameters);
    displayGui.setup(activeScene.displayParameters);
    activeScene.genomeIdx.addListener(this, &GuiApp::genomeModified);

    inputGui.setPosition(10, 450);
    debugGui.setPosition(inputGui.getPosition().x + inputGui.getWidth() + 10, inputGui.getPosition().y);
    metaGui.setPosition(debugGui.getPosition().x, debugGui.getPosition().y + debugGui.getHeight() + 10);
    trackGui.setPosition(510, 65);
    displayGui.setPosition(trackGui.getPosition().x + trackGui.getWidth() + 10, 15);


    float height = MAX(MAX(MAX(MAX(inputGui.getPosition().y + inputGui.getHeight(),
                       debugGui.getPosition().y + inputGui.getHeight()),
                       metaGui.getPosition().y + metaGui.getHeight()),
                       displayGui.getPosition().y + displayGui.getHeight()),
                       trackGui.getPosition().y + trackGui.getHeight());

    ofSetWindowShape(displayGui.getPosition().x + displayGui.getWidth() + 10,
                     height + 10);

    visuals = NULL;
    audioBuckets = NULL;
    nAudioBuckets = 0;
    frameRate = 0;
    pctParticles = 0;
    mpx = 0;
    mpy = 0;

    ofBackground(0);
    ofSetVerticalSync(false);

    // Signal tracks not loaded
    trackIdx = -1;
    sceneIdx = -1;
}

void GuiApp::setupDefaultParams(DotsScene &track) {
    track.displayParameters.clear();
    track.sceneParams.clear();
    track.audioAnalysisParameters.clear();
    track.drawingParams.clear();
    track.speedParams.clear();
    track.dotParams.clear();
    track.lineParams.clear();
    track.audioEffectParams.clear();

    // Track params - not settable here
    track.sceneParams.add(track.genomeIdx.set("genomeIdx", 0, 0, numCPs));
    track.displayParameters.add(track.sceneParams);

    // Audio analysis
    track.audioAnalysisParameters.setName("Audio Analysis");
    track.audioAnalysisParameters.add(track.fftDecayRate.set("fftDecayRate", 0.9, 0, 1));
    track.audioAnalysisParameters.add(track.centroidMaxBucket.set("centroidMax (mpx)", 0.35, 0, 1));
    track.audioAnalysisParameters.add(track.rmsMultiple.set("rmsMult (mpy)", 5, 0, 15));
    track.audioAnalysisParameters.add(track.mpxSmoothingFactor.set("mpxSmoothingFactor", 0.4, 0, 1));
    track.audioAnalysisParameters.add(track.mpySmoothingFactor.set("mpySmoothingFactor", 0.1, 0, 1));
    track.displayParameters.add(track.audioAnalysisParameters);

    // Drawing
    track.drawingParams.setName("Drawing");
    track.drawingParams.add(track.clearSpeed.set("clearSpeed", 50, 0, 255));
    track.drawingParams.add(track.particleAlpha.set("particleAlpha", 50, 0, 255));
    track.drawingParams.add(track.overallScale.set("overallScale", 1, 0.1, 3.0));
    track.displayParameters.add(track.drawingParams);

    // Rotation / Interpolation speed
    track.speedParams.setName("Speed");
    track.speedParams.add(track.baseSpeed.set("baseSpeed", 0, 0, 10));
    track.speedParams.add(track.rmsSpeedMult.set("rmsSpeedMult", 30, 0, 100));
    track.displayParameters.add(track.speedParams);

    // Dot size
    track.dotParams.setName("Dots");
    track.dotParams.add(track.pointRadiusAudioScaleAmt.set("pointRadiusAudioScaleAmt", 1, 0, 1));
    track.dotParams.add(track.pointRadiusAudioScale.set("dotAudioScale", 10, 0, 50));
    track.dotParams.add(track.basePointRadius.set("baseDotRadius", 10, 0, 50));
    track.displayParameters.add(track.dotParams);

    // Line size
    track.lineParams.setName("Lines");
    track.lineParams.add(track.maxLineLength.set("maxLineLength", 100, 0, 3000));
    track.displayParameters.add(track.lineParams);

    // Audio effects
    track.audioEffectParams.setName("Audio Effect Sizes");
    track.audioEffectParams.add(track.audioEffectSize1.set("audioEffectSize1", 1, 0, 1));
    track.audioEffectParams.add(track.audioEffectSize2.set("audioEffectSize2", 1, 0, 1));
    track.audioEffectParams.add(track.audioEffectSize3.set("audioEffectSize3", 1, 0, 1));
    track.audioEffectParams.add(track.audioEffectSize4.set("audioEffectSize4", 1, 0, 1));
    track.displayParameters.add(track.audioEffectParams);

    track.displayParameters.setName("Display");
}

void GuiApp::genomeModified(int & newGenomeIdx) {
    if (newGenomeIdx != currScene->genomeIdx)
        trackDirty = true;
}

void GuiApp::destTrackIdxChanged(int & destsceneIdx) {
    destSceneIdx.setMax(tracks[destTrackIdx].scenes.size());
    destSceneIdx.set(ofClamp(destSceneIdx.get(), destSceneIdx.getMin(), destSceneIdx.getMax()));
}

void GuiApp::update(){
    if (ofGetFrameNum() % 30 == 0) {
        // Every 30 frames, refresh some data...
        ofSoundStream ss;
        soundDevices = ss.getDeviceList();
        if (soundDevices.size() != nSoundDevices) {
            if (soundStreamDevice.get() >= soundDevices.size()) {
                soundStreamDevice.set(0);
            }
            nSoundDevices = soundDevices.size();
            soundStreamDevice.setMax(nSoundDevices);
        }
    }

    if ((wandering || genomeInterpolationAmt > 0.0001) && currScene && nextScene) {
        applyParameterInterpolation(genomeInterpolationAmt);
    }

    if (!wandering) {
        midiToSceneParams();
    } else {
        // TODO: apply to midi adjust
    }
}

void GuiApp::midiToSceneParams() {
    if (midi.sliders[0] > 0) setParam(activeScene.clearSpeed, midi.sliders[0]);
    if (midi.sliders[1] > 0) setParam(activeScene.overallScale, midi.sliders[1]);
    if (midi.sliders[2] > 0) setParam(activeScene.basePointRadius, midi.sliders[2]);
    if (midi.sliders[3] > 0) setParam(activeScene.maxLineLength, midi.sliders[3]);
    if (midi.sliders[4] > 0) setParam(activeScene.audioEffectSize1, midi.sliders[4]);
    if (midi.sliders[5] > 0) setParam(activeScene.audioEffectSize2, midi.sliders[5]);
    if (midi.sliders[6] > 0) setParam(activeScene.audioEffectSize3, midi.sliders[6]);
    if (midi.sliders[7] > 0) setParam(activeScene.audioEffectSize4, midi.sliders[7]);
}

void GuiApp::draw() {
    char s[512];
    float margin = 10, padding = 10;
    
    ofPushMatrix();
    
    if (frameRate) {
        sprintf(s, "%.2f fps", frameRate);
        ofDrawBitmapString(s, 10, 15);
    }

    if (pctParticles) {
        sprintf(s, "%d%% particles", (int)(pctParticles*100));
        ofDrawBitmapString(s, 150, 15);
    }

    if (trackIdx >= 0) {
        sprintf(s, "track: %d / %lu", trackIdx, tracks.size()-1);
        ofDrawBitmapString(s, 510, 25);
        sprintf(s, "scene: %d / %lu", sceneIdx, tracks[trackIdx].scenes.size()-1);
        ofDrawBitmapString(s, 510, 40);
        sprintf(s, "genome: %d / %d", activeScene.genomeIdx.get(), numCPs-1);
        ofDrawBitmapString(s, 510, 55);
    }

    ofTranslate(0, 17);

    if (visuals) {
        ofTranslate(0, margin);
        // TODO fit visuals to a bounding box
        
        float scale = min(480.0 / visuals->getWidth(), 270.0 / visuals->getHeight());
        float width = visuals->getWidth() * scale;
        float height = visuals->getHeight() * scale;

        ofFill();
        ofSetColor(255, 255);
        ofDrawRectangle(margin, 0, width + padding * 2, height + padding * 2);
        ofSetColor(0, 255);
        ofDrawRectangle(margin + padding, padding, width, height);
        ofSetColor(255, 255);
        visuals->draw(margin + padding, padding, width, height);

        ofTranslate(0, 270 + padding * 2);
    }
    
    if (audioBuckets) {
        ofTranslate(0, 100 + margin);

        ofPushStyle();

        ofSetColor(255);
        ofNoFill();
        ofSetLineWidth(1);
        
        float fftWidth = 415.0, fftHeight = 100;
        float fftBucketWidth = fftWidth / nAudioBuckets;
        
        ofPushMatrix();
        
        ofTranslate(margin, 0);
        ofDrawRectangle(0, 0, fftWidth, -fftHeight);
        ofBeginShape();
        for (int i = 0; i < nAudioBuckets; i++) {
            ofVertex(i * fftBucketWidth, -audioBuckets[i] * fftHeight);
        }
        ofEndShape();
        
        string audioModeDesc;
        if (audioMode == AUDIO_MODE_MIC) {
            audioModeDesc = "Microphone Input";
        } else if (audioMode == AUDIO_MODE_MP3) {
            audioModeDesc = "MP3 Playing";
        } else if (audioMode == AUDIO_MODE_NOISE) {
            audioModeDesc = "White Noise";
        } else {
            audioModeDesc = "No Audio";
        }
        ofDrawBitmapString(audioModeDesc, 5, 15-fftHeight);

        if (soundStreamDevice < soundDevices.size()) {
            ofDrawBitmapString(soundDevices[soundStreamDevice].name, 5, 30-fftHeight);
        }
        
        // Draw audio centroid
        float mappedCentroid = fftWidth * audioCentroid;
        ofSetColor(200, 0, 0);
        ofDrawLine(mappedCentroid, 0, mappedCentroid, -fftHeight);
        ofDrawBitmapString("centroid", mappedCentroid + 4, -30);
        float mappedCentroidMax = fftWidth * activeScene.centroidMaxBucket;
        ofSetColor(125, 0, 0);
        ofDrawLine(mappedCentroidMax, 0, mappedCentroidMax, -fftHeight);
        ofDrawBitmapString("centroidMax", mappedCentroidMax + 4, -30);
        
        // Draw MPX, MPY
        float mpxHeight = 90 * mpx;
        float mpyHeight = 90 * mpy;
        ofFill();
        ofSetColor(255);
        ofDrawBitmapString("mpx", fftWidth + 10, -90);
        ofDrawRectangle(fftWidth + 10, 0, 25, -mpxHeight);
        ofDrawBitmapString("mpy", fftWidth + 40, -90);
        ofDrawRectangle(fftWidth + 40, 0, 25, -mpyHeight);
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    ofPopMatrix();

    inputGui.draw();
    debugGui.draw();
    displayGui.draw();
    metaGui.draw();
    trackGui.draw();
}

void GuiApp::handleKey(int key) {
    // None for now
}

void GuiApp::keyPressed(int key) {
    keyPresses.push(key);
}

vector<int> GuiApp::getTrackGenomeIndices() {
    vector<int> indices;
    for (auto track : tracks[trackIdx].scenes) {
        indices.push_back(track->genomeIdx.get());
    }
    return indices;
}

void GuiApp::regressTrack() {
    cout << "Regress track" << endl;
    if (trackIdx < 0) return;

    trackIdx--;
    if (trackIdx < 0) {
        trackIdx = tracks.size() - 1;
    }

    sceneIdx = -1;
    advanceScene();
}

void GuiApp::advanceTrack() {
    cout << "Advance track" << endl;
    if (trackIdx < 0) return;

    trackIdx++;
    if (trackIdx >= tracks.size()) {
        trackIdx = 0;
    }

    sceneIdx = -1;
    advanceScene();
}

void GuiApp::saveTrack() {
    cout << "Save track" << endl;
    copyParameters(activeScene.displayParameters, currScene->displayParameters);
    serializeCurrentTrackToFile();
}

void GuiApp::regressScene() {
    if (trackIdx < 0) return;

    sceneIdx--;
    int nextIdx = sceneIdx + 1;

    int nTracks = tracks[trackIdx].scenes.size();
    if (sceneIdx < 0) {
        sceneIdx = nTracks-1;
        nextIdx = 0;
    }

    if (nextIdx >= nTracks) {
        nextIdx = 0;
    }

    // Save what we're coming from
    if (currScene && !wandering) {
        copyParameters(activeScene.displayParameters, currScene->displayParameters);
    }

    currScene = tracks[trackIdx].scenes[sceneIdx];
    nextScene = tracks[trackIdx].scenes[nextIdx];

    // Load what we're going to
    copyParameters(currScene->displayParameters, activeScene.displayParameters);
}

void GuiApp::advanceScene() {
    if (trackIdx < 0) return;

    sceneIdx++;
    int nextIdx = sceneIdx + 1;

    int nTracks = tracks[trackIdx].scenes.size();
    if (sceneIdx >= nTracks) {
        sceneIdx = 0;
        nextIdx = 1;
    }

    if (nextIdx >= nTracks) {
        nextIdx = 0;
    }

    // Save what we're coming from
    if (currScene && !wandering) {
        copyParameters(activeScene.displayParameters, currScene->displayParameters);
    }

    currScene = tracks[trackIdx].scenes[sceneIdx];
    nextScene = tracks[trackIdx].scenes[nextIdx];

    // Load what we're going to
    copyParameters(currScene->displayParameters, activeScene.displayParameters);
}

void GuiApp::reloadScene() {
    cout << "Reload scene" << endl;
    copyParameters(currScene->displayParameters, activeScene.displayParameters);
}

void GuiApp::deleteScene() {
    cout << "Delete scene" << endl;
    trackDirty = true;

    vector<DotsScene *> &scenes = tracks[trackIdx].scenes;
    tracks.erase(tracks.begin() + sceneIdx);

    // TODO: less ham-fisted way to do this
    regressScene();
    advanceScene();
}

// TODO: unify with the below
void GuiApp::duplicateScene() {
    cout << "Duplicate scene" << endl;
    trackDirty = true;

    DotsScene *cpy = new DotsScene;
    setupDefaultParams(*cpy);
    copyParameters(activeScene.displayParameters, cpy->displayParameters);

    vector<DotsScene *> &destTracks = tracks[trackIdx].scenes;
    destTracks.insert(destTracks.begin() + sceneIdx + 1, cpy);
}

void GuiApp::copyScene() {
    cout << "Copy scene" << endl;
    trackDirty = true;

    DotsScene *cpy = new DotsScene;
    setupDefaultParams(*cpy);
    copyParameters(activeScene.displayParameters, cpy->displayParameters);

    vector<DotsScene *> &destTracks = tracks[destTrackIdx].scenes;
    destTracks.insert(destTracks.begin() + destSceneIdx, cpy);
}

// TODO: clean up if possible
void GuiApp::applyParameterInterpolation(float t) {
    activeScene.pointRadiusAudioScaleAmt.set(ofLerp(currScene->pointRadiusAudioScaleAmt.get(),
                                                    nextScene->pointRadiusAudioScaleAmt.get(),
                                                    t));
    activeScene.pointRadiusAudioScale.set(ofLerp(currScene->pointRadiusAudioScale.get(),
                                                  nextScene->pointRadiusAudioScale.get(),
                                                  t));
    activeScene.fftDecayRate.set(ofLerp(currScene->fftDecayRate.get(),
                                         nextScene->fftDecayRate.get(),
                                         t));
    activeScene.rmsMultiple.set(ofLerp(currScene->rmsMultiple.get(),
                                        nextScene->rmsMultiple.get(),
                                        t));
    activeScene.centroidMaxBucket.set(ofLerp(currScene->centroidMaxBucket.get(),
                                              nextScene->centroidMaxBucket.get(),
                                              t));
    activeScene.mpxSmoothingFactor.set(ofLerp(currScene->mpxSmoothingFactor.get(),
                                               nextScene->mpxSmoothingFactor.get(),
                                               t));
    activeScene.mpySmoothingFactor.set(ofLerp(currScene->mpySmoothingFactor.get(),
                                               nextScene->mpySmoothingFactor.get(),
                                               t));
    activeScene.baseSpeed.set(ofLerp(currScene->baseSpeed.get(),
                                      nextScene->baseSpeed.get(),
                                      t));
    activeScene.rmsSpeedMult.set(ofLerp(currScene->rmsSpeedMult.get(),
                                         nextScene->rmsSpeedMult.get(),
                                         t));
    activeScene.clearSpeed.set(ofLerp(currScene->clearSpeed.get(),
                                       nextScene->clearSpeed.get(),
                                       t));
    activeScene.particleAlpha.set(ofLerp(currScene->particleAlpha.get(),
                                          nextScene->particleAlpha.get(),
                                          t));
    activeScene.overallScale.set(ofLerp(currScene->overallScale.get(),
                                        nextScene->overallScale.get(),
                                        t));
    activeScene.basePointRadius.set(ofLerp(currScene->basePointRadius.get(),
                                            nextScene->basePointRadius.get(),
                                            t));
    activeScene.maxLineLength.set(ofLerp(currScene->maxLineLength.get(),
                                          nextScene->maxLineLength.get(),
                                          t));
    activeScene.audioEffectSize1.set(ofLerp(currScene->audioEffectSize1.get(),
                                             nextScene->audioEffectSize1.get(),
                                             t));
    activeScene.audioEffectSize2.set(ofLerp(currScene->audioEffectSize2.get(),
                                             nextScene->audioEffectSize2.get(),
                                             t));
    activeScene.audioEffectSize3.set(ofLerp(currScene->audioEffectSize3.get(),
                                             nextScene->audioEffectSize3.get(),
                                             t));
    activeScene.audioEffectSize4.set(ofLerp(currScene->audioEffectSize4.get(),
                                             nextScene->audioEffectSize4.get(),
                                             t));
}

void GuiApp::serializeCurrentTrackToFile() {
    cout << "Saving track " << trackIdx << " to file." << endl;
    char filename[255];
    sprintf(filename, "genomeSettings/track-%03d.xml", trackIdx);

    settings.clear();
    settings.addTag("track");
    settings.pushTag("track");

        settings.addTag("scenes");
        settings.pushTag("scenes");
        int nScenes = tracks[trackIdx].scenes.size();
        for (int i = 0; i < nScenes; ++i) {
            DotsScene *scene = tracks[trackIdx].scenes[i];
            settings.addTag("scene");
            settings.pushTag("scene", i);
            settings.serialize(scene->displayParameters);
            settings.popTag();
        }
        settings.popTag();

    settings.popTag();
    settings.save(filename);
}

void GuiApp::createTrack() {
    DotsTrack track;
    track.trackIdx = tracks.size();

    DotsScene *scene = new DotsScene;
    setupDefaultParams(*scene);
    scene->genomeIdx = currScene->genomeIdx;
    track.scenes.push_back(scene);

    tracks.push_back(track);
}

void GuiApp::setupControls(int numCPs) {
    this->numCPs = numCPs;

    DotsTrack defaultTrack;
    defaultTrack.trackIdx = 0;

    for (int cpIdx = 0; cpIdx < numCPs; ++cpIdx) {
        DotsScene *track = new DotsScene;
        setupDefaultParams(*track);

        track->genomeIdx = cpIdx;

        defaultTrack.scenes.push_back(track);
    }

    trackIdx = 0;
    sceneIdx = 0;

    tracks.push_back(defaultTrack);

    // Now load tracks from file
    loadAllParamsFromFile();
    destSceneIdx.set(0);
    destSceneIdx.setMax(tracks.size() - 1);
    destTrackIdx.set(0);
}

void GuiApp::loadAllParamsFromFile() {
    ofDirectory dir("genomeSettings");

    map<int, DotsTrack> trackMap;

    for (auto &file : dir.getFiles()) {
        settings.clear();
        settings.load(file.path());

        string filename = file.getFileName();

        if (filename.find("track") != 0) continue;

        int trackIdx = stoi(filename.substr(6, 9));

        // Skip 0th, even if it's saved.
        if (trackIdx == 0) continue;

        DotsTrack track;
        track.trackIdx = trackIdx;

        settings.clear();
        settings.loadFile(file.getAbsolutePath());
        settings.pushTag("track");
            settings.pushTag("scenes");
            int nScenes = settings.getNumTags("scenes");
            for (int i = 0; i < nScenes; ++i) {
                DotsScene *scene = new DotsScene;
                setupDefaultParams(*scene);

                settings.pushTag("scene", i);
                settings.deserialize(scene->displayParameters);
                settings.popTag();

                track.scenes.push_back(scene);
            }
            settings.popTag();
        settings.popTag();

        cout << "Loading a" << trackIdx << " from file." << endl;
        trackMap[trackIdx] = track;
    }

    for (auto &pair : trackMap) {
        tracks.push_back(pair.second);
    }

    // Sort tracks by idx
    std::sort(tracks.begin(), tracks.end(),
              [](const DotsTrack & a, const DotsTrack & b) -> bool
              {
                  return a.trackIdx < b.trackIdx;
              });
}


