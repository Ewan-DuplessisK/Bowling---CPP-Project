#pragma once
#include "CubeActor.h"

class PinActor : public CubeActor{
public:
	PinActor();
	void updateActor(float dt);
	void fixCollisions();
	void isHit(Vector3 origin);

private:
	bool hasMoved = false;
	float lifetimeSpan;
	class BoxComponent* boxComponent;
	class BallMoveComponent* moveComponent;
	class AudioComponent* audioComponent;
};

