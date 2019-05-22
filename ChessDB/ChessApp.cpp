#include "ChessApp.h"


ChessApp::ChessApp(HINSTANCE instance) : DirectXApplication(instance)
{
	sprite_batch = new DirectX::SpriteBatch(device_context);
	sprite_font = new DirectX::SpriteFont(device, L"myfile.spritefont", false);
	mouse = new DirectX::Mouse();
	mouse->SetWindow(hwnd);
	mouse_tracker = new DirectX::Mouse::ButtonStateTracker();
}

int ChessApp::Run()
{
	return DirectXApplication::Run();
}

void ChessApp::Update(float delta_time)
{
	mouse_tracker->Update(mouse->GetState());
}

void ChessApp::Render(float delta_time)
{
}
