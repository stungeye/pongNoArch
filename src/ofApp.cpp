#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(100);
	ofSetWindowShape(canvasWidth, canvasHeight);
	ofSetWindowPosition(1000, 500);
	ofSetRectMode(OF_RECTMODE_CENTER);

	const auto startingServe = ofRandom(0, 100) < 50 ? PongGame::Player::p1 : PongGame::Player::p2;
	game.restartRally(startingServe);
}

//--------------------------------------------------------------
void ofApp::update() {
	game.update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw() {
	game.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	game.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	game.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	if ((w != canvasWidth) || (h != canvasHeight)) {
		ofSetWindowShape(canvasWidth, canvasHeight);
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
