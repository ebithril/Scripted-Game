#pragma once

namespace CommonUtilities
{
	namespace Vector
	{
		template <typename TYPE>
		class Vector4
		{
		public:
			Vector4();
			Vector4(const TYPE aX, const TYPE aY, const TYPE aZ, const TYPE aW);

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

			union
			{
				TYPE myW;
				TYPE w;
				TYPE a;
				TYPE myA;
			};
		};
	}
}