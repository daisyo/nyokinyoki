#pragma once
#include "ofMain.h"
#include "ofxGui.h"

class wdApp {
  private:
    // gui
    ofxPanel gap;
    ofxToggle wapt[4];
    // toggle event
    void oneToggleC(bool & toggle);
    void oneToggleT(bool & tiggle);
    void oneToggleG(bool & toggle);
    void oneToggleV(bool & toggle);
  public:
    void setup();
    void draw();
    int getToggle();
    void setToggle(int r);
    void unSelect();
};