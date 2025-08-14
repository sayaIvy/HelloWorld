#pragma once

namespace Config
{
	// Window settings
	constexpr int WindowWidth = 1280;
	constexpr int WindowHeight = 720;
	constexpr const WCHAR* WindowTitle = L"HelloWorld!!!!!!!";
	constexpr const WCHAR* WindowClassName = L"HelloWorldWindowClass";

	// Frame rate settings
	constexpr int TargetFrameRate = 60;
	constexpr float DeltaTime = 1.0f / TargetFrameRate;
	

}