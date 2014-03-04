#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    speed.setUsage(true, true, false); // Use Volume, Use Percentage.
    cunt.setUsage(false, true, false); // Use Percentage.
    ae.setUsage(true, false, false); // Use Volume.
    
    vars.reserve(3);
    vars.push_back(&speed);
    vars.push_back(&cunt);
    vars.push_back(&ae);
    
    oscGen.setup(vars);
    
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::update(){

    oscGen.update();

}


//--------------------------------------------------------------
void testApp::draw(){

    ofColor colorOne;
    ofColor colorTwo;
    
    colorOne.set (155, 130, 100);
    colorTwo.set (100, 140, 155);
    
    ofBackgroundGradient(colorOne, colorTwo, OF_GRADIENT_BAR);
    
    myVar = 0.0f;
    if (speed.volume) {
        myVar = *speed.volume;
    }
    ofCircle(50, ofGetHeight()-50, myVar * 25);
    
    if (speed.percentage) {
        ofCircle(50 * 2, ofGetHeight()-50, *speed.percentage * 25);
    }
    if (cunt.percentage) {
        ofCircle(50 * 3, ofGetHeight()-50, *cunt.percentage * 25);
    }
    if (ae.volume) {
        ofCircle(50 * 4, ofGetHeight()-50, *ae.volume * 25);
    }
    
    oscGen.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
