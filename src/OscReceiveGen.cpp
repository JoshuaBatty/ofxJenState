//
//  OscReceiveGen.cpp
//  oscReceiveExample
//
//  Created by Joshua Batty on 28/02/14.
//
//

#include "OscReceiveGen.h"


//--------------------------------------------------------------

OscReceiveGen::OscReceiveGen()
:
genSong("/Song"),
genPart("/Part"),
genSegment("/Segment"),
genKick("/Kick"),
genSnare("/Snare"),
genRide("/Ride"),
genGhost("/Ghost"),
genBar("/Bar"),
genBeat("/Beat"),
genQuaver("/Quaver"),
genSemiQ("/SemiQ")
{
    genSong.setUsePercentage(true);
    genPart.setUsePercentage(true);
    genSegment.setUsePercentage(true);
    genKick.setUsePercentage(true);
    genKick.setUseVolume(true);
    genSnare.setUsePercentage(true);
    genSnare.setUseVolume(true);
    genRide.setUsePercentage(true);
    genRide.setUseVolume(true);
    genGhost.setUsePercentage(true);
    genGhost.setUseVolume(true);
    genBar.setUsePercentage(true);
    genBeat.setUsePercentage(true);
    genQuaver.setUsePercentage(true);
    genSemiQ.setUsePercentage(true);
}

//--------------------------------------------------------------
void OscReceiveGen::setup(vector<GenVar*> _vars){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
    
	current_msg_string = 0;
    
    vars = _vars;
    
    genInputs.reserve(15);
    genInputs.push_back(&genSong);
    genInputs.push_back(&genPart);
    genInputs.push_back(&genSegment);
    genInputs.push_back(&genKick);
    genInputs.push_back(&genSnare);
    genInputs.push_back(&genRide);
    genInputs.push_back(&genGhost);
    genInputs.push_back(&genBar);
    genInputs.push_back(&genBeat);
    genInputs.push_back(&genQuaver);
    genInputs.push_back(&genSemiQ);
    
    totalNumOfInputs = 0;
    
    for (int i=0; i < genInputs.size()-4 /* << TEMP */; i++) {
        if (genInputs.at(i)->bUsePercentage == true) {
            genInputs.at(i)->percentageID = totalNumOfInputs;
            cout << genInputs[i]->address << " | percID = " << genInputs[i]->percentageID << endl;
            totalNumOfInputs++;
        }
    }
    
    for (int i = 0; i < genInputs.size(); i++) {
        if (genInputs.at(i)->bUseVolume == true) {
            genInputs.at(i)->volumeID = totalNumOfInputs;
            cout << genInputs[i]->address << " | volID = " << genInputs[i]->volumeID << endl;
            totalNumOfInputs++;
        }
    }
    
    for (int i=0; i < genInputs.size(); i++) {
        if (genInputs.at(i)->bUseIsPlaying == true) {
            genInputs.at(i)->isPlayingID = totalNumOfInputs;
            cout << genInputs[i]->address << " | playID = " << genInputs[i]->isPlayingID << endl;
            totalNumOfInputs++;
        }
    }
    
    // TEMP
    for (int i=genInputs.size()-4; i < genInputs.size(); i++) {
        if (genInputs.at(i)->bUsePercentage == true) {
            genInputs.at(i)->percentageID = totalNumOfInputs;
            cout << genInputs[i]->address << " | percID = " << genInputs[i]->percentageID << endl;
            totalNumOfInputs++;
        }
    }
    
    genModUI.setup(&vars, genInputs);
    
    genFollowActions.setup();
}

//--------------------------------------------------------------
void OscReceiveGen::update(){
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        for(int i=0; i < genInputs.size(); i++){
            if(m.getAddress() == genInputs[i]->address){
                genInputs[i]->bPlaying = m.getArgAsInt32(0);
                if (genInputs[i]->bPlaying == 0) {
                    genInputs[i]->getPercentage = 0;
                    genInputs[i]->getVolume = 0;
                }
                else {
                    genInputs[i]->getPercentage = m.getArgAsFloat(1);
                    genInputs[i]->getVolume = m.getArgAsFloat(2);
                }
                
            }
        }
    }
}


//--------------------------------------------------------------
void OscReceiveGen::draw(){
    
    int offset = 0;
    int offsetAmount = 25;
    int xPos = 20;
    int yPos = 50;
    
	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
    
	////////////////////// Song //////////////////////////
    buf = "SongPosition:";
    offset += 5;
    genSong.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genPart.bPlaying);
	ofDrawBitmapString(buf, xPos, yPos);
	ofDrawBitmapString(ofToString(genSong.getPercentage), xPos+170, yPos);
    
    buf = "SongIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSong.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Part //////////////////////
    buf = "PartPosition:";
    offset += 5;
    genPart.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genPart.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genPart.getPercentage), xPos+170, yPos+offset);
    
    buf = "PartIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genPart.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
	////////////////////// Segments //////////////////////
    buf = "SegmentPosition:";
    offset += 5;
    genSegment.drawPosition(xPos, yPos+offset);
    offset += offsetAmount;
    ofSetColor(255*genSegment.bPlaying);
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSegment.getPercentage), xPos+170, yPos+offset);
    
    buf = "SegmentIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSegment.bPlaying), xPos+170, yPos+offset);

    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Bar //////////////////////
    buf = "BarPosition:";
    offset += 5;
    genBar.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genBar.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genBar.getPercentage), xPos+170, yPos+offset);
    
    buf = "BarIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genBar.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Beat //////////////////////
    buf = "BeatPosition:";
    offset += 5;
    genBeat.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genBeat.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genBeat.getPercentage), xPos+170, yPos+offset);
    
    buf = "BeatIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genBeat.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Quaver //////////////////////
    buf = "QuaverPosition:";
    offset += 5;
    genQuaver.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genQuaver.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genQuaver.getPercentage), xPos+170, yPos+offset);
    
    buf = "QuaverIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genQuaver.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Semi Quaver //////////////////////
    buf = "SemiQPosition:";
    offset += 5;
    genSemiQ.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genSemiQ.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSemiQ.getPercentage), xPos+170, yPos+offset);
    
    buf = "SemiQIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSemiQ.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    xPos = 260;
    offset = 0;
    
    ////////////////////// Kick //////////////////////////
    
    buf = "KickPosition:";
    offset += 5;
    genKick.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genKick.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genKick.getPercentage), xPos+170, yPos+offset);

    buf = "KickVolume:";
    offset += 10;
    genKick.drawVolume(xPos, yPos+offset);
    ofSetColor(255*genKick.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genKick.getVolume), xPos+170, yPos+offset);
    
    buf = "KickIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genKick.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
	////////////////////// Snare //////////////////////
    buf = "SnarePosition:";
    offset += 5;
    genSnare.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genSnare.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSnare.getPercentage), xPos+170, yPos+offset);
    
    buf = "SnareVolume:";
    offset += 10;
    genSnare.drawVolume(xPos, yPos+offset);
    ofSetColor(255*genSnare.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSnare.getVolume), xPos+170, yPos+offset);
    
    buf = "SnaretIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genSnare.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Ride //////////////////////
    buf = "RidePosition:";
    offset += 5;
    genRide.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genRide.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genRide.getPercentage), xPos+170, yPos+offset);
    
    buf = "RideVolume:";
    offset += 10;
    genRide.drawVolume(xPos, yPos+offset);
    ofSetColor(255*genRide.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genRide.getVolume), xPos+170, yPos+offset);
    
    buf = "RideIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genRide.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    ////////////////////// Ghost //////////////////////
    buf = "GhostPosition:";
    offset += 5;
    genGhost.drawPosition(xPos, yPos+offset);
    ofSetColor(255*genGhost.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genGhost.getPercentage), xPos+170, yPos+offset);
    
    buf = "GhostVolume:";
    offset += 10;
    genGhost.drawVolume(xPos, yPos+offset);
    ofSetColor(255*genGhost.bPlaying);
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genGhost.getVolume), xPos+170, yPos+offset);
    
    buf = "GhostIsPlaying:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(genGhost.bPlaying), xPos+170, yPos+offset);
    
    buf = "----------------------";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
    
    /////////////////////////////////////////////////////////////////////
    ////////////////    CUSTOM VARIABLES ////////////////////////////////
    ////////////////////// Ghost //////////////////////
    offset = 0;
    offsetAmount = 25;
    xPos = 270;
    yPos = 600;
    
    for (int i=0; i < vars.size(); i++) {
        
        if (vars[i]->volume) {
            buf = vars[i]->name + " Vol";
            offset += offsetAmount;
            ofDrawBitmapString(buf, xPos, yPos+offset);
            ofDrawBitmapString(ofToString(*vars[i]->volume), xPos+170, yPos+offset);
        }
        if (vars[i]->percentage) {
            buf = vars[i]->name + " Perc";
            offset += offsetAmount;
            ofDrawBitmapString(buf, xPos, yPos+offset);
            ofDrawBitmapString(ofToString(*vars[i]->percentage), xPos+170, yPos+offset);
        }
        if (vars[i]->isPlaying) {
            buf = vars[i]->name + " Play";
            offset += offsetAmount;
            ofDrawBitmapString(buf, xPos, yPos+offset);
            ofDrawBitmapString(ofToString(*vars[i]->isPlaying), xPos+170, yPos+offset);
        }
    }
    
    /* buf = "Size:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(*vars[SIZE].second), xPos+170, yPos+offset);
    
    buf = "Speed:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(*vars[SPEED].second), xPos+170, yPos+offset);
    
    buf = "CamX:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(*vars[CAMX].second), xPos+170, yPos+offset);
    
    buf = "CamY:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(*vars[CAMY].second), xPos+170, yPos+offset);
    
    buf = "Strobe:";
    offset += offsetAmount;
	ofDrawBitmapString(buf, xPos, yPos+offset);
	ofDrawBitmapString(ofToString(*vars[STROBE].second), xPos+170, yPos+offset);
    */
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}
    
    ofSetColor(255);
    
    genModUI.draw();
    genFollowActions.draw();
}
