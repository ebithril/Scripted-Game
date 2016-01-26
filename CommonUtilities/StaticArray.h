#pragma once

#include <assert.h>

namespace CommonUtilities
{
	namespace Containers
	{
		template <typename Type, int Size>
		class StaticArray
		{
		public:
			StaticArray();
			StaticArray(const StaticArray& aStaticArray);

			~StaticArray();

			StaticArray& operator=(const StaticArray& aStaticArray);

			inline const Type& operator[](const int& aIndex) const;
			inline Type& operator[](const int& aIndex);


			// Utility functions
			inline void Insert(int aIndex, const Type& aObject);
			inline void DeleteAll();
		private:
			Type myArray[Size];
		};
	}
}

namespace CommonUtilities
{
	namespace Containers
	{
		template <typename Type, int Size>
		StaticArray<Type, Size>::StaticArray()
		{
		}

		template <typename Type, int Size>
		StaticArray<Type, Size>::StaticArray(const StaticArray<Type, Size>& aStaticArray)
		{
			*this = aStaticArray;
		}

		template <typename Type, int Size>
		StaticArray<Type, Size>::~StaticArray()
		{
		}

		template <typename Type, int Size>
		StaticArray<Type, Size>& StaticArray<Type, Size>::operator=(const StaticArray<Type, Size>& aStaticArray)
		{
			for (int i = 0; i < Size; i++)
			{
				myArray[i] = aStaticArray[i];
			}

			return *this;
		}

		template <typename Type, int Size>
		inline const Type& StaticArray<Type, Size>::operator[](const int& aIndex) const
		{
			assert(aIndex >= 0 && "Index less than zero.");
			assert(Size > aIndex && "Subscript out of range");

			return myArray[aIndex];
		}

		template <typename Type, int Size>
		inline Type& StaticArray<Type, Size>::operator[](const int& aIndex)
		{
			assert(aIndex >= 0 && "Index less than zero.");
			assert(Size > aIndex && "Subscript out of range");

			return myArray[aIndex];
		}

		template <typename Type, int Size>
		inline void StaticArray<Type, Size>::Insert(int aIndex, const Type& aObject)
		{
			assert(aIndex >= 0 && "Index less than zero.");
			assert(Size > aIndex && "Index bigger than size.");

			for (int i = Size - 1; i > aIndex; i--)
			{
				myArray[i] = myArray[i - 1];
			}

			myArray[aIndex] = aObject;
		}

		template <typename Type, int Size>
		inline void StaticArray<Type, Size>::DeleteAll()
		{
			for (int i = 0; i < Size; i++)
			{
				delete[](myArray[i]);
				myArray[i] = nullptr;
			}
		}
	}
}