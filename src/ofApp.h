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
		// Adjust ceiling and floor for ball size.
		ceilingY += height / 2.0f;
		floorY -= height / 2.0f;

		// Check and execute bounce.
		if (position.y <= ceilingY || position.y >= floorY) {
			velocity.y *= -1;
			position.y = ofClamp(position.y, ceilingY, floorY);
		}
	}

	void bouncePaddle(Sprite paddle) {
		float dy = position.y - paddle.position.y;
		float hitDistanceY = 0.5 * (height + paddle.height);

		// Is the ball inline with the paddle vertically?
		if (std::abs(dy) < hitDistanceY) {
			float hitDistanceX = 0.5 * (width + paddle.width);
			float dx = paddle.position.x - position.x;

			// Has the ball cross over a paddle edge?
			if (std::abs(dx) < hitDistanceX) {
				// Reverse the X speed direction.
				velocity.x *= -1;

				// Increase / Decrease Y speed depending on where we hit on paddle.
				velocity.y += position.y - paddle.position.y;

				// Push ball away from paddle by the hit width.
				float direction = dx / std::abs(dx); // Convert to either +1 or -1
				position.x = paddle.position.x - (hitDistanceX * direction);
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

	void restartRally(Player servingPlayer) {
		const float horizontalMiddle = canvasWidth / 2.0f;
		const float verticalMiddle = canvasHeight / 2.0f;
		ball.warpTo({horizontalMiddle, verticalMiddle});

		const float paddleEdgeBuffer = 50;
		p1Paddle.warpTo({paddleEdgeBuffer, verticalMiddle});
		p2Paddle.warpTo({canvasWidth - paddleEdgeBuffer, verticalMiddle});

		ofRandomize(startYSpeeds);
		const float xSpeed = servingPlayer == Player::p1 ? gameSpeed : -gameSpeed;
		const float ySpeed = startYSpeeds[0];
		ball.cruiseAt({xSpeed, ySpeed});
	}

	void update(float deltaTime) {
        // MOVE PADDLES
        p1Paddle.move(deltaTime);
        p2Paddle.move(deltaTime);
        p1Paddle.clampToBoundary({0, 0}, {canvasWidth, canvasHeight});
        p2Paddle.clampToBoundary({0, 0}, {canvasWidth, canvasHeight});

        // BALL EDGE BOUNCE
        ball.bounceEdge(0, canvasHeight);

        // PADDLE BOUNCE
        ball.bouncePaddle(p1Paddle);
        ball.bouncePaddle(p2Paddle);

        // MOVE BALL
        ball.move(deltaTime);

        // CHECK FOR WIN
        if (ball.position.x < 0) {
            ++p2Score;
			restartRally(Player::p2);
        }

        if (ball.position.x > canvasWidth) {
            ++p1Score;
			restartRally(Player::p1);
        }
	}

	void draw() {
		const float scoreFromEdge = 200;
        ofDrawBitmapString("P1: " + std::to_string(p1Score), scoreFromEdge, 40);
        ofDrawBitmapString("P2: " + std::to_string(p2Score), canvasWidth - scoreFromEdge - 50, 40);

        p1Paddle.draw();
        p2Paddle.draw();
        ball.draw();
	}

	void keyPressed(int key) {
        if (key == 'w') p1Paddle.cruiseAt({0, -gameSpeed});
        if (key == 's') p1Paddle.cruiseAt({0, gameSpeed});
        if (key == 'i') p2Paddle.cruiseAt({0, -gameSpeed});
        if (key == 'k') p2Paddle.cruiseAt({0, gameSpeed});
	}

	void keyReleased(int key) {
        if (key == 'w' || key == 's') p1Paddle.cruiseAt({0, 0});
        if (key == 'i' || key == 'k') p2Paddle.cruiseAt({0, 0});
	}

private:
	const 

	float gameSpeed;
	float canvasWidth, canvasHeight;
	MotionSprite p1Paddle, p2Paddle, ball;
	int p1Score{0}, p2Score{0};
	std::vector<float> startYSpeeds{-105.0f, -70.f, -35.0f, 35.0f, 70.0f, 105.0f};
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
	const static int canvasWidth{ 800 }, canvasHeight{ 500 };
	PongGame game{ {20, 100}, {20, 20}, {canvasWidth, canvasHeight}, 300 };
};