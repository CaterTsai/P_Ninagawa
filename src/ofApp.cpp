#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofBackground(0);
	ofSetFrameRate(30);
	
	setupLed("COM3");
	resetColor();
	setupColor();
	//setupUDP(2233);
}

//--------------------------------------------------------------
void ofApp::update(){
	//updateUDP();
	updateColor();
	
	updateLedColor();
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawColor();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'q':
	{
		randomColor();
		break;
	}
	case 's':
	{
		sendLedColor(ofColor(255, 0, 0));
		break;
	}
	case 'g':
	{
		sendLedColor(ofColor(0, 255, 0));
		break;
	}
	case 'b':
	{
		sendLedColor(ofColor(0, 0, 255));
		break;
	}
	}
}

//--------------------------------------------------------------
void ofApp::drawColor()
{
	ofPushStyle();
	float unitW = ofGetWidth() / cLedSetNum;
	float unitH = ofGetHeight() / cLedStripNum;
	for (int i = 0; i < cLedStripNum; i++)
	{
		for (int j = 0; j < cLedSetNum; j++)
		{
			int index = i * cLedSetNum + j;
			ofSetColor(_colorSet[index]);
			ofDrawRectangle(j * unitW, i * unitH, unitW, unitH);
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::resetColor()
{
	for (auto& iter : _colorSet)
	{
		iter = ofColor::black;
	}
}

//--------------------------------------------------------------
void ofApp::setColor(unsigned char(&color)[100])
{	
	for (int i = 0; i < cTotalLedColor; i++)
	{
		_colorSet[i].r = (unsigned char)color[i * 3];
		_colorSet[i].g = (unsigned char)color[i * 3 + 1];
		_colorSet[i].b = (unsigned char)color[i * 3 + 2];
	}
}

//--------------------------------------------------------------
void ofApp::setupColor()
{
	ofColor color = ofColor::red;
	for (int i = 0; i < _colorSet.size(); i++)
	{
		color.setHueAngle(ofRandom(0, 360));
		_colorB[i] = ofRandom(110, 200);
		color.setSaturation(_colorB[i]);
		_colorSet[i] = color;
	}
}

//--------------------------------------------------------------
void ofApp::updateColor()
{
	float b = sin(ofGetFrameNum() * 0.1) * 100;
	for (int i = 0; i < _colorSet.size(); i++)
	{
		_colorSet[i].setSaturation(_colorB[i] + b);
		
	}
	
}

//--------------------------------------------------------------
void ofApp::randomColor()
{
	for (auto& iter : _colorSet)
	{
		iter.r = ofRandom(0, 255);
		iter.g = ofRandom(0, 255);
		iter.b = ofRandom(0, 255);
	}
}

//--------------------------------------------------------------
void ofApp::setupUDP(int port)
{
	_receive.Create();
	if (_receive.Bind(port))
	{
		_receive.SetNonBlocking(true);
		ofLog(OF_LOG_NOTICE, "[ofApp::setupUDP]setup udp server success");
	}
}

//--------------------------------------------------------------
void ofApp::updateUDP()
{
	unsigned char data[100];
	_receive.Receive((char*)data, 100);
	
	if (data[cPacketSize] == '\x02')
	{
		setColor(data);
	}
}

//--------------------------------------------------------------
void ofApp::setupLed(string serialPort)
{
	_ledCtrl.setup(serialPort, 9600);
}

//--------------------------------------------------------------
void ofApp::updateLed()
{
	if (_ledCtrl.isInitialized())
	{
		char msg[100];
		int num = _ledCtrl.readBytes((unsigned char*)msg, 100);
		string strMsg = msg;
		if (num > 0)
		{
			//cout << strMsg << endl;
		}

	}
}

//--------------------------------------------------------------
void ofApp::updateLedColor()
{
	if (_ledCtrl.isInitialized())
	{
		unsigned char colorMsg[cPacketSize + 1];
		for (int i = 0; i < cTotalLedColor; i++)
		{
			colorMsg[i * 3] = _colorSet[i].r;
			colorMsg[i * 3 + 1] = _colorSet[i].g;
			colorMsg[i * 3 + 2] = _colorSet[i].b;
		}
		colorMsg[cPacketSize] = '\x02';
		_ledCtrl.writeBytes(colorMsg, cPacketSize + 1);
	}
}

//--------------------------------------------------------------
void ofApp::sendLedColor(ofColor test)
{
	if (_ledCtrl.isInitialized())
	{
		unsigned char colorMsg[cPacketSize + 1];
		for (int i = 0; i < cTotalLedColor; i++)
		{
			colorMsg[i * 3] = test.r;
			colorMsg[i * 3 + 1] = test.g;
			colorMsg[i * 3 + 2] = test.b;
		}
		colorMsg[cPacketSize] = '\x02';
		_ledCtrl.writeBytes(colorMsg, cPacketSize + 1);
	}
}
