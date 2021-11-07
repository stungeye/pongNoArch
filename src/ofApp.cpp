#include "ofApp.h"
#include <vector>

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(800, 500);
	ofSetWindowPosition(1000, 500);
	ofSetRectMode(OF_RECTMODE_CENTER);
	p1PaddleYPosition = 250;
	p2PaddleYPosition = 250;
	ofSetFrameRate(100);
	playerOneServes = ofRandom(0, 100) > 50; 
}

//--------------------------------------------------------------
void ofApp::update() {
	// RALLY RESTART
	if (startRally) {
		startRally = false;

		ballXPosition = ofGetWidth() / 2.0f;
		ballYPosition = ofGetHeight() / 2.0f;

		p1PaddleYPosition = ofGetHeight() / 2.0f;
		p2PaddleYPosition = ofGetHeight() / 2.0f;

		std::vector<float> startSpeeds{-120.0f, -110.f, -100.0f, 100.0f, 110.0f, 120.0f};
		ofRandomize(startSpeeds);

		ballYSpeed = startSpeeds[0];
		ballXSpeed = playerOneServes ? 300 : -300;
	}

	// MOVE PADDLES
	double speedChange{500 * ofGetLastFrameTime()};

	if (playerOneUpPress) p1PaddleYPosition -= speedChange;
	if (playerOneDownPress) p1PaddleYPosition += speedChange;
	if (playerTwoUpPress) p2PaddleYPosition -= speedChange;
	if (playerTwoDownPress) p2PaddleYPosition += speedChange;

	p1PaddleYPosition = ofClamp(p1PaddleYPosition, 50, 450);
	p2PaddleYPosition = ofClamp(p2PaddleYPosition, 50, 450);

	// BALL EDGE BOUNCE
	if (ballYPosition <= 5) {
		ballYPosition = 5;
		ballYSpeed *= -1;
	} else if (ballYPosition >= 495) {
		ballYPosition = 495;
		ballYSpeed *= -1;
	}

	// PLAYER ONE BALL PADDLE BOUNCE
	if (ballXPosition > 50 && ballXPosition < 65) {
		if (ballYPosition > p1PaddleYPosition - 50 && ballYPosition < p1PaddleYPosition + 50) {
			// Reverse the X speed direction.
			ballXSpeed *= -1;
			// Increase / Decrease Y speed depending on where we hit on paddle.
			ballYSpeed += ballYPosition - p1PaddleYPosition;
			// Push ball away from paddle on hit. 
			ballXPosition = 65;
		}
	}

	// PLAYER TWO BALL PADDLE BOUNCE
	if (ballXPosition < 750 && ballXPosition > 735) {
		if (ballYPosition > p2PaddleYPosition - 50 && ballYPosition < p2PaddleYPosition + 50) {
			// Reverse the X speed direction.
			ballXSpeed *= -1;
			// Increase / Decrease Y speed depending on where we hit on paddle.
			ballYSpeed += ballYPosition - p2PaddleYPosition;
			// Push ball away from paddle on hit. 
			ballXPosition = 735;
		}
	}

	// MOVE BALL
	ballXPosition += ballXSpeed * ofGetLastFrameTime();
	ballYPosition += ballYSpeed * ofGetLastFrameTime();

	// CHECK FOR WIN
	if (ballXPosition < 0) {
		++playerTwoScore;
		startRally = true;
		playerOneServes = false;
	}

	if (ballXPosition > 800) {
		++playerOneScore;
		startRally = true;
		playerOneServes = true;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawBitmapString("P1: " + std::to_string(playerOneScore), 200, 40);
	ofDrawBitmapString("P2: " + std::to_string(playerTwoScore), 550, 40);

	ofDrawRectangle(50, p1PaddleYPosition, 20, 100);
	ofDrawRectangle(750, p2PaddleYPosition, 20, 100);

	ofDrawCircle(ballXPosition, ballYPosition, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w') playerOneUpPress = true;
	if (key == 's') playerOneDownPress = true;
	if (key == 'i') playerTwoUpPress = true;
	if (key == 'k') playerTwoDownPress = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'w') playerOneUpPress = false;
	if (key == 's') playerOneDownPress = false;
	if (key == 'i') playerTwoUpPress = false;
	if (key == 'k') playerTwoDownPress = false;
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
