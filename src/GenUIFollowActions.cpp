//
//  GenUIFollowActions.cpp
//  oscReceiveExample
//
//  Created by Joshua Batty on 4/03/14.
//
//

#include "GenUIFollowActions.h"

// 0 = No trigger behaviour
// 1 = Trigger previous scene
// 2 = Trigger next scene
// 3 = Trigger first scene
// 4 = Trigger last scene
// 5 = Trigger any scene
// 6 = Trigger other scene
// 7 = Trigger specific scene

//--------------------------------------------------------------
void GenUIFollowActions::setup(){
    
    /*-------------Define Menu Property-------------*/
	menu.OnlyRightClick = true;
	menu.menu_name = "mainMenu";
	
	//Standard Button Menus
	menu.RegisterMenu("Rect");
	menu.RegisterMenu("Circle");
	menu.RegisterMenu("Triangle");
	
	//Branch Buttons Menu
	vector<string> BranchFollow_Actions;
	BranchFollow_Actions.push_back("None");
	BranchFollow_Actions.push_back("Previous");
	BranchFollow_Actions.push_back("Next");
	BranchFollow_Actions.push_back("First");
	BranchFollow_Actions.push_back("Last");
	BranchFollow_Actions.push_back("Any");
	BranchFollow_Actions.push_back("Other");
	BranchFollow_Actions.push_back("Specific");
	menu.RegisterBranch("FollowActions", &BranchFollow_Actions);

    val = 0;
    menu.RegisterFader("specific", &val);
	//Fader Menu(Range is 0.0f~1.0f)
//	menu.RegisterFader("Alpha", &brightness);
//	menu.RegisterFader("Size", &size);
	
	//Add Event Listener
	ofAddListener(ofxCDMEvent::MenuPressed, this, &GenUIFollowActions::cmdEvent);
}

//--------------------------------------------------------------
void GenUIFollowActions::draw(){
    menu.draw();
}

//--------------------------------------------------------------
void GenUIFollowActions::cmdEvent(ofxCDMEvent &ev){
	/*-------------Catch menu messages-------------*/
//	if (ev.message == "mainMenu::Rect") shape = SHAPE_RECT;

}

//--------------------------------------------------------------
// Sets the type of behaviour that the follow actions each scene will control
// Scene = the specific scene to alter its behaviour
// ActionType = the generative bahviour of that scene
//
// 0 = No trigger behaviour
// 1 = Trigger previous scene
// 2 = Trigger next scene
// 3 = Trigger first scene
// 4 = Trigger last scene
// 5 = Trigger any scene
// 6 = Trigger other scene
// 7 = Trigger specific scene

void GenUIFollowActions::setNextScene(int _scene, int _actionType){
    
}