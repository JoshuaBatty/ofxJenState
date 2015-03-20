#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

    // Pull in all the messages from Jen
    jenState.update();
    
    
    jenState.getPlayheads();
    
    vector<const Instrument*> kick;
    vector<const Instrument*> snare;
    vector<const Instrument*> ghost;
    vector<const Instrument*> ride;
    vector<const Instrument*> layer;
    vector<const Instrument*> bass;
    vector<const Instrument*> melodic;
    vector<const Instrument*> chordal;
    vector<const Instrument*> atmos;
    
    if(kick.size()){
        kick.at(0)->name;                  // Name of Instrument
        kick.at(0)->amp;                   // Current Normalised Amplitude
        kick.at(0)->pan;                   // Pan Position
        kick.at(0)->playhead.percentage(); // Percentage of Notes Duration
    }
}

//--------------------------------------------------------------
void ofApp::drawInstrument(const Instrument* instrument, int x, int y){
    int w = 150; // Width of module UI
    int h = 105; // Height of module UI
    
    int uvWidth = 130; // Width of UV meter
    int uvHeight = 20; // Height of UV meter
    
    ofColor uvBgColor = ofColor(ofColor::lightBlue);
    
    string name;
    float amp;
    float percenatge;
    float pan;
    
    // Fill our variables with instrument data
    name       = instrument->name;                  // Name of Instrument
    amp        = instrument->amp;                   // Current Normalised Amplitude
    pan        = instrument->pan;                   // Pan Position
    percenatge = instrument->playhead.percentage(); // Percentage of Notes Duration
    
    
    // Draw a rectangular UI
    ofSetColor(255,100,0);
    ofNoFill();
    ofRect(x,y,w,h);
    ofFill();
    
    // Print the name of the Instrument
    ofSetColor(255);
    ofDrawBitmapString(name, x+(uvWidth/2), y+17);
    
    //------------------------------------------------ Draw a spacer
    ofSetColor(255,100,0);
    ofLine(x, y+25, x+w, y+25);
    
    //------------------------------------------------ Draw an amplitude meter
    ofSetColor(uvBgColor);
    ofRect(x+10, y+30, uvWidth, uvHeight);
    
    ofSetColor(10, 250, 25);
    ofRect(x+10, y+30, amp * uvWidth, uvHeight);
    
    ofSetColor(0);
    ofDrawBitmapString("Volume", x+(uvWidth/2)-8, y+45);
    
    //------------------------------------------------ Draw a percentage meter
    ofSetColor(uvBgColor);
    ofRect(x+10, y+55, uvWidth, uvHeight);
    
    ofSetColor(10, 250, 25);
    ofRect(x+10, y+55, percenatge * uvWidth, uvHeight);
    
    ofSetColor(0);
    ofDrawBitmapString("Perc", x+(uvWidth/2), y+70);
    
    //------------------------------------------------ Draw a pan position meter
    ofSetColor(uvBgColor);
    ofRect(x+10, y+80, uvWidth, uvHeight);
    
    ofSetColor(10, 250, 25);
    ofRect(x+10, y+80, ofMap(pan,0.0,1.0,-(uvWidth/2),uvWidth/2), uvHeight);

    ofSetColor(0);
    ofDrawBitmapString("Pan", x+(uvWidth/2)+3, y+95);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor::black, ofColor::white, OF_GRADIENT_LINEAR);

    vector<const Instrument*> kicks;

   // Instrument myKick = Instrument(Kick, "KICK", 1000);
    myKick.pan = 1.0+sin(ofGetElapsedTimef())*0.5;
    myKick.amp = 0.9;
    const Instrument myACTUALKick = myKick;
    const Instrument* myKickPtr = &myACTUALKick;
    
    kicks.push_back(myKickPtr);
    

    for(int i=0; i < kicks.size(); i++) {
        drawInstrument(kicks.at(0), 100+(i*100), 100);
    }
    
   // drawBitch(kicks.at(0));
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
