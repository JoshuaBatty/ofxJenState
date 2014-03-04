//
//  GenUIFollowActions.h
//  oscReceiveExample
//
//  Created by Joshua Batty on 4/03/14.
//
//


#pragma once

#include "ofMain.h"
#include "ofxClickDownMenu.h"

class GenUIFollowActions{
public:
   // GenUIFollowActions();
    
    void setup();
    void draw();
    
    //FOLLOW ACTIONS
    void setNextScene(int _scene, int _actionType);
    void triggerScene();
    
    
    /*-----ofxCDM objects----*/
	void cmdEvent(ofxCDMEvent &ev);
	ofxClickDownMenu menu;

    float val;
};