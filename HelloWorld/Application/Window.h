#pragma once
#include <Windows.h>

#include "Data/Config.h"

namespace Application
{
	/// <summary>
	/// ウィンドウを管理し、アプリケーションのエントリーポイントを提供するクラス。
	/// </summary>
	class Window
	{
	public:
		static Window& GetInstance()
		{
			static Window instance;
			return instance;
		}

		void Initialize(HINSTANCE hInstance, int nCmdShow);
		void Run();
		void Shutdown();

		HWND GetHWND() const { return mHWND; }
		HINSTANCE GetHInstance() const { return mHInstance; }

	private:
		Window() = default;
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		HWND mHWND = nullptr; // ウィンドウハンドル
		HINSTANCE mHInstance = nullptr; // インスタンスハンドル
		bool mIsRunning = true; // アプリケーションの実行状態
		LARGE_INTEGER mFrequency; // 高精度タイマーの周波数
		LARGE_INTEGER mLastTime; // 前回のフレーム時間

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	};

}
