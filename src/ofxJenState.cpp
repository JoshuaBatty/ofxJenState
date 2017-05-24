 //
//  ofxJenOscState.cpp
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#include "ofxJenState.h"

using namespace ofxJenState;



void State::update() {

    // Pull in new messages from OSC
    update_osc();
}


//--------------------------------------------------------------
//--------------------------------------------------------------
vector<Modulator*> State::getChildren() {
    vector<Modulator*> children;
    children.reserve(5);
    
    children.push_back((Modulator*)&instruments);
    children.push_back((Modulator*)&playhead_bangs);
    children.push_back((Modulator*)&playhead_positions);
    children.push_back((Modulator*)&busses);
    children.push_back((Modulator*)&master);
    
    return children;
}

vector<Modulator*> Instruments::getChildren(){
    vector<Modulator*> children;
    children.reserve(instruments.size());
    
    for (int i=0; i < instruments.size(); i++) {
        children.push_back((Modulator*)&instruments[i]);
    }
    
    return children;
}

vector<Modulator*> Busses::getChildren(){
    vector<Modulator*> children;
    children.reserve(busses.size());
    
    for (int i=0; i < busses.size(); i++) {
        children.push_back((Modulator*)&busses[i]);
    }
    
    return children;
}

//--------------------------------------------------------------
void State::update_osc(){
    
    // Clear our note on mappings
    for(int i = 0; i < instruments.instruments.size(); i++){
        instruments.instruments[i].params[InstrumentParam::NOTE_ON] = 0.0;
    }
    for(int i = 0; i < playhead_bangs.params.size(); i++){
        playhead_bangs.params[i] = 0.0;
    }
    
    // check for waiting messages
    while(osc.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        osc.getNextMessage(m);
        
        if (m.getAddress() != "/jen") {
            continue;
        }
        
        int mode = 0;
        const int note_on = 100;
        const int playhead_bang = 101;
        const int playhead_position = 102;
        
        for (int i=0; i < m.getNumArgs(); i++) {
            
            switch (m.getArgType(i)) {
                case OFXOSC_TYPE_INT32: {
                    int s = m.getArgAsInt(i);
                    
                    // First check if the argument is a mode change.
                    if (s == note_on) {
                        mode = note_on;
                        continue;
                    } else if (s == playhead_bang) {
                        mode = playhead_bang;
                        continue;
                    } else if (s == playhead_position) {
                        mode = playhead_position;
                        playhead_positions.params.clear();
                        continue;
                    }
                    
                    // If we're in note on mode, assume all strings are bangs.
                    if (mode == note_on) {
                        instruments.instruments[s].params[InstrumentParam::NOTE_ON] = 1.0;
                    }
                    if(mode == playhead_bang){
                        playhead_bangs.params[s] = 1.0;
                    }

                    
                    break;
                }
                case OFXOSC_TYPE_FLOAT: {
                    float s = m.getArgAsFloat(i);
                    if(mode == playhead_position){
                        playhead_positions.params.push_back(s);
                    }
                }
                default: break;
                    
                    
            }
        }
    }
}




