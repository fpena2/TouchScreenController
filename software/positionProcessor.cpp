#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofEnableDepthTest();
	grandChildNode.setPosition(x, y , 0);
	ofBackground(0, 0, 0);


	serial.listDevices();
	vector<ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	int baud = 56000;
	serial.setup("COM17", baud); 
}

//--------------------------------------------------------------
void ofApp::update() {

	// ============== Communication ============================

	unsigned char dataFromSerial[20];
	string cleanBuffer;
	string yStringVal;
	string xStringVal;
	int xValue = 0;
	int yValue = 0;

	memset(dataFromSerial, 0, 20);
	serial.readBytes(dataFromSerial, 20);
	
	for (int x = 0; x < 20; x++) {
		if ( isprint(dataFromSerial[x]) ) {
			if (dataFromSerial[x] > 39 && dataFromSerial[x] < 58) {
				cleanBuffer += dataFromSerial[x];
			}
		}
	}
	
	int midPosition = cleanBuffer.find(",");
	
	if (cleanBuffer.find('(') != std::string::npos && cleanBuffer.find(')') != std::string::npos) {
		//cout << cleanBuffer << endl;

		xStringVal = cleanBuffer.substr(1, midPosition - 1);
		xValue = stoi(xStringVal);
		//cout << xValue << endl;

		yStringVal = cleanBuffer.substr(midPosition + 1);
		yStringVal.pop_back();
		yValue = stoi(yStringVal);
		//cout << yValue << endl;
	}

	// Process Section 
	// NO PRESS
	if (yValue < 6) {
		// nothing
	}
	//DOWN
	else if (xValue >= 3995 && xValue <= 4005 && yValue >= 3995 && yValue <= 4005) {
		y = y + 5;
		grandChildNode.setPosition(0, y, 0);
	}
	// UP
	else if (xValue >= 3995 && xValue <= 4005 && yValue >= 3985 && yValue <= 4090) {
		y = y - 5;
		grandChildNode.setPosition(0, y, 0);
	}
	// RIGHT
	else if (xValue >= 3980 && xValue <= 3990 && yValue >= 3965 && yValue <= 3975) {
		x = x + 5; 
		grandChildNode.setPosition(x, 0, 0);
	}
	// DOWN
	else if (xValue >= 4010 && xValue <= 4020 && yValue >= 4025 && yValue <= 4030) {
		x = x - 5;
		grandChildNode.setPosition(x, 0, 0);
	}

	ofSetColor(ofColor::fromHex(0xFFFFFF));
	ofSetLineWidth(5);
	line.addVertex(grandChildNode.getGlobalPosition());
	if (line.size() > 400) {
		line.getVertices().erase(
			line.getVertices().begin()
		);
	}
}
//--------------------------------------------------------------
void ofApp::draw() {

//	ofColor white = ofColor::fromHex(0xFFFFFF);
//	ofColor black = ofColor::fromHex(0x000000);
//	ofColor yellow = ofColor::fromHex(0xffee00);

	cam.begin();
	line.draw();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
