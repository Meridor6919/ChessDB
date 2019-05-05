#include "DirectXApplication.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instace, LPSTR cmd_line, int show_cmd)
{
	try {
		DirectXApplication d(instance);
		d.Run();
	}
	catch (HRESULT h)
	{
		exit(0);
	}
}