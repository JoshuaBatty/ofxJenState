 //
//  ofxJenOscState.cpp
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#include "ofxJenState.h"

using namespace ofxJenState;


float parseFloat(string s) {
    //cout << "parseFloat s = " << s << endl;
    int semicolon = s.find(":");
    string number = s.substr(semicolon + 2, s.size()-1);
    return ofToFloat(number);
}

void State::update() {

    // Pull in new messages from OSC
    osc_receiver.update();
    
    /// ------ TEMP ABLETON
    busses.busses[0].params[0] = osc_receiver.drums;
    busses.busses[1].params[0] = osc_receiver.bass;
    busses.busses[2].params[0] = osc_receiver.melody;
    busses.busses[3].params[0] = osc_receiver.atmos;
    
    // Check for new received string.
    if (!osc_receiver.hasUpdated) {
        return;
    } else {
        osc_receiver.hasUpdated = false;
    }
    
    //string stateString = "StateView { playhead: PlayheadState { tick_count: 101060, phrase_perc: 0.3289713541666667, segment_perc: 0.31588541666666664, bar_perc: 0.6317708333333333, minim_perc: 0.6317708333333333, beat_perc: 0.2635416666666667, quaver_perc: 0.5270833333333333, semi_quaver_perc: 0.05416666666666667, time_sig: TimeSig { top: 2, bottom: 4 }, bpm: 85 }, dsp: DspState { instruments: {(Kick, 1): (0.04907299, 0), (Snare, 0): (0.0014198811, 0), (Chordal, 4): (0.028520431, 0), (Bass, 2): (0.249059, 0), (Chordal, 5): (0.02641474, 0), (Melodic, 3): (0.051713094, 0)}, busses: {}, master: (0.1094684, 0) }, note: NoteState { instruments: {(Snare, 0): 0.2635416666666667, (Melodic, 3): 0.5270833333333333, (Chordal, 5): 0.31588541666666664, (Kick, 1): 0.2635416666666667, (Bass, 2): 0.4434375} } }";
    
    //cout << "osc_receiver.stateString = " << osc_receiver.stateString  << endl;
    
    string stateString = osc_receiver.stateString;
    
    ///--------- PLAY HEADS
    int tick_count_pos = 0;
    int phrase_perc_pos = stateString.find(", phrase_perc: ");
    int segment_perc_pos = stateString.find(", segment_perc: ");
    int bar_perc_pos = stateString.find(", bar_perc: ");
    int minim_perc_pos = stateString.find(", minim_perc: ");
    int beat_perc_pos = stateString.find(", beat_perc: ");
    int quaver_perc_pos = stateString.find(", quaver_perc: ");
    int semi_quaver_perc_pos = stateString.find(", semi_quaver_perc: ");
    int end_of_playheads_plus_ten = stateString.find(", time_sig");
    
    playheads.params[Phrase] = parseFloat(stateString.substr(phrase_perc_pos, segment_perc_pos - phrase_perc_pos));
    playheads.params[Segment] = parseFloat(stateString.substr(segment_perc_pos, bar_perc_pos - segment_perc_pos));
    playheads.params[Bar] = parseFloat(stateString.substr(bar_perc_pos, minim_perc_pos - bar_perc_pos));
    playheads.params[Minim] = parseFloat(stateString.substr(minim_perc_pos, beat_perc_pos - minim_perc_pos));
    playheads.params[Beat] = parseFloat(stateString.substr(beat_perc_pos, quaver_perc_pos - beat_perc_pos));
    playheads.params[Quaver] = parseFloat(stateString.substr(quaver_perc_pos, semi_quaver_perc_pos - quaver_perc_pos));
    playheads.params[SemiQuaver] = parseFloat(stateString.substr(semi_quaver_perc_pos, end_of_playheads_plus_ten - 10 - semi_quaver_perc_pos));
    
    ///--------- TIME SIG & BPM
    int time_sig_top_pos = stateString.find("TimeSig { top: ");
    int time_sig_bottom_pos = stateString.find(", bottom: ");
    int bpm_pos = stateString.find(" }, bpm: ");
    int bpm_end_pos = stateString.find(" }, dsp");
    
    timeSigTop = parseFloat(stateString.substr(time_sig_top_pos, time_sig_bottom_pos - time_sig_top_pos));
    timeSigBottom = parseFloat(stateString.substr(time_sig_bottom_pos, bpm_pos - time_sig_bottom_pos));
    bpm = parseFloat(stateString.substr(bpm_pos, bpm_end_pos - bpm_pos));
    
    ///--------- DSP
    int dsp_start_pos = stateString.find("DspState");
    string dspState = stateString.substr(dsp_start_pos, stateString.size()-1 - dsp_start_pos);
    
    ///--------- INSTRUMENTS
    int instrument_start_pos = 25;
    int instrument_end_pos = dspState.find("}, busses");
    string instrumentState = dspState.substr(instrument_start_pos, instrument_end_pos - instrument_start_pos);
    
    int start_index = 0;
    while (true) {
        
        int end_idx = instrumentState.find("),", start_index);
        
        // If we didn't find any more endings, we're done.
        bool last_inst = false;
        if (end_idx == -1) {
            last_inst = true;
        }
    
        string inst = instrumentState.substr(start_index, end_idx - start_index);
        
        // If there are no strings in the list, bail.
        if (inst == "") {
            break;
        } else {
            parseInstrument(inst);
        }
        
        if (last_inst) { break; }
        start_index = end_idx + 3; // 3 == "), ".size()
    }
    
    ///--------- BUSSES
    int bus_start_pos = dspState.find("busses") + 9; // Inside the curly.
    int bus_end_pos = dspState.find("}, master");
    string busState = dspState.substr(bus_start_pos, bus_end_pos - bus_start_pos);

    
    ///--------- MASTER
    int master_rms_start_pos = dspState.find("master") + 9; // Straight to the rms value mayte.
    int master_rms_end_pos = dspState.find(", ", master_rms_start_pos);
    string masterRmsString = dspState.substr(master_rms_start_pos, master_rms_end_pos - master_rms_start_pos);
    master.params[BUS_RMS] = ofToFloat(masterRmsString);
    
    ///--------- NOTES
    int note_start_pos = dspState.find("NoteState") + 26; // Inside the Curly
    int note_end_pos = dspState.find("}" , note_start_pos);
    
    int start_idx = note_start_pos;
    while (true) {
        int end_idx = dspState.find(", ", start_idx);
        
        bool last_note = false;
        if(end_idx == -1){
            last_note = true;
        }
        
        string note = dspState.substr(start_idx, end_idx - start_idx);
        parseNote(note);
        
        if (last_note) { break; }
        start_idx = end_idx + 2;
    }
    
//    for (int i=0; i < TotalMeasures; i++) {
//        cout << i << ": " << playheads.params[i] << endl;
//    }
//    cout << "Time Sig Top = " << timeSigTop << endl;
//    cout << "Time Sig Bottom = " << timeSigBottom << endl;
//    cout << "BPM = " << bpm << endl;
//    
//    for(int i = 0; i < instruments.instruments.size(); i++){
//        cout << "instrument Name = " << instruments.instruments[i].name << endl;
//        cout << "instrument " + ofToString(1+i) + " Rms = " << instruments.instruments[i].params[RMS] << endl;
//        cout << "instrument " + ofToString(1+i) + " Pan = " << instruments.instruments[i].params[PAN] << endl;
//        cout << "instrument " + ofToString(1+i) + " Perc = " << instruments.instruments[i].params[PERC] << endl;
//        cout << " ---------------------- " << endl;
//    }
//    
//    cout << "MASTER RMS = " << masterRmsString << endl;
    
  //  receiver.hasUpdated = false;
    
}

//--------------------------------------------------------------
// s is something like "(Snare, 0): 0.2635416666666667"
void State::parseNote(string s){
    //cout << "note s = " << s << endl;
    int perc_pos = s.find(": ") + 2;
    int perc_end = s.find(s.size()-1);
    string perc_string = s.substr(perc_pos, perc_end - perc_pos);
    float perc_val = ofToFloat(perc_string);
    
    if (s.find("Kick") != -1) {
        instruments.instruments[Kick].params[PERC] = perc_val;
    } else if (s.find("Snare") != -1){
        instruments.instruments[Snare].params[PERC] = perc_val;
    } else if (s.find("Ride") != -1){
        instruments.instruments[Ride].params[PERC] = perc_val;
    } else if (s.find("Ghost") != -1){
        instruments.instruments[Ghost].params[PERC] = perc_val;
    } else if (s.find("Bass") != -1){
        instruments.instruments[Bass].params[PERC] = perc_val;
    } else if (s.find("Melodic") != -1){
        instruments.instruments[Melodic].params[PERC] = perc_val;
    } else if (s.find("Chordal") != -1){
        instruments.instruments[Chordal].params[PERC] = perc_val;
    } else if (s.find("Atmos") != -1){
        instruments.instruments[Atmos].params[PERC] = perc_val;
    }
}

//--------------------------------------------------------------
// s is something like "(Chordal, 4): (0.028520431, 0)"
void State::parseInstrument(string s){
    //cout << "inst s = " << s << endl;

    int rms_pos = s.find("(", 2) + 1; // 0.028520431, 0)
    int first_comma = s.find(",");
    int rms_end = s.find(",", first_comma + 2);
    
    string rms_string = s.substr(rms_pos, rms_end - rms_pos);
    float rms_val = ofToFloat(rms_string);
    
    int pan_pos = rms_end + 2;
    int pan_end = s.size()-1;
    
    string pan_string = s.substr(pan_pos, pan_end - pan_pos);
    float pan_val = ofToFloat(pan_string);
    
    if (s.find("Kick") != -1) {
        instruments.instruments[Kick].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.6,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Kick].params[PAN] = pan_val;
    } else if (s.find("Snare") != -1){
        instruments.instruments[Snare].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.15,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Snare].params[PAN] = pan_val;
    } else if (s.find("Ride") != -1){
        instruments.instruments[Ride].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.08,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Ride].params[PAN] = pan_val;
    } else if (s.find("Ghost") != -1){
        instruments.instruments[Ghost].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.05,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Ghost].params[PAN] = pan_val;
    } else if (s.find("Bass") != -1){
        instruments.instruments[Bass].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.3,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Bass].params[PAN] = pan_val;
    } else if (s.find("Melodic") != -1){
        instruments.instruments[Melodic].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.1,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Melodic].params[PAN] = pan_val;
    } else if (s.find("Chordal") != -1){
        instruments.instruments[Chordal].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.125,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Chordal].params[PAN] = pan_val;
    } else if (s.find("Atmos") != -1){
        instruments.instruments[Atmos].params[RMS] = ofClamp(ofMap(rms_val,0.0,0.1,0.0,1.0), 0.0, 1.0);
        instruments.instruments[Atmos].params[PAN] = pan_val;
    }
}

//--------------------------------------------------------------
//--------------------------------------------------------------
vector<Modulator*> State::getChildren() {
    vector<Modulator*> children;
    children.reserve(5);
    
    children.push_back((Modulator*)&instruments);
    children.push_back((Modulator*)&playheads);
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
void OSC_Receiver::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // TRIGGERS
        if(m.getAddress() == "/jenState"){
            stateString = m.getArgAsString(0);
            hasUpdated = true;
        }
        // ABLETON SET
        if(m.getAddress() == "/drums"){
            drums = m.getArgAsFloat(0);
        }
        if(m.getAddress() == "/bass"){
            bass = m.getArgAsFloat(0);
        }
        if(m.getAddress() == "/melody"){
            melody = m.getArgAsFloat(0);
        }
        if(m.getAddress() == "/atmos"){
            atmos = m.getArgAsFloat(0);
        }
        //hasUpdated = true;
    }
}
////--------------------------------------------------------------
//void Receiver::threadedFunction(){
//    while(isThreadRunning())
//    {
//        // Attempt to lock the mutex. If blocking is turned on,
//        if(lock())
//        {
//            if (!hasUpdated) {
//                //nanoPull.receive(stateString);
//                hasUpdated = true;
//            }
//            
//            // Unlock the mutex. This is only
//            // called if lock() returned true above.
//            unlock();
//        }
//        else
//        {
//            // If we reach this else statement, it means that we could not
//            // lock out mutex, and so we do not need to call unlock().
//            // Calling unlock without locking will lead to porblems.
//            ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
//        }
//    }
//}

