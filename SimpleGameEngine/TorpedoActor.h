#pragma once
#include "Actor.h"
class TorpedoActor : public Actor {
public:
	TorpedoActor();
	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget(Actor*);


private:
	class AudioComponent* audio;
	class TorpedoMoveComponent* torpedoMove;
	float lifetimeSpan;
};

