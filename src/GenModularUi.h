//
//  GenModularUi.h
//  oscReceiveExample
//
//  Created by Joshua Batty on 28/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxFontStash.h"
#include "GenPack.h"
#include "GenVar.h"

#define NUM_OF_GENINPUTS 15

class GenModularUi{
public:

    GenModularUi();
    GenModularUi(vector<GenVar*> *_vars, vector<GenPack*> _genInputs);
    ~GenModularUi();
    
    void setup(vector<GenVar*> *_vars, vector<GenPack*> _genInputs);
    void draw();
    void update();
    
    //GUI
    ofxUISuperCanvas *guiModular;
    ofxUISuperCanvas *guiPresets;
    ofxUIDropDownList *ddl;
    ofxUITextInput *text;
    void guiEvent(ofxUIEventArgs &e);
    string newPresetName;
    float dim;
    int textOffsetHeight;
    int textOffsetWidth;
    
    //Presets
    void initXMLpreset();
    void saveXMLpreset();
    ofxXmlSettings XMLpresetNames;
    string xmlStructure;
    
    //COUNTS
    int numOfVolumes;
    int numOfPercentages;
    int numOfIsPlayings;
    int totalNumOfCols;
    
    //FONT STASH
    ofxFontStash font;
    
    //Variables
    
    vector<GenPack*> genInputs;
    vector<GenVar*> *vars;
    GenVar *genVar;
    GenPack *genIn;
    //, var2, var3, var4;
};