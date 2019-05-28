#include "Object.h"
#include <string>

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
	if (mouse_info->leftButton == 3 && mouse->GetState().x*x_ratio >= sprite->GetX() && mouse->GetState().x*x_ratio <= sprite->GetX() + sprite->GetWidth() &&
		mouse->GetState().y*y_ratio >= sprite->GetY() && mouse->GetState().y*y_ratio <= sprite->GetY() + sprite->GetHeight() && !draging && !s_draging)
	{
		draging = true;
		s_draging = true;
		sprite->SetDepth(sprite->GetDepth() * 2);
		OutputDebugString((std::to_string(mouse->GetState().x*x_ratio) + " " + std::to_string(mouse->GetState().y*y_ratio) + "\n").c_str());
	}
	else if (draging && mouse_info->leftButton == 2)
	{
		draging = false;
		s_draging = false;
		sprite->SetDepth(sprite->GetDepth() / 2);
		return true;
	}
	else if (draging)
	{
		sprite->SetX(mouse->GetState().x*x_ratio - sprite->GetWidth()/2);
		sprite->SetY(mouse->GetState().y*y_ratio - sprite->GetHeight()/2);
	}
	return false;
}
void Object::Draw()
{
	sprite->Draw();
}
double Object::x_ratio = 1.0;
double Object::y_ratio = 1.0;