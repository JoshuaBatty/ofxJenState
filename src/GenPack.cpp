//
//  GenPack.cpp
//  oscReceiveExample
//
//  Created by Joshua Batty on 28/02/14.
//
//

#include "GenPack.h"

//--------------------------------------------------------------
GenPack::GenPack(string _address){
    address = _address;
    bPlaying = false;
    getPercentage = 0.0;
    getVolume = 0.0;

    bUseVolume = false;
    bUsePercentage = false;
    bUseIsPlaying = false;
    
    volumeID = -1;
    percentageID = -1;
    isPlayingID = -1;
}

//--------------------------------------------------------------
void GenPack::drawPosition(int _x, int _y){
    
	float barWidth = 180;
    float barHeight = 8;
    
	ofSetColor(255);

    // the background to the progress bar
    ofSetColor(100);
    ofFill();
    ofRect(_x,_y, barWidth, barHeight);
    
	// get the percantage of the timer
    float pct = getPercentage;
    ofSetHexColor(0xf02589);
    ofRect(_x,_y, barWidth*pct, barHeight);
    
    ofSetColor(255);
}

//--------------------------------------------------------------
void GenPack::drawVolume(int _x, int _y){
    
	float barWidth = 180;
    float barHeight = 8;
    
	ofSetColor(255);
    
    // the background to the progress bar
    ofSetColor(100);
    ofFill();
    ofRect(_x,_y, barWidth, barHeight);
    
	// get the percantage of the timer
    float pct = getVolume;
    ofSetColor(0,255,200);
    ofRect(_x,_y, barWidth*pct, barHeight);
    
    ofSetColor(255);
}

//--------------------------------------------------------------
void GenPack::setUseVolume(bool _useVol)
{
    bUseVolume = _useVol;
}

void GenPack::setUsePercentage(bool _usePerc)
{
    bUsePercentage = _usePerc;
}

void GenPack::setUseIsPlaying(bool _useIsPlaying)
{
    bUseIsPlaying = _useIsPlaying;
}

//--------------------------------------------------------------


//--------------------------------------------------------------


//--------------------------------------------------------------


//--------------------------------------------------------------