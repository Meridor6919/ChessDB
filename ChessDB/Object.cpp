#include "Object.h"


Object::Object(Graphics::Sprite * sprite, bool dragable)
{
	draging = false;
	this->dragable = dragable;
	this->sprite = sprite;
}
bool Object::s_draging = false;
bool Object::Update(DirectX::Mouse::ButtonStateTracker * mouse_info, DirectX::Mouse * mouse)
{
	if (!dragable)
		return false;

	//just started draging
	if (mouse_info->leftButton == 3 && mouse->GetState().x >= sprite->GetX() && mouse->GetState().x <= sprite->GetX() + sprite->GetWidth() &&
		mouse->GetState().y >= sprite->GetY() && mouse->GetState().y <= sprite->GetY() + sprite->GetHeight() && !draging && !s_draging)
	{
		draging = true;
		s_draging = true;
	}
	else if (draging && mouse_info->leftButton == 2)
	{
		draging = false;
		s_draging = false;
		return true;
	}
	else if (draging)
	{
		sprite->SetX(mouse->GetState().x - sprite->GetWidth()/2);
		sprite->SetY(mouse->GetState().y - sprite->GetHeight()/2);
	}
	return false;
}

void Object::Draw()
{
	sprite->Draw();
}
