/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"

void GuiApp::setup(){
    parameters.setName("parameters");
    parameters.add(wandering.set("wandering", false));
    gui.setup(parameters);
    gui.setPosition(10, 300);
    
    visuals = NULL;

    ofBackground(0);
    ofSetVerticalSync(false);
}

void GuiApp::update(){

}

void GuiApp::draw() {
    if (visuals) {
        // TODO fit visuals to a bounding box
        float margin = 10, padding = 10;
        float width = visuals->getWidth() / 4.0;
        float height = visuals->getHeight() / 4.0;

        ofFill();
        ofSetColor(255, 255);
        ofDrawRectangle(margin, margin, width + padding * 2, height + padding * 2);
        ofSetColor(0, 255);
        ofDrawRectangle(margin + padding, margin + padding, width, height);
        ofSetColor(255, 255);
        visuals->draw(margin + padding, margin + padding, width, height);
    }

    gui.draw();
}


void GuiApp::keyPressed(int key) {
    if (key == ' ') {
        wandering.set(!wandering.get());
    }
}