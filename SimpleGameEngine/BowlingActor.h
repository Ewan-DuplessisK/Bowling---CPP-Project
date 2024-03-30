#pragma once
#include "Actor.h"
class BowlingActor : public Actor{
public:
	BowlingActor();

	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;
	void shoot();

	void setVisible(bool isVisible);
	void fixCollisions();

private:
	class MoveComponent* moveComponent;
	class AudioComponent* audioComponent;
	class MeshComponent* meshComponent;
	class BowlingCameraComponent* cameraComponent;
	class SphereActor* ball;
	class CubeActor* directionArrow;
	CubeActor* powerBar;
	float maxLaunchAngle;
	float currentAngle;
	Vector2 powerScale;
	float currentPower;
	float loopTime;
	float modTime=0.0f;
	bool isLaunched = false;
	bool isPowerSet = false;
};

