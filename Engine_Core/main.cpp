#include <iostream>

#include "Math/Vector.h"

int main()
{
	FVector2D F(3, 1);
	std::cout << F.ToString();

	F.Normalize();
	std::cout << F.ToString();
}
