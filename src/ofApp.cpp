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
    
	//light.setPosition(ofVec3f(2000, 2000, 2000));

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
	
	mat Middle = (myRight1Mat + myLeft1Mat)/2;
	
	setFrameRate (track("1").frameRate()); // Set the framerate of the application to the framerate of the track,
									   //so that it is played at the real speed

	setPlayerSize(track("1").nOfFrames());
	ofSetColor(255);
	int G = 0;
	int M = 0;
	int D = 0;

	clicked = 0;

}

void ofApp::update( void ) {
	//cout<<track("1").nodeList<<endl;
	//track("1").nodeList->print();



}

void ofApp::scene3d(void) {

	float Buffsize = track("1").nOfFrames();
	//cout << Buffsize;
	//float Buffsize = 500;


   // draw(track("1")[getAppTime()]); // Draw the current frame (at the current time of the application) of the track "1"
	ofPushMatrix();
	ofRotateX(90);
	//screen.draw(ofVec3f(500, 50, 50));
	ofPopMatrix();
	// Same as :
	draw(track("1").frame(getAppTime()));
	//ofVec3f vec1 = toVec3f(Right1trace.position) - toVec3f(RElbow.position);

	Node Right = track("1")("Right1")[getAppTime()]; //position data of the right hand at the current time of the
	//Trace Right = track("1")("Right1");												 //application

	Node Left = track("1")("Left1")[getAppTime()]; //position data of the pelvis at the current time of the 
												   //application
	Node Front = track("1")("Front1")[getAppTime()];

	vec RightVector = Right.position;
	vec LeftVector = Left.position;
	vec FrontVector = Front.position;

	vec Mid = (RightVector + LeftVector) / 2;
	//	ofVec3f Mid = toVec3f(RightVector) - toVec3f(LeftVector);
	vec diff = (FrontVector - Mid);


	ofLine(toVec3f(Mid), toVec3f(FrontVector + 80 * diff));
	//ofLine(toVec3f(LHandPositionVector), toVec3f(PelvisPositionVector)); //draw a line between two points

	vec head = (FrontVector + Mid) / 2;
	//cout<<head << endl;

	ofEnableLighting();
	light.enable();

	ofPushMatrix();
	ofRotateX(90);
	ofRotateY(90);


	float decalage =750;
	float profondeur =6000;
	float scale = 2;

	decalage = decalage*scale;
	screen.draw(-(scale*screen_width) / 2 - decalage, 1200, profondeur, scale*screen_width, scale*screen_height);
	//screen.draw((head[1]-(screen_width) / 2)-250, 1200, 4000, screen_width, screen_height);

	ofSetColor(255, 0, 0);
	//Ligne gauche
	ofVec3f point11;
	point11.set((scale*screen_width) / 2 - decalage, 0, profondeur - 100);
	ofVec3f point12;
	point12.set((scale*screen_width) / 2 - decalage, 5000, profondeur - 100);
	ofDrawLine(point11, point12);

	ofVec3f point21;
	point21.set(-decalage - (scale*screen_width) / 6, 0, profondeur - 100);
	ofVec3f point22;
	point22.set(-decalage - (scale*screen_width) / 6, 5000, profondeur - 100);
	ofDrawLine(point21, point22);

	ofVec3f point31;
	point31.set(-decalage + (scale*screen_width) / 6, 0, profondeur - 100);
	ofVec3f point32;
	point32.set(-decalage + (scale*screen_width) / 6, 5000, profondeur - 100);
	ofDrawLine(point31, point32);


	ofVec3f point41;
	point41.set(-(scale*screen_width) / 2 - decalage, 0, profondeur - 100);
	ofVec3f point42;
	point42.set(-(scale*screen_width) / 2 - decalage, 5000, profondeur - 100);
	ofDrawLine(point41, point42);
	ofPopMatrix();

	//Projection
	ofVec3f NormalOrigin;
	NormalOrigin.set(0, 0, 0);
	ofVec3f Normal;
	Normal.set(0, 0, 1);

	//projection de MID
	ofVec3f Dmid = toVec3f(Mid) - NormalOrigin;
	ofVec3f Distmid = Dmid*Normal;
	ofVec3f MidProj = toVec3f(Mid) - Distmid*Normal;

	//projection du front (* dist)
	ofVec3f Dfront = toVec3f(FrontVector + 20 * diff) - NormalOrigin;
	ofVec3f Distfront = Dfront*Normal;
	ofVec3f FrontProj = toVec3f(FrontVector + 20 * diff) - Distfront*Normal;

	//projection head 
	ofVec3f Dhead = toVec3f(head) - NormalOrigin;
	ofVec3f Disthead = Dhead*Normal;
	ofVec3f HeadProj = toVec3f(head) - Disthead*Normal;

	//line vision
	ofVec3f lignevision(MidProj - FrontProj);
	ofDrawLine(MidProj, FrontProj);
	ofSetColor(0, 255, 0);

	//line between head and first line
	ofVec3f pointligne1;
	pointligne1.set((profondeur - 100), ((scale*screen_width) / 2 - decalage), 0);
	ofVec3f ligne1 = -(pointligne1 - HeadProj);
	ofDrawLine(pointligne1, HeadProj);

	//line between head and second line
	ofVec3f pointligne2;
	pointligne2.set(profondeur - 100, -decalage + (scale*screen_width) / 6, 0);
	ofVec3f ligne2 = -(pointligne2 - HeadProj);
	ofDrawLine(pointligne2, HeadProj);

	//line between head and third line
	ofVec3f pointligne3;
	pointligne3.set(profondeur - 100, -decalage - (scale*screen_width) / 6, 0);
	ofVec3f ligne3 = -(pointligne3 - HeadProj);
	ofDrawLine(pointligne3, HeadProj);

	//line between head and fourth line
	ofVec3f pointligne4;
	pointligne4.set(profondeur - 100, -(scale*screen_width) / 2 - decalage, 0);
	ofVec3f ligne4 = -(pointligne4 - HeadProj);
	ofDrawLine(pointligne4, HeadProj);



	//if premiere zone
	if (clicked==1) {
	if (lignevision.angle(ligne1) < ligne2.angle(ligne1)) {
		G++;
	}
	if (lignevision.angle(ligne1) > ligne2.angle(ligne1) && lignevision.angle(ligne1) < ligne3.angle(ligne1)) {
		M++;
	}

	if (lignevision.angle(ligne1) < ligne4.angle(ligne1) && lignevision.angle(ligne1) > ligne3.angle(ligne1)){
		D++;
}
	}
	cout << " G: " << G << " M: " << M << " D: " << D << endl;
	



	light.disable();
	ofDisableLighting();

	ofSetColor(Turquoise, 128);

	// This line pushes a LWrist/RWrist point pair in the memory queue named 'carpet'
	/*
	carpet.push_front( make_pair( toVec3f(Mid), toVec3f(FrontVector + 80 * diff) ) );
	if( carpet.size() >  Buffsize ) carpet.pop_back(); // If memory queue >  Buffsize, oldest is removed
	
	ofSetColor( Turquoise, 128 );
	for( int l=0; l<carpet.size(); l++ ) {

	// We draw a line between each point pair for the
	// size of the carpet queue = past of LWrist/RWrist
	ofDrawLine( carpet[l].first, carpet[l].second );
	}  */
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
	
	if (key == ' ') { clicked = !clicked; }
    

}

void ofApp::keyReleased( int key ) {
    
    
}

void ofApp::mousePressed( int x, int y, int button ) {
 /*   
	if (button == 1) {
		clicked = !clicked;
	}
	*/
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
