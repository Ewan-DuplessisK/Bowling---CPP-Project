#pragma once
#include "Actor.h"
class ScrollScreenActor : public Actor{
public:
	ScrollScreenActor();

	void actorInput(const InputState& inputState) override;
	void shoot();
	void setVisible(bool isVisibleP);

private:
	class MoveComponent* moveComponent;
	class ScrollScreenCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
	class Actor* ScrollModel;
	const float sideLimit = 700.0f;
	const float forwardLimit = 3500.0f;

};

