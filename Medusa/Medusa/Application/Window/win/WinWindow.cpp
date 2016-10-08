// Copyright (c) 2015 fjz13. All rights reserved.
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file.
#include "MedusaPreCompiled.h"

#ifdef MEDUSA_WINDOWS

#include "WinWindow.h"
#include "Graphics/ResolutionAdapter.h"
#include "Node/Input/InputManager.h"
#include "Node/Input/Touch.h"
#include "Node/Input/EventArg/TouchEventArg.h"
#include "Node/Input/EventArg/KeyDownEventArg.h"
#include "Node/Input/EventArg/KeyUpEventArg.h"
#include "Node/Input/EventArg/ScrollEventArg.h"
#include "Node/Input/EventArg/CharInputEventArg.h"
#include "Application/Application.h"
#include "Application/ApplicationStatics.h"

MEDUSA_BEGIN;

LRESULT CALLBACK _WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WinWindow* currentWindow = (WinWindow*)Application::Instance().Window();
	if (currentWindow->WindowHandle() != hWnd)
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	else
	{
		return currentWindow->WndProc(message, wParam, lParam);
	}


}

WinWindow::WinWindow(MedusaWindowHandle parentWindow, StringRef name/*=StringRef::Empty*/) :IWindow(parentWindow, name)
{

}

WinWindow::~WinWindow()
{

}

bool WinWindow::Initialize()
{
	RETURN_FALSE_IF_FALSE(IWindow::Initialize());

	//register window class
	WNDCLASSEX wcex;

	HINSTANCE instance = GetModuleHandle(nullptr);

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC&~WS_CAPTION&~WS_SYSMENU;
	wcex.lpfnWndProc = _WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = instance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"MedusaGameWindow";
	wcex.hIconSm = nullptr;

	if (!RegisterClassEx(&wcex))
	{
		/*DWORD err= GetLastError();*/
		//log error
		MEDUSA_ASSERT_FAILED("");

	}

	////get window rect
	WHeapString windowName = StringParser::ToW(mName);

	//int windowStyle=mParentWindowHandle==nullptr?WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX:WS_CHILDWINDOW|WS_VISIBLE;
	int windowStyle = mParentWindowHandle == nullptr ? WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX : WS_CHILDWINDOW | WS_VISIBLE;

	mWindowHandle = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, L"MedusaGameWindow", windowName.c_str(), windowStyle,
		0, 0, (int)mSize.Width, (int)mSize.Height, mParentWindowHandle, nullptr, instance, nullptr);

	RegisterTouchWindow(mWindowHandle, 0);

	//ImmAssociateContext(mWindowHandle, nullptr);	//disable ime

	if (!mWindowHandle)
	{
		/*DWORD err= GetLastError();*/
		//log error
		MEDUSA_ASSERT_FAILED("");
	}

	//SetForegroundWindow(mWindowHandle);
	MakeCenter();
	Resize(mSize);
	ShowWindow(mWindowHandle, SW_SHOW);
	UpdateWindow(mWindowHandle);

	return true;
}


bool WinWindow::Uninitialize()
{
	RETURN_TRUE_IF_NULL(mWindowHandle);
	if (DestroyWindow(mWindowHandle) != 0)
	{
		//DWORD error= GetLastError();
		mWindowHandle = nullptr;
	}

	mWindowHandle = nullptr;

	HINSTANCE instance = GetModuleHandle(nullptr);
	if (!UnregisterClass(L"MedusaGameWindow", instance))
	{
		/*DWORD err= GetLastError();*/
		//log error
		MEDUSA_ASSERT_FAILED("");
	}
	return true;
}

void WinWindow::Show()
{

}


bool WinWindow::OnEvent(IEventArg& eventArg)
{
	return true;
}


bool WinWindow::Start()
{
	RETURN_FALSE_IF_FALSE(IWindow::Start());

	// Main message loop:
	MSG msg;

	HACCEL hAccelTable = nullptr;

	mWatch.Start();


	while (1)
	{
		if (!PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (IsRunning())
			{
				// Get current time tick.
				//mNow= PerformanceCounter::Ticks();
				mWatch.Shot();
				float dt = mWatch.ElapsedSeconds();

				// If it's the time to draw next frame, draw it, else sleep a while.
				if (dt >= Application::Instance().FrameIntervalSeconds())
				{
					mWatch.Go();
					if (!Application::Instance().UpdateAndDraw(dt))
					{
						break;
					}
				}
				else
				{
					Sleep(1);
				}
			}
			else if (IsDone())
			{
				break;	//quit
			}
			else
			{
				Sleep(1);	//not active
			}

		}
		else
		{
			if (WM_QUIT == msg.message)
			{
				// Quit message loop
				break;
			}

			if (hAccelTable == nullptr || !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

	}

	return (int)msg.wParam >= 0;
}


bool WinWindow::Stop()
{
	RETURN_FALSE_IF_FALSE(IWindow::Stop());
	mWatch.Reset();
	return true;
}

bool WinWindow::Pause()
{
	RETURN_FALSE_IF_FALSE(IWindow::Pause());
	mWatch.Reset();

	return true;
}

bool WinWindow::Resume()
{
	RETURN_FALSE_IF_FALSE(IWindow::Resume());
	mWatch.Start();
	return true;
}

void WinWindow::MakeCenter()
{
	RETURN_IF_NULL(mWindowHandle);
	RECT parentRect;
	RECT selfRect;
	MedusaWindowHandle parentWindowHandle = mParentWindowHandle;
	if (parentWindowHandle == nullptr)
	{
		parentWindowHandle = GetDesktopWindow();
		GetClientRect(parentWindowHandle, &parentRect);

		// subtract the task bar
		HWND hTaskBar = FindWindow(TEXT("Shell_TrayWnd"), nullptr);
		if (hTaskBar != nullptr)
		{
			APPBARDATA abd;

			abd.cbSize = sizeof(APPBARDATA);
			abd.hWnd = hTaskBar;

			SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
			SubtractRect(&parentRect, &parentRect, &abd.rc);
		}

		GetWindowRect(mWindowHandle, &selfRect);

		int offsetX = (parentRect.right - parentRect.left - (selfRect.right - selfRect.left)) / 2;
		offsetX = (offsetX > 0) ? offsetX : parentRect.left;
		int offsetY = (parentRect.bottom - parentRect.top - (selfRect.bottom - selfRect.top)) / 2;
		offsetY = (offsetY > 0) ? offsetY : parentRect.top;

		SetWindowPos(mWindowHandle, 0, offsetX, offsetY, 0, 0, SWP_NOCOPYBITS | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	}
	else
	{
		GetClientRect(parentWindowHandle, &parentRect);
		MoveWindow(mWindowHandle, parentRect.left, parentRect.top, (int)mSize.Width, (int)mSize.Height, TRUE);
	}

}

void WinWindow::Resize(const Size2F& newSize)
{
	RECT clientRect;
	GetClientRect(mWindowHandle, &clientRect);
	if (clientRect.right - clientRect.left == (int)newSize.Width&&clientRect.bottom - clientRect.top == (int)newSize.Height)
	{
		return;
	}

	clientRect.right = clientRect.left + (int)newSize.Width;
	clientRect.bottom = clientRect.top + (int)newSize.Height;

	AdjustWindowRectEx(&clientRect, GetWindowLong(mWindowHandle, GWL_STYLE), FALSE, GetWindowLong(mWindowHandle, GWL_EXSTYLE));
	SetWindowPos(mWindowHandle, 0, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	OnResize(newSize);
}


void WinWindow::OnResize(const Size2F& newSize)
{
	mSize = newSize;

	WHeapString windowName = StringParser::ToW(mName);
	WHeapString title;
	title.AppendFormat(L"{}    {}*{}", windowName.c_str(), (int)newSize.Width, (int)newSize.Height);
	SetWindowText(mWindowHandle, title.c_str());

	for (auto view : mViews)
	{
		view->Resize(newSize);
	}
	FOR_EACH_TO(mViews, Resize(newSize));
	ResolutionAdapter::Instance().SetWinSize(newSize);
}


LRESULT WinWindow::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	SetFocus(mWindowHandle);
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(mWindowHandle, &ps);
		EndPaint(mWindowHandle, &ps);
	}
	break;
	case WM_DESTROY:
		//DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		if (MK_LBUTTON == wParam)
		{
			SetCapture(mWindowHandle);
			short xi = Math::ClampAboveZero((short)LOWORD(lParam));
			short yi = Math::ClampAboveZero((short)HIWORD(lParam));
			float x = Math::Clamp((float)xi, 0.f, mSize.Width);
			float y = mSize.Height - Math::Clamp((float)yi, 0.f, mSize.Height);

			double timeStamp = Application::Instance().TimeStamp();
			Touch touch(TouchPhase::Began, 0, timeStamp, mpp(x, y), Point2F::Zero);
			TouchEventArg e(TouchPhase::Began, touch);
			InputManager::Instance().TouchesBegan(e);
			mPrevMouseTouch = touch;
		}
		break;
	case WM_MOUSEMOVE:
		if (MK_LBUTTON == wParam)
		{
			short xi = Math::ClampAboveZero((short)LOWORD(lParam));
			short yi = Math::ClampAboveZero((short)HIWORD(lParam));
			float x = Math::Clamp((float)xi, 0.f, mSize.Width);
			float y = mSize.Height - Math::Clamp((float)yi, 0.f, mSize.Height);

			double timeStamp = Application::Instance().TimeStamp();
			Touch touch(TouchPhase::Moved, 0, timeStamp, mpp(x, y), mPrevMouseTouch.Pos);
			TouchEventArg e(TouchPhase::Moved, touch);
			InputManager::Instance().TouchesMoved(e);
			mPrevMouseTouch = touch;
		}
		else
		{
			short xi = Math::ClampAboveZero((short)LOWORD(lParam));
			short yi = Math::ClampAboveZero((short)HIWORD(lParam));
			float x = Math::Clamp((float)xi, 0.f, mSize.Width);
			float y = mSize.Height - Math::Clamp((float)yi, 0.f, mSize.Height);

			ApplicationStatics::Instance().SetDebugTouch(mpp(x, y));
		}
		break;

	case WM_LBUTTONUP:
	{
		short xi = Math::ClampAboveZero((short)LOWORD(lParam));
		short yi = Math::ClampAboveZero((short)HIWORD(lParam));
		float x = Math::Clamp((float)xi, 0.f, mSize.Width);
		float y = mSize.Height - Math::Clamp((float)yi, 0.f, mSize.Height);
		double timeStamp = Application::Instance().TimeStamp();

		Touch touch(TouchPhase::Ended, 0, timeStamp, mpp(x, y), mPrevMouseTouch.Pos);

		TouchEventArg e(TouchPhase::Ended, touch);
		InputManager::Instance().TouchesEnded(e);
		ReleaseCapture();
		mPrevMouseTouch = Touch::Zero;

	}
	break;
	case WM_TOUCH:
	{
		unsigned int numInputs = (unsigned int)wParam;
		TOUCHINPUT* ti = new TOUCHINPUT[numInputs];
		if (GetTouchInputInfo((HTOUCHINPUT)lParam, numInputs, ti, sizeof(TOUCHINPUT)))
		{
			// Handle each contact point   
			for (unsigned int i = 0; i < numInputs; ++i)
			{
				/* handle ti[i]  */
			}
		}
		CloseTouchInputHandle((HTOUCHINPUT)lParam);
		delete[] ti;

	}
	break;
	case  WM_GESTURE:
	{
		GESTUREINFO gi;
		ZeroMemory(&gi, sizeof(GESTUREINFO));
		gi.cbSize = sizeof(gi);
		BOOL bResult = GetGestureInfo((HGESTUREINFO)lParam, &gi);
		bool isHandled = false;
		if (bResult)
		{
			switch (gi.dwID)
			{
			case GID_BEGIN:
				break;
			case GID_END:
				break;
			case GID_ZOOM:
				// Code for zooming goes here     
				isHandled = true;
				break;
			case GID_PAN:
				// Code for panning goes here
				isHandled = true;
				break;
			case GID_ROTATE:
				// Code for rotation goes here
				isHandled = true;
				break;
			case GID_TWOFINGERTAP:
				// Code for two-finger tap goes here
				isHandled = true;
				break;
			case GID_PRESSANDTAP:
				// Code for roll over goes here
				isHandled = true;
				break;
			default:
				// A gesture was not recognized
				break;
			}
		}
		else
		{
			DWORD dwErr = GetLastError();
			if (dwErr > 0)
			{
				MessageBoxW(mWindowHandle, L"Error!", L"Could not retrieve a GESTUREINFO structure.", MB_OK);
			}
		}

		CloseGestureInfoHandle((HGESTUREINFO)lParam);

		if (isHandled)
		{
			return 0;
		}
		else
		{
			return DefWindowProc(mWindowHandle, message, wParam, lParam);
		}


	}
	break;
	case WM_SIZE:
		switch (wParam)
		{
		case SIZE_RESTORED:
		case SIZE_MAXIMIZED:
		{
			Size2F newSize;
			newSize.Width = (float)LOWORD(lParam);
			newSize.Height = (float)HIWORD(lParam);
			OnResize(newSize);
			Application::Instance().Wakeup();
			Application::Instance().Resume();
		}
		break;
		case SIZE_MINIMIZED:
			Application::Instance().Pause();
			Application::Instance().Sleep();
			break;
		}
		break;
	case WM_KEYDOWN:
	{
		KeyDownEventArg e((uint)wParam, (uint)lParam);
		InputManager::Instance().KeyDown(e);
	}
	break;
	case WM_KEYUP:
	{
		KeyUpEventArg e((uint)wParam, (uint)lParam);
		InputManager::Instance().KeyUp(e);
	}
	break;
	case WM_CHAR:
	{
		CharInputEventArg e((uint)wParam, (uint)lParam);
		InputManager::Instance().CharInput(e);
	}
	break;
	case WM_MOUSEWHEEL:
	{
		short scrollPos = (short)HIWORD(wParam);
		short key = (short)LOWORD(wParam);
		ScrollEventArg e(scrollPos, key);
		InputManager::Instance().Scroll(e);

	}
	break;
	default:
		return DefWindowProc(mWindowHandle, message, wParam, lParam);
	}

	return 0;
}


MEDUSA_END;

#endif
