//
//  GenVar.h
//  oscReceiveExample
//
//  Created by Joshua Batty on 2/03/14.
//
//

#pragma once

#include "ofMain.h"


class GenVar{
public:
    
    GenVar(string _name = "", bool _useVol = false, bool _usePerc = false, bool _useIsPlaying = false);
    
    void setup(string _name, bool _useVol, bool _usePerc, bool _useIsPlaying);
    void setUsage(bool _useVol, bool _usePerc, bool _useIsPlaying);
    void setUseVolume(bool _useVol);
    void setUsePercentage(bool _usePerc);
    void setUseIsPlaying(bool _useIsPlaying);
    
    string name;
    float *volume;
    float *percentage;
    bool *isPlaying;
    
    bool bUseVolume;
    bool bUsePercentage;
    bool bUseIsPlaying;
    
    int volID;
    int percID;
    int playID;
    
};
