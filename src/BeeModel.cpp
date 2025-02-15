#include "BeeModel.hpp"
#include <iostream>

BeeModel::BeeModel() {
}

BeeModel::~BeeModel() {
	UnloadModel(m_model);
	UnloadModelAnimations(m_anims, m_animsCount);
}

void BeeModel::update() {
	ModelAnimation anim = m_anims[0];
	m_animCurrentFrame = (m_animCurrentFrame + 1) % anim.frameCount;
	UpdateModelAnimation(m_model, anim, m_animCurrentFrame);
}

Model& BeeModel::getModel() {
	return m_model;
}
