#pragma once
#include "Sprite.h"
#include "Mouse.h"
#include "Keyboard.h"

class Object
{
	bool dragable;
	bool draging;
	static bool s_draging;
	MeridorGraphics::Sprite *sprite;

public:

	static double x_ratio;
	static double y_ratio;

	Object(MeridorGraphics::Sprite *sprite, bool dragable);
	bool Update(DirectX::Mouse::ButtonStateTracker* mouse_info, DirectX::Mouse * mouse);
	void Draw();
	int GetX() { return sprite->GetX(); }
	int GetY() { return sprite->GetY(); }
	bool GetDragable() { return dragable; }
	void SetX(int x) { sprite->SetX(x); }
	void SetY(int y) { sprite->SetY(y); }
	void SetDragable(bool dragable) { this->dragable = dragable; }
};

