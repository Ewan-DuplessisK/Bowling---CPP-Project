#include "Warship.h"
#include "BoxComponent.h"
#include "Assets.h"

Warship::Warship() {
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Cube").getBox());
}