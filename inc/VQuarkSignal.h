/*
 * VQuarkSignal.h (2023/5.27)
 * 	 The siganl slot in VQuark
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

#include <functional>
#include <list>
#include <memory>

namespace VQuark
{
template <class... ParameterType> class ConnectBasic
{
public:
	explicit ConnectBasic(std::function<void(ParameterType...)> Function)
	{
		CallFunction = Function;
	}
	inline std::function<void(ParameterType...)> *GetFunction()
	{
		return &CallFunction;
	}

	const bool IsBlock() const
	{
		return Blocked;
	}
	void SetBlock(const bool &Status)
	{
		Blocked = Status;
	}

private:
	std::function<void(ParameterType...)> CallFunction;
	bool								  Blocked = false;
};

template <class... Type> class ConnectFunctional : public ConnectBasic<Type...>
{
public:
	using FunctionPointer = void (*)(Type...);

public:
	explicit ConnectFunctional(FunctionPointer Init) : ConnectBasic<Type...>(std::function<void(Type...)>(Init))
	{
		Function = Init;
	}
	inline FunctionPointer GetPointer()
	{
		return Function;
	}

private:
	FunctionPointer Function;
};
template <class ObjectType, class... Type> class Connection : public ConnectBasic<Type...>
{
public:
	using ObjectPointer = void (ObjectType::*)(Type...);

public:
	Connection(ObjectType *ObjectPointer, ObjectPointer Function)
		: ConnectBasic<Type...>(
			  [ObjectPointer, Function](Type... Agrument) { (*ObjectPointer.*Function)(Agrument...); })
	{
		Object = ObjectPointer;
	}

	inline void *GetRawObject()
	{
		return Object;
	}
	inline ObjectPointer GetRawFunction()
	{
		return ObjectFunction;
	}

private:
	ObjectType	 *Object;
	ObjectPointer ObjectFunction;
};

/**
 * @brief : The operation
 */
enum class VQuarkSignalOperation
{
	Del,
	Block,
	Disblock
};

/**
 * @brief : The signal in VQuark
 * @tparam ...Type : The agrument type list
 */
template <class... Type> class VSignal
{
private:
	void _Operator(void (*Function)(Type...), VQuarkSignalOperation OperatorStage)
	{
		for (auto Iterator = Slots->begin; Iterator != Slots->end();)
		{
			ConnectBasic<Type...> *ConnectFunction = static_cast<ConnectBasic<Type...> *>((*Iterator));
			if (ConnectFunction->GetFunction() == Function)
			{
				switch (OperatorStage)
				{
				case VQuarkSignalOperation::Del: {
					Slots->erase(Iterator++);

					break;
				}
				case VQuarkSignalOperation::Block: {
					ConnectFunction->SetBlock(true);

					++Iterator;

					break;
				}
				case VQuarkSignalOperation::Disblock: {
					ConnectFunction->SetBlock(false);

					++Iterator;

					break;
				}
				}
			}
			else
			{
				++Iterator;
			}
		}
	}

	template <class ObjectType>
	void _Operator(ObjectType *Object, void (ObjectType::*ObjectFunction)(Type...), VQuarkSignalOperation OperatorStage)
	{
		for (auto Iterator = Slots->begin; Iterator != Slots->end();)
		{
			Connection<ObjectType, Type...> *ConnectFunction =
				static_cast<Connection<ObjectType, Type...> *>((*Iterator));
			if (ConnectFunction->GetRawFunction() == ObjectFunction && ConnectFunction->GetRawFunction() == Object)
			{
				switch (OperatorStage)
				{
				case VQuarkSignalOperation::Del: {
					Slots->erase(Iterator++);

					break;
				}
				case VQuarkSignalOperation::Block: {
					ConnectFunction->SetBlock(true);

					++Iterator;

					break;
				}
				case VQuarkSignalOperation::Disblock: {
					ConnectFunction->SetBlock(false);

					++Iterator;

					break;
				}
				}
			}
			else
			{
				++Iterator;
			}
		}
	}

public:
	inline void Connect(void (*Function)(Type...))
	{
		std::shared_ptr<ConnectFunctional<Type...>> FunctionPointer(new ConnectFunctional<Type...>(Function));
		Slots->push_back(FunctionPointer);
	}
	template <class ObjectType> inline void Connect(ObjectType *Object, void (ObjectType::*Function)(Type...))
	{
		std::shared_ptr<Connection<ObjectType, Type...>> FunctionPointer(
			new Connection<ObjectType, Type...>(Object, Function));
		Slots->push_back(FunctionPointer);
	}
	template <class ObjectType> inline void Disconnect(ObjectType *Object, void (ObjectType::*Function)(Type...))
	{
		_Operator(Object, Function, VQuarkSignalOperation::Del);
	}
	void Block(void (*Function)(Type...), bool BlockStatus)
	{
		_Operator(Function, BlockStatus ? VQuarkSignalOperation::Block : VQuarkSignalOperation::Disblock);
	}
	template <class ObjectType> void Block(ObjectType *Object, void (*Function)(Type...), bool BlockStatus)
	{
		_Operator(Function, Object, BlockStatus ? VQuarkSignalOperation::Block : VQuarkSignalOperation::Disblock);
	}
	void Emit(Type... Agruments)
	{
		for (auto Iterator = Slots->begin(); Iterator != Slots->end(); ++Iterator)
		{
			if ((*Iterator)->IsBlock() == true)
			{
				continue;
			}

			auto Function = (*Iterator)->GetFunction();

			(*Function)(Agruments...);
		}
	}

public:
	VSignal()
	{
		Slots = new std::list<std::shared_ptr<ConnectBasic<Type...>>>;
	}
	~VSignal()
	{
		delete Slots;
	}

private:
	std::list<std::shared_ptr<ConnectBasic<Type...>>> *Slots;
};

} // namespace VQuark
