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
    
    GenVar(string _name = "", bool _useVol = false, bool _usePerc = false, bool _useIsPlaying = false, float _min = 0.0f, float _max = 1.0f);
    
    void setup(string _name, bool _useVol, bool _usePerc, bool _useIsPlaying, float _min, float _max);
    void setUsage(bool _useVol, bool _usePerc, bool _useIsPlaying);
    void setUseVolume(bool _useVol);
    void setUsePercentage(bool _usePerc);
    void setUseIsPlaying(bool _useIsPlaying);
    void setRange(float _min, float _max);
    
    float getVolume();
    float getPercentage();
    bool getIsPlaying();
    
    string name;
    float *volume;
    float *percentage;
    bool *isPlaying;
    
    float min;
    float max;
    
    bool bUseVolume;
    bool bUsePercentage;
    bool bUseIsPlaying;
    
    int volID;
    int percID;
    int playID;
    
};
