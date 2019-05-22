#pragma once
#include "DirectXApplication.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include <SpriteFont.h>
#include "Object.h"

class ChessApp : DirectXApplication
{
public:
	ChessApp(HINSTANCE instance);
	int Run();

private:

	
	DirectX::Mouse* mouse;
	DirectX::Mouse::ButtonStateTracker* mouse_tracker;

	DirectX::SpriteBatch* sprite_batch;
	DirectX::SpriteFont* sprite_font;
	Graphics::Sprite *a;
	Object *b;

	void Update(float delta_time);
	void Render(float delta_time);
};

