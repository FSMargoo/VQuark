/*
 * VQuarkData.h (2023/5.26)
 * 	 This file defines some data types in VQuark (Point, Rectangle, e.t.c)
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

#include <utility>

namespace VQuark
{

/**
 * @brief			: The abstract of the rectangle
 * @tparam DataType : The data typew will using
 */
template <class DataType> class VCoreRect
{
public:
	/**
	 * @brief : The alias of "DataType"
	 */
	using Integer = const DataType &;
	/**
	 * @brief : The alias of "VCoreRect"
	 */
	using Rect = const VCoreRect &;

public:
	/**
	 * @brief : Get the width of the rectangle
	 * @return : The width value
	 */
	const DataType GetWidth() const
	{
		return Right - Left;
	}
	/**
	 * @brief : Get the height of the rectangle
	 * @return : The height value
	 */
	const DataType GetHeight() const
	{
		return Bottom - Top;
	}

public:
	/**
	 * @brief	: Move the rectangle to the target position
	 * @param X : The X
	 * @param Y : The Y
	 */
	void Move(Integer X, Integer Y)
	{
		Integer Width  = GetWidth();
		Integer Height = GetHeight();

		Left   = X;
		Top	   = Y;
		Right  = Y + Bottom;
		Bottom = Y + Height;
	}
	/**
	 * @brief	: Move the rectangle to the target position (Chaining method)
	 * @param X : The X
	 * @param Y : The Y
	 * @return	: The self-pointer (For chaining method)
	 */
	VCoreRect *MoveChaining(Integer X, Integer Y)
	{
		Move(X, Y);

		return this;
	}
	/**
	 * @brief				: Extended the rectangle
	 * @param LeftPanding	: The left panding
	 * @param TopPanding	: The top panding
	 * @param RightPanding	: The right panding
	 * @param BottomPanding : The bottom panding
	 */
	void Extended(Integer LeftPanding, Integer TopPanding, Integer RightPanding, Integer BottomPanding)
	{
		Right += RightPanding;
		Bottom += BottomPanding;
		Left -= LeftPanding;
		Top -= TopPanding;
	}
	/**
	 * @brief			: Resize the rectangle
	 * @param Width		: The width
	 * @param Height	: The height
	 */
	void Resize(Integer Width, Integer Height)
	{
		Right  = Left + Width;
		Bottom = Top + Height;
	}
	/**
	 * @brief			: Mix the targeted rectangle with the rectangle
	 * @param Rectangle : The rectangle value
	 */
	void FusionRect(Rect Rectangle)
	{
		Left   = min(Rectangle.Left, Left);
		Right  = max(Rectangle.Right, Right);
		Top	   = min(Rectangle.Top, Top);
		Bottom = max(Rectangle.Bottom, Bottom);
	}
	/**
	 * @brief					: Judge a target rectangle overlap with this rectangle
	 * @param JudgeRectangle	: The Judgement
	 * @return					: If it overalps with this rectangle, return true, nor false.
	 */
	bool Overlap(Rect JudgeRectangle)
	{
		return max(Left, JudgeRectangle.Left) < min(Right, JudgeRectangle.Right) &&
			   max(Top, JudgeRectangle.Top) < min(Bottom, JudgeRectangle.Bottom);
	}
	/**
	 * @brief			: Judge a target rectangle include with this rectangle
	 * @param Judgement : The Judgement
	 * @return 			: If it include with this rectangle, return true, nor false.
	 */
	bool Include(Rect Judgement)
	{
		return Left <= Judgement.Left && Top <= Judgement.Top && Right <= Judgement.Right && Bottom >= Judgement.Bottom;
	}
	/**
	 * @brief			 : Convert this rectangle into a quadruple
	 * @tparam TupleType : The quadruple
	 */
	template <class TupleType, class RawType = DataType> TupleType ToQuadruple()
	{
		return TupleType{static_cast<RawType>(Left), static_cast<RawType>(Top), static_cast<RawType>(Right),
						 static_cast<RawType>(Bottom)};
	}

public:
	VCoreRect(Integer _ILeft, Integer _IRight, Integer _ITop, Integer _IBottom)
		: Left(_ILeft), Right(_IRight), Top(_ITop), Bottom(_IBottom)
	{
	}
	VCoreRect(Rect Rectangle)
		: Left(Rectangle.Left), Right(Rectangle.Right), Top(Rectangle.Top), Bottom(Rectangle.Bottom)
	{
	}
	VCoreRect()
		: Left(reinterpret_cast<Integer>(0)), Right(reinterpret_cast<Integer>(0)), Top(reinterpret_cast<Integer>(0)),
		  Bottom(reinterpret_cast<Integer>(0))
	{
	}

public:
	DataType Left;
	DataType Right;
	DataType Top;
	DataType Bottom;
};
/**
 * @brief
 * @tparam DataType
 */
template <class DataType> class VCorePoint
{
public:
	using Rect		= VCoreRect<DataType>;
	using ConstRect = const Rect &;
	using Integer	= const DataType &;
	using Point		= const VCorePoint &;

public:
	/**
	 * @brief			: Judge the point inside the rectangle or not
	 * @param Judgement : Rectangle for judging
	 * @return			: If the point inside the rectangle, return true, nor return false
	 */
	const bool InsideRectangle(ConstRect Judgement) const
	{
		return Judgement.Left >= X && X <= Judgement.Right && Judgement.Top >= Y && Y <= Judgement.Bottom;
	}
	/**
	 * @brief	: Move the point to specified position
	 * @param X	: The new X
	 * @param Y	: The new Y
	 */
	void Move(Integer X, Integer Y)
	{
		X = X;
		Y = Y;
	}
	/**
	 * @brief		: Offset the point
	 * @param XOF	: The offset value of x
	 * @param YOF	: The offset value of y
	 */
	void Offset(Integer XOF, Integer YOF)
	{
		X += XOF;
		Y += YOF;
	}

public:
	/**
	 * @brief				: Convert the point into two-tuple
	 * @tparam TupleType	: The two-tuple type
	 * @tparam RawType		: The data type of two-tuple type
	 * @return				: The two-tuple
	 */
	template <class TupleType, class RawType = DataType> TupleType ToTwoTuple()
	{
		return TupleType{reinterpret_cast<RawType>(X), RawType<RawType>(Y)};
	}

public:
	friend bool operator==(ConstRect Left, ConstRect Right)
	{
		return Left.X == Right.X && Left.Y == Right.Y;
	}
	friend bool operator!=(ConstRect Left, ConstRect Right)
	{
		return Left.X != Right.X || Left.Y != Right.Y;
	}

public:
	VCorePoint(Integer _IX, Integer _IY) : X(_IX), Y(_IY)
	{
	}
	VCorePoint(Point Point) : X(Point.X), Y(Point.Y)
	{
	}
	VCorePoint() : X(reinterpret_cast<Integer>(0)), Y(reinterpret_cast<Integer>(0))
	{
	}

public:
	DataType X;
	DataType Y;
};

using VRect		 = VCoreRect<long>;
using VRectFloat = VCoreRect<double>;
using VPoint	 = VCorePoint<long>;
using VPointF	 = VCorePoint<double>;

}; // namespace VQuark