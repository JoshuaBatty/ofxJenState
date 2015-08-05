//
//  ofxJenOscState.cpp
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#include "ofxJenState.h"

using namespace ofxJenState;


float parsePlayhead(string s) {
    int semicolon = s.find(":");
    string number = s.substr(semicolon + 2, s.size()-1);
    return ofToFloat(number);
}

void State::update() {

    // Check for new received string.
    if (!receiver.hasUpdated) {
        //return;
    }
    
    string sampleState = "StateView { playhead: PlayheadState { tick_count: 1060530, phrase_perc: 0.9863560267857143, segment_perc: 0.9727120535714285, bar_perc: 0.7816964285714286, minim_perc: 0.490625, beat_perc: 0.7359375, quaver_perc: 0.471875, semi_quaver_perc: 0.94375, time_sig: TimeSig { top: 7, bottom: 8 }, bpm: 131 }, dsp: DspState { instruments: {Melodic: (0.0456732, 0)}, busses: {}, master: (0.1376343, 0) } }";
    
    
    cout << sampleState << endl << endl;
    
    vector<string> jenStates;
    
    int offsets[] = {38,212,53,200};
    offset_separator f(offsets, offsets+4);
    tokenizer<offset_separator> tok(sampleState,f);
    for(tokenizer<offset_separator>::iterator beg=tok.begin(); beg!=tok.end();++beg){
        cout << *beg << "\n";
        jenStates.push_back(*beg);
    }
    
    int tick_count_pos = 0;
    int phrase_perc_pos = jenStates[1].find(", phrase_perc: ");
    int segment_perc_pos = jenStates[1].find(", segment_perc: ");
    int bar_perc_pos = jenStates[1].find(", bar_perc: ");
    int minim_perc_pos = jenStates[1].find(", minim_perc: ");
    int beat_perc_pos = jenStates[1].find(", beat_perc: ");
    int quaver_perc_pos = jenStates[1].find(", quaver_perc: ");
    int semi_quaver_perc_pos = jenStates[1].find(", semi_quaver_perc: ");

    playheads[Phrase] = parsePlayhead(jenStates[1].substr(phrase_perc_pos, segment_perc_pos));
    playheads[Segment] = parsePlayhead(jenStates[1].substr(segment_perc_pos, bar_perc_pos));
    playheads[Bar] = parsePlayhead(jenStates[1].substr(bar_perc_pos, minim_perc_pos));
    playheads[Minim] = parsePlayhead(jenStates[1].substr(minim_perc_pos, beat_perc_pos));
    playheads[Beat] = parsePlayhead(jenStates[1].substr(beat_perc_pos, quaver_perc_pos));
    playheads[Quaver] = parsePlayhead(jenStates[1].substr(quaver_perc_pos, semi_quaver_perc_pos));
    playheads[SemiQuaver] = parsePlayhead(jenStates[1].substr(semi_quaver_perc_pos, jenStates[1].size()-2));
    
    for (int i=0; i < TotalMeasures; i++) {
        cout << i << ": " << playheads[i] << endl;
    }

  
//    typedef tokenizer<boost::char_separator<char> > tokenizer;
//    char_separator<char> sep(",", ",", keep_empty_tokens);
//    //    char_separator<char> sep(" ", ":,", keep_empty_tokens);
//    tokenizer tok2(jenStates[1], sep);
//    
//    for(tokenizer::iterator beg=tok2.begin(); beg!=tok2.end();++beg){
//        cout << *beg << "\n";
//        if(*beg != ","){
//            
//            
//            cout << strs.size() << endl;
//            
//            for (size_t i = 0; i < strs.size(); i++)
//                cout << strs[i] << endl;
//            //cout << strs[1] << ": " << strs[3] << endl;
//        }
//    }
    
    receiver.hasUpdated = false;
}

//--------------------------------------------------------------
void Receiver::threadedFunction(){
    while(isThreadRunning())
    {
        // Attempt to lock the mutex. If blocking is turned on,
        if(lock())
        {
            if (!hasUpdated) {
                nanoPull.receive(stateString);
                hasUpdated = true;
            }
            
            // Unlock the mutex. This is only
            // called if lock() returned true above.
            unlock();
        }
        else
        {
            // If we reach this else statement, it means that we could not
            // lock out mutex, and so we do not need to call unlock().
            // Calling unlock without locking will lead to porblems.
            ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
        }
    }
}

