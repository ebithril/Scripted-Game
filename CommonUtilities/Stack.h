#pragma once

#include "GrowingArray.h"

namespace CommonUtilities
{
	namespace Containers
	{
		template <typename Type>
		class Stack
		{
		public:
			Stack(unsigned int aSize);
			Stack(const Stack &aStack);
			~Stack();

			const Stack& operator=(const Stack &aStack);

			inline void Add(const Type &aObject);
			inline void PopBack();
			inline Type& GetLast();
			inline const Type& GetLast() const;
			inline void Clear();
			inline unsigned int Size();
		private:
			GrowingArray<Type, unsigned int> myData;
		};
	}
}

namespace CommonUtilities
{
	namespace Containers
	{
		template <typename Type>
		Stack<Type>::Stack(unsigned int aSize) : myData(aSize)
		{
		}

		template <typename Type>
		Stack<Type>::Stack(const Stack &aStack)
		{
			*this = aStack;
		}

		template <typename Type>
		Stack<Type>::~Stack()
		{
		}

		template <typename Type>
		const Stack<Type>& Stack<Type>::operator=(const Stack &aStack)
		{
			myData = aStack.myData;
			return *this;
		}

		template <typename Type>
		inline void Stack<Type>::Add(const Type &aObject)
		{
			myData.Add(aObject);
		}

		template <typename Type>
		inline void Stack<Type>::PopBack()
		{
			myData.PopBack();
		}

		template <typename Type>
		inline Type& Stack<Type>::GetLast()
		{
			return myData.GetLast();
		}

		template <typename Type>
		inline const Type& Stack<Type>::GetLast() const
		{
			return myData.GetLast();
		}

		template <typename Type>
		inline void Stack<Type>::Clear()
		{
			myData.RemoveAll();
		}

		template <typename Type>
		inline unsigned int Stack<Type>::Size()
		{
			return myData.Size();
		}
	}
}