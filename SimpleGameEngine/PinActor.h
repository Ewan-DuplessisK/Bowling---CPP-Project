#pragma once
#include "CubeActor.h"

class BoxComponent;

class PinActor : public CubeActor{
public:
	PinActor();
	void updateActor(float dt);
	void fixCollisions();
	void isHit(Vector3 origin);
	bool getHasMoved() { return hasMoved; }
	BoxComponent* getBoxComponent() { return boxComponent; }

private:
	bool hasMoved = false;
	float lifetimeSpan;
	BoxComponent* boxComponent;
	class BallMoveComponent* moveComponent;
	class AudioComponent* audioComponent;
};

