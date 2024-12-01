#include "GameObject.h"
#include "TextUIScript.h"
#include "IDamageable.h"
#include "Canvas.h"
#include "Renderer.h"

TextUIScript::TextUIScript(GameObject* gameObject)
	: Component(gameObject),
	hp(0.0f), n_remaining_frames(60),
	damageable(nullptr)
{}


void TextUIScript::update() {
	char buf[20];

	if (damageable == nullptr) return;

	float current_hp = damageable->getHealth();
	if (hp == current_hp) {
		if (n_remaining_frames == 0) {
			renderer->setEnabled(false);
		}
		else {
			n_remaining_frames--;
			renderer->setEnabled(true);
		}
		return;
	}

	hp = current_hp;
	n_remaining_frames = canvas->getFrameRate();
	sprintf(buf, "%-6.1f", hp);
	renderer->setShape(buf);
}


