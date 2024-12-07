#include "BeeModel.hpp"

BeeModel::BeeModel() {
}

BeeModel::~BeeModel() {
	UnloadModel(m_model);
}

void BeeModel::update() {
	ModelAnimation anim = m_anims[m_animIndex];
	m_animCurrentFrame = (m_animCurrentFrame + 1) % anim.frameCount;
	UpdateModelAnimation(m_model, anim, m_animCurrentFrame);
}

Model& BeeModel::getModel() {
	return m_model;
}
