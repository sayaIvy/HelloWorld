#pragma once
#include <Windows.h>

#include "Data/Config.h"

namespace Application
{
	/// <summary>
	/// �E�B���h�E���Ǘ����A�A�v���P�[�V�����̃G���g���[�|�C���g��񋟂���N���X�B
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

		HWND mHWND = nullptr; // �E�B���h�E�n���h��
		HINSTANCE mHInstance = nullptr; // �C���X�^���X�n���h��
		bool mIsRunning = true; // �A�v���P�[�V�����̎��s���
		LARGE_INTEGER mFrequency; // �����x�^�C�}�[�̎��g��
		LARGE_INTEGER mLastTime; // �O��̃t���[������

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	};

}
