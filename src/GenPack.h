//
//  GenPack.h
//  oscReceiveExample
//
//  Created by Joshua Batty on 28/02/14.
//
//

#pragma once

#include "ofMain.h"


class GenPack{
public:
    GenPack(string _address = "");

    void drawPosition(int _x, int _y);
    void drawVolume(int _x, int _y);
    
    void setUseVolume(bool _useVol);
    void setUsePercentage(bool _usePerc);
    void setUseIsPlaying(bool _useIsPlaying);
    
    float getVolume;
    float getPercentage;
    bool bPlaying;
    
    bool bUseVolume;
    bool bUsePercentage;
    bool bUseIsPlaying;
    
    int volumeID;
    int percentageID;
    int isPlayingID;

    string address;
};