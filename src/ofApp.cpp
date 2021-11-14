#include "ofApp.h"
#include <vector>


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(100);
	ofSetWindowShape(800, 500);
	ofSetWindowPosition(1000, 500);
	ofSetRectMode(OF_RECTMODE_CENTER);

	game.restartRally(PongGame::Player::p1);
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
/*	if (key == 'w') p1Paddle.cruiseAt({0, -300});
	if (key == 's') p1Paddle.cruiseAt({0, 300});
	if (key == 'i') p2Paddle.cruiseAt({0, -300});
	if (key == 'k') p2Paddle.cruiseAt({0, 300});
*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	/*
	if (key == 'w' || key == 's') p1Paddle.cruiseAt({0, 0});
	if (key == 'i' || key == 'k') p2Paddle.cruiseAt({0, 0});
	*/
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
	if ((w != 800) || (h != 500)) {
		ofSetWindowShape(800, 500);
	}
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
