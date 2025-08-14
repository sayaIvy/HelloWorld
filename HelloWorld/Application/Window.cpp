#include "Window.h"

#include "Utility/Logger.h"

using namespace Utility;

namespace Application
{
	void Window::Initialize(HINSTANCE hInstance, int nCmdShow)
	{
		mHInstance = hInstance;
		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = Config::WindowClassName;
		
		if(!RegisterClass(&wc))
		{
			LOG_ERROR("Failed to register window class: {}", GetLastError());
			return;
		}

		mHWND = CreateWindowEx(
			0,
			wc.lpszClassName,
			Config::WindowTitle,
			WS_OVERLAPPEDWINDOW & (~WS_THICKFRAME) & (~WS_MAXIMIZEBOX), CW_USEDEFAULT, CW_USEDEFAULT, Config::WindowWidth, Config::WindowHeight,
			nullptr, // 親ウィンドウ
			nullptr, // メニューハンドル
			hInstance,
			NULL
		);

		if(!mHWND)
		{
			LOG_ERROR("Failed to create window: {}", GetLastError());
			return;
		}

		RECT rc = {};
		GetClientRect(mHWND, &rc);
		SetWindowPos(
			mHWND,
			nullptr,
			0,
			0,
			Config::WindowWidth + (Config::WindowWidth - rc.right),
			Config::WindowHeight + (Config::WindowHeight - rc.bottom),
			SWP_NOZORDER | SWP_NOMOVE);


		ShowWindow(mHWND, nCmdShow);
		LOG_INFO("Window created successfully: {}x{} at ({}, {})", Config::WindowWidth, Config::WindowHeight, rc.left, rc.top);

		QueryPerformanceFrequency(&mFrequency);
		QueryPerformanceCounter(&mLastTime);
	}

	void Window::Run()
	{
		MSG msg = {};
		while (mIsRunning)
		{
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					mIsRunning = false;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			LARGE_INTEGER currentTime;
			QueryPerformanceCounter(&currentTime);
			float deltaTime = static_cast<float>(currentTime.QuadPart - mLastTime.QuadPart) / mFrequency.QuadPart;
			mLastTime = currentTime;
			if (deltaTime < Config::DeltaTime)
			{
				Sleep(static_cast<DWORD>((Config::DeltaTime - deltaTime) * 1000));
			}
			// Update and render logic can be added here
		}
		LOG_INFO("Application is exiting.");
	}

	void Window::Shutdown()
	{
		if (mHWND)
		{
			DestroyWindow(mHWND);
			mHWND = nullptr;
		}

		if (mHInstance)
		{
			UnregisterClass(Config::WindowClassName, mHInstance);
			mHInstance = nullptr;
		}

		mIsRunning = false;
		LOG_INFO("Application shutdown successfully.");
	}

	LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				PostQuitMessage(0); // ESCキーでアプリケーションを終了
				return 0;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}