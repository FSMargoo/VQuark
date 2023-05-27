/*
 * VQuarkSys.h (2023/5.27)
 * 	 Some system API operation's wrapper	
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

#include "VQuarkData.h"
#include "VQuarkBase.h"

VQUARK_SPACE_BEGIN

class VQuarkScreenDevice {
public:
	/**
	 * @brief : Get the screen's width
	 * @return : The width
	*/
	static const unsigned short GetWidth();
	/**
	 * @brief : Get the screen's height
	 * @return : The height
	*/
	static const unsigned short GetHeight();
	/**
	 * @brief : Get the screen's width (Without the bar)
	 * @return : The width
	*/
	static const unsigned short MurseClientWidth();
	/**
	 * @brief : Get the screen's height (Without the bar)
	 * @return : The height
	*/
	static const unsigned short MurseClientHeight();
};

VQUARK_SPACE_END