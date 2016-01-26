#pragma once

#include <tga2d/math/vector2.h>
#include "../CommonUtilities/Vector2.h"

DX2D::Vector2f ConvertToDXD2DVector(const CommonUtilities::Vector::Vector2<float>& aVector);

CommonUtilities::Vector::Vector2<float> ConvertToCUVector(const DX2D::Vector2f& aVector);