#pragma once
#include <vector>
#include "ofGraphics.h"
#include "MotionSprite.h"

class PongGame {
public:
    enum class Player { p1, p2 };

    PongGame(glm::vec2 paddleSize, glm::vec2 ballSize, glm::vec2 canvasSize, float gameSpeed)
        : gameSpeed{gameSpeed},
          canvasWidth{canvasSize.x}, canvasHeight{canvasSize.y},
          p1Paddle{0, 0, paddleSize.x, paddleSize.y, 0, 0},
          p2Paddle{0, 0, paddleSize.x, paddleSize.y, 0, 0},
          ball{0, 0, ballSize.x, ballSize.y, 0, 0} {
    }

    void restartRally(Player servingPlayer);
    void update(float deltaTime);
    void draw() const;
    void keyPressed(int key);
    void keyReleased(int key);

private:
    float gameSpeed;
    float canvasWidth, canvasHeight;
    MotionSprite p1Paddle, p2Paddle, ball;
    int p1Score{0}, p2Score{0};
    std::vector<float> startYSpeeds{-105.0f, -70.f, -35.0f, 35.0f, 70.0f, 105.0f};
};
