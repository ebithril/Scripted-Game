#pragma once

#include <memory.h>
#include <assert.h>

namespace CommonUtilities
{
	namespace Containers
	{
		template<typename ObjectType, typename SizeType = unsigned short>
		class GrowingArray
		{
		public:
			GrowingArray();
			GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true);
			GrowingArray(const GrowingArray& aGrowingArray);
			~GrowingArray();

			typedef ObjectType* iterator;
			typedef const ObjectType* const_iterator;
			iterator begin() { return &myArray[0]; }
			const_iterator begin() const { return &myArray[0]; }
			iterator end() { return &myArray[mySize]; }
			const_iterator end() const { return &myArray[mySize]; }

			GrowingArray& operator=(const GrowingArray& aGrowingArray);

			void Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);
			void ReInit(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true);

			inline ObjectType& operator[](const SizeType& aIndex);
			inline const ObjectType& operator[](const SizeType& aIndex) const;

			inline void Add(const ObjectType& aObject);
			inline void Insert(SizeType aIndex, const ObjectType& aObject);
			inline void DeleteCyclic(ObjectType& aObject);
			inline void DeleteCyclicAtIndex(SizeType aItemNumber);
			inline void RemoveCyclic(const ObjectType& aObject);
			inline void RemoveCyclicAtIndex(SizeType aItemNumber);
			inline void PopBack();
			inline void Pop();
			inline SizeType Find(const ObjectType& aObject);

			inline ObjectType& GetLast();
			inline const ObjectType& GetLast() const;

			inline ObjectType& GetFirst();
			inline const ObjectType& GetFirst() const;

			static const SizeType FoundNone = static_cast<SizeType>(-1);

			inline void RemoveAll();
			inline void DeleteAll();

			inline SizeType GetCapacity() const;

			void Optimize();
			__forceinline const SizeType Size() const;
		private:
			inline void Resize(int aNewSize);

			SizeType mySize;
			SizeType myCapacity;
			ObjectType* myArray;
			bool mySafeModeFlag;
			bool myIsInitialized;
		};
	}
}

namespace CommonUtilities
{
	namespace Containers
	{
		template<typename ObjectType, typename SizeType = unsigned short>
		GrowingArray<ObjectType, SizeType>::GrowingArray()
		{
			myArray = nullptr;
			myCapacity = 0;
			mySize = 0;
			mySafeModeFlag = true;
			myIsInitialized = false;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		GrowingArray<ObjectType, SizeType>::GrowingArray(SizeType aNrOfRecommendedItems, bool aUseSafeModeFlag = true)
		{
			assert(aNrOfRecommendedItems > 0 && "Size can't be less than 1.");

			myCapacity = aNrOfRecommendedItems;
			myArray = new ObjectType[myCapacity];
			mySize = 0;
			mySafeModeFlag = aUseSafeModeFlag;
			myIsInitialized = true;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		GrowingArray<ObjectType, SizeType>::GrowingArray(const GrowingArray& aGrowingArray)
		{
			myArray = nullptr;
			*this = aGrowingArray;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		GrowingArray<ObjectType, SizeType>::~GrowingArray()
		{
			delete[] myArray;
			myArray = nullptr;

			mySafeModeFlag = true;
			mySize = 0;
			myCapacity = 0;
			myIsInitialized = false;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		SizeType GrowingArray<ObjectType, SizeType>::GetCapacity() const
		{
			return myCapacity;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		GrowingArray<ObjectType, SizeType>& GrowingArray<ObjectType, SizeType>::operator=(const GrowingArray& aGrowingArray)
		{
			delete[] myArray;
			myCapacity = aGrowingArray.myCapacity;
			myArray = new ObjectType[myCapacity];

			mySize = aGrowingArray.mySize;
			mySafeModeFlag = aGrowingArray.mySafeModeFlag;

			if (mySafeModeFlag == true)
			{
				for (SizeType i = 0; i < mySize; i++)
				{
					myArray[i] = aGrowingArray.myArray[i];
				}
			}
			else
			{
				memcpy(myArray, aGrowingArray.myArray, sizeof(aGrowingArray.myArray) * aGrowingArray.mySize);
			}

			myIsInitialized = true;

			return *this;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		void GrowingArray<ObjectType, SizeType>::Init(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true)
		{
			assert(myIsInitialized == false && "growing array is already initalized.");
			assert(aNrOfRecomendedItems > 0 && "Size can't be less than 1.");

			mySize = 0;
			myCapacity = aNrOfRecomendedItems;
			mySafeModeFlag = aUseSafeModeFlag;
			myIsInitialized = true;

			myArray = new ObjectType[myCapacity];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		void GrowingArray<ObjectType, SizeType>::ReInit(SizeType aNrOfRecomendedItems, bool aUseSafeModeFlag = true)
		{
			assert(myIsInitialized == true && "growing array isn't initalized.");
			assert(aNrOfRecomendedItems > 0 && "Size can't be less than 1.");

			delete[] myArray;

			mySize = 0;
			myCapacity = aNrOfRecomendedItems;
			mySafeModeFlag = aUseSafeModeFlag;
			myIsInitialized = true;

			myArray = new ObjectType[myCapacity];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex)
		{
			assert(mySize > aIndex && "Subscript out of range.");
			assert(aIndex >= 0 && "Subscript less than 0.");

			return myArray[aIndex];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline const ObjectType& GrowingArray<ObjectType, SizeType>::operator[](const SizeType& aIndex) const
		{
			assert(mySize > aIndex && "Subscript out of range.");
			assert(aIndex >= 0 && "Subscript less than 0.");

			return myArray[aIndex];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::Add(const ObjectType& aObject)
		{
			if (mySize >= myCapacity)
			{
				Resize(myCapacity * 2);
			}

			myArray[mySize] = aObject;

			++mySize;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::Insert(SizeType aIndex, const ObjectType& aObject)
		{
			assert(mySize > aIndex && "Index larger than size.");

			if (myCapacity <= mySize)
			{
				Resize(myCapacity * 2);
			}

			++mySize;

			for (SizeType i = mySize - 1; i > aIndex; i--)
			{
				myArray[i] = myArray[i - 1];
			}

			myArray[aIndex] = aObject;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::DeleteCyclic(ObjectType& aObject)
		{
			for (SizeType i = 0; i < mySize; i++)
			{
				if (myArray[i] == aObject)
				{
					--mySize;

					delete myArray[i];

					myArray[i] = myArray[mySize];
					break;
				}
			}
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::DeleteCyclicAtIndex(SizeType aItemNumber)
		{
			assert(mySize > aItemNumber && "Index bigger than size.");
			assert(aItemNumber >= 0 && "Index less than 0.");

			--mySize;

			delete[] myArray[aItemNumber];

			myArray[aItemNumber] = myArray[mySize];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::RemoveCyclic(const ObjectType& aObject)
		{
			for (SizeType i = 0; i < mySize; i++)
			{
				if (myArray[i] == aObject)
				{
					--mySize;

					myArray[i] = myArray[mySize];
					break;
				}
			}
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::RemoveCyclicAtIndex(SizeType aItemNumber)
		{
			assert(mySize > aItemNumber && "Index bigger than size.");
			assert(aItemNumber >= 0 && "Index less than 0.");

			--mySize;

			myArray[aItemNumber] = myArray[mySize];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline SizeType GrowingArray<ObjectType, SizeType>::Find(const ObjectType& aObject)
		{
			for (SizeType i = 0; i < mySize; i++)
			{
				if (myArray[i] == aObject)
				{
					return i;
				}
			}

			return FoundNone;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline ObjectType& GrowingArray<ObjectType, SizeType>::GetLast()
		{
			return myArray[mySize - 1];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline const ObjectType& GrowingArray<ObjectType, SizeType>::GetLast() const
		{
			return myArray[mySize - 1];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::RemoveAll()
		{
			mySize = 0;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::DeleteAll()
		{
			for (SizeType i = 0; i < mySize; i++)
			{
				delete[] myArray[i];
			}

			mySize = 0;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		void GrowingArray<ObjectType, SizeType>::Optimize()
		{
			myCapacity = mySize;

			ObjectType *newArray = new ObjectType[myCapacity];

			for (SizeType i = 0; i < mySize; i++)
			{
				newArray[i] = myArray[i];
			}

			delete[] myArray;
			myArray = newArray;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		__forceinline const SizeType GrowingArray<ObjectType, SizeType>::Size() const
		{
			return mySize;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::Resize(int aNewSize)
		{
			myCapacity = aNewSize;

			ObjectType *newArray = new ObjectType[myCapacity];

			for (SizeType i = 0; i < mySize; i++)
			{
				newArray[i] = myArray[i];
			}

			delete[] myArray;
			myArray = newArray;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::PopBack()
		{
			--mySize;
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline void GrowingArray<ObjectType, SizeType>::Pop()
		{
			--mySize;

			for (int i = 0; i < mySize; i++)
			{
				myArray[i] = myArray[i + 1];
			}
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline ObjectType& GrowingArray<ObjectType, SizeType>::GetFirst()
		{
			assert(mySize > 0 && "No Items in array.");

			return myArray[0];
		}

		template<typename ObjectType, typename SizeType = unsigned short>
		inline const ObjectType& GrowingArray<ObjectType, SizeType>::GetFirst() const
		{
			assert(mySize > 0 && "No Items in array.");

			return myArray[0];

		}
	}
}