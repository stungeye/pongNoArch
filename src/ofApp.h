#pragma once

#include "ofMain.h"
#include "PongGame.h"


class ofApp : public ofBaseApp {

public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void windowResized(int w, int h) override;

private:
	const static int canvasWidth{800}, canvasHeight{500};
	PongGame game{{20, 100}, {20, 20}, {canvasWidth, canvasHeight}, 400};
};
