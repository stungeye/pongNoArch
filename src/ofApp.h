#pragma once

#include "ofMain.h"

class Sprite {
protected:
public:
	float width;
	float height;
	glm::vec2 position;

	Sprite(float xPosition, float yPosition, float width, float height)
		: width{width}, height{height}, position{xPosition, yPosition} {
	}

	void warpTo(glm::vec2 destination) {
		position = destination;
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

	void bounceEdge(float ceilingY, float floorY) {
		if (position.y <= ceilingY || position.y >= floorY) {
			velocity.y *= -1;
			position.y = ofClamp(position.y, ceilingY, floorY);
		}
	}

	void bouncePaddle(Sprite paddle) {
		float dy = position.y - paddle.position.y;

		if (std::abs(dy) < paddle.height / 2) {
			float hitWidth = 0.5 * (width + paddle.width);
			float dx = paddle.position.x - position.x;

			if (std::abs(dx) < hitWidth) {
				// Reverse the X speed direction.
				velocity.x *= -1;

				// Increase / Decrease Y speed depending on where we hit on paddle.
				velocity.y += position.y - paddle.position.y;

				// Push ball away from paddle by the hit width.
				float direction = dx / std::abs(dx); // Convert to either +1 or -1
				position.x = paddle.position.x - (hitWidth * direction);
			}
		}
	}

	void move(float deltaTime) {
		position += velocity * deltaTime;
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

	MotionSprite p1Paddle{0, 0, 20, 100, 0, 0};
	MotionSprite p2Paddle{0, 0, 20, 100, 0, 0};
	MotionSprite ball{0, 0, 20, 20, 0, 0};
	int p1Score, p2Score;

	std::vector<float> startSpeeds{-105.0f, -70.f, -35.0f, 35.0f, 70.0f, 105.0f};
};
