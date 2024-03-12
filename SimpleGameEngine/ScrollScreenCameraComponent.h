#pragma once
#include "CameraComponent.h"
class ScrollScreenCameraComponent : public CameraComponent{
public:
	ScrollScreenCameraComponent(class Actor* ownerP);

	void update(float dt) override;

	void setHorizontalDistance(float distance);
	void setVerticalDistance(float distance);
	void setTargetDistance(float distance);


private:
	Vector3 computeCameraPosition() const;

	float horizontalDistance;
	float verticalDistance;
	float targetDistance;
};

constexpr float SCROLL_HORIZONTAL_DISTANCE = 100.0f;
constexpr float SCROLL_VERTICAL_DISTANCE = 1000.0f;
constexpr float SCROLL_TARGET_DISTANCE = 600.0f;

