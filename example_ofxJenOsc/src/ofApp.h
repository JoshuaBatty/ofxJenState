#pragma once

#include "ofMain.h"
#include "ofxJenState.h"

using namespace ofxJenState;

class ofApp : public ofBaseApp{
    
public:

    ofApp():
    myKick(Kick, "KICK", 10000)
    {}

	void setup();
	void update();
	void draw();
    
    void drawInstrumentsInfo(vector<const Instrument*> instruments);
    void drawInstrument(const Instrument* instrument, int x, int y);
    
    void drawPlayheads(int x, int y);

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
    Measure myDurations;
};
