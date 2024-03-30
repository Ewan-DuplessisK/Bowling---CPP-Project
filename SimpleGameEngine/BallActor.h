#pragma once
#include "Actor.h"
class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget();
	void setSpeed(float speedP);


private:
	class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	class MeshComponent* mesh;
	float lifetimeSpan;
};

