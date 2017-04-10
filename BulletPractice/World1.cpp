#include "World1.h"

World1::World1(ID3D11Device * device, Enemy* enemy) : 
	World(device),
	Enemy1(enemy)
{

}

World1::~World1() {

	delete Enemy1;
}

void World1::update(float deltaTime) {
	if (Enemy1) {
		Enemy1->update(deltaTime);
	}
}

void World1::draw(ID3D11DeviceContext* deviceContext, CXMMATRIX orthoMatrix) {
	if (Enemy1) {
		Enemy1->draw(deviceContext, orthoMatrix);
	}
	for (int i = 0; i < 10000; i++) {
		if (Bullets[i]) {
			Bullets[i]->draw(deviceContext, orthoMatrix);
		}
	}
}