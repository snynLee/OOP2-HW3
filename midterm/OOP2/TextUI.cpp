#include "TextUI.h"
#include "IDamageable.h"
#include "Canvas.h"

TextUI::TextUI(GameObject* parent, const Position& pos, const Dimension& dim)
	: GameObject(parent, "", pos - Dimension{3,0}, dim), hp(0.0f),
	n_remaining_frames(60), 
	damageable(dynamic_cast<IDamageable*>(parent))
{}


void TextUI::draw() {
	if (n_remaining_frames == 0) return;

	GameObject::draw();
}

void TextUI::update() {
	char buf[20];

	if (damageable == nullptr) return;

	if (n_remaining_frames > 0) --n_remaining_frames;

	float current_hp = damageable->getHealth();
	if (hp == current_hp) return;

	hp = current_hp;
	n_remaining_frames = canvas->getFrameRate();
	sprintf(buf, "%-6.1f", hp);
	setShape(buf);
}
