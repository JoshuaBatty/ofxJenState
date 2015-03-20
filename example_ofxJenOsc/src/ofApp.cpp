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
void drawInstrument(const Instrument* instrument, int x, int y){
    int w = 150; // Width of module UI
    int h = 100; // Height of module UI
    
    int uvWidth = 120; // Width of UV meter
    int uvHeight = 30; // Height of UV meter
    
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
    ofSetColor(255,90,0);
    ofRect(x,y,w,h);
    
    // Print the name of the Instrument
    ofSetColor(255);
    ofDrawBitmapString(name, x + (x-w)/2, y+10);
    
    //------------------------------------------------ Draw a spacer
    ofSetColor(100, 40, 190);
    ofLine(x, y+15, w, y+15);
    
    // Draw an amplitude meter
    ofSetColor(255);
    ofDrawBitmapString("Volume", x+10, y+35);
    
    ofSetColor(40, 50, 255);
    ofRect(x+20, y+40, uvWidth, uvHeight);
    
    ofSetColor(10, 250, 25);
    ofRect(x+20, y+40, amp * uvWidth, uvHeight);
    
    //------------------------------------------------ Draw a spacer
    ofSetColor(100, 40, 190);
    ofLine(x, y+75, w, y+75);
    
    // Draw a percentage meter
    ofSetColor(255);
    ofDrawBitmapString("Perc", x+10, y+95);
    
    ofSetColor(40, 50, 255);
    ofRect(x+20, y+100, uvWidth, uvHeight);
    
    ofSetColor(10, 250, 25);
    ofRect(x+20, y+100, percenatge * uvWidth, uvHeight);
    
    //------------------------------------------------ Draw a spacer
    ofSetColor(100, 40, 190);
    ofLine(x, y+115, w, y+115);
    
    // Draw a pan position meter
    ofSetColor(255);
    ofDrawBitmapString("Pan", x+10, y+125);
    
    ofSetColor(40, 50, 255);
    ofRect(x+20, y+125, uvWidth, uvHeight);
    
    ofSetColor(10, 250, 25);
    ofRect(x+20, y+125, ofMap(pan,0.0,1.0,-(uvWidth/2),uvWidth/2), uvHeight);
}

//--------------------------------------------------------------
void ofApp::draw(){

    vector<const Instrument*> kicks;

   // Instrument myKick = Instrument(Kick, "KICK", 1000);
    myKick.pan = 0.0;
    myKick.amp = 0.9;
    const Instrument myACTUALKick = myKick;
    const Instrument* myKickPtr = &myACTUALKick;
    
    //kicks.push_back(myKickPtr);
    

    for(int i=0; i < kicks.size(); i++) {
        drawInstrument(kicks.at(0), 100+(10*100), 100);
    }
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
