/*
 * VQuarkSys.cpp (2023/5.27)
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

#include "../inc/VQuarkSys.h"

VQUARK_SPACE_BEGIN

const unsigned short VQuarkScreenDevice::GetWidth() {
	return GetSystemMetrics(SM_CXFULLSCREEN);
}
const unsigned short VQuarkScreenDevice::GetHeight() {
	return GetSystemMetrics(SM_CYFULLSCREEN);
}
const unsigned short VQuarkScreenDevice::MurseClientWidth() {
	RECT Murse;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &Murse, NULL);

	return static_cast<unsigned short>(Murse.right - Murse.left);
}
const unsigned short VQuarkScreenDevice::MurseClientHeight() {
	RECT Murse;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &Murse, NULL);

	return static_cast<unsigned short>(Murse.bottom - Murse.top);
}

VQUARK_SPACE_END