#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofParameterGroup parameters;
    ofParameter<bool> wandering;
    ofxPanel gui;
    
    ofTexture* visuals;
};
