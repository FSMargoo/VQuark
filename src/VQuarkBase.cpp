/*
 * VQuarkBase.h.cpp (2023/5.20)
 * 	 The basic defition of the VQuark (Window handle, Basic type, e.t.c)
 *
 *
 * Copyright (C) 2023~now Margoo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated
 * documentation files(the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions :
 *
 * The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Make MSVC happy :) */
#pragma warning(disable : 4302 4267 4244)

#include "../inc/VQuarkBase.h"

#include <thread>

namespace VQuark
{
std::map<HWND, VQuarkWinProcessPipeObject *> _VQuarkThreadPipeline;
bool										 _VQuarkMainThreadEnd = false;

VWindowHandle::VWindowHandle() : Handle(NULL)
{
}
VWindowHandle::VWindowHandle(const VWindowHandle &Handle) : Handle(Handle.Handle)
{
}
VWindowHandle::VWindowHandle(const HWND &Data) : Handle(Data)
{
}

const bool operator==(const VWindowHandle &Left, const VWindowHandle &Right)
{
	return Left.Handle == Right.Handle;
}
const bool operator!=(const VWindowHandle &Left, const VWindowHandle &Right)
{
	return Left.Handle != Right.Handle;
}

const HWND VWindowHandle::ToWinId() const
{
	return Handle;
}
const bool VWindowHandle::IsNull() const
{
	return Handle == NULL;
}

void VAssert(const bool &Expression)
{
	assert(Expression);
}

VWindowHandle VQuarkCreateWindow(const VString &Title, const VString &ClassName, const size_t &Width,
								 const size_t &Height, const VWindowHandle Parent)
{
	HWND WindowHandle = NULL;
	bool HoldLock	  = false;

	std::thread QuarkWindowProcess([&]() {
		auto InstanceHandle = ( HINSTANCE )GetModuleHandle(NULL);

		WNDCLASSEX WindowClass;
		WindowClass.cbSize		  = sizeof(WindowClass);
		WindowClass.style		  = CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc	  = DefWindowProc;
		WindowClass.cbClsExtra	  = 0;
		WindowClass.cbWndExtra	  = 0;
		WindowClass.hInstance	  = InstanceHandle;
		WindowClass.hIcon		  = LoadIcon(nullptr, IDI_APPLICATION);
		WindowClass.hCursor		  = LoadCursor(nullptr, IDC_ARROW);
		WindowClass.hbrBackground = NULL;
		WindowClass.lpszMenuName  = NULL;
		WindowClass.lpszClassName = ClassName.CStyleString();
		WindowClass.hIconSm		  = NULL;

		RegisterClassEx(&WindowClass);

		WindowHandle = CreateWindow(ClassName.CStyleString(), Title.CStyleString(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
									CW_USEDEFAULT, Width, Height, Parent.ToWinId(), NULL, InstanceHandle, NULL);

		HoldLock = true;

		// Move window into the client center
		RECT WindowRect;
		RECT ClientRect;

		GetWindowRect(WindowHandle, &WindowRect);
		GetClientRect(WindowHandle, &ClientRect);

		int TitleBarHeight = WindowRect.bottom - WindowRect.top - ClientRect.bottom;

		MoveWindow(WindowHandle, 0, 0, Width, Height + TitleBarHeight, FALSE);

		MSG WinMsg{};

		while (GetMessage(&WinMsg, 0, 0, 0))
		{
			TranslateMessage(&WinMsg);
			DispatchMessage(&WinMsg);
		}
	});
	QuarkWindowProcess.detach();

	while (!HoldLock)
	{
		Sleep(1);
	}

	return WindowHandle;
}
size_t VQuarkGetWindowWidth(const VWindowHandle &Window)
{
	RECT Rect;
	GetWindowRect(Window.ToWinId(), &Rect);

	return Rect.right - Rect.left;
}
size_t VQuarkGetWindowHeight(const VWindowHandle &Window)
{
	RECT Rect;
	GetWindowRect(Window.ToWinId(), &Rect);

	return Rect.bottom - Rect.top;
}
void VQuarkMoveWindow(const VWindowHandle &Window, const size_t &X, const size_t &Y)
{
	RECT Rect;
	GetWindowRect(Window.ToWinId(), &Rect);

	MoveWindow(Window.ToWinId(), X, Y, Rect.right - Rect.left, Rect.bottom - Rect.top, TRUE);
}
void VQuarkShowWindow(const VWindowHandle &Window)
{
	ShowWindow(Window.ToWinId(), SW_SHOW);
}
void VQuarkHideWindow(const VWindowHandle &Window)
{
	ShowWindow(Window.ToWinId(), SW_HIDE);
}
std::tuple<size_t, size_t> VQuarkMurseWindow(const VWindowHandle &Window)
{
	RECT Rect;
	GetWindowRect(Window.ToWinId(), &Rect);

	return {Rect.bottom - Rect.top, Rect.right - Rect.left};
}
void VQuarkRenameWindow(const VWindowHandle &Window, const VString &Title)
{
	SetWindowText(Window.ToWinId(), Title.CStyleString());
}
void VQuarkResizeWindow(const VWindowHandle &Window, const std::tuple<size_t, size_t> &Geomtery)
{
	RECT Rect;
	GetWindowRect(Window.ToWinId(), &Rect);

	MoveWindow(Window.ToWinId(), Rect.left, Rect.right, std::get<0>(Geomtery), std::get<1>(Geomtery), FALSE);
}

/**
 * @brief			: Filter the Win32 Message that dosen't need to be process
 * @param Message	: The windows message
 * @return			: If it need to be dealed, return true, nor return false
 */
bool VQuarkFilterWinMessage(const UINT &Message)
{
	if (!(Message == WM_PAINT || Message == WM_NCHITTEST || Message == WM_SETCURSOR || Message == WM_NCLBUTTONDOWN ||
		  Message == WM_SIZING || Message == WM_SIZE || Message == WM_GETMINMAXINFO || Message == WM_IME_COMPOSITION ||
		  Message == WM_CHAR || Message == WM_KILLFOCUS || Message == WM_NCMOUSELEAVE || Message == WM_CLOSE ||
		  Message == WM_LBUTTONDOWN || Message == WM_LBUTTONUP || Message == WM_MBUTTONDOWN ||
		  Message == WM_MBUTTONUP || Message == WM_RBUTTONUP || Message == WM_RBUTTONDOWN || Message == WM_MOUSEMOVE ||
		  Message == WM_IME_CHAR || Message == WM_KEYDOWN || Message == WM_KEYUP || Message == WM_MOUSEWHEEL ||
		  Message == WM_CLOSE || Message == WM_NCCALCSIZE || Message == WM_DROPFILES))
	{
		return false;
	}

	return true;
}

LRESULT _VQuarkMsgDealy(HWND Handle, UINT Message, WPARAM WideParameter, LPARAM LowParameter)
{
	/* If the main thread has gone, return the default window process */
	if (_VQuarkMainThreadEnd)
	{
		return DefWindowProc(Handle, Message, WideParameter, LowParameter);
	}
	/* If the window isn't exists in the conversation pipeline, return default window process */
	if (_VQuarkThreadPipeline.find(Handle) == _VQuarkThreadPipeline.end())
	{
		return DefWindowProc(Handle, Message, WideParameter, LowParameter);
	}
	/* If the message dosen't need to be processed, return default window process */
	if (!VQuarkFilterWinMessage(Message))
	{
		return DefWindowProc(Handle, Message, WideParameter, LowParameter);
	}

	VQuarkWinProcessPipeObject *Object = _VQuarkThreadPipeline.find(Handle)->second;
	switch (Message)
	{
	/**
	 * @brief : Deal with the file dropping message
	 */
	case WM_DROPFILES: {
		VChar FilePath[MAX_PATH];
		HDROP DropHandle = reinterpret_cast<HDROP>(WideParameter);
		UINT  ListCount	 = DragQueryFile(DropHandle, -1, NULL, NULL);

		std::vector<VString> Files;
		while (ListCount > 0)
		{
			if (DragQueryFile(DropHandle, ListCount - 1, FilePath, MAX_PATH - 1))
			{
				Files.push_back(FilePath);
			}

			--ListCount;
		}

		DragFinish(DropHandle);

		Object->FileOnDrag(Files);

		break;
	}
	/**
	 * @brief : Deal with the painting message
	 */
	case WM_PAINT: {
		Object->Repaint();

		break;
	}
	/**
	 * @brief : Deal with the window hit test
	 */
	case WM_NCHITTEST: {
		POINT Point = {(( int )( short )LOWORD(LowParameter)), (( int )( short )HIWORD(LowParameter))};

		/**
		 * @brief : Deal with the framless window
		 */
		if (Object->Frameless)
		{
			RECT Rect;

			GetWindowRect(Handle, &Rect);
			if (Point.x <= Rect.left + 10 && Point.y <= Rect.top + 10)
			{
				if (Object->Sizable)
				{
					return HTTOPLEFT;
				}

				return HTCLIENT;
			}
			else if (Point.x >= Rect.right - 10 && Point.y <= Rect.top + 10)
			{
				if (Object->Sizable)
				{
					return HTTOPRIGHT;
				}

				return HTCLIENT;
			}
			else if (Point.x >= Rect.right + 10 && Point.y <= Rect.top - 10)
			{
				if (Object->Sizable)
				{
					return HTBOTTOMLEFT;
				}

				return HTCLIENT;
			}
			else if (Point.x >= Rect.right - 10 && Point.y <= Rect.top - 10)
			{
				if (Object->Sizable)
				{
					return HTBOTTOMRIGHT;
				}

				return HTCLIENT;
			}
			else if (Point.x <= Rect.left + 10)
			{
				if (Object->Sizable)
				{
					return HTLEFT;
				}

				return HTCLIENT;
			}
			else if (Point.x >= Rect.right - 10)
			{
				if (Object->Sizable)
				{
					return HTRIGHT;
				}

				return HTCLIENT;
			}
			else if (Point.y <= Rect.top + 10)
			{
				if (Object->Sizable)
				{
					return HTTOP;
				}

				return HTCLIENT;
			}
			else if (Point.y >= Rect.bottom - 10)
			{
				if (Object->Sizable)
				{
					return HTBOTTOM;
				}

				return HTCLIENT;
			}
		}
		/**
		 * @brief : Deal with the borderless window
		 */
		if (Object->Borderless && Object->Sizable)
		{
			RECT Rect;
			ScreenToClient(Handle, &Point);
			GetClientRect(Handle, &Rect);

			if (Point.y > 0 && Point.y < 5)
			{
				return HTTOP;
			}

			Rect.bottom -= Rect.top + GetSystemMetrics(SM_CYCAPTION) - 5;
			if (Point.y <= Rect.bottom && Point.y >= Rect.bottom - 5)
			{
				return HTBOTTOM;
			}
		}

		break;
	}
	case WM_SETCURSOR: {
		if (Object->Frameless && Object->Sizable)
		{
			switch (LOWORD(LowParameter))
			{
			case HTTOP:
			case HTBOTTOM: {
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));
				return true;
			}

			case HTLEFT:
			case HTRIGHT: {
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
				return true;
			}

			case HTTOPLEFT:
			case HTBOTTOMRIGHT: {
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENWSE)));
				return true;
			}

			case HTTOPRIGHT:
			case HTBOTTOMLEFT: {
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENESW)));
				return true;
			}
			}
		}
		if (Object->Borderless)
		{
			switch (LOWORD(LowParameter))
			{
			case HTTOP:
			case HTBOTTOM: {
				SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS)));

				return true;
			}
			}
		}

		break;
	}
	case WM_NCLBUTTONDOWN: {
		if (Object->Frameless && Object->Sizable)
		{
			POINT Point = {(( int )( short )LOWORD(LowParameter)), (( int )( short )HIWORD(LowParameter))};
			switch (WideParameter)
			{
			case HTTOP:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(Point.x, Point.y));

				break;
			case HTBOTTOM:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(Point.x, Point.y));

				break;
			case HTLEFT:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(Point.x, Point.y));

				break;
			case HTRIGHT:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(Point.x, Point.y));

				break;
			case HTTOPLEFT:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(Point.x, Point.y));

				break;
			case HTTOPRIGHT:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(Point.x, Point.y));

				break;
			case HTBOTTOMLEFT:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(Point.x, Point.y));

				break;
			case HTBOTTOMRIGHT:
				SendMessage(Handle, WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(Point.x, Point.y));

				break;
			}
		}
	}
	case WM_SIZING: {
		RECT *Rect = reinterpret_cast<RECT *>(LowParameter);

		Object->OnResize(Rect->right - Rect->left, Rect->bottom - Rect->top);

		break;
	}
	case WM_NCCALCSIZE: {
		if (!WideParameter)
		{
			break;
		}

		if (Object->Borderless)
		{
			int OffsetX = GetSystemMetrics(SM_CXFRAME);
			int OffsetY = GetSystemMetrics(SM_CYFRAME);
			int Margin	= GetSystemMetrics(SM_CXPADDEDBORDER);

			NCCALCSIZE_PARAMS *Parameter  = ( NCCALCSIZE_PARAMS	 *)LowParameter;
			RECT			  *ClientRect = Parameter->rgrc;

			ClientRect->right -= OffsetY + Margin;
			ClientRect->left += OffsetX + Margin;
			ClientRect->bottom -= OffsetY + Margin - GetSystemMetrics(SM_CYCAPTION);

			return 0;
		}

		break;
	}
	case WM_SIZE: {
		if (WideParameter != SIZE_MINIMIZED)
		{
			if (WideParameter != SIZE_RESTORED)
			{
				RECT WidgetRect;
				RECT ClientRect;

				GetWindowRect(Handle, &WidgetRect);
				GetClientRect(Handle, &ClientRect);

				int BarHeight = WidgetRect.bottom - WidgetRect.top - ClientRect.bottom;
				Object->OnResize(LOWORD(LowParameter), HIWORD(LowParameter) + BarHeight);
			}
			else
			{
				RECT Rect;
				GetWindowRect(Handle, &Rect);

				Object->OnResize(Rect.right - Rect.left, Rect.bottom - Rect.top);
			}
		}
	}
	case WM_GETMINMAXINFO: {
		MINMAXINFO *WidgetProperty = reinterpret_cast<MINMAXINFO *>(LowParameter);
		if (Object->Frameless)
		{
			WidgetProperty->ptMaxSize.y =
				GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);
		}
		if (Object->MaxMinSize)
		{
			WidgetProperty->ptMinTrackSize.x = std::get<0>(Object->MinSize);
			WidgetProperty->ptMinTrackSize.y = std::get<1>(Object->MinSize);

			WidgetProperty->ptMaxTrackSize.x = std::get<0>(Object->MaxSize);
			WidgetProperty->ptMaxTrackSize.y = std::get<1>(Object->MaxSize);
		}

		break;
	}
	/**
	 * @brief : Deal with the IME operation
	 */
	case WM_IME_COMPOSITION: {
		HIMC IMMContext = ImmGetContext(Handle);
		if (IMMContext)
		{
			Object->IMEOperating = true;

			if (Object->StartInput != nullptr)
			{
				Object->StartInput();
			}

			/**
			 * @brief : Move the IME widget into specified position
			 */
			COMPOSITIONFORM IMMForm;
			IMMForm.dwStyle		   = CFS_POINT;
			IMMForm.ptCurrentPos.x = std::get<0>(Object->IMEPosition);
			IMMForm.ptCurrentPos.y = std::get<1>(Object->IMEPosition);

			/**
			 * @brief : Set the IMM style
			 */
			ImmAssociateContextEx(Handle, IMMContext, IACE_CHILDREN);
			ImmSetCompositionFont(IMMContext, &Object->IMEFontStyle);
			ImmSetCompositionWindow(IMMContext, &IMMForm);
		}

		break;
	}
	/**
	 * @brief : In this situation the IME input end
	 */
	case WM_IME_CHAR: {
		Object->IMEOperating = false;
		if (Object->EndInput != nullptr)
		{
			Object->EndInput();
		}

		break;
	}
	case WM_KILLFOCUS:
	case WM_NCMOUSELEAVE: {
		if (!Object->IMEOperating)
		{
			Object->LoseFocus();
		}
	}
	case WM_CLOSE: {
		if (Object->Quit())
		{
			return 0;
		}

		break;
	}
	}

	return DefWindowProc(Handle, Message, WideParameter, LowParameter);
}
}; // namespace VQuark