#include "TorpedoMoveComponent.h"
#include "Game.h"
#include "Warship.h"
#include "TorpedoActor.h"

TorpedoMoveComponent::TorpedoMoveComponent(Actor* ownerP) : MoveComponent(ownerP), player(nullptr){}

void TorpedoMoveComponent::setPlayer(Actor* playerP){
	player = playerP;
}

void TorpedoMoveComponent::update(float dt){

	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = owner.getPosition();
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
		dir = waterSpeed;
		owner.rotateToNewForward(dir);
		// Did we hit a target?
		Warship* target = dynamic_cast<Warship*>(info.actor);
		if (target)
		{
			static_cast<TorpedoActor*>(&owner)->hitTarget(target);
		}
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}