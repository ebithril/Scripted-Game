#pragma once

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename TYPE>
		class Vector3
		{
		public:
			Vector3();
			Vector3(const TYPE aX, const TYPE aY, const TYPE aZ);

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

			union
			{
				TYPE myZ;
				TYPE z;
				TYPE b;
				TYPE myB;
			};
		};
	}
}