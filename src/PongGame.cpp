#include "PongGame.h"
#include "ofUtils.h"

void PongGame::restartRally(const Player servingPlayer) {
    const auto horizontalMiddle{canvasWidth / 2.0f};
    const auto verticalMiddle{canvasHeight / 2.0f};
    ball.warpTo({horizontalMiddle, verticalMiddle});

    const auto paddleEdgeBuffer{50.0f};
    p1Paddle.warpTo({paddleEdgeBuffer, verticalMiddle});
    p2Paddle.warpTo({canvasWidth - paddleEdgeBuffer, verticalMiddle});

    ofRandomize(startYSpeeds);
    const auto xSpeed = servingPlayer == Player::p1 ? gameSpeed : -gameSpeed;
    const auto ySpeed = startYSpeeds[0];
    ball.cruiseAt({xSpeed, ySpeed});
}

void PongGame::update(const float deltaTime) {
    // MOVE PADDLES
    p1Paddle.move(deltaTime);
    p2Paddle.move(deltaTime);
    p1Paddle.clampToBoundary({0, 0}, {canvasWidth, canvasHeight});
    p2Paddle.clampToBoundary({0, 0}, {canvasWidth, canvasHeight});

    // BALL EDGE BOUNCE
    ball.bounceHorizontalEdges(0, canvasHeight);

    // PADDLE BOUNCE
    ball.bounce(p1Paddle);
    ball.bounce(p2Paddle);

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

void PongGame::draw() const {
    const auto scoreFromEdge{200};
    ofDrawBitmapString("P1: " + std::to_string(p1Score), scoreFromEdge, 40);
    ofDrawBitmapString("P2: " + std::to_string(p2Score), canvasWidth - scoreFromEdge - 50, 40);

    p1Paddle.draw();
    p2Paddle.draw();
    ball.draw();
}

void PongGame::keyPressed(int key) {
    if (key == 'w') p1Paddle.cruiseAt({0, -gameSpeed});
    if (key == 's') p1Paddle.cruiseAt({0, gameSpeed});
    if (key == 'i') p2Paddle.cruiseAt({0, -gameSpeed});
    if (key == 'k') p2Paddle.cruiseAt({0, gameSpeed});
}

void PongGame::keyReleased(int key) {
    if (key == 'w' || key == 's') p1Paddle.cruiseAt({0, 0});
    if (key == 'i' || key == 'k') p2Paddle.cruiseAt({0, 0});
}
