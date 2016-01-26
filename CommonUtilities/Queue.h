#pragma once

#include "GrowingArray.h"

namespace CommonUtilities
{
	namespace Containers
	{
		template <typename T, typename CountType = unsigned short>
		class Queue
		{
		public:
			Queue();
			~Queue();

			void Add(const T& aObject);
			void Pop();

			const T& GetFirst() const;
			T& GetFirst();

			inline CountType GetSize() const;
		private:
			GrowingArray<T, CountType> myData;
		};
	}
}


namespace CommonUtilities
{
	namespace Containers
	{
		template <typename T, typename CountType = unsigned short>
		Queue<T, CountType>::Queue() : myData(1)
		{
		}

		template <typename T, typename CountType = unsigned short>
		Queue<T, CountType>::~Queue()
		{
		}

		template <typename T, typename CountType = unsigned short>
		void Queue<T, CountType>::Add(const T& aObject)
		{
			myData.Add(aObject);
		}

		template <typename T, typename CountType = unsigned short>
		void Queue<T, CountType>::Pop()
		{
			myData.Pop();
		}

		template <typename T, typename CountType = unsigned short>
		const T& Queue<T, CountType>::GetFirst() const
		{
			return myData.GetFirst();
		}
		
		template <typename T, typename CountType = unsigned short>
		T& Queue<T, CountType>::GetFirst()
		{
			return myData.GetFirst();
		}

		template <typename T, typename CountType = unsigned short>
		CountType Queue<T, CountType>::GetSize() const
		{
			return myData.Size();
		}
	}
}