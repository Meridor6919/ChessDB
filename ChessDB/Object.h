#pragma once
#include "Sprite.h"
#include "Mouse.h"

class Object
{
	bool dragable;
	bool draging;
	static bool s_draging;
	Graphics::Sprite *sprite;

public:
	Object(Graphics::Sprite *sprite, bool dragable);
	bool Update(DirectX::Mouse::ButtonStateTracker* mouse_info, DirectX::Mouse * mouse);
	void Draw();
	int GetX() { return sprite->GetX(); }
	int GetY() { return sprite->GetY(); }
	void SetX(int x) { sprite->SetX(x); }
	void SetY(int y) { sprite->SetY(y); }
};

