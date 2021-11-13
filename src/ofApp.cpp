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

		std::vector<float> startSpeeds{-120.0f, -110.f, -100.0f, 100.0f, 110.0f, 120.0f};
		ofRandomize(startSpeeds);
		ball.cruiseAt({p1Serves ? 300 : -300, startSpeeds[0]});
	}

	// MOVE PADDLES
	const double speedChange{300 * ofGetLastFrameTime()};

	if (p1UpPress) p1Paddle.moveBy({0, -speedChange});
	if (p1DownPress)p1Paddle.moveBy({0, speedChange});
	if (p2UpPress) p2Paddle.moveBy({0, -speedChange});
	if (p2DownPress)p2Paddle.moveBy({0, speedChange});

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

	//	ofDrawRectangle(50, p1YPosition, 20, 100);
	//	ofDrawRectangle(750, p2YPosition, 20, 100);
	p1Paddle.draw();
	p2Paddle.draw();
	ball.draw();

	//	ofDrawRectangle(ballXPosition, ballYPosition, 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w') p1UpPress = true;
	if (key == 's') p1DownPress = true;
	if (key == 'i') p2UpPress = true;
	if (key == 'k') p2DownPress = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'w') p1UpPress = false;
	if (key == 's') p1DownPress = false;
	if (key == 'i') p2UpPress = false;
	if (key == 'k') p2DownPress = false;
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
