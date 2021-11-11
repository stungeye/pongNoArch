#pragma once

#include "ofMain.h"

class Sprite {
protected:
	float width;
	float height;
public:
	glm::vec2 position;

	Sprite(float xPosition, float yPosition, float width, float height)
		: position{xPosition, yPosition}, width{width}, height{height} {
	}

	void warpTo(glm::vec2 destination) {
		position = destination;
	}

	void moveBy(glm::vec2 delta) {
		position += delta;
	}

	void clampToBoundary(glm::vec2 min, glm::vec2 max) {
		position.x = ofClamp(position.x, min.x + width / 2, max.x - width / 2);
		position.y = ofClamp(position.y, min.y + height / 2, max.y - height / 2);
	}

	void draw() {
		ofDrawRectangle(position.x, position.y, width, height);
	}
};

class Paddle : public Sprite {
public:
	enum class Side { left, right };

	Paddle(float xPosition, float yPosition, float width, float height, Side side)
		: Sprite{xPosition, yPosition, width, height}, side{side} {
	}

private:
	Side side;
};

class Ball : public Sprite {
	Ball(float xPosition, float yPosition, float width, float height)
		: Sprite{xPosition, yPosition, width, height} {
	}

};

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

	Paddle p1Paddle{0, 0, 20, 100, Paddle::Side::left};
	Paddle p2Paddle{0, 0, 20, 100, Paddle::Side::right};
	int p1Score, p2Score;
};
