#pragma once

#include "ofMain.h"
#include "ofxJenOscState.h"

using namespace ofxJenOsc;

class ofApp : public ofBaseApp{
    
public:

    ofApp():
    myKick(Kick, "KICK", 1000)
    {}

	void setup();
	void update();
	void draw();
    
    void drawInstrument(const Instrument* instrument, int x, int y);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

    State jenState;
    
    Instrument myKick;

};
