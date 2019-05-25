#pragma once
#include "DirectXApplication.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include <SpriteFont.h>
#include "Object.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "CommonStates.h"
#include "Effects.h"

class ChessApp : DirectXApplication
{
public:
	ChessApp(HINSTANCE instance);
	int Run();

private:

	
	DirectX::Mouse* mouse;
	DirectX::Mouse::ButtonStateTracker* mouse_tracker;

	DirectX::SpriteBatch* sprite_batch;
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor >* primitive_batch;
	DirectX::CommonStates* m_states;
	DirectX::BasicEffect* m_effect;
	ID3D11InputLayout* m_inputLayout;
	DirectX::SpriteFont* sprite_font;
	Graphics::Sprite *a;
	std::vector< Object*> b;

	void Update(float delta_time);
	void Render(float delta_time);
};

