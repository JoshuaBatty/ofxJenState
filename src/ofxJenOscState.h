//
//  ofxJenOscState.h
//  example_ofxJenOsc
//
//  Created by Mitchell Nordine on 1/11/2014.
//
//

#ifndef __example_ofxJenOsc__ofxJenOscState__
#define __example_ofxJenOsc__ofxJenOscState__

#include "ofMain.h"

namespace ofxJenOsc {

    enum Measure {
        Song,
        Part,
        Segment,
        Bar,
        Minim,
        Beat,
        Quaver,
        SemiQuaver,
        TotalMeasures,
    };

    /// Represents a playhead for a given duration.
    class Playhead {
    public:
        
        Playhead(unsigned int _durationInTicks = 0)
        : durationInTicks(_durationInTicks)
        , positionInTicks(0) {
        }
        
        /// Return the position of the playhead within the duration as a percentage.
        double percentage() {
            if (durationInTicks > 0) {
                return (double)positionInTicks / (double)durationInTicks;
            } else {
                return 0.0;
            }
        }
        
        unsigned int durationInTicks;
        unsigned int positionInTicks;
        
    };


    class State {
    public:

        State()
        : playheads(TotalMeasures, Playhead()) {
        }
        
        const vector<Playhead>& getPlayheads() {
            return playheads;
        }

    private:
        vector<Playhead> playheads;
    };
        
}

#endif /* defined(__example_ofxJenOsc__ofxJenOscState__) */
