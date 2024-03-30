#include "BowlingCameraComponent.h"
#include "Actor.h"

BowlingCameraComponent::BowlingCameraComponent(Actor* ownerP) :CameraComponent(ownerP), horizontalDistance(BOWLING_HORIZONTAL_DISTANCE),verticalDistance(BOWLING_VERTICAL_DISTANCE),targetDistance(BOWLING_TARGET_DISTANCE) {}

Vector3 BowlingCameraComponent::computeCameraPosition() const {

	Vector3 cameraPosition = owner.getPosition();
	cameraPosition -= owner.getForward() * horizontalDistance;
	cameraPosition += Vector3::unitZ * verticalDistance;
	cameraPosition.y = 0.0f;
	return cameraPosition;
}

void BowlingCameraComponent::update(float dt){
	CameraComponent::update(dt);

	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	target.y = 0.0f;
	Matrix4 view = Matrix4::createLookAt(computeCameraPosition(), target, Vector3::unitZ);
	setViewMatrix(view);
}

void BowlingCameraComponent::setHorizontalDistance(float distance) {

	horizontalDistance = distance;
}

void BowlingCameraComponent::setVerticalDistance(float distance) {

	verticalDistance = distance;
}

void BowlingCameraComponent::setTargetDistance(float distance) {

	targetDistance = distance;
}