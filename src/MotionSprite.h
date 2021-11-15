#pragma once
#include "Sprite.h"

class MotionSprite : public Sprite {
private:
	glm::vec2 velocity;
public:
	MotionSprite(const float xPosition, const float yPosition, const float width, const float height,
	             const float xSpeed, const float ySpeed)
		: Sprite{xPosition, yPosition, width, height}, velocity{xSpeed, ySpeed} {
	}

	void cruiseAt(const glm::vec2& newVelocity);
	void accelerate(const glm::vec2& impulse);
	void move(float deltaTime);
	void bounceHorizontalWithEdges(float ceilingY, float floorY);
	void bounceVerticalWith(const Sprite& other);
};
