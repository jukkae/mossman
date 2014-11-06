/*
 * main.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include <chrono>
#include "core/Application.h"

using namespace mossman;

int main()
{
	using namespace std::chrono;

	mossman::Application app;
	app.init();

	auto currentTime = high_resolution_clock::now();

	while(app.isRunning()) {
		auto newTime = high_resolution_clock::now();
		double dt = duration_cast<duration<double>>(currentTime - newTime).count();
		app.update(dt);
		currentTime = newTime;
	}

	return 0;
}
