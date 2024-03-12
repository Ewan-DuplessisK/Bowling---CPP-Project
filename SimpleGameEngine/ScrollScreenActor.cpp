#include "ScrollScreenActor.h"
#include "MoveComponent.h"
#include "Game.h"
#include "ScrollScreenCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "TorpedoActor.h"

ScrollScreenActor::ScrollScreenActor() :
	Actor(),
	moveComponent(nullptr),
	cameraComponent(nullptr),
	meshComponent(nullptr)
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_RacingCar"));
	setPosition(Vector3(-1000.0f, 0.0f, 100.0f));

	moveComponent = new MoveComponent(this);
	cameraComponent = new ScrollScreenCameraComponent(this);
}


void ScrollScreenActor::actorInput(const InputState& inputState){
	float forwardSpeed = 200.0f;
	float strafeSpeed = 0.0f;

	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A)&&getPosition().y>(sideLimit*-1.0f))
	{
		strafeSpeed -= 800.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D) && getPosition().y < sideLimit)
	{
		strafeSpeed += 800.0f;
	}
	if (getPosition().x > forwardLimit) {
		forwardSpeed = 0.0f;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setStrafeSpeed(strafeSpeed);

	// Shoot
	if (inputState.mouse.getButtonState(1) == ButtonState::Pressed)
	{
		shoot();
	}
}

void ScrollScreenActor::shoot()
{
	// Spawn a torpedo
	TorpedoActor* torpedo = new TorpedoActor();
	torpedo->setPlayer(this);
	Vector3 start = getPosition() + Vector3(0.0f, 0.0f, -50.0f);
	Vector3 dir =Vector3(8.0f, 0.0f, -3.0f);
	dir.normalize();
	torpedo->setPosition(start + dir * 20.0f);
	torpedo->rotateToNewForward(dir);
	
}

void ScrollScreenActor::setVisible(bool isVisibleP){
	meshComponent->setVisible(isVisibleP);
}
