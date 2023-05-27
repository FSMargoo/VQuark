/*
 * VQuarkWidget.cpp (2023/5.20)
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
#include "../inc/VQuarkWidget.h"

VQUARK_SPACE_BEGIN

VQuarkWidget::VQuarkWidget(VWindowHandle WidgetHandle) : Handle(WidgetHandle)
{
	assert(!Handle.IsNull());
}
void VQuarkWidget::SetTitle(const VString &Title)
{
	VQuarkRenameWindow(Handle, Title);
}
void VQuarkWidget::Resize(const size_t Width, const size_t Height)
{
	VQuarkResizeWindow(Handle, {Width, Height});
}
void VQuarkWidget::Move(const size_t &X, const size_t &Y)
{
	VQuarkMoveWindow(Handle, X, Y);
}
void VQuarkWidget::Show()
{
	VQuarkShowWindow(Handle);
}
void VQuarkWidget::Hide()
{
	VQuarkHideWindow(Handle);
}
void VQuarkWidget::MoveCenter()
{
	VQuarkMoveWindow(Handle, VQuarkMurseCenter(VQuarkScreenDevice::GetWidth(), VQuarkGetWindowWidth(Handle)),
					 VQuarkMurseCenter(VQuarkScreenDevice::GetHeight(), VQuarkGetWindowHeight(Handle)));
}
inline const size_t VQuarkWidget::GetWidth() const noexcept
{
	return VQuarkGetWindowWidth(Handle);
}
inline const size_t VQuarkWidget::GetHeight() const noexcept
{
	return VQuarkGetWindowHeight(Handle);
}

const VWindowHandle VQuarkWidget::GetHandle() const noexcept
{
	return Handle;
}

VQUARK_SPACE_END