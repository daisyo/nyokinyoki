#include "ofMain.h"
#include "wdApp.h"

//--------------------------------------------------------------
void wdApp::setup() {
  gap.setup();
  wapt[0].addListener(this, &wdApp::oneToggleC);
  wapt[1].addListener(this, &wdApp::oneToggleT);
  wapt[2].addListener(this, &wdApp::oneToggleG);
  wapt[3].addListener(this, &wdApp::oneToggleV);
  gap.add(wapt[0].setup("clac", false));
  gap.add(wapt[1].setup("timer", false));
  gap.add(wapt[2].setup("glaph", false));
  gap.add(wapt[3].setup("visializer", false));
  gap.setPosition(240, 0);
}

//--------------------------------------------------------------
void wdApp::draw() {
  gap.draw();
}

//--------------------------------------------------------------
int wdApp::getToggle() {
  for (int i = 0; i < 4; ++i) {
    if (wapt[i] == true) { return i; }
  }
  return 4;
}

//--------------------------------------------------------------
void wdApp::setToggle(int r) {
  wapt[r] = true;
  for (int i = 0; i < 4; ++i) { if (i != r) { wapt[i] = false; } }
}

void wdApp::unSelect() {
  for (int i = 0; i < 4; ++i) { wapt[i] = false; }
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
void wdApp::oneToggleC(bool & toggle) {
  if (toggle == true) {
    for (int i = 1; i < 4; ++i) { wapt[i] = false; }
  }
}
//--------------------------------------------------------------
void wdApp::oneToggleT(bool & toggle) {
  if (toggle == true) {
    wapt[0] = false; wapt[2] = false; wapt[3] = false;
  }
}
//--------------------------------------------------------------
void wdApp::oneToggleG(bool & toggle) {
  if (toggle == true) {
    wapt[0] = false; wapt[1] = false; wapt[3] = false;
  }
}
//--------------------------------------------------------------
void wdApp::oneToggleV(bool & toggle) {
  if (toggle == true) {
    wapt[0] = false; wapt[1] = false; wapt[2] = false;
  }
}