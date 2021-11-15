#include "ofGraphics.h"
#include "ofMath.h"
#include "MotionSprite.h"

void MotionSprite::cruiseAt(const glm::vec2& newVelocity) {
	velocity = newVelocity;
}

void MotionSprite::accelerate(const glm::vec2& impulse) {
	velocity += impulse;
}

void MotionSprite::move(const float deltaTime) {
	position += velocity * deltaTime;
}

void MotionSprite::bounceHorizontalWithEdges(float ceilingY, float floorY) {
	// Adjust ceiling and floor for ball size.
	ceilingY += height / 2.0f;
	floorY -= height / 2.0f;

	// Check and execute bounce.
	if (position.y <= ceilingY || position.y >= floorY) {
		velocity.y *= -1;
		position.y = ofClamp(position.y, ceilingY, floorY);
	}
}

void MotionSprite::bounceVerticalWith(const Sprite& other) {
	const auto dy{position.y - other.position.y};
	const auto hitDistanceY{0.5f * (height + other.height)};

	// Is the ball inline with the other sprite vertically?
	if (std::abs(dy) < hitDistanceY) {
		const auto hitDistanceX{0.5f * (width + other.width)};
		const auto dx{other.position.x - position.x};

		// Has the ball cross over the other sprite's vertical edge?
		if (std::abs(dx) < hitDistanceX) {
			// Reverse the X speed direction.
			velocity.x *= -1;

			// Increase / Decrease Y speed depending on where we hit the other sprite.
			accelerate({0, position.y - other.position.y});

			// Push ball away from colliding sprite by the hit width.
			const auto direction = dx / std::abs(dx); // Convert to either +1 or -1
			position.x = other.position.x - (hitDistanceX * direction);
		}
	}
}
