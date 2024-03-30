#include "BallMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "PinActor.h"
#include "Game.h"

BallMoveComponent::BallMoveComponent(Actor* ownerP) : MoveComponent(ownerP), player(nullptr)
{
}

void BallMoveComponent::setPlayer(Actor* playerP)
{
	player = playerP;
}

void BallMoveComponent::update(float dt)
{
	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = owner.getPosition();

	if (abs(start.y) > 85.0f) {
		owner.rotateToNewForward(Vector3::unitX);
		setForwardSpeed(500.0f);
	}
	else {
		if (getForwardSpeed() > 50)setForwardSpeed(getForwardSpeed() * 0.99f);
	}
	
	Vector3 dir = owner.getForward();
	Vector3 end = start + dir * segmentLength;

	// Create line segment
	LineSegment l(start, end);

	// Test segment vs world
	PhysicsSystem::CollisionInfo info;
	// (Don't collide vs player)
	if (owner.getGame().getPhysicsSystem().segmentCast(l, info) && info.actor != player)
	{
		// If we collided, reflect the ball about the normal
		dir = Vector3::reflect(dir, info.normal);
		owner.rotateToNewForward(dir);
		// Did we hit a target?
		PinActor* target = dynamic_cast<PinActor*>(info.actor);
		if (target)
		{
			target->isHit(owner.getPosition());
			//static_cast<BallActor*>(&owner)->hitTarget();
		}
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}
