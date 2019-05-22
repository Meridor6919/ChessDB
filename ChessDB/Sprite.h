#pragma once
#include "SpriteBatch.h"
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include <vector>

namespace Graphics {
	class Sprite {

	protected:
		DirectX::SpriteBatch* sprite_batch;
		ID3D11ShaderResourceView* rc_view;
		float depth;
		float rotation;
		RECT source;
		LONG pos_x;
		LONG pos_y;
		LONG width;
		LONG height;
		DirectX::XMFLOAT2 orgin;
		DirectX::SpriteEffects effect;

	public:

		Sprite(DirectX::SpriteBatch* sprite_batch, RECT source, LONG pos_x, LONG pos_y, LONG width, LONG height, float depth = 0.0f, float rotation = 0.0f);
		virtual ID3D11ShaderResourceView* AddTexture(const wchar_t* file_name, ID3D11Device *device);
		virtual void Draw();
		void SetRotation(float rotation);
		void SetSourceRect(RECT source);
		void SetX(LONG pos_x);
		void SetY(LONG pos_y);
		void SetWidth(LONG width);
		void SetHeight(LONG height);
		void SetEffect(DirectX::SpriteEffects effect);
		void SetDepth(float depth);

		float GetRotation() { return rotation; }
		RECT GetSourceRect() { return source; }
		LONG GetX() { return pos_x; }
		LONG GetY() { return pos_y; }
		LONG GetWidth() { return width; }
		LONG GetHeight() { return height; }
		float GetDepth() { return depth; }
		DirectX::SpriteEffects GetEffect() { return effect; }
	};

	class Text {

		DirectX::SpriteBatch* sprite_batch;
		ID3D11ShaderResourceView* rc_view;
		DirectX::SpriteFont* sprite_font;
		float depth;
		float rotation;
		float scale;
		DirectX::XMFLOAT2 position;
		DirectX::SpriteEffects effect;

	public:

		Text(DirectX::SpriteFont* sprite_font, DirectX::SpriteBatch* sprite_batch, float fontsize, DirectX::XMFLOAT2 position, float depth = 0.0f, float rotation = 0.0f);
		void Draw(const wchar_t* text);
		void SetRotation(float rotation);
		void SetPosition(DirectX::XMFLOAT2 position);
		void SetFontSize(float font_size);
		void SetEffect(DirectX::SpriteEffects effect);
		void SetDepth(float depth);

		float GetRotation() { return rotation; }
		DirectX::XMFLOAT2 GetPosition() { return position; }
		float GetScale() { return scale; }
		DirectX::SpriteEffects GetEffect() { return effect; }
		float GetDepth() { return depth; }
	};
}