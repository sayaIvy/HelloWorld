#include <Windows.h>
#include "Application/Window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	Application::Window& window = Application::Window::GetInstance();
	window.Initialize(hInstance, nCmdShow);
	window.Run();
	window.Shutdown();
	return 0;
}