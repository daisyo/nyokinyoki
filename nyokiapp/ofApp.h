#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "wdGui.h"
#include "wdApp.h"

#define R_OSC 10000
#define HOST "192.168.152.48"
#define S_OSC 10001

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
    void claculator();
    void timer();
    void glaph();
    void visialaizer();
  
    unsigned char intToUchar(int i);
    void motorTest();
  
    void keyControler();

    wdGui wdgui;
    wdApp wdapp;
  
    vector<int> wood;
  
  
    // visialaizer
    ofSoundPlayer player;
    float* fft;
    int nBandsToGet;
    bool startMusic;
    int selectMusic;
    int playingMusic;
  
    const string music1 = "goodbye2.mp3";
    const string music2 = "in tune.mp3";
    const string music3 = "3.mp3";
    const string music4 = "4.wav";
    const string music5 = "5.mp3";
    const string music6 = "6.mp3";
    const string music7 = "7.mp3";
    const string music8 = "8.mp3";
  
  
    // calc
    bool drawResult;
    int result;
    ofxPanel gui;
    ofxIntSlider slider;
  
    // timer
    float stopTimer;
    float beginTimer;
    float endTimer;
    bool startTimer;
    ofxPanel guiTimer;
    ofxToggle st;
  
    // graph
    string status;

    // arduino
    ofSerial port;
  
    // ofxOsc
    ofxOscSender sender;
    ofxOscReceiver receiver;
  
    //
    bool typeKey[9];
    float startTime[9];
  
    const int FRAME_RATE_NORMAL = 20;
};
