#include "ofGraphics.h"
#include "ofMath.h"
#include "Sprite.h"

void Sprite::warpTo(const glm::vec2& destination) {
    position = destination;
}

void Sprite::clampToBoundary(const glm::vec2& min, const glm::vec2& max) {
    position.x = ofClamp(position.x, min.x + width / 2, max.x - width / 2);
    position.y = ofClamp(position.y, min.y + height / 2, max.y - height / 2);
}

void Sprite::draw() const {
    ofDrawRectangle(position.x, position.y, width, height);
}
