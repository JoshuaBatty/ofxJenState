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
    gui = NULL;
}

GenModularUi::GenModularUi(vector<GenVar*> *_vars, vector<GenPack*> _genInputs){
    setup(_vars, _genInputs);
}


GenModularUi::~GenModularUi(){
    if (gui) {
        gui->saveSettings("genModUISettings.xml");
        delete gui;
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
    font.setup("Vera.ttf"); //load verdana font, set lineHeight to be 130%

    //GUI
    dim = 32;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
	
    gui = new ofxUISuperCanvas("GEN MODULAR", ofGetWidth()/2, 0, 450, ofGetHeight());
    gui->addWidgetDown(new ofxUIFPS(OFX_UI_FONT_MEDIUM));
    
    gui->setGlobalButtonDimension(24);
    gui->addSpacer();
    
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
    cout << totalNumOfCols << endl;
    for(int i=0; i < totalNumOfCols; i++){
        
        if(i == 0){
            gui->addWidgetDown( new ofxUISpacer(gui->getRect()->getWidth(), 110));
            gui->addWidgetDown( new ofxUISpacer(120, ofGetHeight()));

            gui->addWidgetRight(new ofxUIToggleMatrix(dim, dim, NUM_OF_GENINPUTS, 1, "Var" + ofToString(i+1)));
        } else {
            gui->addWidgetRight(new ofxUIToggleMatrix(dim, dim, NUM_OF_GENINPUTS, 1, "Var" + ofToString(i+1)));
        }
        

//        gui->addWidgetDown(new ofxUINumberDialer(-1.0, 100.0, 0.0, 1, "min" + ofToString(i+1), 100));

    //    gui->addWidgetDown(new ofxUINumberDialer("min" + ofToString(i+1), -1.0, 100.0, 1));
//        gui2->addNumberDialer("DIALER", -10000, 10000, 5000, 3);

        ofxUIToggleMatrix* mtx = (ofxUIToggleMatrix *) gui->getWidget("Var" + ofToString(i+1));
        mtx->setAllowMultiple(false);
    }


    
    ofAddListener(gui->newGUIEvent,this,&GenModularUi::guiEvent);
    
    gui->loadSettings("genModUISettings.xml");

}


//--------------------------------------------------------------
void GenModularUi::draw(){
    
    int fontSize = 16;
    int offset = 70;
    int offsetAmount = dim+2;
    int xPos = gui->getRect()->getX()+10;
    int yPos = gui->getRect()->getY();
    
   // cout << "yPos = " << yPos << endl;
   // cout << "xPos = " << xPos << endl;
    
	////////////////////// USER VARIABLES //////////////////////////
    
    offset = 0;
    
    for(int i=0; i < vars->size(); i++){
        string buf;
        
        if (vars->at(i)->bUseVolume) {
            buf = vars->at(i)->name + "V";
            ofSetColor(255);
            font.drawMultiLineColumn(buf, fontSize, xPos+130+offset, yPos+70, 1);
            offset += offsetAmount+4;
        }
        
        if (vars->at(i)->bUsePercentage) {
            buf = vars->at(i)->name + "P";
            //buf = vars->at(i)->address;
            ofSetColor(255);
            font.drawMultiLineColumn(buf, fontSize, xPos+130+offset, yPos+70, 1);
            offset += offsetAmount+4;
        }
        
        if (vars->at(i)->bUseIsPlaying) {
            buf = vars->at(i)->name + "Pl";
            //buf = vars->at(i)->address;
            ofSetColor(255);
            font.drawMultiLineColumn(buf, fontSize, xPos+130+offset, yPos+70, 1);
            offset += offsetAmount+4;
        }
        
        
    }
    
    ////////////////////// Position //////////////////////////

    offset = 70;
    offsetAmount = dim+3;
    xPos = gui->getRect()->getX()+10;
    yPos = gui->getRect()->getY();
    
	//string buf;
    string buf;
	buf = "Song Pos";
    ofSetColor(255);
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Part Pos:";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Segment Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Kick Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Snare Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Ride Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Ghost Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Kick Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Snare Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Ride Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Ghost Volume";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Bar Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Beat Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "Quaver Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
    buf = "SemiQ Pos";
    offset += offsetAmount;
	font.draw(buf,fontSize, xPos, yPos+offset+110);
    
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

