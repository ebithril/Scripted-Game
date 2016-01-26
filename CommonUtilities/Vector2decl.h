#pragma once

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename TYPE>
		class Vector2
		{
		public:
			Vector2();
			Vector2(const TYPE aX, const TYPE aY);
			
			union
			{
				TYPE myX;
				TYPE x;
				TYPE r;
				TYPE myR;
			};

			union
			{
				TYPE myY;
				TYPE y;
				TYPE g;
				TYPE myG;
			};
		};
	}
}