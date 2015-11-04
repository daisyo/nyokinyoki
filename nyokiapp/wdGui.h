#pragma once
#include "ofMain.h"
#include "ofxGui.h"
class wdGui {
private:
  // wood status
  const int WD_WIDTH = 3;
  const int WD_HEIGHT = 3;
  const int WD = WD_WIDTH * WD_HEIGHT;
  // gui
  ofxPanel gwd;
  ofxIntSlider wdh[9];
  ofxButton wdub[9];
  ofxButton wddb[9];
  // button event
  void woodUpButton1();
  void woodUpButton2();
  void woodUpButton3();
  void woodUpButton4();
  void woodUpButton5();
  void woodUpButton6();
  void woodUpButton7();
  void woodUpButton8();
  void woodUpButton9();
  void woodDownButton1();
  void woodDownButton2();
  void woodDownButton3();
  void woodDownButton4();
  void woodDownButton5();
  void woodDownButton6();
  void woodDownButton7();
  void woodDownButton8();
  void woodDownButton9();
  // max
  const int WD_H_MAX = 50;
  
  vector<int> prov;
public:
  void setup();
  void update();
  void draw();
  int getHeight(int index);
  vector<int> getHeight();
  void setHeight(vector<int> a);
  float getGuiWidth();
  int getMin();
  
  void save(vector<int> a);
  vector<int> load();
  
  int getWdMax();
};
