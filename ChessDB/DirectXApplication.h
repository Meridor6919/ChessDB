#pragma once
#pragma warning(disable : 4996)
#pragma comment(lib, "d3d11.lib")

#include <windows.h>
#include <string>
#include <exception>
#include <directxmath.h>
#include <d3d11_1.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <time.h>
#include "Resource.h"

class DirectXApplication {

public:

	DirectXApplication(HINSTANCE instance);
	virtual void Update(float delta_time) {};
	virtual void Render(float delta_time) {};

	UINT GetWindowHeight() { return window_height; }
	UINT GetWindowWidth() { return window_width; }
	virtual int Run();
	virtual bool Init();
	virtual bool InitD3D11();
	static LRESULT CALLBACK DefaultMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
protected:

	double y_ratio;
	double x_ratio;
	HWND hwnd;
	HINSTANCE *instance;
	UINT window_width;
	UINT window_height;
	std::string title;
	DWORD window_style;
	WNDCLASSEX wc;

	ID3D11Device *device;
	ID3D11DeviceContext* device_context;
	ID3D11DepthStencilView *stencil_view;
	IDXGISwapChain* swap_chain;
	ID3D11RenderTargetView* render_target_view;
	D3D_DRIVER_TYPE driver_type;
	D3D_FEATURE_LEVEL feature_level;
	D3D11_VIEWPORT viewport;

};