#include "GuiApp.h"

void GuiApp::setup(){
    parameters.setName("parameters");
    
    ofSoundStream ss;
    soundDevices = ss.getDeviceList();
    nSoundDevices = soundDevices.size();
    
    parameters.add(audioMode.set("audioMode", AUDIO_MODE_MIC, 0, N_AUDIO_MODES-1));
    parameters.add(soundStreamDevice.set("soundStreamDevice", 0, 0, nSoundDevices-1));
    parameters.add(wandering.set("wandering", false));
    parameters.add(fftDecayRate.set("fftDecayRate", 0.9, 0, 1));
    gui.setup(parameters);
    gui.setPosition(10, 450);
    
    visuals = NULL;
    audioBuckets = NULL;
    nAudioBuckets = 0;
    frameRate = 0;

    ofBackground(0);
    ofSetVerticalSync(false);
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
}

void GuiApp::draw() {
    char s[512];
    float margin = 10, padding = 10;
    
    ofPushMatrix();
    
    if (frameRate) {
        sprintf(s, "%.2f fps", frameRate);
        ofDrawBitmapString(s, 10, 15);
        ofTranslate(0, 17);
    }

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
        
        float fftWidth = 480.0 / nAudioBuckets;
        
        ofPushMatrix();
        
        ofTranslate(margin, 0);
        ofDrawRectangle(0, 0, 480, -100);
        ofBeginShape();
        for (int i = 0; i < nAudioBuckets; i++) {
            ofVertex(i * fftWidth, -audioBuckets[i] * 100);
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
        ofDrawBitmapString(audioModeDesc, 5, 15-100);

        if (soundStreamDevice < soundDevices.size()) {
            ofDrawBitmapString(soundDevices[soundStreamDevice].name, 5, 30-100);
        }
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    ofPopMatrix();

    gui.draw();
}


void GuiApp::keyPressed(int key) {
    if (key == ' ') {
        wandering.set(!wandering.get());
    }
}