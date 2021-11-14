#pragma once

class Sprite {
public:
    float width, height;
    glm::vec2 position;

    Sprite(const float xPosition, const float yPosition, const float width, const float height)
        : width{width}, height{height}, position{xPosition, yPosition} {
    }

    void warpTo(const glm::vec2& destination);
    void clampToBoundary(const glm::vec2& min, const glm::vec2& max);
    void draw() const;
};
