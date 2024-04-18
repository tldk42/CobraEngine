#pragma once

#include "Vector2D.h"

namespace Cobra
{
	namespace Math
	{
		template <typename T>
		struct TVector
		{
			static_assert(std::is_floating_point_v<T>, "T must be floating point!");

		public:
			using FReal = T;

			union
			{
				struct
				{
					T X;
					T Y;
					T Z;
				};

				T XYZ[3];
			};

			static const TVector ZeroVector;
			static const TVector OneVector;

			static const TVector UpVector;
			static const TVector DownVector;
			static const TVector ForwardVector;
			static const TVector BackwardVector;
			static const TVector RightVector;
			static const TVector LeftVector;

			static const TVector XAxisVector;
			static const TVector YAxisVector;
			static const TVector ZAxisVector;

			static inline TVector Zero() { return ZeroVector; }
			static inline TVector One() { return OneVector; }
			static inline TVector UnitX() { return XAxisVector; }
			static inline TVector UnitY() { return YAxisVector; }
			static inline TVector UnitZ() { return ZAxisVector; }

		public:
			TVector();
			TVector(T InF);
			TVector(T InX, T InY, T InZ);

			explicit TVector(const TVector2<T> V, T InZ);

			inline TVector        operator^(const TVector& V) const;
			inline TVector        Cross(const TVector& V2) const;
			inline static TVector CrossProduct(const TVector& V1, const TVector& V2);

			inline T        operator|(const TVector& V) const;
			inline T        Dot(const TVector& V) const;
			inline static T DotProduct(const TVector& V1, const TVector& V2);

			inline TVector operator+(const TVector& V) const;
			inline TVector operator+(T Value) const;

			inline TVector operator-(const TVector& V) const;
			inline TVector operator-(T Value) const;

			inline TVector operator*(const TVector& V) const;
			inline TVector operator*(T Value) const;

			inline TVector operator/(const TVector& V) const;
			inline TVector operator/(T Value) const;

			inline bool operator==(const TVector& V) const;
			inline bool operator!=(const TVector& V) const;
			inline bool Equals(const TVector& V, T Tolerance = CB_KINDA_SMALL_NUMBER) const;
			inline bool AllComponentsEqual(T Tolerance = CB_KINDA_SMALL_NUMBER) const;

			inline TVector operator-() const;

			inline TVector operator+=(const TVector& V);
			inline TVector operator-=(const TVector& V);

		public:
			T GetMax() const;
			T GetMax_Abs() const;
			T GetMin() const;
			T GetMin_Abs() const;

			bool    IsNormalized() const;
			bool    Normalize(T Tolerance = CB_SMALL_NUMBER);
			TVector GetSafeNormal(T Tolerance = CB_SMALL_NUMBER, const TVector& ResultIfZero = ZeroVector) const;
			TVector GetSafeNormal2D(T Tolerance = CB_SMALL_NUMBER, const TVector& ResultIfZero = ZeroVector) const;

			T GetLength() const;
			T GetLengthSquared() const;
			T GetLength2D() const;
			T GetLengthSquared2D() const;

			bool IsNearlyZero(T Tolerance = CB_KINDA_SMALL_NUMBER) const;
			bool IsZero() const;

			TVector GetAbsVector() const;

			std::string ToString() const;
		};

		template <typename T>
		TVector<T>::TVector()
			: X(0),
			  Y(0),
			  Z(0)
		{
		}

		template <typename T>
		TVector<T>::TVector(T InF)
			: X(InF),
			  Y(InF),
			  Z(InF)
		{
		}

		template <typename T>
		TVector<T>::TVector(T InX, T InY, T InZ)
			: X(InX),
			  Y(InY),
			  Z(InZ)
		{
		}

		template <typename T>
		TVector<T>::TVector(const TVector2<T> V, T InZ)
			: X(V.X),
			  Y(V.Y),
			  Z(InZ)
		{
		}

		template <typename T>
		TVector<T> TVector<T>::operator^(const TVector& V) const
		{
			return TVector
			{
				Y * V.Z - Z * V.Y,
				Z * V.X - X * V.Z,
				X * V.Y - Y * V.X
			};
		}

		template <typename T>
		TVector<T> TVector<T>::Cross(const TVector& V2) const
		{
			return *this ^ V2;
		}

		template <typename T>
		TVector<T> TVector<T>::CrossProduct(const TVector& V1, const TVector& V2)
		{
			return V1 ^ V2;
		}

		template <typename T>
		T TVector<T>::operator|(const TVector& V) const
		{
			return X * V.X + Y * V.Y + Z * V.Z;
		}

		template <typename T>
		T TVector<T>::Dot(const TVector& V) const
		{
			return *this | V;
		}

		template <typename T>
		T TVector<T>::DotProduct(const TVector& V1, const TVector& V2)
		{
			return V1 | V2;
		}

		template <typename T>
		TVector<T> TVector<T>::operator+(const TVector& V) const
		{
			return TVector
			{
				X + V.X,
				Y + V.Y,
				Z + V.Z
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator+(T Value) const
		{
			return TVector
			{
				X + Value,
				Y + Value,
				Z + Value
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator-(const TVector& V) const
		{
			return TVector
			{
				X - V.X,
				Y - V.Y,
				Z - V.Z
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator-(T Value) const
		{
			return TVector
			{
				X - Value,
				Y - Value,
				Z - Value
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator*(const TVector& V) const
		{
			return TVector
			{
				X * V.X,
				Y * V.Y,
				Z * V.Z
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator*(T Value) const
		{
			return TVector
			{
				X * Value,
				Y * Value,
				Z * Value
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator/(const TVector& V) const
		{
			return TVector
			{
				X / V.X,
				Y / V.Y,
				Z / V.Z
			};
		}

		template <typename T>
		TVector<T> TVector<T>::operator/(T Value) const
		{
			return TVector
			{
				X / Value,
				Y / Value,
				Z / Value
			};
		}

		template <typename T>
		bool TVector<T>::operator==(const TVector& V) const
		{
			return (X == V.X && Y == V.Y && Z == V.Z);
		}

		template <typename T>
		bool TVector<T>::operator!=(const TVector& V) const
		{
			return (X != V.X || Y != V.Y || Z != V.Z);
		}

		template <typename T>
		bool TVector<T>::Equals(const TVector& V, T Tolerance) const
		{
			return (abs(X - V.X) <= Tolerance && abs(Y - V.Y) <= Tolerance && abs(Z - V.Z) <= Tolerance);
		}

		template <typename T>
		bool TVector<T>::AllComponentsEqual(T Tolerance) const
		{
			return (abs(X - Y) <= Tolerance && abs(Y - Z) <= Tolerance && abs(X - Z) <= Tolerance);
		}

		template <typename T>
		TVector<T> TVector<T>::operator-() const
		{
			return TVector{-X, -Y, -Z};
		}

		template <typename T>
		TVector<T> TVector<T>::operator+=(const TVector& V)
		{
			X += V.X;
			Y += V.Y;
			Z += V.Z;

			return *this;
		}

		template <typename T>
		TVector<T> TVector<T>::operator-=(const TVector& V)
		{
			X -= V.X;
			Y -= V.Y;
			Z -= V.Z;

			return *this;
		}

		template <typename T>
		T TVector<T>::GetMax() const
		{
			return std::max(std::max(X, Y), Z);
		}

		template <typename T>
		T TVector<T>::GetMax_Abs() const
		{
			return std::max(std::max(abs(X), abs(Y)), abs(Z));
		}

		template <typename T>
		T TVector<T>::GetMin() const
		{
			return std::min(std::min(X, Y), Z);
		}

		template <typename T>
		T TVector<T>::GetMin_Abs() const
		{
			return std::min(std::min(abs(X), abs(Y)), abs(Z));
		}

		template <typename T>
		bool TVector<T>::IsNormalized() const
		{
			return abs(1.f - GetLengthSquared()) < CB_THRESH_VECTOR_NORMALIZED;
		}

		template <typename T>
		bool TVector<T>::Normalize(T Tolerance)
		{
			const T squareSum = X * X + Y * Y + Z * Z;
			if (squareSum > Tolerance)
			{
				const T Scale = 1 / sqrt(squareSum);
				X *= Scale;
				Y *= Scale;
				Z *= Scale;
				return true;
			}
			return false;
		}

		template <typename T>
		TVector<T> TVector<T>::GetSafeNormal(T Tolerance, const TVector& ResultIfZero) const
		{
			const T squareSum = X * X + Y * Y + Z * Z;

			if (squareSum == 1.f)
			{
				return *this;
			}
			else if (squareSum < Tolerance)
			{
				return ResultIfZero;
			}
			const T Scale = (T)(1 / sqrt(squareSum));
			return TVector<T>(X * Scale, Y * Scale, Z * Scale);
		}

		template <typename T>
		TVector<T> TVector<T>::GetSafeNormal2D(T Tolerance, const TVector& ResultIfZero) const
		{
			const T squareSum = X * X + Y * Y;

			if (squareSum == 1.f)
			{
				if (Z == 0.f)
				{
					return *this;
				}
				else
				{
					return TVector<T>(X, Y, 0.f);
				}
			}
			else if (squareSum < Tolerance)
			{
				return ResultIfZero;
			}

			const T Scale = (T)(1 / sqrt(squareSum));
			return TVector<T>(X * Scale, Y * Scale, 0.f);
		}

		template <typename T>
		T TVector<T>::GetLength() const
		{
			return sqrt(X * X + Y * Y + Z * Z);
		}

		template <typename T>
		T TVector<T>::GetLengthSquared() const
		{
			return X * X + Y * Y + Z * Z;
		}

		template <typename T>
		T TVector<T>::GetLength2D() const
		{
			return sqrt(X * X + Y * Y);
		}

		template <typename T>
		T TVector<T>::GetLengthSquared2D() const
		{
			return X * X + Y * Y;
		}

		template <typename T>
		bool TVector<T>::IsNearlyZero(T Tolerance) const
		{
			return abs(X) <= Tolerance && abs(Y) <= Tolerance && abs(Z) <= Tolerance;
		}

		template <typename T>
		bool TVector<T>::IsZero() const
		{
			return X == 0.f && Y = 0.f && Z = 0.f;
		}

		template <typename T>
		TVector<T> TVector<T>::GetAbsVector() const
		{
			return TVector
			{
				abs(X),
				abs(Y),
				abs(Z)
			};
		}

		template <typename T>
		std::string TVector<T>::ToString() const
		{
			return std::format("X={0:3.3f} Y={1:3.3f} Z={2:3.3f}\n", X, Y, Z);
		}
	}
}
