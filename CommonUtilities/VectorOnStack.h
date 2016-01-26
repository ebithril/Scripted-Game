#pragma once

#include <assert.h>
#include <memory.h>

namespace CommonUtilities
{
	namespace Containers
	{
		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		class VectorOnStack
		{
		public:
			VectorOnStack();
			VectorOnStack(const VectorOnStack& aVectorOnStack);

			~VectorOnStack();

			VectorOnStack& operator=(const VectorOnStack &aVectorOnStack);

			inline const Type& operator[](const CountType &aIndex) const;
			inline Type& operator[](const CountType &aIndex);

			inline void Add(const Type& aObject);
			inline void Insert(CountType aIndex, const Type &aObject);
			inline void DeleteCyclic(const Type &aObject);
			inline void DeleteCyclicAtIndex(CountType aItemNumber);
			inline void RemoveCyclic(const Type &aObject);
			inline void RemoveCyclicAtIndex(CountType aItemNumber);

			inline void Clear();
			inline void DeleteAll();

			inline CountType Size() const;
		private:
			Type myArray[MaxSize];
			CountType mySize;
		};
	}
}


namespace CommonUtilities
{
	namespace Containers
	{
		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack()
		{
			mySize = 0;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack &aVectorOnStack)
		{
			*this = aVectorOnStack;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::~VectorOnStack()
		{
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>& VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::operator= (const VectorOnStack &aVectorOnStack)
		{
			if (UseSafeModeFlag == true)
			{
				mySize = aVectorOnStack.Size();

				for (int i = 0; i < aVectorOnStack.Size(); i++)
				{
					myArray[i] = aVectorOnStack.myArray[i];
				}
			}
			else
			{
				memcpy(this, &aVectorOnStack, sizeof(aVectorOnStack));
			}

			return *this;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline const Type& VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType &aIndex) const
		{
			assert(aIndex >= 0 && "Index less than zero");
			assert(mySize > aIndex && "Subscript out of range.");

			return myArray[aIndex];
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline Type& VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType &aIndex)
		{
			assert(aIndex >= 0 && "Index less than zero");
			assert(mySize > aIndex && "Subscript out of range.");

			return myArray[aIndex];
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Add(const Type& aObject)
		{
			assert(MaxSize > mySize && "Vector is full");

			myArray[mySize] = aObject;

			++mySize;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Insert(CountType aIndex, const Type &aObject)
		{
			assert(MaxSize > mySize && "Vector is full.");
			assert(aIndex >= 0 && "Index less than zero");
			assert(mySize > aIndex && "Subscript out of range.");

			for (CountType i = mySize - 1; i > aIndex; i--)
			{
				myArray[i] = myArray[i - 1];
			}

			myArray[aIndex] = aObject;

			++mySize;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclic(const Type &aObject)
		{
			for (CountType i = 0; i < mySize; i++)
			{
				if (aObject == myArray[i])
				{
					--mySize;
					delete[] myArray[i];
					myArray[i] = myArray[mySize];
					delete[] myArray[mySize];
					return;
				}
			}
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
		{
			assert(mySize > aItemNumber && "Index bigger than size.");

			--mySize;
			delete[] myArray[aItemNumber];
			myArray[aItemNumber] = myArray[mySize];
			delete[] myArray[mySize];
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclic(const Type &aObject)
		{
			for (CountType i = 0; i < mySize; i++)
			{
				if (myArray[i] == aObject)
				{
					--mySize;
					myArray[i] = myArray[mySize];
					return;
				}
			}
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
		{
			assert(mySize > aItemNumber && "Index bigger than size.");

			--mySize;
			myArray[aItemNumber] = myArray[mySize];
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Clear()
		{
			mySize = 0;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline void VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::DeleteAll()
		{
			for (CountType i = 0; i < mySize; i++)
			{
				delete[] myArray[i];
			}

			mySize = 0;
		}

		template <typename Type, int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
		inline CountType VectorOnStack<Type, MaxSize, CountType, UseSafeModeFlag>::Size() const
		{
			return mySize;
		}
	}
}