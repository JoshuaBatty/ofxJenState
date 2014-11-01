#pragma once

#include "ofMain.h"
#include "OscReceiveGen.h"

class ofApp : public ofBaseApp{
    
	public:
    
    ofApp()
    : speed("Speed")
    , cunt("Cunt")
    , ae("ae") {}

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	 
        vector<GenVar*> vars;
        
        GenVar speed;
        GenVar cunt;
        GenVar ae;
        
        float myVar;
        
        OscReceiveGen oscGen;	
};
