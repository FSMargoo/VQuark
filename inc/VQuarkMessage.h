/*
 * VQuarkMessage.h (2023/5.21)
 * 	 The message system in the VQuark	
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

#include "VQuarkBase.h"

VQUARK_SPACE_BEGIN

enum VMessageType
{
	UnknowMessage,
	MouseMoveMessage,
	MouseClickedMessage,
	KeyClickedMessage,
	RepaintMessage,
	GetRepaintAeraMessage,
	IMECharMessage,
	MouseWheelMessage,
	FreeResourceMessage,
	CheckLocalFocusMessage,
	KillFocusMessage,
	QuitWindowMessage,
	BlurCombinationOnRend
};

typedef class VMessage
{
private:
	VMessageType MessageType;

public:
	UINT   Win32ID;
	HWND   MessageTriggerWidget = NULL;
	WPARAM wParameter;
	LPARAM lParameter;

public:
	explicit VMessage(VMessageType Type = UnknowMessage);

	VMessageType GetType()
	{
		return MessageType;
	}
} VBasicMessage;

class VFreeSourceMessage : public VMessage
{
public:
	VFreeSourceMessage(HWND TriggerWidget);
};

class VMouseMoveMessage : public VMessage
{
public:
	VPoint MousePosition;

public:
	VMouseMoveMessage(HWND TriggerWidget, int X, int Y);
};

class VMouseWheelMessage : public VMessage
{
public:
	VPoint MousePosition;

	short WheelValue;

public:
	VMouseWheelMessage(HWND TriggerWidget, int X, int Y, short WheelParameter);
};

typedef enum VMouseClickedFlag
{
	Down,
	Up
} VkeyClickedFlag;
enum VMouseKeyFlag
{
	Middle,
	Left,
	Right
};

class VMouseClickedMessage : public VMessage
{
public:
	VPoint MousePosition;

	VMouseClickedFlag ClickedMethod;
	VMouseKeyFlag	  ClickedKey;

public:
	VMouseClickedMessage(HWND TriggerWidget, int X, int Y, VMouseClickedFlag ClickedFlag, VMouseKeyFlag Key);
};

class VKeyClickedMessage : public VMessage
{
public:
	byte			KeyVKCode;
	bool			KeyPrevDown;
	bool			KeyExtened;
	VkeyClickedFlag KeyStats;

public:
	VKeyClickedMessage(HWND TriggerWidget, byte VKCode, bool PrevDown, bool Extened, VkeyClickedFlag Stats);
};

class VRepaintMessage : public VMessage
{
public:
	VRect DirtyRectangle;

public:
	explicit VRepaintMessage(HWND TriggerWidget, const VRect& RepaintRegion);
};

class VGetRepaintAeraMessage : public VMessage
{
public:
	VRect* RepaintAera;

public:
	explicit VGetRepaintAeraMessage(HWND TriggerWidget, VRect& RepaintRegion);
	~VGetRepaintAeraMessage();
};

class VIMECharMessage : public VMessage
{
public:
	wchar_t IMEChar;

public:
	explicit VIMECharMessage(HWND TriggerWidget, wchar_t CharInputed);
};

class VCheckFocusMessage : public VMessage
{
public:
	VPoint FocusPoint;
	void* Object;
	bool   Click;

public:
	explicit VCheckFocusMessage(HWND TriggerWidget, const VPoint& Point, void* MessageObject,
		const bool& MouseClick = false);
};

class VKillFocusMessage : public VMessage
{
public:
	VKillFocusMessage(HWND TriggerWidget);
};

class VQuitWindowMessage : public VMessage
{
public:
	VQuitWindowMessage(HWND TriggerWidget);
};

VQUARK_SPACE_END