/**
 *
 *  @file ofApp.cpp
 *  @brief MotionMachine source file for empty example
 *  @copyright Numediart Institute, UMONS (c) 2015
 *
 *

TUTORIAL DESCRIPTION
This is a short example showing how to enable the dragging of motion data in the application and their display.
*/

#include "ofApp.h"
#include "mmGeometry.h"

using namespace std;
using namespace arma;
using namespace MoMa;

void ofApp::setup( void ) {    
    
	light.setPosition(ofVec3f(4, 40, 0) * 10);

    setActiveMode(SCENE3D); // Focus mode on the 3D scene (so that the mouse controls the 3D scene)
    addNewTrack("1"); // Add a new track called "1" (to put the data in it) in the internal track vector of the 
    //application
   // registerDragEvent(track("1")); // Make the drag event load the dragged data in the track "1"
	track("1").load(getDataPath() + "vitrine1_1.c3d");
	screen.loadImage("background.jpg");

	Trace Right1trace = track("1")("Right1");
	Trace Left1trace = track("1")("Left1");
	Trace Front1trace = track("1")("Front1");

	TimedMat myRight1Position = Right1trace.position;
	TimedMat myLeft1Position = Left1trace.position;
	TimedMat myFront1Position =Front1trace.position;

	mat myRight1Mat = myRight1Position.getData();
	mat myLeft1Mat = myLeft1Position.getData();
	mat myFront1Mat = myFront1Position.getData();
	
	mat Middle = (myRight1Mat - myLeft1Mat)/2;
	
	setFrameRate (track("1").frameRate()); // Set the framerate of the application to the framerate of the track,
									   //so that it is played at the real speed

	setPlayerSize(track("1").nOfFrames());

}

void ofApp::update( void ) {
	//cout<<track("1").nodeList<<endl;
	//track("1").nodeList->print();



}

void ofApp::scene3d( void ) {
    

	ofEnableLighting();
	light.enable();

	ofPushMatrix();
	ofRotateX(90);
	ofRotateY(90);
	screen.draw(-(screen_width) / 2, 500, 2500, screen_width, screen_height);
	ofPopMatrix();

	light.disable();
	ofDisableLighting();



    draw(track("1")[getAppTime()]); // Draw the current frame (at the current time of the application) of the track "1"
	ofPushMatrix();
	ofRotateX(90);
	//screen.draw(ofVec3f(500, 50, 50));
	ofPopMatrix();
	// Same as :
    //draw(track("1").frame(getAppTime()));
	//ofVec3f vec1 = toVec3f(Right1trace.position) - toVec3f(RElbow.position);
	
	Node Right = track("1")("Right1")[getAppTime()]; //position data of the right hand at the current time of the
													 //application

	Node Left = track("1")("Left1")[getAppTime()]; //position data of the pelvis at the current time of the 
												   //application
	Node Front = track("1")("Front1")[getAppTime()];

	vec RightVector =Right.position;
	vec LeftVector =Left.position;
	vec FrontVector = Front.position;
	
	//ofSetColor(255, 0, 0); //Set drawing color to red
	vec Mid = (RightVector + LeftVector)/2;
//	ofVec3f Mid = toVec3f(RightVector) - toVec3f(LeftVector);
	ofLine(toVec3f(Mid), toVec3f(FrontVector));
	//ofLine(toVec3f(LHandPositionVector), toVec3f(PelvisPositionVector)); //draw a line between two points
	
}


void ofApp::scene2d( void ) {
    
    // Example to draw some timed data in the 2D scene
    //draw(track("1")(0).position, "First node position data"); // Draw the positions (x,y,z) of the first node (node 0) 
                                                                //of the track "1"

    draw(COM); //Draw the positions of the center of mass (extracted in dragEvent)
               //of the track "1"
}

void ofApp::annotate( void ) {
    
    
}

void ofApp::keyPressed( int key ) {
    
    
}

void ofApp::keyReleased( int key ) {
    
    
}

void ofApp::mousePressed( int x, int y, int button ) {
    
    
}

void ofApp::mouseReleased( int x, int y, int button ) {
    
    
}

void ofApp::mouseDragged( int x, int y, int button ) {
    
    
}

void ofApp::mouseMoved( int x, int y ) {
    
    
}

void ofApp::windowResized( int w, int h ) {
    
    
}

void ofApp::dragEvent( ofDragInfo dragInfo ) {
    
    //This event is still called when a track file is dragged in the application window.
    // Here we extract the center of mass of the track (to display its trace it in the 2D layer)
    COM = Geometry::centerOfMassTrace(track("1"));
}

void ofApp::gotMessage( ofMessage msg ) {
    
    
}
