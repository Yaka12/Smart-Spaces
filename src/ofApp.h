/**
 *
 *  @file ofApp.h
 *  @brief MotionMachine header file for empty example
 *  @copyright Numediart Institute, UMONS (c) 2015
 *
 */

#pragma once

#include "MoMa.h"
#include "MoMaUI.h"
#include "ofMain.h"

class ofApp : public MoMa::SceneApp {

  public:
    
    void setup( void );
    void update( void );
    
    void scene3d( void );
    void scene2d( void );
    void annotate( void );
    
    void keyPressed( int key );
    void keyReleased( int key );
    
    void mousePressed( int x, int y, int button );
    void mouseReleased( int x, int y, int button );
    void mouseDragged( int x, int y, int button );
    void mouseMoved( int x, int y );
    
    void windowResized( int w, int h );
    void dragEvent( ofDragInfo dragInfo );
    void gotMessage( ofMessage msg );
	deque< pair< ofVec3f, ofVec3f > > carpet;
    MoMa::Trace COM;
	
	ofImage screen;
	ofLight light;

	//  MoMa::Track myTrack;

	int screen_width = 4000;
	int screen_height = 2250;
	int G;
	int M;
	int D;
};
