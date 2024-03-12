#pragma once
#include "MoveComponent.h"
#include "Vector3.h"
class TorpedoMoveComponent : public MoveComponent{
public:
	TorpedoMoveComponent(class Actor* ownerP);

	void setPlayer(class Actor* playerP);

	void update(float dt) override;

	Vector3 getForwardDropSpeed()const { return forwardDropSpeed; }
	Vector3 getDownwardDropSpeed()const { return downwardDropSpeed; }
	Vector3 getWaterSpeed()const { return waterSpeed; }
protected:
	class Actor* player;
private:
	const Vector3 forwardDropSpeed = Vector3(8.0f,0.0f,0.0f);
	const Vector3 downwardDropSpeed = Vector3(0.0f,0.0f,-3.0f);
	const Vector3 waterSpeed = Vector3(15.0f,0.0,0.0f);
};

