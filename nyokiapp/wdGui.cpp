#include "ofMain.h"
#include "wdGui.h"
//--------------------------------------------------------------
void wdGui::setup(){
  // set up to gui
  gwd.setup();
  wdub[0].addListener(this, &wdGui::woodUpButton1);
  wdub[1].addListener(this, &wdGui::woodUpButton2);
  wdub[2].addListener(this, &wdGui::woodUpButton3);
  wdub[3].addListener(this, &wdGui::woodUpButton4);
  wdub[4].addListener(this, &wdGui::woodUpButton5);
  wdub[5].addListener(this, &wdGui::woodUpButton6);
  wdub[6].addListener(this, &wdGui::woodUpButton7);
  wdub[7].addListener(this, &wdGui::woodUpButton8);
  wdub[8].addListener(this, &wdGui::woodUpButton9);
  wddb[0].addListener(this, &wdGui::woodDownButton1);
  wddb[1].addListener(this, &wdGui::woodDownButton2);
  wddb[2].addListener(this, &wdGui::woodDownButton3);
  wddb[3].addListener(this, &wdGui::woodDownButton4);
  wddb[4].addListener(this, &wdGui::woodDownButton5);
  wddb[5].addListener(this, &wdGui::woodDownButton6);
  wddb[6].addListener(this, &wdGui::woodDownButton7);
  wddb[7].addListener(this, &wdGui::woodDownButton8);
  wddb[8].addListener(this, &wdGui::woodDownButton9);
  for (int i = 0; i < WD; ++i) {
    gwd.add(wdh[i].setup("wood " + ofToString(i + 1), 0, 0, 5));
    gwd.add(wdub[i].setup("up_button " + ofToString(i + 1)));
    gwd.add(wddb[i].setup("down_button " + ofToString(i + 1)));
  }
}
//--------------------------------------------------------------
void wdGui::draw() {
  gwd.draw();
}
//--------------------------------------------------------------
// 0 origin
int wdGui::getHeight(int index) {
  int t = wdh[index]; return t;
}
//--------------------------------------------------------------
vector<int> wdGui::getHeight() {
  vector<int> a(9);
  for (int i = 0; i < WD; ++i) { a[i] = wdh[i]; }
  return a;
}
//--------------------------------------------------------------
float wdGui::getGuiWidth() {
  return gwd.getWidth();
}
//--------------------------------------------------------------
void wdGui::setHeight(vector<int> a) {
  for (int i = 0; i < WD; ++i) { wdh[i] = a[i]; }
}
//--------------------------------------------------------------
int wdGui::getMin() {
  int t = wdh[0];
  for (int i = 1; i < WD; ++i) { if (t > wdh[i]) { t = wdh[i]; } }
  return t;
}
//--------------------------------------------------------------
void wdGui::save(vector<int> a) { prov = a; }
//--------------------------------------------------------------
vector<int> wdGui::load() {
  for (int i = 0; i < prov.size(); ++i) {
    wdh[i] = prov[i];
  }
  return prov;
}
//--------------------------------------------------------------
int wdGui::getWdMax() { return WD_H_MAX; }
//--------------------------------------------------------------
void wdGui::woodUpButton1(){
  int ind = 0;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton2(){
  int ind = 1;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton3(){
  int ind = 2;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton4(){
  int ind = 3;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton5(){
  int ind = 4;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton6(){
  int ind = 5;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton7(){
  int ind = 6;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton8(){
  int ind = 7;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodUpButton9(){
  int ind = 8;
  if (wdh[ind] < WD_H_MAX) { int t = wdh[ind]; t++; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton1() {
  int ind = 0;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton2() {
  int ind = 1;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton3() {
  int ind = 2;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton4() {
  int ind = 3;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton5() {
  int ind = 4;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton6() {
  int ind = 5;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton7() {
  int ind = 6;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton8() {
  int ind = 7;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}
//--------------------------------------------------------------
void wdGui::woodDownButton9() {
  int ind = 8;
  if (wdh[ind] > 0) { int t = wdh[ind]; t--; wdh[ind] = t; }
}