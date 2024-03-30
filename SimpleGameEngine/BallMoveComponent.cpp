#include "BallMoveComponent.h"
#include "Actor.h"
#include "Vector3.h"
#include "LineSegment.h"
#include "Collisions.h"
#include "PhysicsSystem.h"
#include "BallActor.h"
#include "PinActor.h"
#include "Game.h"
#include "BoxComponent.h"

BallMoveComponent::BallMoveComponent(Actor* ownerP) : MoveComponent(ownerP), player(nullptr)
{
}

void BallMoveComponent::setPlayer(Actor* playerP)
{
	player = playerP;
}

void BallMoveComponent::update(float dt)
{
	if (dynamic_cast<BallActor*>(&owner)) {
		for(auto pin:owner.getGame().getPins()){
			if (!pin->getHasMoved()) { //ignore active pins to reduce collisions checks
				//Collisions brocken, anything below 4.5 raduis doesn't register hits, at 4.5 and over, all pins are pushed when the ball is lauched
				// Abandonned 
				if (Collisions::intersect(Sphere(owner.getPosition(), 1.0f), pin->getBoxComponent()->getObjectBox())) {
					pin->isHit(owner.getPosition());
				}
			}
		}
	}
	else {
		PinActor* own = dynamic_cast<PinActor*>(&owner);
		if (own->getHasMoved()) { //only active pins can hit other pins
			for (auto pin : owner.getGame().getPins()) {
				if (!pin->getHasMoved()) { //ignore other active pins to reduce collisions checks
					if (Collisions::intersect(own->getBoxComponent()->getObjectBox(), pin->getBoxComponent()->getObjectBox())) {
						pin->isHit(owner.getPosition());
					}
				}
			}
		}
	}
	Vector3 start = owner.getPosition();

	if (abs(start.y) > 85.0f) {
		owner.rotateToNewForward(Vector3::unitX);
		setForwardSpeed(500.0f);
	}
	else {
		if (getForwardSpeed() > 100)setForwardSpeed(getForwardSpeed() * 0.999f);
	}

	// Base class update moves based on forward speed
	MoveComponent::update(dt);
}
