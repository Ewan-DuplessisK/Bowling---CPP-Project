#pragma once
#include "CameraComponent.h"
class BowlingCameraComponent : public CameraComponent{
public:
	BowlingCameraComponent(class Actor* ownerP);

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

constexpr float BOWLING_HORIZONTAL_DISTANCE = 50.0f;
constexpr float BOWLING_VERTICAL_DISTANCE = 20.0f;
constexpr float BOWLING_TARGET_DISTANCE = 100.0f;


