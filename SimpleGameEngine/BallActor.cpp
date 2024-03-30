#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "AudioComponent.h"
#include "BallMoveComponent.h"

BallActor::BallActor() : Actor(), lifetimeSpan(10.0f), audio(nullptr), ballMove(nullptr), mesh(nullptr)
{
	mesh = new MeshComponent(this);
	mesh->setMesh(Assets::getMesh("Mesh_Sphere"));
	audio = new AudioComponent(this);
	ballMove = new BallMoveComponent(this);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);
	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget()
{
	audio->playEvent("event:/Ding");
}

void BallActor::setSpeed(float speedP) {
	ballMove->setForwardSpeed(speedP);
}
