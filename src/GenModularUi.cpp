//
//  GenModularUi.cpp
//  oscReceiveExample
//
//  Created by Joshua Batty on 28/02/14.
//
//

#include "GenModularUi.h"

//--------------------------------------------------------------

GenModularUi::GenModularUi(){
    guiModular = NULL;
    guiPresets = NULL;
}

GenModularUi::GenModularUi(vector<GenVar*> *_vars, vector<GenPack*> _genInputs){
    setup(_vars, _genInputs);
}


GenModularUi::~GenModularUi(){
    if (guiModular) {
        guiModular->saveSettings("GUI/Modular/genModUISettings.xml");
        delete guiModular;
    }
    if(guiPresets){
        guiPresets->saveSettings("GUI/Presets/genPresetUISettings.xml");
        delete guiPresets;
    }
}


//--------------------------------------------------------------
void GenModularUi::setup(vector<GenVar*> *_vars, vector<GenPack*> _genInputs){

    vars = _vars;
    genInputs = _genInputs;
    
    numOfVolumes = 0;
    numOfPercentages = 0;
    numOfIsPlayings = 0;
    totalNumOfCols = 0;
    
    //FONT
//    font.setup("Vera.ttf"); //load verdana font, set lineHeight to be 130%
    font.setup("BebasNeue.ttf");
    
    for (int i = 0; i < vars->size(); i++) {
        if (vars->at(i)->bUseVolume == true) {
            vars->at(i)->volID = totalNumOfCols;
            cout << vars->at(i)->name << " | VolID = " << vars->at(i)->volID << endl;
            totalNumOfCols++;
        }
        if (vars->at(i)->bUsePercentage == true) {
            vars->at(i)->percID = totalNumOfCols;
            cout << vars->at(i)->name << " | PercID = " << vars->at(i)->percID << endl;
            totalNumOfCols++;
        }
        if (vars->at(i)->bUseIsPlaying == true) {
            vars->at(i)->playID = totalNumOfCols;
            cout << vars->at(i)->name << " | PlayID = " << vars->at(i)->playID << endl;
            totalNumOfCols++;
        }
    }
    
    //GUI
    textOffsetWidth = 110;
    textOffsetHeight = 130;
    dim = 42;
    newPresetName = "INIT";
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////// MODULAR /////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    guiModular = new ofxUISuperCanvas("GEN MODULAR", ofGetWidth()/2, 0, textOffsetWidth + ((totalNumOfCols+1) * dim), ofGetHeight());
    guiModular->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_MEDIUM));
    
    guiModular->setGlobalButtonDimension(dim);
    guiModular->addSpacer();
    
    cout << totalNumOfCols << endl;
    for(int i=0; i < totalNumOfCols; i++){
        
        if(i == 0){
            guiModular->addWidgetDown( new ofxUISpacer(guiModular->getRect()->getWidth(), textOffsetHeight));
            guiModular->addWidgetDown( new ofxUISpacer(textOffsetWidth, ofGetHeight()));

            guiModular->addWidgetRight(new ofxUIToggleMatrix(dim, dim, NUM_OF_GENINPUTS, 1, "Var" + ofToString(i+1)));
        } else {
            guiModular->addWidgetRight(new ofxUIToggleMatrix(dim, dim, NUM_OF_GENINPUTS, 1, "Var" + ofToString(i+1)));
        }
        ofxUIToggleMatrix* mtx = (ofxUIToggleMatrix *) guiModular->getWidget("Var" + ofToString(i+1));
        mtx->setAllowMultiple(false);
    }
    
    // MINIMUM UI's
    for(int i=0; i < totalNumOfCols; i++){
        if(i == 0){
            guiModular->addWidgetDown( new ofxUISpacer(textOffsetWidth, ofGetHeight()));
            guiModular->addWidgetRight(new ofxUITextInput("min" + ofToString(i+1), "0.0", dim));
        } else {
            guiModular->addWidgetRight(new ofxUITextInput("min" + ofToString(i+1), "0.0", dim));
        }
    }
    // MAXIMUM UI's
    for(int i=0; i < totalNumOfCols; i++){
        if(i == 0){
            guiModular->addWidgetDown( new ofxUISpacer(textOffsetWidth, ofGetHeight()));
            guiModular->addWidgetRight(new ofxUITextInput("max" + ofToString(i+1), "1.0", dim));
        } else {
            guiModular->addWidgetRight(new ofxUITextInput("max" + ofToString(i+1), "1.0", dim));
        }
    }

    guiModular->addSpacer();

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////// PRESETS /////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    guiPresets = new ofxUISuperCanvas("MODULAR PRESETS", ofGetWidth()/2, 0, textOffsetWidth + ((totalNumOfCols+1) * dim), ofGetHeight());
    
    guiPresets->addSpacer();
    

    //text = guiPresets->addTextInput("Preset Name", "enter new preset name");
    text = dynamic_cast<ofxUITextInput*>(guiPresets->addWidgetDown(new ofxUITextInput("Preset Name", "enter new preset name", 200)));
    guiPresets->addWidgetRight(new ofxUIButton("Store", false, 30,18));
    guiPresets->addWidgetDown(new ofxUIButton("Load", false, 115, 18));
    guiPresets->addWidgetRight(new ofxUIButton("Delete", false, 115, 18));
    
    //Drop Down
    vector<string> names;
    names.push_back("INIT"); names.push_back("CUNT");
//    guiPresets->addWidgetDown(new ofxUIDropDownList("PRESETS", names));
    ddl = guiPresets->addDropDownList("PRESETS", names);
    ddl->setAllowMultiple(false);
    
    ofAddListener(guiModular->newGUIEvent,this,&GenModularUi::guiEvent);
    ofAddListener(guiPresets->newGUIEvent,this,&GenModularUi::guiEvent);
    
    guiModular->loadSettings("GUI/Modular/genModUISettings.xml");
    guiPresets->loadSettings("GUI/Presets/genPresetUISettings.xml");

}


//--------------------------------------------------------------
void GenModularUi::draw(){
    
    int fontSize = 22;//16;
    int offset = 70;
    int textOffsetWidth = 125;
    int offsetAmount = dim+2;
    int xPos = guiModular->getRect()->getX()+10;
    int yPos = guiModular->getRect()->getY();
    
   // cout << "yPos = " << yPos << endl;
   // cout << "xPos = " << xPos << endl;
    
	////////////////////// USER VARIABLES //////////////////////////
    
    offset = 0;
    
    for(int i=0; i < vars->size(); i++){
        string buf;
        
        if (vars->at(i)->bUseVolume) {
            buf = vars->at(i)->name + "V";
            ofSetColor(255);
            font.drawMultiLineColumn(buf, fontSize, xPos+textOffsetWidth+offset, yPos+70, 1);
            offset += offsetAmount+4;
        }
        
        if (vars->at(i)->bUsePercentage) {
            buf = vars->at(i)->name + "P";
            //buf = vars->at(i)->address;
            ofSetColor(255);
            font.drawMultiLineColumn(buf, fontSize, xPos+textOffsetWidth+offset, yPos+70, 1);
            offset += offsetAmount+4;
        }
        
        if (vars->at(i)->bUseIsPlaying) {
            buf = vars->at(i)->name + "Pl";
            //buf = vars->at(i)->address;
            ofSetColor(255);
            font.drawMultiLineColumn(buf, fontSize, xPos+textOffsetWidth+offset, yPos+70, 1);
            offset += offsetAmount+4;
        }
        
        
    }
    
    ////////////////////// Position //////////////////////////

    offset = 70;
    offsetAmount = dim+3;
    xPos = guiModular->getRect()->getX()+10;
    yPos = guiModular->getRect()->getY();
    
	//string buf;
    string buf;
	buf = "Song Pos";
    ofSetColor(255);
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Part Pos:";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Segment Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Bar Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Beat Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Quaver Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "SemiQ Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Kick Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Snare Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Ride Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Ghost Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Kick Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Snare Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Ride Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "Ghost Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+textOffsetHeight);
    
    buf = "MIN";
    offset += offsetAmount-14;
	font.draw(buf,fontSize, xPos+50, yPos+offset+textOffsetHeight);
    
    buf = "MAX";
    offset += offsetAmount-23;
	font.draw(buf,fontSize, xPos+50, yPos+offset+textOffsetHeight);
    
}



//--------------------------------------------------------------
void GenModularUi::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();

    /* cout << genVar->name << " - " << genIn->address << endl;
    cout << "i = " << i << " | j = " << j << " | x = " << x << " | y = " << y << endl;
    cout << " | GenVar VolID = " << genVar->volID << " | x = " << x << endl;
    cout << " | GenVar PercID = " << genVar->percID << " | x = " << x << endl;
    cout << " | GenVar PlayID = " << genVar->playID << " | x = " << x << endl;
    cout << " | GenInp VolID = " << genIn->volumeID << " | y = " << y << endl;
    cout << " | GenInp PercID = " << genIn->percentageID << " | y = " << y << endl;
    cout << " | GenInp PlayID = " << genIn->isPlayingID << " | y = " << y << endl; */
    
    //PRESET LOADING AND SAVING
    if(name == "Preset Name"){
        ofxUITextInput *t = (ofxUITextInput *) e.widget;
        newPresetName = t->getTextString();
    }
    else if(name == "Store"){
        ofxUIButton *b = (ofxUIButton *) e.widget;
        
        bool overwrite = false;
        if(b->getValue() == 1){
            for(int i = 0; i < ddl->getToggles().size(); i++){
                if(text->getTextString() == ddl->getToggles()[i]->getName()){
                    overwrite = true;
                }
                    
            }
            if (overwrite) {
                // OVERWRITE HERE
            } else {
                ddl->addToggle(newPresetName);
            }
        }
    }
    /*
    else if(name == "Load"){
        ofxUIButton *b = (ofxUIButton *) e.widget;
        if(b->getValue() == 1){
            ddl->addToggle(newPresetName);
        }
    }
    */
    else if(name == "Delete"){
        ofxUIButton *b = (ofxUIButton *) e.widget;
        if(b->getValue() == 1){
            cout << "sick" << endl;
            for(int i = 0; i < ddl->getToggles().size(); i++){
                if(text->getTextString() == ddl->getToggles()[i]->getName()){
                    ddl->removeToggle(ddl->getToggles()[i]->getName());
                }
            }
            
        }
    }

    else if(name == "PRESETS"){
        vector<ofxUIWidget *> &selected = ddl->getSelected();
        for(int i = 0; i < selected.size(); i++)
        {
            cout << "SELECTED: " << selected[i]->getName() << endl;
            text->setTextString(selected[i]->getName());
        }
    }
    
    
    //MINIMUM AND MAXIMUM INPUTS
    for(int i=0; i < totalNumOfCols; i++){
        if(name == "min" + ofToString(i+1)){
            ofxUITextInput *t = (ofxUITextInput *) e.widget;
            float min = ofToFloat(t->getTextString());
            
            for (int j=0; j < vars->size(); j++) {
                if (vars->at(j)->volID == i) {
                    vars->at(j)->setMin(min);
                }
                else if (vars->at(j)->percID == i) {
                    vars->at(j)->setMin(min);
                }
                else if (vars->at(j)->playID == i) {
                    vars->at(j)->setMin(min);
                }
            }
            
            
            cout << "min val" + ofToString(i) + " = " << min << endl;
        }
        if(name == "max" + ofToString(i+1)){
            ofxUITextInput *t = (ofxUITextInput *) e.widget;
            float max = ofToFloat(t->getTextString());
            
            for (int j=0; j < vars->size(); j++) {
                if (vars->at(j)->volID == i) {
                    vars->at(j)->setMax(max);
                }
                else if (vars->at(j)->percID == i) {
                    vars->at(j)->setMax(max);
                }
                else if (vars->at(j)->playID == i) {
                    vars->at(j)->setMax(max);
                }
            }
            
            cout << "max val" + ofToString(i) + " = " << max << endl;
        }
    }
    
        
    for(int x = 0; x < totalNumOfCols; x++){
        for(int y=0; y < NUM_OF_GENINPUTS; y++){
            if(name == "Var" + ofToString(x+1) + "(" + ofToString(0) + "," + ofToString(y) + ")")
            {
                cout << name << " | x = " << x << " | y = " << y << endl;
                
                for (int i=0; i < vars->size(); i++) {
                    genVar = vars->at(i);
                    cout << "vars at i = " << genVar->name << " | volID = " << genVar->volID << " | percID = " << genVar->percID << " | playID = " << genVar->playID << endl;
                    
                    for (int j=0; j < genInputs.size(); j++) {
                        genIn = genInputs[j];
                        
                        if (x == genVar->volID && y == genIn->volumeID) {
                            genVar->volume = &genIn->getVolume;
                            cout << genVar->name << " -> " << genIn->address << endl;
                        }
                        else if (x == genVar->volID && y == genIn->percentageID) {
                            genVar->volume = &genIn->getPercentage;
                            cout << genVar->name << " -> " << genIn->address << endl;
                        }
                        
                        else if (x == genVar->percID && y == genIn->volumeID) {
                            genVar->percentage = &genIn->getVolume;
                            cout << genVar->name << " -> " << genIn->address << endl;
                        }
                        else if (x == genVar->percID && y == genIn->percentageID){
                            genVar->percentage = &genIn->getPercentage;
                            cout << genVar->name << " -> " << genIn->address << endl;
                        }
                        
                        else if (x == genVar->playID && y == genIn->isPlayingID) {
                            genVar->isPlaying = &genIn->bPlaying;
                            cout << genVar->name << " -> " << genIn->address << endl;
                        }
                        
                    }
                    
                }
                
            }
        }
    }
    
}

