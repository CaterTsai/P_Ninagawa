#pragma once

#include "constParameter.h"
#include "ofxNetwork.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);


//--------------------------------
//Display Color
public:
	void drawColor();
	void resetColor();
	void setColor(unsigned char(&color)[100]);

//Debug
	void setupColor();
	void updateColor();
	void randomColor();
private:
	array<ofColor, cTotalLedColor> _colorSet;
	array<float, cTotalLedColor> _colorB;

//--------------------------------
//Udp Server
public:
	void setupUDP(int port);
	void updateUDP();
private:
	ofxUDPManager	_receive;

//--------------------------------
//Led Control
public:
	void setupLed(string serialPort);
	void updateLed();
	void updateLedColor();
	void sendLedColor(ofColor test);

private:
	ofSerial	_ledCtrl;

};
