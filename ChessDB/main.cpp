#include "ChessApp.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instace, LPSTR cmd_line, int show_cmd)
{
	try {
		ChessApp d(instance);
		d.Run();
	}
	catch (HRESULT h)
	{
		exit(0);
	}
}