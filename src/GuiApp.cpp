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
    metaParams.add(wanderSpeed.set("wanderSpeed", 0, 0, 20));
    metaParams.add(genomeInterpolationAmt.set("interpolate", 0, 0, 1));
    metaGui.setup(metaParams);

    albumGui.setup("Album");

    albumControls.setup();
    albumControls.setName("< >");
    albumControls.add(prevAlbumBtn.setup("Prev album"));
    albumControls.add(nextAlbumBtn.setup("Next album"));
    albumControls.add(saveAlbumBtn.setup("Save album"));
    albumControls.add(newAlbumBtn.setup("New album"));
    albumGui.add(&albumControls);

    prevAlbumBtn.addListener(this, &GuiApp::regressAlbum);
    nextAlbumBtn.addListener(this, &GuiApp::advanceAlbum);
    saveAlbumBtn.addListener(this, &GuiApp::saveAlbum);
    newAlbumBtn.addListener(this, &GuiApp::createAlbum);

    trackControls.setup();
    trackControls.setName("Tracks");
    trackControls.add(duplicateTrackBtn.setup("Duplicate track"));
    trackControls.add(reloadTrackBtn.setup("Reload track"));
    trackControls.add(deleteTrackBtn.setup("Remove track"));
    albumGui.add(&trackControls);

    duplicateTrackBtn.addListener(this, &GuiApp::duplicateTrack);
    reloadTrackBtn.addListener(this, &GuiApp::reloadTrack);
    deleteTrackBtn.addListener(this, &GuiApp::deleteTrack);

    albumCopyControls.setup();
    albumCopyControls.setName("Copy");
    albumCopyControls.add(destAlbumIdx.set("destAlbum", -1, 0, 0));
    albumCopyControls.add(destTrackIdx.set("destTrack", -1, 0, 0));
    albumCopyControls.add(copyToAlbumBtn.setup("Copy to album at idx"));
    albumGui.add(&albumCopyControls);
    destAlbumIdx.addListener(this, &GuiApp::destAlbumIdxChanged);
    copyToAlbumBtn.addListener(this, &GuiApp::copyTrack);

    setupDefaultParams(defaultTrack);
    setupDefaultParams(activeTrack);
    copyParameters(defaultTrack.displayParameters, activeTrack.displayParameters);
    displayGui.setup(activeTrack.displayParameters);
    ofAddListener(displayGui.savePressedE, this, &GuiApp::saveClicked);
    ofAddListener(displayGui.loadPressedE, this, &GuiApp::loadClicked);
    activeTrack.genomeIdx.addListener(this, &GuiApp::genomeModified);

    inputGui.setPosition(10, 450);
    debugGui.setPosition(inputGui.getPosition().x + inputGui.getWidth() + 10, inputGui.getPosition().y);
    metaGui.setPosition(debugGui.getPosition().x, debugGui.getPosition().y + debugGui.getHeight() + 10);
    albumGui.setPosition(510, 65);
    displayGui.setPosition(albumGui.getPosition().x + albumGui.getWidth() + 10, 15);


    float height = MAX(MAX(MAX(MAX(inputGui.getPosition().y + inputGui.getHeight(),
                       debugGui.getPosition().y + inputGui.getHeight()),
                       metaGui.getPosition().y + metaGui.getHeight()),
                       displayGui.getPosition().y + displayGui.getHeight()),
                       albumGui.getPosition().y + albumGui.getHeight());

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

    // Signal albums not loaded
    albumIdx = -1;
    trackIdx = -1;
}

void GuiApp::setupDefaultParams(dotsTrack &track) {
    track.displayParameters.clear();
    track.trackParams.clear();
    track.audioAnalysisParameters.clear();
    track.drawingParams.clear();
    track.speedParams.clear();
    track.dotParams.clear();
    track.lineParams.clear();
    track.audioEffectParams.clear();

    // Track params - not settable here
    track.trackParams.add(track.genomeIdx.set("genomeIdx", 0, 0, numCPs));
    track.displayParameters.add(track.trackParams);

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
    track.dotParams.add(track.pointRadiusAudioScaleAmt.set("pointRadiusAudioScaleAmt", true));
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

void GuiApp::saveClicked() {
    cout << "Pushed save." << endl;
    serializeCurrentAlbumToFile();
}

void GuiApp::loadClicked() {
    cout << "Pushed load." << endl;
}

void GuiApp::genomeModified(int & newGenomeIdx) {
    if (newGenomeIdx != currTrack->genomeIdx)
        albumDirty = true;
}

void GuiApp::destAlbumIdxChanged(int & destAlbumIdx) {
    destTrackIdx.setMax(albums[destAlbumIdx].trackList.size());
    destTrackIdx.set(ofClamp(destTrackIdx.get(), destTrackIdx.getMin(), destTrackIdx.getMax()));
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

    if ((wandering || genomeInterpolationAmt > 0.0001) && currTrack && nextTrack) {
        applyParameterInterpolation(genomeInterpolationAmt);
    }

    if (!wandering) {
        midiToTrackParams();
    } else {
        // TODO: apply to midi adjust
    }
}

void GuiApp::midiToTrackParams() {
    if (midi.sliders[0] > 0) setParam(activeTrack.clearSpeed, midi.sliders[0]);
    if (midi.sliders[1] > 0) setParam(activeTrack.overallScale, midi.sliders[1]);
    if (midi.sliders[2] > 0) setParam(activeTrack.basePointRadius, midi.sliders[2]);
    if (midi.sliders[3] > 0) setParam(activeTrack.maxLineLength, midi.sliders[3]);
    if (midi.sliders[4] > 0) setParam(activeTrack.audioEffectSize1, midi.sliders[4]);
    if (midi.sliders[5] > 0) setParam(activeTrack.audioEffectSize2, midi.sliders[5]);
    if (midi.sliders[6] > 0) setParam(activeTrack.audioEffectSize3, midi.sliders[6]);
    if (midi.sliders[7] > 0) setParam(activeTrack.audioEffectSize4, midi.sliders[7]);
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

    if (albumIdx >= 0) {
        sprintf(s, "album: %d", albumIdx);
        ofDrawBitmapString(s, 510, 25);
        sprintf(s, "track: %d", trackIdx);
        ofDrawBitmapString(s, 510, 40);
        sprintf(s, "genome: %d", activeTrack.genomeIdx.get());
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
        float mappedCentroidMax = fftWidth * activeTrack.centroidMaxBucket;
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
    albumGui.draw();
}

void GuiApp::handleKey(int key) {
    // None for now
}

void GuiApp::keyPressed(int key) {
    keyPresses.push(key);
}

vector<int> GuiApp::getAlbumGenomeIndices() {
    vector<int> indices;
    for (auto track : albums[albumIdx].trackList) {
        indices.push_back(track->genomeIdx.get());
    }
    return indices;
}

void GuiApp::regressAlbum() {
    cout << "Regress album" << endl;
    if (albumIdx < 0) return;

    albumIdx--;
    if (albumIdx < 0) {
        albumIdx = albums.size() - 1;
    }

    trackIdx = -1;
    advanceTrack();
}

void GuiApp::advanceAlbum() {
    cout << "Advance album" << endl;
    if (albumIdx < 0) return;

    albumIdx++;
    if (albumIdx >= albums.size()) {
        albumIdx = 0;
    }

    trackIdx = -1;
    advanceTrack();
}

void GuiApp::regressTrack() {
    if (albumIdx < 0) return;

    trackIdx--;
    int nextIdx = trackIdx + 1;

    int nTracks = albums[albumIdx].trackList.size();
    if (trackIdx < 0) {
        trackIdx = nTracks-1;
        nextIdx = 0;
    }

    if (nextIdx >= nTracks) {
        nextIdx = 0;
    }

    // Save what we're coming from
    if (currTrack && !wandering) {
        copyParameters(activeTrack.displayParameters, currTrack->displayParameters);
    }

    currTrack = albums[albumIdx].trackList[trackIdx];
    nextTrack = albums[albumIdx].trackList[nextIdx];

    // Load what we're going to
    copyParameters(currTrack->displayParameters, activeTrack.displayParameters);
}

void GuiApp::advanceTrack() {
    if (albumIdx < 0) return;

    trackIdx++;
    int nextIdx = trackIdx + 1;

    int nTracks = albums[albumIdx].trackList.size();
    if (trackIdx >= nTracks) {
        trackIdx = 0;
        nextIdx = 1;
    }

    if (nextIdx >= nTracks) {
        nextIdx = 0;
    }

    // Save what we're coming from
    if (currTrack && !wandering) {
        copyParameters(activeTrack.displayParameters, currTrack->displayParameters);
    }

    currTrack = albums[albumIdx].trackList[trackIdx];
    nextTrack = albums[albumIdx].trackList[nextIdx];

    // Load what we're going to
    copyParameters(currTrack->displayParameters, activeTrack.displayParameters);
}

void GuiApp::reloadTrack() {
    cout << "Reload track" << endl;
    copyParameters(currTrack->displayParameters, activeTrack.displayParameters);
}

void GuiApp::saveAlbum() {
    cout << "Save album" << endl;
    copyParameters(activeTrack.displayParameters, currTrack->displayParameters);
    serializeCurrentAlbumToFile();
}

void GuiApp::deleteTrack() {
    cout << "Delete track" << endl;
    albumDirty = true;

    vector<dotsTrack *> &tracks = albums[albumIdx].trackList;
    tracks.erase(tracks.begin() + trackIdx);

    // TODO: less ham-fisted way to do this
    regressTrack();
    advanceTrack();
}

// TODO: unify with the below
void GuiApp::duplicateTrack() {
    cout << "Duplicate track" << endl;
    albumDirty = true;

    dotsTrack *cpy = new dotsTrack;
    setupDefaultParams(*cpy);
    copyParameters(activeTrack.displayParameters, cpy->displayParameters);

    vector<dotsTrack *> &destTracks = albums[albumIdx].trackList;
    destTracks.insert(destTracks.begin() + trackIdx + 1, cpy);
}

void GuiApp::copyTrack() {
    cout << "Copy track" << endl;
    albumDirty = true;

    dotsTrack *cpy = new dotsTrack;
    setupDefaultParams(*cpy);
    copyParameters(activeTrack.displayParameters, cpy->displayParameters);

    vector<dotsTrack *> &destTracks = albums[destAlbumIdx].trackList;
    destTracks.insert(destTracks.begin() + destTrackIdx, cpy);
}

// TODO: clean up if possible
void GuiApp::applyParameterInterpolation(float t) {
    activeTrack.pointRadiusAudioScaleAmt.set(ofLerp(currTrack->pointRadiusAudioScaleAmt.get(),
                                                    nextTrack->pointRadiusAudioScaleAmt.get(),
                                                    t));
    activeTrack.pointRadiusAudioScale.set(ofLerp(currTrack->pointRadiusAudioScale.get(),
                                                  nextTrack->pointRadiusAudioScale.get(),
                                                  t));
    activeTrack.fftDecayRate.set(ofLerp(currTrack->fftDecayRate.get(),
                                         nextTrack->fftDecayRate.get(),
                                         t));
    activeTrack.rmsMultiple.set(ofLerp(currTrack->rmsMultiple.get(),
                                        nextTrack->rmsMultiple.get(),
                                        t));
    activeTrack.centroidMaxBucket.set(ofLerp(currTrack->centroidMaxBucket.get(),
                                              nextTrack->centroidMaxBucket.get(),
                                              t));
    activeTrack.mpxSmoothingFactor.set(ofLerp(currTrack->mpxSmoothingFactor.get(),
                                               nextTrack->mpxSmoothingFactor.get(),
                                               t));
    activeTrack.mpySmoothingFactor.set(ofLerp(currTrack->mpySmoothingFactor.get(),
                                               nextTrack->mpySmoothingFactor.get(),
                                               t));
    activeTrack.baseSpeed.set(ofLerp(currTrack->baseSpeed.get(),
                                      nextTrack->baseSpeed.get(),
                                      t));
    activeTrack.rmsSpeedMult.set(ofLerp(currTrack->rmsSpeedMult.get(),
                                         nextTrack->rmsSpeedMult.get(),
                                         t));
    activeTrack.clearSpeed.set(ofLerp(currTrack->clearSpeed.get(),
                                       nextTrack->clearSpeed.get(),
                                       t));
    activeTrack.particleAlpha.set(ofLerp(currTrack->particleAlpha.get(),
                                          nextTrack->particleAlpha.get(),
                                          t));
    activeTrack.overallScale.set(ofLerp(currTrack->overallScale.get(),
                                        nextTrack->overallScale.get(),
                                        t));
    activeTrack.basePointRadius.set(ofLerp(currTrack->basePointRadius.get(),
                                            nextTrack->basePointRadius.get(),
                                            t));
    activeTrack.maxLineLength.set(ofLerp(currTrack->maxLineLength.get(),
                                          nextTrack->maxLineLength.get(),
                                          t));
    activeTrack.audioEffectSize1.set(ofLerp(currTrack->audioEffectSize1.get(),
                                             nextTrack->audioEffectSize1.get(),
                                             t));
    activeTrack.audioEffectSize2.set(ofLerp(currTrack->audioEffectSize2.get(),
                                             nextTrack->audioEffectSize2.get(),
                                             t));
    activeTrack.audioEffectSize3.set(ofLerp(currTrack->audioEffectSize3.get(),
                                             nextTrack->audioEffectSize3.get(),
                                             t));
    activeTrack.audioEffectSize4.set(ofLerp(currTrack->audioEffectSize4.get(),
                                             nextTrack->audioEffectSize4.get(),
                                             t));
}

void GuiApp::serializeCurrentAlbumToFile() {
    cout << "Saving album " << albumIdx << " to file." << endl;
    char filename[255];
    sprintf(filename, "genomeSettings/album-%03d.xml", albumIdx);

    settings.clear();
    settings.addTag("album");
    settings.pushTag("album");

        settings.addTag("tracks");
        settings.pushTag("tracks");
        int nTracks = albums[albumIdx].trackList.size();
        for (int i = 0; i < nTracks; ++i) {
            dotsTrack *track = albums[albumIdx].trackList[i];
            settings.addTag("track");
            settings.pushTag("track", i);
            settings.serialize(track->displayParameters);
            settings.popTag();
        }
        settings.popTag();

    settings.popTag();
    settings.save(filename);
}

void GuiApp::createAlbum() {
    dotsAlbum album;
    album.albumIdx = albums.size();

    dotsTrack *track = new dotsTrack;
    setupDefaultParams(*track);
    track->genomeIdx = currTrack->genomeIdx;
    album.trackList.push_back(track);

    albums.push_back(album);
}

void GuiApp::setupControls(int numCPs) {
    this->numCPs = numCPs;

    dotsAlbum defaultAlbum;
    defaultAlbum.albumIdx = 0;

    for (int cpIdx = 0; cpIdx < numCPs; ++cpIdx) {
        dotsTrack *track = new dotsTrack;
        setupDefaultParams(*track);

        track->genomeIdx = cpIdx;

        defaultAlbum.trackList.push_back(track);
    }

    albumIdx = 0;
    trackIdx = 0;

    albums.push_back(defaultAlbum);

    // Now load albums from file
    loadAllParamsFromFile();
    destAlbumIdx.set(0);
    destAlbumIdx.setMax(albums.size() - 1);
    destTrackIdx.set(0);
}

void GuiApp::loadAllParamsFromFile() {
    ofDirectory dir("genomeSettings");

    map<int, dotsAlbum> albumMap;

    for (auto &file : dir.getFiles()) {
        settings.clear();
        settings.load(file.path());

        string filename = file.getFileName();
        int albumIdx = stoi(filename.substr(6, 9));

        // Skip 0th, even if it's saved.
        if (albumIdx == 0) continue;

        dotsAlbum album;
        album.albumIdx = albumIdx;

        settings.clear();
        settings.loadFile(file.getAbsolutePath());
        settings.pushTag("album");
            settings.pushTag("tracks");
            int nTracks = settings.getNumTags("track");
            for (int i = 0; i < nTracks; ++i) {
                dotsTrack *track = new dotsTrack;
                setupDefaultParams(*track);

                settings.pushTag("track", i);
                settings.deserialize(track->displayParameters);
                settings.popTag();

                album.trackList.push_back(track);
            }
            settings.popTag();
        settings.popTag();

        cout << "Loading a" << albumIdx << " from file." << endl;
        albumMap[albumIdx] = album;
    }

    for (auto &pair : albumMap) {
        albums.push_back(pair.second);
    }

    // Sort albums by idx
    std::sort(albums.begin(), albums.end(),
              [](const dotsAlbum & a, const dotsAlbum & b) -> bool
              {
                  return a.albumIdx < b.albumIdx;
              });
}


