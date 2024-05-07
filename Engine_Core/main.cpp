#include <iostream>

#include "App/Window/Window.h"


int main()
{
	using namespace Cobra;

	Window* testWindow = new Window(L"Test Window", {1600, 900, false, true});

	while (!testWindow->IsClosed())
		testWindow->Update();

	return 0;
}
