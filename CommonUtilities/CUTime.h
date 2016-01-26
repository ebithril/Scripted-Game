#pragma once

namespace CommonUtilities
{
	namespace Timers
	{
		class Time
		{
		public:
			Time();
			~Time();
			inline const long double GetHours() const;
			inline const long double GetMinutes() const;
			inline const long double GetSeconds() const;
			inline const long double GetMilliseconds() const;
			inline const long double GetMicroseconds() const;
			void AddTime(long double timePassed);
			void Reset();
		private:
			long double myTime;
		};
	}
}


namespace CommonUtilities
{
	namespace Timers
	{
		inline const long double Time::GetHours() const
		{
			return ((myTime / 60.0) / 60.0);
		}

		inline const long double Time::GetMinutes() const
		{
			return (myTime / 60.0);
		}

		inline const long double Time::GetSeconds() const
		{
			return myTime;
		}

		inline const long double Time::GetMilliseconds() const
		{
			return (myTime * 1000.0);
		}

		inline const long double Time::GetMicroseconds() const
		{
			return ((myTime * 1000.0) * 1000.0);
		}
	}
}