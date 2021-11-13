#include "ofApp.h"
#include <vector>


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(100);
	ofSetWindowShape(800, 500);
	ofSetWindowPosition(1000, 500);
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {
	// RALLY RESTART
	if (startRally) {
		startRally = false;

		const float horizontalMiddle = ofGetWidth() / 2.0f;
		const float verticalMiddle = ofGetHeight() / 2.0f;

		ball.warpTo({horizontalMiddle, verticalMiddle});
		p1Paddle.warpTo({50, verticalMiddle});
		p2Paddle.warpTo({750, verticalMiddle});

		ofRandomize(startSpeeds);
		std::cout << startSpeeds[0] << "\n";
		ball.cruiseAt({p1Serves ? 300 : -300, startSpeeds[0]});
	}

	// MOVE PADDLES
	p1Paddle.move(ofGetLastFrameTime());
	p2Paddle.move(ofGetLastFrameTime());
	p1Paddle.clampToBoundary({0, 0}, {ofGetWidth(), ofGetHeight()});
	p2Paddle.clampToBoundary({0, 0}, {ofGetWidth(), ofGetHeight()});

	// BALL EDGE BOUNCE
	ball.bounceEdge(5, 495);

	// PADDLE BOUNCE
	ball.bouncePaddle(p1Paddle);
	ball.bouncePaddle(p2Paddle);

	// MOVE BALL
	ball.move(ofGetLastFrameTime());

	// CHECK FOR WIN
	if (ball.position.x < 0) {
		++p2Score;
		startRally = true;
		p1Serves = false;
	}

	if (ball.position.x > 800) {
		++p1Score;
		startRally = true;
		p1Serves = true;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawBitmapString("P1: " + std::to_string(p1Score), 200, 40);
	ofDrawBitmapString("P2: " + std::to_string(p2Score), 550, 40);

	p1Paddle.draw();
	p2Paddle.draw();
	ball.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w') p1Paddle.cruiseAt({0, -300});
	if (key == 's') p1Paddle.cruiseAt({0, 300});
	if (key == 'i') p2Paddle.cruiseAt({0, -300});
	if (key == 'k') p2Paddle.cruiseAt({0, 300});

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'w' || key == 's') p1Paddle.cruiseAt({0, 0});
	if (key == 'i' || key == 'k') p2Paddle.cruiseAt({0, 0});
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
