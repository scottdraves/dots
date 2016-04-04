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

void GuiApp::setup(){

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
    metaParams.add(wanderSpeed.set("wanderSpeed", 0, 0, 20));
    metaParams.add(genomeInterpolationAmt.set("interpolate", 0, 0, 1));
    metaGui.setup(metaParams);

    inputGui.setPosition(10, 450);
    debugGui.setPosition(inputGui.getPosition().x + inputGui.getWidth() + 10, inputGui.getPosition().y);
    metaGui.setPosition(debugGui.getPosition().x, debugGui.getPosition().y + debugGui.getHeight() + 10);

    loadAllParamsFromFile();
    setupDefaultParams(defaultParams);
    setupDefaultParams(activeParams);
    copyParameters(defaultParams.displayParameters, activeParams.displayParameters);

    displayGui.setup(activeParams.displayParameters);
    displayGui.setPosition(580, 15);
    ofAddListener(displayGui.savePressedE, this, &GuiApp::saveClicked);
    ofAddListener(displayGui.loadPressedE, this, &GuiApp::loadClicked);

    float height = MAX(MAX(MAX(inputGui.getPosition().y + inputGui.getHeight(),
                       debugGui.getPosition().y + inputGui.getHeight()),
                       metaGui.getPosition().y + metaGui.getHeight()),
                       displayGui.getPosition().y + displayGui.getHeight());

    ofSetWindowShape(displayGui.getPosition().x + displayGui.getWidth() + 10,
                     height + 10);

    visuals = NULL;
    audioBuckets = NULL;
    nAudioBuckets = 0;
    frameRate = 0;
    pctParticles = 0;
    genomeIdx = -1;
    mpx = 0;
    mpy = 0;

    ofBackground(0);
    ofSetVerticalSync(false);
}

void GuiApp::setupDefaultParams(dotsParams &params) {
    params.displayParameters.clear();
    params.audioAnalysisParameters.clear();
    params.drawingParams.clear();
    params.speedParams.clear();
    params.dotParams.clear();
    params.lineParams.clear();
    params.audioEffectParams.clear();

    // Audio analysis
    params.audioAnalysisParameters.setName("Audio Analysis");
    params.audioAnalysisParameters.add(params.fftDecayRate.set("fftDecayRate", 0.9, 0, 1));
    params.audioAnalysisParameters.add(params.centroidMaxBucket.set("centroidMax (mpx)", 0.35, 0, 1));
    params.audioAnalysisParameters.add(params.rmsMultiple.set("rmsMult (mpy)", 5, 0, 15));
    params.audioAnalysisParameters.add(params.mpxSmoothingFactor.set("mpxSmoothingFactor", 0.4, 0, 1));
    params.audioAnalysisParameters.add(params.mpySmoothingFactor.set("mpySmoothingFactor", 0.1, 0, 1));
    params.displayParameters.add(params.audioAnalysisParameters);

    // Drawing
    params.drawingParams.setName("Drawing");
    params.drawingParams.add(params.clearSpeed.set("clearSpeed", 50, 0, 255));
    params.drawingParams.add(params.particleAlpha.set("particleAlpha", 50, 0, 255));
    params.drawingParams.add(params.overallScale.set("overallScale", 1, 0.1, 3.0));
    params.displayParameters.add(params.drawingParams);

    // Rotation / Interpolation speed
    params.speedParams.setName("Speed");
    params.speedParams.add(params.baseSpeed.set("baseSpeed", 0, 0, 10));
    params.speedParams.add(params.rmsSpeedMult.set("rmsSpeedMult", 30, 0, 100));
    params.displayParameters.add(params.speedParams);

    // Dot size
    params.dotParams.setName("Dots");
    params.dotParams.add(params.pointRadiusUsesAudio.set("dotSizeUsesAudio", true));
    params.dotParams.add(params.pointRadiusAudioScale.set("dotAudioScale", 10, 0, 50));
    params.dotParams.add(params.basePointRadius.set("baseDotRadius", 10, 0, 50));
    params.displayParameters.add(params.dotParams);

    // Line size
    params.lineParams.setName("Lines");
    params.lineParams.add(params.maxLineLength.set("maxLineLength", 100, 0, 3000));
    params.displayParameters.add(params.lineParams);

    // Audio effects
    params.audioEffectParams.setName("Audio Effect Sizes");
    params.audioEffectParams.add(params.audioEffectSize1.set("audioEffectSize1", 1, 0, 1));
    params.audioEffectParams.add(params.audioEffectSize2.set("audioEffectSize2", 1, 0, 1));
    params.audioEffectParams.add(params.audioEffectSize3.set("audioEffectSize3", 1, 0, 1));
    params.audioEffectParams.add(params.audioEffectSize4.set("audioEffectSize4", 1, 0, 1));
    params.displayParameters.add(params.audioEffectParams);

    params.displayParameters.setName("Display");
}

void GuiApp::saveClicked() {
    cout << "Pushed save." << endl;
    serializeCurrentParamsToFile();
}

void GuiApp::loadClicked() {
    cout << "Pushed load." << endl;
    copyGenomeParams(genomeIdx);
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

    if (currParams && nextParams) {
        applyParameterInterpolation(genomeInterpolationAmt);
    }
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

    sprintf(s, "genome: %d", genomeIdx);
    ofDrawBitmapString(s, 300, 15);

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
        
        float fftWidth = 480.0, fftHeight = 100;
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
        float mappedCentroidMax = fftWidth * activeParams.centroidMaxBucket;
        ofSetColor(125, 0, 0);
        ofDrawLine(mappedCentroidMax, 0, mappedCentroidMax, -fftHeight);
        ofDrawBitmapString("centroidMax", mappedCentroidMax + 4, -30);
        
        // Draw MPX, MPY
        float mpxHeight = 100 * mpx;
        float mpyHeight = 100 * mpy;
        ofFill();
        ofSetColor(255);
        ofDrawBitmapString("mpx", fftWidth + 10, -100);
        ofDrawRectangle(fftWidth + 10, 0, 25, -mpxHeight);
        ofDrawBitmapString("mpy", fftWidth + 40, -100);
        ofDrawRectangle(fftWidth + 40, 0, 25, -mpyHeight);
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    ofPopMatrix();

    inputGui.draw();
    debugGui.draw();
    displayGui.draw();
    metaGui.draw();
}

void GuiApp::handleKey(int key) {
    // None for now
}

void GuiApp::keyPressed(int key) {
    keyPresses.push(key);
}

void GuiApp::copyGenomeParams(int idx) {
    if (paramsMap.count(idx) > 0) {
        cout << "Genome is now " << idx << ", we have settings saved." << endl;
        copyParameters(paramsMap[idx]->displayParameters, activeParams.displayParameters);
    } else {
        cout << "Genome is now " << idx << ", no settings saved." << endl;
        copyParameters(defaultParams.displayParameters, activeParams.displayParameters);
    }
}

void GuiApp::setGenomeIdx(int newIdx) {
    if (useSavedParams.get()) {
        // Save params in case someone set them
        if (paramsMap.count(genomeIdx) > 0) {
            cout << "Saved params from " << genomeIdx << "." << endl;
            copyParameters(activeParams.displayParameters, paramsMap[genomeIdx]->displayParameters);
        }
        
        copyGenomeParams(newIdx);

        // TODO: merge into tracks
        if (paramsMap.count(newIdx) > 0) {
            currParams = paramsMap[newIdx];
            if (paramsMap.count(newIdx+1) > 0) {
                nextParams = paramsMap[genomeIdx+1];
            } else {
                nextParams = paramsMap[0];
            }
        }
    }

    genomeIdx = newIdx;
}

void GuiApp::setupControls(int numCPs) {
    for (int i = 0; i < numCPs; ++i) {
        if (paramsMap.count(i) == 0) {
            dotsParams *params = new dotsParams;
            setupDefaultParams(*params);
            paramsMap[i] = params;
        }
    }
}

// TODO: clean up if possible
void GuiApp::applyParameterInterpolation(float t) {
    activeParams.pointRadiusUsesAudio.set(ofLerp(currParams->pointRadiusUsesAudio.get(),
                                                 nextParams->pointRadiusUsesAudio.get(),
                                                 t));
    activeParams.pointRadiusAudioScale.set(ofLerp(currParams->pointRadiusAudioScale.get(),
                                                  nextParams->pointRadiusAudioScale.get(),
                                                  t));
    activeParams.fftDecayRate.set(ofLerp(currParams->fftDecayRate.get(),
                                         nextParams->fftDecayRate.get(),
                                         t));
    activeParams.rmsMultiple.set(ofLerp(currParams->rmsMultiple.get(),
                                        nextParams->rmsMultiple.get(),
                                        t));
    activeParams.centroidMaxBucket.set(ofLerp(currParams->centroidMaxBucket.get(),
                                              nextParams->centroidMaxBucket.get(),
                                              t));
    activeParams.mpxSmoothingFactor.set(ofLerp(currParams->mpxSmoothingFactor.get(),
                                               nextParams->mpxSmoothingFactor.get(),
                                               t));
    activeParams.mpySmoothingFactor.set(ofLerp(currParams->mpySmoothingFactor.get(),
                                               nextParams->mpySmoothingFactor.get(),
                                               t));
    activeParams.baseSpeed.set(ofLerp(currParams->baseSpeed.get(),
                                      nextParams->baseSpeed.get(),
                                      t));
    activeParams.rmsSpeedMult.set(ofLerp(currParams->rmsSpeedMult.get(),
                                         nextParams->rmsSpeedMult.get(),
                                         t));
    activeParams.clearSpeed.set(ofLerp(currParams->clearSpeed.get(),
                                       nextParams->clearSpeed.get(),
                                       t));
    activeParams.particleAlpha.set(ofLerp(currParams->particleAlpha.get(),
                                          nextParams->particleAlpha.get(),
                                          t));
    activeParams.basePointRadius.set(ofLerp(currParams->basePointRadius.get(),
                                            nextParams->basePointRadius.get(),
                                            t));
    activeParams.maxLineLength.set(ofLerp(currParams->maxLineLength.get(),
                                          nextParams->maxLineLength.get(),
                                          t));
    activeParams.audioEffectSize1.set(ofLerp(currParams->audioEffectSize1.get(),
                                             nextParams->audioEffectSize1.get(),
                                             t));
    activeParams.audioEffectSize2.set(ofLerp(currParams->audioEffectSize2.get(),
                                             nextParams->audioEffectSize2.get(),
                                             t));
    activeParams.audioEffectSize3.set(ofLerp(currParams->audioEffectSize3.get(),
                                             nextParams->audioEffectSize3.get(),
                                             t));
    activeParams.audioEffectSize4.set(ofLerp(currParams->audioEffectSize4.get(),
                                             nextParams->audioEffectSize4.get(),
                                             t));
}

void GuiApp::serializeCurrentParamsToFile() {
    cout << "Saving " << genomeIdx << " to file." << endl;
    char filename[255];
    sprintf(filename, "genomeSettings/cp-%03d.xml", genomeIdx);

    settings.clear();
    settings.serialize(activeParams.displayParameters);
    settings.save(filename);
}

void GuiApp::loadAllParamsFromFile() {
    ofDirectory dir("genomeSettings");
    for (auto &file : dir.getFiles()) {
        settings.clear();
        settings.load(file.path());

        dotsParams *params = new dotsParams;
        setupDefaultParams(*params);
        settings.deserialize(params->displayParameters);

        string filename = file.getFileName();
        int idx = stoi(filename.substr(3, 6));
        cout << "Loading " << idx << " from file." << endl;

        paramsMap[idx] = params;
    }
}


