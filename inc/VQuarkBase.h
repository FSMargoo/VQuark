/*
 * VQuarkBase.h.h (2023/5.20)
 * 	 The basic defition of the VQuark (Window handle, Basic type, e.t.c)	
 *
 *
 * Copyright (C) 2023~now Margoo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this softwareand associated documentation files(the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
 *
 * The above copyright noticeand this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

/*
 * This API is only for the specified platform, it can't work on the other
 * platform.
*/
#define PLANTFORM_INCOMPATIBLE_API 
#define VQUARK_SPACE_BEGIN namespace VQuark {
#define VQUARK_SPACE_END };

#include "VQuarkString.h"

#include <tuple>
#include <functional>
#include <vector>
#include <map>

#ifdef _WIN64
#include <Windows.h>
#include <assert.h>
#include <string>

#pragma comment(lib, "IMM32.LIB")

namespace VQuark {
	/* The Window handle define */
	class VWindowHandle {
	public:
		VWindowHandle();
		/**
		 * @brief		 : Build the VQuark handle from win32 ID (Can only be used in Windows Platform)
		 * @param Handle : The Win32 handle of the window
		*/
		VWindowHandle(const HWND& Handle) PLANTFORM_INCOMPATIBLE_API;
		/**
		 * @brief 
		 * @param Data 
		*/
		VWindowHandle(const VWindowHandle& Data);

	public:
		/**
		 * @brief  : Judge the handle a null handle or not
		 * @return : If the handle is null, return true, nor return false
		*/
		const bool IsNull() const;

	public:
		/**
		 * @brief : Convert the VQuark handle into Win32 API handle(This API can only be used in the Windows Platform)
		*/
		const HWND ToWinId() const PLANTFORM_INCOMPATIBLE_API;

	public:
		friend const bool operator==(const VWindowHandle& Left, const VWindowHandle& Right);
		friend const bool operator!=(const VWindowHandle& Left, const VWindowHandle& Right);

	public:
		/**
		 * @brief The handle of the handle
		*/
		HWND Handle;
	};

	/**
	 * @brief			: Create a window
	 * @param Title		: The window's titile
	 * @param ClassName : The class name of the window
	 * @param Width		: The width of the window
	 * @param Height	: The height of the window
	 * @param Parent	: The parent of the window
	 * @return			: If a window was created successfully, return the VQuark handle of the window
	*/
	VWindowHandle	VQuarkCreateWindow(const VString& Title, const VString& ClassName, const size_t& Width, const size_t& Height,
		const VWindowHandle Parent = NULL);
	/**
	 * @brief		 : Get the width of the window
	 * @param Window : The window's handle
	 * @return		 : The width of the window
	*/
	size_t			VQuarkGetWindowWidth(const VWindowHandle& Window);
	/**
	 * @brief		 : Get the height of the window
	 * @param Window : The window's handle
	 * @return		 : The height of the window
	*/
	size_t			VQuarkGetWindowHeight(const VWindowHandle& Window);
	/**
	 * @brief		 : Move the window int oa target position
	 * @param Window : The window's handle
	 * @param X		 : The X position
	 * @param Y		 : The Y position
	*/
	void			VQuarkMoveWindow(const VWindowHandle& Window, const size_t& X, const size_t& Y);
	/**
	 * @brief		 : Set the title of the window
	 * @param Window : The window's handle
	 * @param Title  : The title
	*/
	void			VQuarkRenameWindow(const VWindowHandle& Window, const VString& Title);
	/**
	 * @brief		 : Get the Window's geomtery information
	 * @param Window : The window's handle
	 * @return		 : A tuple which contains the geomtery information of the window
	*/
	std::tuple<size_t, size_t>
					VQuarkMurseWindow(const VWindowHandle& Window);
	/**
	 * @brief			: Resize the window
	 * @param Window	: The window handle
	 * @param Geomtery	: The geomtery information tuple (width and height)
	*/
	void			VQuarkResizeWindow(const VWindowHandle& Window,
		const std::tuple<size_t, size_t>& Geomtery);
	/**
	 * @brief			: Show the window
	 * @param Window	: The window handle
	*/
	void			VQuarkShowWindow(const VWindowHandle& Window);
	/**
	 * @brief			: Hide the window
	 * @param Window	: The window handle
	*/
	void			VQuarkHideWindow(const VWindowHandle& Window);
	
	/**
	 * @brief			 : The wrapper of the assert
	 * @param Expression : The expression (if expression is false, break)
	*/
	void			VAssert(const bool& Expression);

	using VRawFont = LOGFONT;

	/**
	 * @brief : The pipe object of the process contact pipeline
	*/
	struct VQuarkWinProcessPipeObject {
		std::tuple<size_t, size_t>	IMEPosition;
		VRawFont					IMEFontStyle;
		bool						IMEOperating = false;

		bool Frameless  = false;
		bool MaxMinSize = false;
		bool Sizable	= false;
		bool Borderless = false;

		std::tuple<size_t, size_t> MaxSize;
		std::tuple<size_t, size_t> MinSize;

		std::function<void()>						Repaint;
		std::function<void()>						StartInput;
		std::function<void()>						EndInput;
		std::function<void()>						LoseFocus;
		std::function<bool()>						Quit;
		std::function<void(std::vector<VString>)>	FileOnDrag;
		std::function<void(int, int)>				OnResize;
	};

	/**
	 * @brief		: The dealy function for Win32
	 * @param hWnd
	 * @param Msg 
	 * @param wParam 
	 * @param lParam 
	 * @return 
	*/
	LRESULT _VQuarkMsgDealy(HWND Handle, UINT Message, WPARAM WideParameter, LPARAM LowParameter);

	/**
	 * @brief			: Caculate the center position of two specified value
	 * @tparam TypeLeft : The left value type
	 * @tparam TypeRight : The right value type
	 * @param Left		: The left value
	 * @param Right		: The right value
	 * @return			: The center value
	*/
	template<class TypeLeft, class TypeRight>
	decltype(TypeLeft(0) + TypeRight(0)) VQuarkMurseCenter(const TypeLeft& Left, const TypeRight& Right) {
		return max(Left, Right) / 2 - min(Left, Right) / 2;
	}

#define VQUARK_WINDOWS
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#   error "VQuark Error : Unsupported platform"
#elif TARGET_OS_IPHONE
#   error "VQuark Error : Unsupported platform"
#elif TARGET_OS_MAC
#   error "VQuark Error : Unsupported platform"
#else
#   error "VQuark Error : Unknown Apple platform"
#endif

#	define VQUARK_APPLE
#elif __linux__
#   error "VQuark Error : Unsupported platform"
#	define VQUARK_LINUX
#elif __unix__
#   error "VQuark Error : Unsupported platform"
#	define VQUARK_UNIX
#elif defined(_POSIX_VERSION)
#   error "VQuark Error : Unsupported platform"
#	define VQUARK_POSIX_LINX
#else
#   error "VQuark Error : Unsupported platform"
#	define VQUARK_UNKNOWN
#endif
};