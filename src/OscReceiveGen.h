//
//  OscReceiveGen.h
//  oscReceiveExample
//
//  Created by Joshua Batty on 28/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "GenPack.h"
#include "GenModularUi.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 33

#define SIZE 0
#define SPEED 1
#define CAMX 2
#define CAMY 3
#define STROBE 4

class OscReceiveGen{
public:
    
    OscReceiveGen();
    
    void setup(vector<GenVar*> _vars);
    void update();
    void draw();
    

    void gotMessage(ofMessage msg);
    
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    int totalNumOfInputs;
    
    //Song percentage, Note, Part
    //PART
    GenPack genPart;
    
    //SEGMENT
    GenPack genSegment;
    
        //* Kick  *//
        GenPack genKick;
    
        //* Snare *//
        GenPack genSnare;

        //* Ride  *//
        GenPack genRide;
    
        //* Ghost *//
        GenPack genGhost;

    //SONG
    GenPack genSong;
    
    //DIVISIONS
    GenPack genBar; //Bar
    GenPack genBeat; //Beat
    GenPack genSemiQ; //SemiQ
    GenPack genQuaver; //Quaver
    


    vector<GenPack*> genInputs;
    vector<GenVar*> vars;
    
    //GUI
    GenModularUi genModUI;
};
