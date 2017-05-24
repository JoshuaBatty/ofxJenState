//
//  ofxJenOscState.h
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#pragma once

#include "ofMain.h"
//#include "ofThread.h"
//#include "ofxNanomsg.h"
#include "ofxOsc.h"
#include "Modulator.h"

// Cereal includes
//#include "cereal.hpp"
//#include "json.hpp"
//#include "map.hpp"

namespace ofxJenState {

    /// Represents the different type of musical durations within Jen.
    /// These will also be used to index the `playheads` vector within `State`.
    enum Measure {
        Phrase,
        Segment,
        Bar,
        Minim,
        Beat,
        Quaver,
        SemiQuaver,
        TotalMeasures
    };
    
    class Playheads : public Modulator{
    public:
        Playheads(){
            for(int i = 0; i < TotalMeasures; i++){
                params.push_back(0.0);
            }
        }
    };


    /// Represents the state of a Note.
    class Note {
    public:

        Note(unsigned int _id, float _playhead, float _velocity = 1.0f)
        : id(_id)
        , playhead(_playhead)
        , velocity(_velocity) {
        }
        
        unsigned int id;
        float playhead;
        float velocity;
        
    };

    /// Represents the different types of Patterns generated by Jen.
    enum PatternType {
        Kick,
        Snare,
        Ghost,
        Ride,
        Layer,
        Bass,
        Melodic,
        Chordal,
        Atmos
    };
    
    
    enum InstrumentParam{
        RMS,
        PERC,
        PAN,
        TotalInstrumentParams
    };
    
    /// Represents the state of an Instrument.
    class Instrument: public Modulator {
    public:

        Instrument(PatternType _type)
        : type(_type) {
            switch (_type) {
                case Kick: name = "kick"; break;
                case Snare: name = "Snare"; break;
                case Ghost: name = "Ghost"; break;
                case Ride: name = "Ride"; break;
                case Layer: name = "Layer"; break;
                case Bass: name = "Bass"; break;
                case Melodic: name = "Melodic"; break;
                case Chordal: name = "Chordal"; break;
                case Atmos: name = "Atmos"; break;
                    
                default:
                    break;
            }
            
            for(int i = 0; i < TotalInstrumentParams; i++){
                params.push_back(0.0);
            }
        }

        PatternType type;
        string name;
    };
    
    class Instruments: public Modulator {
    public:
        Instruments()
        {
            instruments.reserve(8);
            instruments.push_back(Instrument(Kick));
            instruments.push_back(Instrument(Snare));
            instruments.push_back(Instrument(Ghost));
            instruments.push_back(Instrument(Ride));
            instruments.push_back(Instrument(Layer));
            instruments.push_back(Instrument(Bass));
            instruments.push_back(Instrument(Melodic));
            instruments.push_back(Instrument(Chordal));
            instruments.push_back(Instrument(Atmos));
            
        }
        vector<Instrument> instruments;
        vector<Modulator*> getChildren();
    };
    
    enum BusParams{
        BUS_RMS,
        BUS_PAN,
        TotalBusParams
    };
    
    class Bus : public Modulator {
    public:
        Bus(string _name)
        : name(_name)
        {
            for(int i = 0; i < TotalBusParams; i++){
                params.push_back(0.0);
            }
        }
        string name;
    };
    
    class Busses: public Modulator{
    public:
        Busses()
        {
            busses.reserve(5);
            busses.push_back(Bus("Bus 1"));
            busses.push_back(Bus("Bus 2"));
            busses.push_back(Bus("Bus 3"));
            busses.push_back(Bus("Bus 4"));
            busses.push_back(Bus("Bus 5"));
        }
        vector<Bus> busses;
        vector<Modulator*> getChildren();
    };
    
//    class Receiver: public ofThread {
//        
//    public:
//        Receiver() {
//            nanoPull.bind("tcp://*:9001");
//        }
//        
//        void threadedFunction();
//        
//        ofxNanomsgPull nanoPull;
//        bool hasUpdated;
//    };

    
    
    class OSC_Receiver {
    public:
        OSC_Receiver(){
            OSC_PORT = 9001;
            receiver.setup(OSC_PORT);
            stateString = "";
            hasUpdated = false;
        }
        void update();
        ofxOscReceiver receiver;
        int OSC_PORT;
        string stateString;
        bool hasUpdated;
        
        /// ------ TEMP ABLETON
        float drums, bass, melody, atmos;
        float semi_quaver, quaver, beat, minim, bar, segment, phrase;
    };
    

    /// Represents the entire state of Jen. By calling `update`, the state will
    /// check for OSC messages and update its entire state accordingly.
    class State: public Modulator {
    public:

        ~State(){
            //receiver.stopThread();
            //while (receiver.isThreadRunning());//sleep(10); };
        }
        
        State()
        : master("MASTER")
        {
            //receiver.startThread();
        }
        
        void update();
        void parseInstrument(string s);
        void parseNote(string s);
        vector<Modulator*> getChildren();

        Instruments instruments;
        Playheads playheads;
        Busses busses;
        Bus master;
        //Receiver receiver;
        OSC_Receiver osc_receiver;
        
        int timeSigTop;
        int timeSigBottom;
        int bpm;

    };

}


