#include "PinActor.h"
#include "BoxComponent.h"
#include "Assets.h"
#include "Collisions.h"
#include "Game.h"
#include "BallMoveComponent.h"
#include "AudioComponent.h"

PinActor::PinActor() :boxComponent(nullptr),moveComponent(nullptr),lifetimeSpan(2.0f),audioComponent(nullptr) {
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
	boxComponent = bc;
	audioComponent = new AudioComponent(this);
	//moveComponent = new MoveComponent(this);
}

void PinActor::updateActor(float dt) {
	Actor::updateActor(dt);
	if(hasMoved)lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
	fixCollisions();
}

void PinActor::fixCollisions()
{
	// Need to recompute world transform to update world box
	computeWorldTransform();

	const AABB& playerBox = boxComponent->getWorldBox();
	Vector3 pos = getPosition();

	auto& planes = getGame().getPlanes();
	for (auto pa : planes)
	{
		// Do we collide with this PlaneActor?
		const AABB& planeBox = pa->getBox()->getWorldBox();
		if (Collisions::intersect(playerBox, planeBox))
		{
			// Calculate all our differences
			float dx1 = planeBox.max.x - playerBox.min.x;
			float dx2 = planeBox.min.x - playerBox.max.x;
			float dy1 = planeBox.max.y - playerBox.min.y;
			float dy2 = planeBox.min.y - playerBox.max.y;
			float dz1 = planeBox.max.z - playerBox.min.z;
			float dz2 = planeBox.min.z - playerBox.max.z;

			// Set dx to whichever of dx1/dx2 have a lower abs
			float dx = Maths::abs(dx1) < Maths::abs(dx2) ? dx1 : dx2;
			// Ditto for dy
			float dy = Maths::abs(dy1) < Maths::abs(dy2) ? dy1 : dy2;
			// Ditto for dz
			float dz = Maths::abs(dz1) < Maths::abs(dz2) ? dz1 : dz2;

			// Whichever is closest, adjust x/y position
			if (Maths::abs(dx) <= Maths::abs(dy) && Maths::abs(dx) <= Maths::abs(dz))
			{
				pos.x += dx;
			}
			else if (Maths::abs(dy) <= Maths::abs(dx) && Maths::abs(dy) <= Maths::abs(dz))
			{
				pos.y += dy;
			}
			else
			{
				pos.z += dz;
			}

			// Need to set position and update box component
			setPosition(pos);
			boxComponent->onUpdateWorldTransform();
		}
	}
}

void PinActor::isHit(Vector3 origin) {
	moveComponent = new BallMoveComponent(this);
	origin.z = getPosition().z;
	Vector3 newForward = getPosition() - origin;
	newForward.normalize();
	rotateToNewForward(newForward);
	moveComponent->setForwardSpeed(650.0f);
	hasMoved = true;
}