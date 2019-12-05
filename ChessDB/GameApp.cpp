#include "GameApp.h"


GameApp::GameApp(HINSTANCE instance) : DirectXApplication(instance)
{
	common_states = std::make_unique<DirectX::CommonStates>(device);
	basic_effect = std::make_unique<DirectX::BasicEffect>(device);
	basic_effect->SetVertexColorEnabled(true);


	void const* shaderByteCode;
	size_t byteCodeLength;

	basic_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		&input_layout);

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, float(window_width), float(window_height), 0.f, 0.f, 1.f);
	basic_effect->SetProjection(proj);

	sprite_batch = std::make_shared<DirectX::SpriteBatch>(device_context);
	primitive_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(device_context);
	sprite_font = std::make_unique<DirectX::SpriteFont>(device, L"myfile.spritefont", false);
	mouse = std::make_unique<DirectX::Mouse>();
	mouse->SetWindow(hwnd);
	mouse_tracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	keyboard = std::make_unique<DirectX::Keyboard>();
	keyboard_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	game = std::make_unique<Game>(sprite_batch.get(), device);
}

void GameApp::Update(float delta_time)
{
	mouse_tracker->Update(mouse->GetState());
	keyboard_tracker->Update(keyboard->GetState());
	auto keyboard_state = keyboard->GetState();
	if (keyboard_state.R)
	{
		game = std::make_unique<Game>(sprite_batch.get(), device);
	}
	else if (keyboard_state.Escape)
	{
		exit(0);
	}
	game->Update(mouse_tracker.get(), mouse.get(), keyboard_tracker.get(), keyboard.get(), delta_time);
}

void GameApp::Render(float delta_time)
{
	Clear();
	game->DrawPrimitiveBatch(primitive_batch.get(), delta_time);
	game->DrawSpriteBatch(sprite_batch.get(), delta_time);
	swap_chain->Present(0, 0);


}

void GameApp::Clear()
{
	device_context->ClearRenderTargetView(render_target_view, DirectX::Colors::White);
	device_context->ClearDepthStencilView(stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	device_context->OMSetRenderTargets(1, &render_target_view, stencil_view);

	CD3D11_VIEWPORT viewPort(0.0f, 0.0f, static_cast<float>(window_width), static_cast<float>(window_height));
	device_context->RSSetViewports(1, &viewPort);
	basic_effect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	basic_effect->Apply(device_context);

	float f[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	D3D11_BLEND_DESC BlendStateDescription;
	ZeroMemory(&BlendStateDescription, sizeof(D3D11_BLEND_DESC));

	ID3D11BlendState* blend;

	BlendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	BlendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	BlendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

	BlendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
	BlendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	BlendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	device->CreateBlendState(&BlendStateDescription, &blend);
	float blendFactor[] = { 0, 0, 0, 0 };

	device_context->OMSetBlendState(blend, blendFactor, 0x0000000f);
	device_context->OMSetDepthStencilState(common_states->DepthDefault(), 0);
	device_context->RSSetState(common_states->CullNone());
	device_context->IASetInputLayout(input_layout);

}
