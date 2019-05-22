#include "Sprite.h"

Graphics::Sprite::Sprite(DirectX::SpriteBatch* sprite_batch, RECT source, LONG pos_x, LONG pos_y, LONG width, LONG height, float depth, float rotation)
{
	this->sprite_batch = sprite_batch;
	this->depth = depth;
	this->rotation = rotation;
	this->source = source;
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->width = width;
	this->height = height;
	//orgin will be at the middle of the sprite to allow rotation around its own axis
	this->orgin = { static_cast<float>(source.right) / 2.0f, static_cast<float>(source.bottom) / 2.0f };
	this->effect = DirectX::SpriteEffects::SpriteEffects_None;
}
ID3D11ShaderResourceView * Graphics::Sprite::AddTexture(const wchar_t * file_name, ID3D11Device * device)
{
	DirectX::CreateWICTextureFromFile(device, file_name, nullptr, &rc_view);
	return rc_view;
}
void Graphics::Sprite::Draw()
{
	//destination RECT now will be placed accordingly to top-left corner
	sprite_batch->Draw(rc_view, { pos_x + width / 2, pos_y + height / 2, width + pos_x + width / 2, height + pos_y + height / 2 }, &source, DirectX::Colors::White, rotation, orgin, effect, depth);
}
void Graphics::Sprite::SetRotation(float rotation)
{
	this->rotation = rotation;
}
void Graphics::Sprite::SetSourceRect(RECT source)
{
	this->source = source;
}
void Graphics::Sprite::SetX(LONG pos_x)
{
	this->pos_x = pos_x;
}
void Graphics::Sprite::SetY(LONG pos_y)
{
	this->pos_y = pos_y;
}
void Graphics::Sprite::SetWidth(LONG width)
{
	this->width = width;
}
void Graphics::Sprite::SetHeight(LONG height)
{
	this->height = height;
}
void Graphics::Sprite::SetEffect(DirectX::SpriteEffects effect)
{
	this->effect = effect;
}
void Graphics::Sprite::SetDepth(float depth)
{
	this->depth = depth;
}
Graphics::Text::Text(DirectX::SpriteFont* sprite_font, DirectX::SpriteBatch* sprite_batch, float fontsize, DirectX::XMFLOAT2 position, float depth, float rotation)
{
	this->sprite_font = sprite_font;
	this->sprite_batch = sprite_batch;
	this->scale = fontsize / 32.0f;
	this->depth = depth;
	this->rotation = rotation;
	this->position = position;
	this->effect = DirectX::SpriteEffects::SpriteEffects_None;
}
void Graphics::Text::Draw(const wchar_t* text)
{
	sprite_font->DrawString(sprite_batch, text, position, DirectX::Colors::White, rotation, { 0.0f,0.0f }, scale, effect, depth);
}

void Graphics::Text::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void Graphics::Text::SetPosition(DirectX::XMFLOAT2 position)
{
	this->position = position;
}

void Graphics::Text::SetFontSize(float font_size)
{
	this->scale = font_size / 32.0f;
}

void Graphics::Text::SetEffect(DirectX::SpriteEffects effect)
{
	this->effect = effect;
}

void Graphics::Text::SetDepth(float depth)
{
	this->depth = depth;
}
