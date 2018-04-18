/**LAB WEEK 6: DRAWING EVENTS
 * CS3210
 * @author Dennis Droese
 * @file main.cpp
 * @date April 18, 2018
 */

/*
 * A simple driver program for drawing shapes n' stuff
 */

#include "x11context.h"
#include "shape.h"
#include "image.h"
#include "dynamicdraw.h"
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <fstream>

int main(int argc, char**argv) {

	GraphicsContext* gc = new X11Context(800, 600, GraphicsContext::BLACK);

	std::ofstream fileOut;

	dynamicdraw dd;

	gc->runLoop(&dd);


	fileOut.open("output.txt");
	if(fileOut.is_open()){
		dd.theImage->out(fileOut);
		std::cout << "OUTPUT FILE WAS SAVED AS output.txt\n";
	} else {
		std::cout << "COULD NOT OUTPUT DATA TO output.txt FILE!!!\n";
	}

	fileOut.close();

	delete gc;

	return 0;
}
