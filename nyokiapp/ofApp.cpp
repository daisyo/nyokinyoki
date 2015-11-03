#include "ofApp.h"

unsigned char s[] = { 0x7E, '0', '0', '0', '0', '0', '0', '0', '0', '0' };

long long int fib = 0;
long long int fib_prev1 = 1;
long long int fib_prev2 = 0;

//--------------------------------------------------------------
void ofApp::setup(){
  // set up tp screen
  ofSetFrameRate(FRAME_RATE_NORMAL);
  ofSetVerticalSync(true);
  ofBackground(53, 53, 53);
  // set up to gui
  wdgui.setup();
  wdapp.setup();
  
  // app
  // visialaizer
  //player.loadSound("goodbye2.mp3");
  startMusic = false;
  player.setLoop(true);
  nBandsToGet = 1024;
  selectMusic = 0;
  
  // calc
  drawResult = false;
  gui.setup();
  gui.add(slider.setup("RESULT", 0, 0, 50));
  gui.setPosition(ofGetWidth() - gui.getWidth(), 0);
  
  // timer
  startTimer = false;
  guiTimer.setup();
  guiTimer.add(st.setup("start", false));
  guiTimer.setPosition(ofGetWidth() - guiTimer.getWidth(), 0);
  
  // graph
  status = "";
  
  // arudino
  port.setup("/dev/tty.usbserial-AI02KIGU", 19200);
  
  // ofxOsc
  sender.setup(HOST, S_OSC);
  receiver.setup(R_OSC);
  
  // key
  for (int i = 0; i < 9; ++i) { typeKey[i] = false; startTime[i] = 0; }
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSetWindowTitle(ofToString(ofGetFrameRate()));
  port.flush();
  wood = wdgui.getHeight();
  
  // oscMessage
  while (receiver.hasWaitingMessages()) {
    ofxOscMessage m;
    receiver.getNextMessage(&m);
    if (m.getAddress() == "/config") {
      string str = m.getArgAsString(0);
      if (str == "calc") { wdapp.setToggle(0); }
      else if (str == "timer") { wdapp.setToggle(1); }
      else if (str == "graph") { wdapp.setToggle(2); }
      else if (str == "visualizer") { wdapp.setToggle(3); }
      else if (str == "menu") { wdapp.unSelect(); }
    }
    if (m.getAddress() == "/visualizer") { int k = m.getArgAsInt32(0); selectMusic = k; }
    if (m.getAddress() == "/graph") { status = m.getArgAsString(0); }
  }
  
  //
  drawResult = false;
  //
  
  switch (wdapp.getToggle()) {
    cout << wdapp.getToggle() << endl;
    case 0: claculator(); break;
    case 1: timer(); break;
    case 2: glaph(); break;
    case 3: visialaizer(); break;
    case 4: ofSetFrameRate(FRAME_RATE_NORMAL); player.stop(); startMusic = false; fib = 0; fib_prev1 = 1; fib_prev2 = 0; startTimer = false;selectMusic = 0; playingMusic = 0; break;
    default: break;
  }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
  // draw wood
  int width = ofGetWidth() / 9;
  
  if (drawResult) {
    ofDrawBitmapStringHighlight(ofToString(result), ofGetWidth() / 2, ofGetHeight() / 2 - 200);
    gui.draw();
  }
  else if (startTimer) {
    if (st) { ofDrawBitmapStringHighlight(ofToString(endTimer), ofGetWidth() / 2, ofGetHeight() / 2 - 200); }
    else { ofDrawBitmapStringHighlight(ofToString(stopTimer), ofGetWidth() / 2, ofGetHeight() / 2 - 200); }
    guiTimer.draw();
  }
  
  
  for (int i = 0; i < 9; ++i) {
    ofPushStyle();
    ofSetColor(ofMap(i, 0, 8, 0, 255), ofMap(i, 0, 8, 100, 255), ofMap(i, 0, 8, 125, 255));
    ofRect(i * width, ofGetHeight(), width, -(wood[i] * 100));
    ofPopStyle();
  }
  // gui draw
  wdgui.draw();
  wdapp.draw();
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::claculator() {
  if (startMusic) { player.stop(); startMusic = false; ofSetFrameRate(FRAME_RATE_NORMAL); playingMusic = 0; selectMusic = 0; }
  drawResult = true;
  startTimer = false;
  
  int t = slider / 10;
  for (int i = 0; i < 9; ++i) { wood[i] = t; }
  int dt = slider - (t * 10);
  if (1 <= dt && dt <= 9) { wood[dt - 1] += 1; }
  
  for (int i = 1; i <= 9; ++i) {
    s[i] = intToUchar(wood[i - 1]);
  }
  port.writeBytes(s, sizeof(s));
  wdgui.setHeight(wood);
  result = slider;
  
//  int t = wdgui.getMin();
//  int t2 = 0;
//  for (int i = 0; i < 9; ++i) {
//    if (wood[i] - t > 0) { t2 = i + 1; }
//  }
//
//  result = t * 10 + t2;
//  
//  slider = result;
}

//--------------------------------------------------------------
void ofApp::timer() {
  if (startMusic) { player.stop(); startMusic = false; ofSetFrameRate(FRAME_RATE_NORMAL); playingMusic = 0; selectMusic = 0; }
  //
  if (!startTimer || !st) {
    beginTimer = ofGetElapsedTimef();
    startTimer = true;
    stopTimer = 0;
    for (int i = 0; i < 9; ++i) {
      stopTimer += wood[i] * 6;
    }
    wdgui.save(wood);
  }
  //
  else if (startTimer && st) {
    wdgui.load();
    float t = ofGetElapsedTimef();
    if (t - beginTimer < stopTimer) {
      if (t - beginTimer >= 6) {
        for (int i = 0; i < 9; ++i) {
          if (wood[i] > 0) { wood[i]--; wdgui.save(wood); wdgui.setHeight(wood); break; }
          wdgui.load();
        }
        
        stopTimer = stopTimer - (t - beginTimer);
        beginTimer = t;
    }
      endTimer = stopTimer - (t - beginTimer);
      
      ofxOscMessage m;
      m.setAddress("/timer");
      m.addIntArg((int)endTimer);
      sender.sendMessage(m);
      
    }
    else {
      for (int i = 0; i < 9; ++i) { wood[i] = 0; }
      wdgui.setHeight(wood);
      endTimer = -1;
    }
  }
  
  for (int i = 1; i <= 9; ++i) {
    s[i] = intToUchar(wood[i - 1]);
  }
  port.writeBytes(s, sizeof(s));
  
  
//  fib = fib_prev2 + fib_prev1;
//  fib_prev2 = fib_prev1;
//  fib_prev1 = fib;
//  
//  int k = fib % 10;
//  wood[k] = 5;
//  for (int i = 0; i < 9; ++i) {
//    if (k != i) { wood[i] = 0; }
//  }
//  
//  for (int i = 1; i <= 9; ++i) {
//    s[i] = intToUchar(wood[i - 1]);
//  }
//  port.writeBytes(s, sizeof(s));
//  wdgui.setHeight(wood);
}

//--------------------------------------------------------------
void ofApp::glaph() {
  if (startMusic) { player.stop(); startMusic = false; ofSetFrameRate(FRAME_RATE_NORMAL); playingMusic = 0; selectMusic = 0; }
  startTimer = false;
  
  if (status.length() == 3) {
    int n = 0, s = 0;
    n = ofToInt(&status[0]);
    s = ofToInt(&status[2]);
    
    //cout << "n = " << n << ", s = " << s << endl;
    
    wood[n - 1] = s / 10;
    wdgui.setHeight(wood);
  }
  else if (status.length() == 4) {
    int n = 0, s = 0;
    n = ofToInt(&status[0]);
    char str[3];
    for (int i = 2; i < status.length(); ++i) {
      str[i - 2] = status[i];
    }
    s = ofToInt(str);
    
    //cout << "n = " << n << ", s = " << s << endl;
    
    wood[n - 1] = s / 10;
    wdgui.setHeight(wood);
  }
    
  for (int i = 1; i <= 9; ++i) {
    s[i] = intToUchar(wood[i - 1]);
  }
  port.writeBytes(s, sizeof(s));
}

//--------------------------------------------------------------
void ofApp::visialaizer() {
  if (!startMusic) {
    if (selectMusic == 1) { player.loadSound(music1); playingMusic = 1; startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 2) { player.loadSound(music2); playingMusic = 2;  startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 3) { player.loadSound(music3); playingMusic = 3;  startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 4) { player.loadSound(music4); playingMusic = 4;  startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 5) { player.loadSound(music5); playingMusic = 5;  startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 6) { player.loadSound(music6); playingMusic = 6;  startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 7) { player.loadSound(music7); playingMusic = 7;  startMusic = true; player.play(); ofSetFrameRate(5); }
    else if (selectMusic == 8) { player.loadSound(music8); playingMusic = 8;  startMusic = true; player.play(); ofSetFrameRate(5); }
    startTimer = false;
  }
  else {
    if (selectMusic != playingMusic) {
      if (selectMusic == 1) { player.loadSound("goodbye2.mp3"); playingMusic = 1; startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 2) { player.loadSound("in tune.mp3"); playingMusic = 2;  startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 3) { player.loadSound(music3); playingMusic = 3;  startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 4) { player.loadSound(music4); playingMusic = 4;  startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 5) { player.loadSound(music5); playingMusic = 5;  startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 6) { player.loadSound(music6); playingMusic = 6;  startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 7) { player.loadSound(music7); playingMusic = 7;  startMusic = true; player.play(); ofSetFrameRate(5); }
      else if (selectMusic == 8) { player.loadSound(music8); playingMusic = 8;  startMusic = true; player.play(); ofSetFrameRate(5); }
    }
  
    ofSoundUpdate();
    fft = ofSoundGetSpectrum(nBandsToGet);
    int e = nBandsToGet / 9, con = 0, c = 0;
    vector<double> v(9); for (int i = 0; i < v.size(); ++i) { v[i] = 0; }
    for (int i = 0; i < nBandsToGet; ++i) {
      if (c < e) {
        v[con] += fft[i];
      }
      else {
        c = 0; con++;
        v[con] += fft[i];
      }
      ++c;
    }
    for (int i = 0; i < v.size(); ++i) {
      v[i] /= (double)e;
      v[i] *= 10;
      if (v[i] >= 1.f) { v[i] = 1.f; }
      if (v[i] <= 0.f) { v[i] = 0.f; }
    }

    for (int i = 1; i <= 9; ++i) {
      float y = ofMap(v[i - 1], 0.f, 1.f, 0.f, 5.f);
      s[i] = intToUchar(y);
      wood[i - 1] = y;
    }
    port.writeBytes(s, sizeof(s));
    wdgui.setHeight(wood);
  }
}
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  int t = -1;
  switch (key) {
    case '0': t = 10; break;
    case '1': t = 1; break;
    case '2': t = 2; break;
    case '3': t = 3; break;
    case '4': t = 4; break;
    case '5': t = 5; break;
    case '6': t = 6; break;
    case '7': t = 7; break;
    case '8': t = 8; break;
    case '9': t = 9; break;
  }
  if (1 <= t && t <= 9) {
    int temp = wood[t - 1];
    temp++;
    if (temp >= 6) {
      wood[t - 1] = 0;
    }else { wood[t - 1] = temp; }
  
    for (int i = 1; i <= 9; ++i) {
      s[i] = intToUchar(wood[i - 1]);
    }
    wdgui.setHeight(wood);
    port.writeBytes(s, sizeof(s));
  }
  else if (t == 10) {
    for (int i = 0; i < 9;++i) { wood[i] = 0; }
    
    for (int i = 1; i <= 9; ++i) {
      s[i] = intToUchar(wood[i - 1]);
    }
    wdgui.setHeight(wood);
    port.writeBytes(s, sizeof(s));
  }
  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
unsigned char ofApp::intToUchar(int i) {
  switch (i) {
     case 0: return '0';
     case 1: return '1';
     case 2: return '2';
     case 3: return '3';
     case 4: return '4';
     case 5: return '5';
  }
  return '0';
}