#pragma once
#include "DirectXApplication.h"
#include "PrimitiveBatch.h"
#include "SpriteBatch.h"
#include "VertexTypes.h"
#include "CommonStates.h"
#include "Effects.h"
#include <SpriteFont.h>
#include "SimpleMath.h"
#include "Game.h"


class GameApp : DirectXApplication
{
protected:

	std::unique_ptr<DirectX::Mouse> mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mouse_tracker;
	std::unique_ptr<DirectX::Keyboard> keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboard_tracker;
	std::shared_ptr<DirectX::SpriteBatch> sprite_batch;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> primitive_batch;
	std::unique_ptr<DirectX::CommonStates> common_states;
	std::unique_ptr<DirectX::BasicEffect> basic_effect;
	std::unique_ptr<DirectX::SpriteFont> sprite_font;
	std::unique_ptr<Game> game;
	ID3D11InputLayout *input_layout;

	void Update(float delta_time) override;
	void Render(float delta_time) override;
	void Clear();

public:
	GameApp(HINSTANCE instance);
	int Run() { return DirectXApplication::Run(); };

};

