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
	bool startRally{true};
	bool p1Serves{ofRandom(0, 100) > 50};
	bool p1UpPress, p1DownPress, p2UpPress, p2DownPress;

	float ballXPosition, ballYPosition;
	float ballXSpeed, ballYSpeed;

	float p1YPosition, p2YPosition;
	int p1Score, p2Score;
};
