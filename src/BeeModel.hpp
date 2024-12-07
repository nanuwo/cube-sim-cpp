#pragma once
#include <raylib.h>

class BeeModel {
private:
	Model m_model = LoadModel(ASSETS_PATH"untitled.glb");
	int m_animsCount = 0;
	unsigned int m_animIndex = 0;
	unsigned int m_animCurrentFrame = 0;
	ModelAnimation* m_anims = LoadModelAnimations(ASSETS_PATH"bee.glb", &m_animsCount);

public:
	BeeModel();
	~BeeModel();
	BeeModel(const BeeModel&) = delete;
	BeeModel& operator=(const BeeModel&) = delete;

	void update();
	Model& getModel();
};