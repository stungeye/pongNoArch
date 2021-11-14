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
void ofApp::windowResized(int w, int h) {
	if ((w != canvasWidth) || (h != canvasHeight)) {
		ofSetWindowShape(canvasWidth, canvasHeight);
	}
}
