#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    speed.setup("SPEED", true, true, false, 0.5, 1.0); // Use Volume, Use Percentage.
    cunt.setup("CUNT", false, true, false, 0.1, 0.7); // Use Percentage.
    ae.setup("AESLUT", true, false, false, 0.5f, 200.0f); // Use Volume.
    
    vars.reserve(3);
    vars.push_back(&speed);
    vars.push_back(&cunt);
    vars.push_back(&ae);
    
    oscGen.setup(vars);

}

//--------------------------------------------------------------
void ofApp::update(){
    oscGen.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofColor colorOne;
    ofColor colorTwo;
    
    colorOne.set (155, 130, 100);
    colorTwo.set (100, 140, 155);
    
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_BAR);
    
    myVar = 0.0f;
    if (speed.volume) {
        myVar = speed.getVolume();
    }
    ofCircle(50, ofGetHeight()-50, myVar * 25);
    
    if (speed.percentage) {
        ofCircle(50 * 2, ofGetHeight()-50, speed.getPercentage() * 25);
    }
    if (cunt.percentage) {
        ofCircle(50 * 3, ofGetHeight()-50, cunt.getPercentage() * 25);
    }
    if (ae.volume) {
        ofCircle(50 * 4, ofGetHeight()-50, ae.getVolume() * 25);
    }
    
    oscGen.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
