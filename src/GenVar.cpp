//
//  GenVar.cpp
//  oscReceiveExample
//
//  Created by Joshua Batty on 2/03/14.
//
//

#include "GenVar.h"

//--------------------------------------------------------------
GenVar::GenVar(string _name, bool _useVol, bool _usePerc, bool _useIsPlaying)
{
    volume = NULL;
    percentage = NULL;
    isPlaying = NULL;
    volID = -1;
    percID = -1;
    playID = -1;
    setup(_name, _useVol, _usePerc, _useIsPlaying);
}

//--------------------------------------------------------------

void GenVar::setup(string _name, bool _useVol, bool _usePerc, bool _useIsPlaying)
{
    name = _name;
    setUsage(_useVol, _usePerc, _useIsPlaying);
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



//--------------------------------------------------------------



//--------------------------------------------------------------



//--------------------------------------------------------------



//--------------------------------------------------------------



//--------------------------------------------------------------