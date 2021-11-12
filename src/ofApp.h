#pragma once

#include "ofMain.h"

class Sprite {
protected:
	float width;
	float height;
public:
	glm::vec2 position;

	Sprite(float xPosition, float yPosition, float width, float height)
		: width{width}, height{height}, position{xPosition, yPosition} {
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

class MotionSprite : public Sprite {
public:
	glm::vec2 velocity;

	MotionSprite(float xPosition, float yPosition, float width, float height, float xSpeed, float ySpeed)
		: Sprite{xPosition, yPosition, width, height}, velocity{xSpeed, ySpeed} {
	}

	void cruiseAt(glm::vec2 newVelocity) {
		velocity = newVelocity;
	}

	void accelerate(glm::vec2 impulse) {
		velocity += impulse;
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

	Sprite p1Paddle{0, 0, 20, 100};
	Sprite p2Paddle{0, 0, 20, 100};
	MotionSprite ball{0, 0, 20, 20, 0, 0};
	int p1Score, p2Score;
};
