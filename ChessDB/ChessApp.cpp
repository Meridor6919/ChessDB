#include "ChessApp.h"


ChessApp::ChessApp(HINSTANCE instance) : DirectXApplication(instance)
{
	sprite_batch = new DirectX::SpriteBatch(device_context);
	sprite_font = new DirectX::SpriteFont(device, L"myfile.spritefont", false);
	mouse = new DirectX::Mouse();
	mouse->SetWindow(hwnd);
	mouse_tracker = new DirectX::Mouse::ButtonStateTracker();

	a = new Graphics::Sprite(sprite_batch, { 0,0,60,60 }, 400, 100, 120, 120, 0.1);
	a->AddTexture(L"figures.png", device);
	b = new Object(a, true);
}

int ChessApp::Run()
{
	return DirectXApplication::Run();
}

void ChessApp::Update(float delta_time)
{
	mouse_tracker->Update(mouse->GetState());
	b->Update(mouse_tracker, mouse);
}

void ChessApp::Render(float delta_time)
{
	float f[4] = { 0,0,0,0.7f };
	sprite_batch->Begin(DirectX::SpriteSortMode_FrontToBack);
	device_context->ClearRenderTargetView(render_target_view, f);
	b->Draw();

	sprite_batch->End();
	swap_chain->Present(0, 0);
}
