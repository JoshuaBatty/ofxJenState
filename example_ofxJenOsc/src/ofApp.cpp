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
void ofApp::drawInstrumentsInfo(vector<const Instrument*> instruments){
    int totalNumInstrumentsInSong = instruments.size();
}

//--------------------------------------------------------------
void ofApp::drawInstrument(const Instrument* instrument, int x, int y){
    int w = 150; // Width of module UI
    int h = 105; // Height of module UI
    
    int uvWidth = 130; // Width of UV meter
    int uvHeight = 20; // Height of UV meter
    
    ofColor uvBgColor = ofColor(ofColor::lightGoldenRodYellow);
    ofColor uvBarColor = ofColor(10, 250, 25);
    
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
    
    ofSetColor(uvBarColor);
    ofRect(x+10, y+30, amp * uvWidth, uvHeight);
    
    ofSetColor(0);
    ofDrawBitmapString("Volume", x+(uvWidth/2)-8, y+45);
    
    //------------------------------------------------ Draw a percentage meter
    ofSetColor(uvBgColor);
    ofRect(x+10, y+55, uvWidth, uvHeight);
    
    ofSetColor(uvBarColor);
    ofRect(x+10, y+55, percenatge * uvWidth, uvHeight);
    
    ofSetColor(0);
    ofDrawBitmapString("Perc", x+(uvWidth/2), y+70);
    
    //------------------------------------------------ Draw a pan position meter
    ofSetColor(uvBgColor);
    ofRect(x+10, y+80, uvWidth, uvHeight);
    
    ofSetColor(uvBarColor);
    ofRect(x+10, y+80, ofMap(pan,0.0,1.0,-(uvWidth/2),uvWidth/2), uvHeight);

    ofSetColor(0);
    ofDrawBitmapString("Pan", x+(uvWidth/2)+3, y+95);
}

//--------------------------------------------------------------
void ofApp::drawPlayheads(int x, int y){
    int w = 150; // Width of module UI
    int h = 235; // Height of module UI
    
    int uvWidth = 130; // Width of UV meter
    int uvHeight = 20; // Height of UV meter
    
    int initOffset = 33;
    int offsetMultiplier = 25;
    
    ofColor uvBgColor = ofColor(ofColor::lightGoldenRodYellow);
    ofColor uvBarColor = ofColor(10, 250, 25);
    
    string name;
    float time = ofGetElapsedTimef()*0.1;

    vector<string> playheads;
    playheads.push_back("Song");
    playheads.push_back("Part");
    playheads.push_back("Segment");
    playheads.push_back("Bar");
    playheads.push_back("Minim");
    playheads.push_back("Beat");
    playheads.push_back("Quaver");
    playheads.push_back("SemiQuaver");
    playheads.push_back("TotalMeasures");

    // Draw a rectangular UI
    ofSetColor(255,100,0);
    ofNoFill();
    ofRect(x,y,w,h);
    ofFill();
    
    // Print the name of the Instrument
    ofSetColor(255);
    ofDrawBitmapString("PLAYHEADS", x+(uvWidth/2)-25, y+17);
    
    //------------------------------------------------ Draw a spacer
    ofSetColor(255,100,0);
    ofLine(x, y+25, x+w, y+25);
    
    for(int i = 0; i < jenState.getPlayheads().size(); i++){
        ofSetColor(uvBgColor);
        ofRect(x+10, y+initOffset+(offsetMultiplier*i), uvWidth, uvHeight);
        
        ofSetColor(uvBarColor);
        ofRect(x+10, y+initOffset+(offsetMultiplier*i), fmod(uvWidth * (time*(1+pow(i,2.0))),uvWidth), uvHeight);

        ofSetColor(0);
        ofDrawBitmapString(playheads[i], x+35, y+(initOffset+15)+(offsetMultiplier*i));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor::black, ofColor::white, OF_GRADIENT_LINEAR);

    vector<const Instrument*> kicks;
    myKick.pan = 1.0+sin(ofGetElapsedTimef())*0.5;
    myKick.amp = 0.9;
    const Instrument* myKickPtr = &myKick;
    kicks.push_back(myKickPtr);
    

    for(int i=0; i < kicks.size(); i++) {
        drawInstrument(kicks.at(0), 100+(i*100), 100);
    }
    
    drawPlayheads(400, 100);
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
