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

		ballXPosition = ofGetWidth() / 2.0f;
		const float horizontalMiddle = ofGetWidth() / 2.0f;
		const float verticalMiddle = ofGetHeight() / 2.0f;
		ballYPosition = verticalMiddle;
		ball.warpTo({horizontalMiddle, verticalMiddle});
		p1Paddle.warpTo({50, verticalMiddle});
		p2Paddle.warpTo({750, verticalMiddle});

		std::vector<float> startSpeeds{-120.0f, -110.f, -100.0f, 100.0f, 110.0f, 120.0f};
		ofRandomize(startSpeeds);

		ballYSpeed = startSpeeds[0];
		ballXSpeed = p1Serves ? 300 : -300;
		ball.cruiseAt({startSpeeds[0], p1Serves ? 300 : -300});
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
	if (ballYPosition <= 5 || ballYPosition >= 495) {
		ballYSpeed *= -1;
		ballYPosition = ofClamp(ballYPosition, 5, 495);
	}

	// PLAYER ONE BALL PADDLE BOUNCE
	if ((ballXPosition > 50 && ballXPosition < 65)
		&& (ballYPosition > p1Paddle.position.y - 50)
		&& (ballYPosition < p1Paddle.position.y + 50)) {
		// Reverse the X speed direction.
		ballXSpeed *= -1;
		// Increase / Decrease Y speed depending on where we hit on paddle.
		ballYSpeed += ballYPosition - p1Paddle.position.y;
		// Push ball away from paddle on hit to the right.
		ballXPosition = 65;
	}

	// PLAYER TWO BALL PADDLE BOUNCE
	if ((ballXPosition > 735 && ballXPosition < 750)
		&& (ballYPosition > p2Paddle.position.y - 50)
		&& (ballYPosition < p2Paddle.position.y + 50)) {
		// Reverse the X speed direction.
		ballXSpeed *= -1;
		// Increase / Decrease Y speed depending on where we hit on paddle.
		ballYSpeed += ballYPosition - p2Paddle.position.y;
		// Push ball away from paddle on hit to the left.
		ballXPosition = 735;
	}

	// MOVE BALL
	ballXPosition += ballXSpeed * ofGetLastFrameTime();
	ballYPosition += ballYSpeed * ofGetLastFrameTime();

	// CHECK FOR WIN
	if (ballXPosition < 0) {
		++p2Score;
		startRally = true;
		p1Serves = false;
	}

	if (ballXPosition > 800) {
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

	ofDrawRectangle(ballXPosition, ballYPosition, 20, 20);
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
