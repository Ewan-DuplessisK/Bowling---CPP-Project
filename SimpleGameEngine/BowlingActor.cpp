#include "BowlingActor.h"
#include "MoveComponent.h"
#include "AudioComponent.h"
#include "Game.h"
#include "BowlingCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "BallActor.h"
#include "SphereActor.h"
#include "Collisions.h"
#include "CubeActor.h"
#include <iostream>

BowlingActor::BowlingActor() : Actor(), moveComponent(nullptr), audioComponent(nullptr), meshComponent(nullptr), cameraComponent(nullptr), ball(nullptr), powerBar(nullptr),directionArrow(nullptr) {
	setScale(Vector3(1.0f, 1.0f, 1.0f));
	moveComponent = new MoveComponent(this);
	audioComponent = new AudioComponent(this);
	cameraComponent = new BowlingCameraComponent(this);

	ball = new SphereActor();
	powerBar = new CubeActor();
	powerBar->setPosition(Vector3(10.0f, -35.0f, 50.0f));
	powerBar->setRotation(Quaternion(Vector3(0.0f, 0.0f, 1.0f), 1));
	directionArrow = new CubeActor();
	directionArrow->setPosition(Vector3(25.0f, 0.0f, 10.0f));
	directionArrow->setScale(Vector3(50.0f, 10.0f, 1.0f));
	meshComponent = new MeshComponent(ball);
	meshComponent->setMesh(Assets::getMesh("Mesh_Sphere"));
	powerScale = Vector2(250.0f, 600.0f);
}

void BowlingActor::updateActor(float dt) {
	Actor::updateActor(dt);
	if (!isLaunched) {
		modTime = modTime + dt;
		float loopAlpha = sin(modTime * 2) / 2.0f + 0.5f;
		if (!isPowerSet) {
			currentPower = powerScale.x + (powerScale.y - powerScale.x) * loopAlpha;
			powerBar->setScale(Vector3(10.0f, 10.0f, loopAlpha * 50.0f));
		}
		else {
			currentAngle = sin(modTime); //rad
			directionArrow->setRotation(Quaternion(Vector3(0.0f, 0.0f, 1.0f), currentAngle));
		}

	}
}

void BowlingActor::actorInput(const InputState& inputState)
{
	if (inputState.mouse.getButtonState(1) == ButtonState::Released && !isLaunched)
	{
		if (isPowerSet) {
			isLaunched = true;
			modTime = 0.0f;
			shoot();
		}
		isPowerSet = true;
	}
}

void BowlingActor::shoot()
{
	// Get start point (in center of screen on near plane)
	// Get end point (in center of screen, between near and far)
	//dir.normalize();
	// Spawn a ball
	BallActor* ball = new BallActor();
	ball->setPlayer(this);
	ball->setPosition(Vector3(0.0f,0.0f,5.0f) /* + dir * 20.0f*/);
	ball->setSpeed(currentPower);
	// Rotate the ball to face new direction
	ball->setRotation(Quaternion(Vector3(0.0f, 0.0f, 1.0f), currentAngle));
	// Play shooting sound
	audioComponent->playEvent("event:/Shot");
}

void BowlingActor::setVisible(bool isVisible){
	meshComponent->setVisible(isVisible);
}

void BowlingActor::fixCollisions()
{
}
