#include "DirectXApplication.h"

DirectXApplication::DirectXApplication(HINSTANCE instance)
{
	hwnd = 0;
	this->instance = &instance;
	window_width = 1280;
	window_height = 800;
	title = "Chess DB";
	window_style = WS_OVERLAPPED;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->DefaultMsgProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszMenuName = MAKEINTRESOURCE(RC_TOOLBAR);
	wc.lpszClassName = "xd";

	if (!Init())
		throw 1;
	if (!InitD3D11())
		throw 1;
}
int DirectXApplication::Run()
{
	float delta_time = 0.0f;
	float current_time = static_cast<float>(clock()) / static_cast<float>(CLOCKS_PER_SEC);

	HANDLE timer;
	LARGE_INTEGER large_int;
	large_int.QuadPart = -166666; //60Hz

	timer = CreateWaitableTimer(0, TRUE, "WaitableTimer");
	SetWaitableTimer(timer, &large_int, 0, 0, 0, 0);


	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SetWaitableTimer(timer, &large_int, 0, 0, 0, 0);
			Update(delta_time);
			Render(delta_time);
			WaitForSingleObject(timer, INFINITE);

			delta_time = static_cast<float>(clock()) / 1000.0f - current_time;
			current_time = static_cast<float>(clock()) / static_cast<float>(CLOCKS_PER_SEC);
		}
	}
	return static_cast<int>(msg.wParam);
}
bool DirectXApplication::reset = false;
LRESULT CALLBACK DirectXApplication::DefaultMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	switch (msg)
	{
	case WM_COMMAND:
	{
		int id = LOWORD(wparam);
		// Parse the menu selections:
		switch (id)
		{
		case RC_NEWGAME_PLAYER:
		{
			
			MessageBox(0, "RC_NEWGAME_PLAYER", "", 0);
			reset = true;
			break;
		}
		case RC_NEWGAME_AI:
		{
			MessageBox(0, "RC_NEWGAME_AI", "", 0);
			break;
		}
		case RC_SAVEGAME:
		{
			MessageBox(0, "RC_SAVEGAME", "", 0);
			break;
		}
		case RC_GAMES:
		{
			MessageBox(0, "RC_GAMES", "", 0);
			break;
		}
		case RC_PLAYERS:
		{
			MessageBox(0, "RC_PLAYERS", "", 0);
			break;
		}
		case RC_CHESSBOARD_COLOR:
		{
			MessageBox(0, "RC_CHESSBOARD_COLOR", "", 0);
			break;
		}
		case RC_INTERFACE_COLOR:
		{
			MessageBox(0, "RC_INTERFACE_COLOR", "", 0);
			break;
		}
		case RC_FULLSCREEN:
		{
			MessageBox(0, "RC_FULLSCREEN", "", 0);
			break;
		}
		case RC_GENERAL:
		{
			MessageBox(0, "RC_GENERAL", "", 0);
			break;
		}
		case RC_PIECES:
		{
			MessageBox(0, "RC_PIECES", "", 0);
			break;
		}
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
	{
		DirectX::Mouse::ProcessMessage(msg, wparam, lparam);
		break;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		DirectX::Keyboard::ProcessMessage(msg, wparam, lparam);
		break;
	}
	default:
	{
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
bool DirectXApplication::Init()
{
	if (!RegisterClassEx(&wc))
	{
		MessageBox(0, "register error", "Error", 0);
		return false;
	}
	RECT wr = { 0, 0, window_width, window_height };
	if (!AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE))
	{
		MessageBox(0, "window rect error", "Error", 0);
		return false;
	}
	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	x_ratio = (double)(wr.right - wr.left/2) / window_width;
	y_ratio = (double)(wr.bottom - wr.top/2) / window_height;

	hwnd = CreateWindowEx(NULL, "xd", title.c_str(), WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, (dr.right - window_width) / 2, (dr.bottom - window_height) / 2, wr.right - wr.left, wr.bottom - wr.top, 0, 0, *instance, 0);
	if (!hwnd)
	{
		MessageBox(0, "handle error", "Error", 0);
		return false;
	}
	if (ShowWindow(hwnd, SW_SHOW))
	{
		MessageBox(0, "show error", "Error", 0);
		return false;
	}
	RAWINPUTDEVICE Input[2];

	//keyboard
	Input[0].usUsagePage = 0x01;
	Input[0].usUsage = 0x06;
	Input[0].dwFlags = 0;
	Input[0].hwndTarget = 0;
	//mouse
	Input[1].usUsagePage = 0x01;
	Input[1].usUsage = 0x02;
	Input[1].dwFlags = 0;
	Input[1].hwndTarget = 0;
	if (!RegisterRawInputDevices(Input, 2, sizeof(Input[0])))
		return false;

	return true;
}

bool DirectXApplication::InitD3D11()
{
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	D3D_FEATURE_LEVEL feature_levels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3
	};
	DXGI_SWAP_CHAIN_DESC swap_desc = { 0 };
	swap_desc.BufferCount = 1;
	swap_desc.BufferDesc.Width = window_width;
	swap_desc.BufferDesc.Height = window_height;
	swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_desc.OutputWindow = hwnd;
	swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_desc.Windowed = true;
	swap_desc.SampleDesc.Count = 1;
	swap_desc.SampleDesc.Quality = 0;
	swap_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	for (int i = 0; i < 3; i++)
	{
		if (D3D11CreateDeviceAndSwapChain(0, driver_types[i], 0, 0, feature_levels, 4, D3D11_SDK_VERSION, &swap_desc,
			&swap_chain, &device, &feature_level, &device_context) >= 0)
		{
			driver_type = driver_types[i];
			break;
		}
	}
	ID3D11Texture2D* back_buffer = nullptr;
	swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer));
	device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
	viewport.Width = (float)window_width;
	viewport.Height = (float)window_height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	device_context->RSSetViewports(1, &viewport);

	return true;
}
