//
//  GenVar.cpp
//  oscReceiveExample
//
//  Created by Joshua Batty on 2/03/14.
//
//

#include "GenVar.h"

//--------------------------------------------------------------
GenVar::GenVar(string _name, bool _useVol, bool _usePerc, bool _useIsPlaying, float _min, float _max)
{
    volume = NULL;
    percentage = NULL;
    isPlaying = NULL;
    volID = -1;
    percID = -1;
    playID = -1;
    setup(_name, _useVol, _usePerc, _useIsPlaying, _min, _max);
}

//--------------------------------------------------------------

void GenVar::setup(string _name, bool _useVol, bool _usePerc, bool _useIsPlaying, float _min, float _max)
{
    name = _name;
    setUsage(_useVol, _usePerc, _useIsPlaying);
    setRange(_min, _max);
}

//--------------------------------------------------------------

void GenVar::setUsage(bool _useVol, bool _usePerc, bool _useIsPlaying)
{
    bUseVolume = _useVol;
    bUsePercentage = _usePerc;
    bUseIsPlaying = _useIsPlaying;
}

//--------------------------------------------------------------

void GenVar::setUseVolume(bool _useVol)
{
    bUseVolume = _useVol;
}

void GenVar::setUsePercentage(bool _usePerc)
{
    bUsePercentage = _usePerc;
}

void GenVar::setUseIsPlaying(bool _useIsPlaying)
{
    bUseIsPlaying = _useIsPlaying;
}

//--------------------------------------------------------------

float GenVar::getVolume()
{
    return ofMap(*volume, 0.0f, 1.0f, min, max);
}

float GenVar::getPercentage()
{
    return ofMap(*percentage, 0.0f, 1.0f, min, max);
}

//--------------------------------------------------------------

void GenVar::setRange(float _min, float _max)
{
    min = _min;
    max = _max;
}

//--------------------------------------------------------------

void GenVar::setMin(float _min)
{
    min = _min;
}

//--------------------------------------------------------------

void GenVar::setMax(float _max)
{
    max = _max;
}

//--------------------------------------------------------------



//--------------------------------------------------------------