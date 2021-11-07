#include "ofApp.h"
#include <vector>

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(800, 500);
	ofSetWindowPosition(1000, 500);
	ofSetRectMode(OF_RECTMODE_CENTER);
	p1PaddleYPosition = 250;
	p2PaddleYPosition = 250;

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

		if (ofRandom(0, 100) > 50) {
			ballXSpeed = -5;
		} else {
			ballXSpeed = 5;
		}

		std::vector<float> startSpeeds{-2.0f, -1.5f, -1.0f, 1.0f, 1.5f, 2.0f};
		ofRandomize(startSpeeds);

		ballYSpeed = startSpeeds[0];
	}

	// MOVE PADDLES
	float speedChange{10};
	if (playerOneUpPress) {
		if (p1PaddleYPosition <= 50) {
			p1PaddleYPosition = 50;
		} else {
			p1PaddleYPosition -= speedChange;
		}
	}

	if (playerOneDownPress) {
		if (p1PaddleYPosition >= 450) {
			p1PaddleYPosition = 450;
		} else {
			p1PaddleYPosition += speedChange;
		}
	}

	if (playerTwoUpPress) {
		if (p2PaddleYPosition <= 50) {
			p2PaddleYPosition = 50;
		} else {
			p2PaddleYPosition -= speedChange;
		}
	}

	if (playerTwoDownPress) {
		if (p2PaddleYPosition >= 450) {
			p2PaddleYPosition = 450;
		} else {
			p2PaddleYPosition += speedChange;
		}
	}


	// BALL EDGE BOUNCE
	if (ballYPosition <= 5) {
		ballYPosition = 5;
		ballYSpeed *= -1;
	} else if (ballYPosition >= 495) {
		ballYPosition = 495;
		ballYSpeed *= -1;
	}

	// BALL PADDLE BOUNCE
	if (ballXPosition >= 50 && ballXPosition <= 60) {
		if (ballYPosition > p1PaddleYPosition - 50 && ballYPosition < p1PaddleYPosition + 50) {
			ballXSpeed *= -1;
			ballXPosition = 61;
		}
	}

	if (ballXPosition <= 750 && ballXPosition >= 740) {
		if (ballYPosition > p2PaddleYPosition - 50 && ballYPosition < p2PaddleYPosition + 50) {
			ballXSpeed *= -1;
			ballXPosition = 739;
		}
	}

	// MOVE BALL
	ballXPosition += ballXSpeed;
	ballYPosition += ballYSpeed;

	// CHECK FOR WIN
	if (ballXPosition < 0) {
		++playerTwoScore;
		startRally = true;
	}

	if (ballXPosition > 800) {
		++playerOneScore;
		startRally = true;
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
