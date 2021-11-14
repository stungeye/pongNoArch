#pragma once
#include "ofGraphics.h"
#include "ofMath.h"


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

	void bounceHorizontalEdges(float ceilingY, float floorY) {
		// Adjust ceiling and floor for ball size.
		ceilingY += height / 2.0f;
		floorY -= height / 2.0f;

		// Check and execute bounce.
		if (position.y <= ceilingY || position.y >= floorY) {
			velocity.y *= -1;
			position.y = ofClamp(position.y, ceilingY, floorY);
		}
	}

	void bounce(Sprite other) {
		float dy = position.y - other.position.y;
		float hitDistanceY = 0.5 * (height + other.height);

		// Is the ball inline with the paddle vertically?
		if (std::abs(dy) < hitDistanceY) {
			float hitDistanceX = 0.5 * (width + other.width);
			float dx = other.position.x - position.x;

			// Has the ball cross over a paddle edge?
			if (std::abs(dx) < hitDistanceX) {
				// Reverse the X speed direction.
				velocity.x *= -1;

				// Increase / Decrease Y speed depending on where we hit on paddle.
				velocity.y += position.y - other.position.y;

				// Push ball away from paddle by the hit width.
				float direction = dx / std::abs(dx); // Convert to either +1 or -1
				position.x = other.position.x - (hitDistanceX * direction);
			}
		}
	}

	void move(float deltaTime) {
		position += velocity * deltaTime;
	}

};

class PongGame {
public:
	enum class Player { p1, p2 };

	PongGame(glm::vec2 paddleSize, glm::vec2 ballSize, glm::vec2 canvasSize, float gameSpeed)
  		: gameSpeed{ gameSpeed },
          canvasWidth{canvasSize.x}, canvasHeight{canvasSize.y},
		  p1Paddle{0, 0, paddleSize.x, paddleSize.y, 0, 0},
          p2Paddle{0, 0, paddleSize.x, paddleSize.y, 0, 0}, 
          ball{0, 0, ballSize.x, ballSize.y, 0, 0} {
	}

    void restartRally(Player servingPlayer);
    void update(float deltaTime);
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);

private:
	float gameSpeed;
	float canvasWidth, canvasHeight;
	MotionSprite p1Paddle, p2Paddle, ball;
	int p1Score{0}, p2Score{0};
	std::vector<float> startYSpeeds{-105.0f, -70.f, -35.0f, 35.0f, 70.0f, 105.0f};
};
