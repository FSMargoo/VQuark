/*
 * VQuarkWidget.h (2023/5.20)
 * 	 The wrapper of the widget operation
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
#pragma once

#include "VQuarkBase.h"
#include "VQuarkString.h"
#include "VQuarkSys.h"

VQUARK_SPACE_BEGIN

class VQuarkWidget
{
public:
	/**
	 * @brief				: Build the Widget from the window handle
	 * @param WidgetHandle	: The window handle
	 */
	VQuarkWidget(VWindowHandle WidgetHandle);

public:
	/**
	 * @brief			: Create a window
	 * @param Class		: The window's titile
	 * @param Title		: The class name of the window
	 * @param Width		: The width of the window
	 * @param Height	: The height of the window
	 * @param BelongTo	: The parent of the window
	 * @return			: If a window was created successfully, return the VQuark widget instance
	 */
	static VQuarkWidget *CreateWidget(const VString &Class, const VString &Title, const size_t &Width,
									  const size_t &Height, const VWindowHandle &BelongTo = NULL)
	{
		return new VQuarkWidget(VQuarkCreateWindow(Title, Class, Width, Height, BelongTo));
	}

public:
	/**
	 * @brief		: Set the title of the window
	 * @param Title : The title
	 */
	void SetTitle(const VString &Title);
	/**
	 * @brief		 : Set the size of the window
	 * @param Width	 : The width
	 * @param Height : The height
	 */
	void Resize(const size_t Width, const size_t Height);
	/**
	 * @brief	: Move the widget into specified position
	 * @param X	: The x data
	 * @param Y	: The y data
	 */
	void Move(const size_t &X, const size_t &Y);
	/**
	 * @brief : Display the window
	 */
	void Show();
	/**
	 * @brief : Hide the window
	 */
	void Hide();
	/**
	 * @brief : Move the window into center place
	 */
	void MoveCenter();
	/**
	 * @brief : Get the window's width
	 * @return : The width
	 */
	inline const size_t GetWidth() const noexcept;
	/**
	 * @brief : Get the window's height
	 * @return : The height
	 */
	inline const size_t GetHeight() const noexcept;

	/**
	 * @brief : Get the handle of the window
	 * @return : The handle of the window
	 */
	const VWindowHandle GetHandle() const noexcept;

private:
	VWindowHandle Handle;
};

VQUARK_SPACE_END