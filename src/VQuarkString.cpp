/*
 * VQuarkString.cpp (2023/5.20)
 * 	 The wrapper of the STL string	
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
#include "../inc/VQuarkString.h"

namespace VQuark {


#ifdef _UNICODE
const wchar_t* operator"" vs(const wchar_t* OriginString, size_t StringLength)
{
	return OriginString;
}
const wchar_t* operator"" vs(const char* OriginString, size_t StringLength)
{
	_bstr_t ConvertedString(OriginString);

	return (const wchar_t*)ConvertedString;
}

const wchar_t* vstring_convert(const wchar_t* OriginString)
{
	return OriginString;
}
const wchar_t* vstring_convert(const char* OriginString)
{
	_bstr_t ConvertedString(OriginString);

	return (const wchar_t*)ConvertedString;
}
#else
const char* operator"" vs(const wchar_t* OriginString, size_t StringLength)
{
	_bstr_t ConvertedString(OriginString);

	return (const char*)ConvertedString;
}
const char* operator"" vs(const char* OriginString, size_t StringLength)
{
	return OriginString;
}

const wchar_t* vstring_convert(const wchar_t* OriginString)
{
	_bstr_t ConvertedString(OriginString);

	return (const char*)ConvertedString;
}
const wchar_t* vstring_convert(const char* OriginString)
{
	return OriginString;
}
#endif

VString::VString() : VProxyString()
{
}
VString::VString(const std::wstring& String)
{
	Set(FromWideString(String));
}
VString::VString(const std::string& String)
{
	Set(FromString(String));
}
VString::VString(const wchar_t* String)
{
	assign(vstring_convert(String));
}
VString::VString(wchar_t* String)
{
	Set(vstring_convert(String));
}
VString::VString(const char* String)
{
	Set(vstring_convert(String));
}
VString::VString(char* String)
{
	Set(vstring_convert(String));
}

VString VString::Split(const size_t& Begin, const size_t& SplitCount)
{
	return substr(Begin, SplitCount);
}
VString VString::Split(const size_t& Begin, const size_t& SplitCount) const
{
	return substr(Begin, SplitCount);
}
VString VString::SplitRange(const size_t& Begin, const size_t& End)
{
	return substr(Begin, End - Begin);
}
void VString::Append(const VString& AppendString)
{
	this->operator+=(AppendString);
}
size_t VString::Size() const
{
	return size();
}
bool VString::StartWith(const VString& JudgeString, const size_t& StartOn)
{
	for (auto Count = StartOn; Count < StartOn + JudgeString.Size(); ++Count)
	{
		if (at(Count) != JudgeString[Count - StartOn])
		{
			return false;
		}
	}

	return true;
}
bool VString::EndWith(const VString& JudgeString)
{
	return StartWith(JudgeString, size() - JudgeString.size());
}
VChar& VString::At(const size_t& Position)
{
	return at(Position);
}

bool VString::IsEmpty()
{
	return empty();
}

void VString::Fill(const VChar& Character, size_t FillSize)
{
	if (FillSize == 0)
	{
		FillSize = size();
	}

	for (auto Count = 0; Count < FillSize; ++Count)
	{
		At(Count) = Character;
	}
}

size_t VString::IndexOf(const VString& String, const size_t& StartAt) const
{
	return find(String, StartAt);
}
size_t VString::IndexLastOf(const VString& String, const size_t& StartAt)
{
	return find_last_of(String, StartAt);
}
VString::Iterator VString::Begin()
{
	return begin();
}
VString::Iterator VString::End()
{
	return end();
}
VString::ReverseIterator VString::ReverseBegin()
{
	return rbegin();
}
VString::ReverseIterator VString::ReverseEnd()
{
	return rend();
}
void VString::Set(const VString& String)
{
	assign(String);
}
void VString::Erase(const size_t& Begin, const size_t& Count)
{
	erase(Begin, Count);
}
void VString::Erase(ConstIterator Iterator)
{
	erase(Iterator);
}
void VString::EraseRange(const size_t& Begin, const size_t& End)
{
	erase(Begin, End - Begin);
}
void VString::Insert(const size_t& Position, const VString& String)
{
	insert(Position, String);
}
void VString::Insert(const size_t& Position, const VString& String, const size_t& Count)
{
	insert(Position, String, Count);
}
void VString::Insert(ConstIterator Iterator, const VChar& Character)
{
	insert(Iterator, Character);
}
VString VString::FromNumber(const int& NumberConvert)
{
	return VSTCStr(NumberConvert);
}
VString VString::FromNumber(const long long& NumberConvert)
{
	return VSTCStr(NumberConvert);
}
VString VString::FromNumber(const long& NumberConvert)
{
	return VSTCStr(NumberConvert);
}
VString VString::FromNumber(const unsigned int& NumberConvert)
{
	return VSTCStr(NumberConvert);
}
VString VString::FromNumber(const unsigned long& NumberConvert)
{
	return VSTCStr(NumberConvert);
}
VString VString::FromNumber(const unsigned long long& NumberConvert)
{
	return VSTCStr(NumberConvert);
}
VString VString::FromString(const std::string& String)
{
	return vstring_convert(String.c_str());
}
VString VString::FromWideString(const std::wstring& String)
{
	return vstring_convert(String.c_str());
}
VString VString::Args(VString FormatInstance) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FormatInstance);

		return NewString;
	}

	return NewString;
}
VString VString::Args(int IntFormat) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FromNumber(IntFormat));
	}

	return NewString;
}
VString VString::Args(const long IntFormat) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FromNumber(IntFormat));
	}

	return NewString;
}
VString VString::Args(const long long IntFormat) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FromNumber(IntFormat));
	}

	return NewString;
}
VString VString::Args(const unsigned int IntFormat) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FromNumber(IntFormat));
	}

	return NewString;
}
VString VString::Args(const unsigned long IntFormat) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FromNumber(IntFormat));
	}

	return NewString;
}
VString VString::Args(const unsigned long long IntFormat) const
{
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, FromNumber(IntFormat));
	}

	return NewString;
}
VString VString::Args(const VPoint Format) const {
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, VString("({}, {})").Args(Format.X).Args(Format.Y));
	}

	return NewString;
}
VString VString::Args(const VRect Format) const {
	VString NewString(*this);
	auto Index = IndexOf(VStr("{}"));
	if (Index != VString::NoPosition)
	{
		NewString.EraseRange(Index, Index + 2);
		NewString.Insert(Index, VString("[({}, {}), ({}, {})]").Args(Format.Left).Args(Format.Top).
			Args(Format.Right).Args(Format.Bottom));
	}

	return NewString;
}
size_t VString::Length() const
{
	return length();
}
const VChar* VString::CStyleString() const
{
	return (const VChar*)c_str();
}

};