#include "ScrollScreenCameraComponent.h"
#include "Actor.h"

ScrollScreenCameraComponent::ScrollScreenCameraComponent(Actor* ownerP) :
	CameraComponent(ownerP),
	horizontalDistance(SCROLL_HORIZONTAL_DISTANCE),
	verticalDistance(SCROLL_VERTICAL_DISTANCE),
	targetDistance(SCROLL_TARGET_DISTANCE)
{}
Vector3 ScrollScreenCameraComponent::computeCameraPosition() const{

	Vector3 cameraPosition = owner.getPosition();
	cameraPosition -= owner.getForward() * horizontalDistance;
	cameraPosition += Vector3::unitZ * verticalDistance;
	cameraPosition.y = 0.0f;
	return cameraPosition;
}


void ScrollScreenCameraComponent::update(float dt){

	CameraComponent::update(dt);

	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	target.y = 0.0f;
	Matrix4 view = Matrix4::createLookAt(computeCameraPosition(), target, Vector3::unitZ);
	setViewMatrix(view);
}

void ScrollScreenCameraComponent::setHorizontalDistance(float distance){

	horizontalDistance = distance;
}

void ScrollScreenCameraComponent::setVerticalDistance(float distance){

	verticalDistance = distance;
}

void ScrollScreenCameraComponent::setTargetDistance(float distance){

	targetDistance = distance;
}