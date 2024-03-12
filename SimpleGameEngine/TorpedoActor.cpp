#include "TorpedoActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "AudioComponent.h"
#include "TorpedoMoveComponent.h"

TorpedoActor::TorpedoActor(): Actor(), lifetimeSpan(2.0f), audio(nullptr), torpedoMove(nullptr){
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	audio = new AudioComponent(this);
	torpedoMove = new TorpedoMoveComponent(this);
	torpedoMove->setForwardSpeed(1500.0f);
}

void TorpedoActor::updateActor(float dt){
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void TorpedoActor::setPlayer(Actor* player){
	torpedoMove->setPlayer(player);
}

void TorpedoActor::hitTarget(Actor* target){
	audio->playEvent("event:/Ding");
	target->setState(ActorState::Dead);
	lifetimeSpan = -1.0f;
}
