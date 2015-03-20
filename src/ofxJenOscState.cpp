//
//  ofxJenOscState.cpp
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#include "ofxJenOscState.h"

using namespace ofxJenOsc;

double Playhead::percentage() const{
    if (durationInTicks > 0) {
        return (double)positionInTicks / (double)durationInTicks;
    } else {
        return 0.0;
    }
}

void State::update() {
	while(oscReceiver.hasWaitingMessages()){
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
        
        // Use messages to update current state here...

    }
}

const Playhead* State::getPlayhead(Measure measure) {
    const Playhead* playhead = &playheads[measure];
    return playhead;
}

vector<const Playhead*> State::getPlayheads() {
    vector<const Playhead*> vec;
    vec.reserve(playheads.size());
    for (int i = 0; i < playheads.size(); i++) {
        const Playhead* playhead = &playheads[i];
        vec.push_back(playhead);
    }
    return vec;
}

vector<const Rhythm*> State::getRhythms() {
    vector<const Rhythm*> vec;
    vec.reserve(rhythms.size());
    for (int i = 0; i < rhythms.size(); i++) {
        const Rhythm* rhythm = &rhythms[i];
        vec.push_back(rhythm);
    }
    return vec;
}

vector<const Rhythm*> State::getRhythmsOfType(RhythmType type) {
    vector<const Rhythm*> vec;
    vec.reserve(rhythms.size());
    for (int i = 0; i < rhythms.size(); i++) {
        if (rhythms[i].type == type) {
            const Rhythm* rhythm = &rhythms[i];
            vec.push_back(rhythm);
        }
    }
    return vec;
}

vector<const Instrument*> State::getInstruments() {
    vector<const Instrument*> vec;
    vec.reserve(instruments.size());
    for (int i = 0; i < instruments.size(); i++) {
        const Instrument* instrument = &instruments[i];
        vec.push_back(instrument);
    }
    return vec;
}

vector<const Instrument*> State::getInstrumentsOfType(RhythmType type) {
    vector<const Instrument*> vec;
    vec.reserve(instruments.size());
    for (int i = 0; i < instruments.size(); i++) {
        if (instruments[i].type == type) {
            const Instrument* instrument = &instruments[i];
            vec.push_back(instrument);
        }
    }
    return vec;
}