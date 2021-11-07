#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void mouseMoved(int x, int y) override;
	void mouseDragged(int x, int y, int button) override;
	void mousePressed(int x, int y, int button) override;
	void mouseReleased(int x, int y, int button) override;
	void mouseEntered(int x, int y) override;
	void mouseExited(int x, int y) override;
	void windowResized(int w, int h) override;
	void dragEvent(ofDragInfo dragInfo) override;
	void gotMessage(ofMessage msg) override;

private:
	float p1PaddleYPosition;
	float p2PaddleYPosition;

	float ballXPosition;
	float ballYPosition;

	float ballXSpeed;
	float ballYSpeed;

	int playerOneScore;
	int playerTwoScore;

	bool startRally = true;
	bool playerOneUpPress, playerOneDownPress, playerTwoUpPress, playerTwoDownPress;
};
