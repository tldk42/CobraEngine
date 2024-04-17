#pragma once

namespace Cobra
{
	namespace Math
	{
		template <typename T>
		struct TVector;
		template <typename T>
		struct TVector2;
	}
}

using FVector = Cobra::Math::TVector<double>;
using FVector2D = Cobra::Math::TVector2<double>;

using FVector3d = Cobra::Math::TVector<double>;
using FVector2d = Cobra::Math::TVector2<double>;

using FVector3f = Cobra::Math::TVector<float>;
using FVector2f = Cobra::Math::TVector2<float>;
