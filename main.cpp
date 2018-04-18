/**LAB WEEK 4: SHAPES
 * CS3210
 * @author Dennis Droese
 * @file main.cpp
 * @date March 28, 2018
 */

/*
 * A simple driver program for drawing shapes n' stuff
 */

#include "x11context.h"
#include "shape.h"
#include "image.h"
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <fstream>

int main(int argc, char**argv) {

	std::string arg2 = argv[1];

	if (argc < 2) {
		std::cout << "Run demo mode if you want a demo file created.\n";
		std::cout << "Run file load mode if you have a pre-existing shape file.\n";

		std::cout << "Usage (file load): " << argv[0] << " <filename>\n";
		std::cout << "Usage (demo mode): " << argv[0] << " DEMO\n";
		return 0;
	} else if (arg2.compare("DEMO") == 0) {
		// Do the file output demo

		std::ofstream fileOut;

		// Set up a bunch of matrices
		matrix* p0 = new matrix(4, 1);
		(*p0)[0][0] = 50.0;
		(*p0)[1][0] = 200.0;
		(*p0)[2][0] = 99.0;
		(*p0)[3][0] = 1.0;

		matrix* p1 = new matrix(4, 1);
		(*p1)[0][0] = 75.0;
		(*p1)[1][0] = 222.0;
		(*p1)[2][0] = 283.0;
		(*p1)[3][0] = 1.0;

		matrix* p2 = new matrix(4, 1);
		(*p2)[0][0] = 100.0;
		(*p2)[1][0] = 300.0;
		(*p2)[2][0] = 88.0;
		(*p2)[3][0] = 1.0;

		matrix* p3 = new matrix(4, 1);
		(*p3)[0][0] = 124.0;
		(*p3)[1][0] = 300.0;
		(*p3)[2][0] = 84.0;
		(*p3)[3][0] = 1.0;

		matrix* p4 = new matrix(4, 1);
		(*p4)[0][0] = 50.0;
		(*p4)[1][0] = 365.0;
		(*p4)[2][0] = 45.0;
		(*p4)[3][0] = 1.0;

		std::vector<matrix*> myVect;

		// set up a matrix vector
		myVect.push_back(p0);
		myVect.push_back(p1);
		myVect.push_back(p2);
		myVect.push_back(p3);
		myVect.push_back(p4);

		// A bunch of demo data for reading in a predefined istream.
		std::istringstream pointToReadIn("POINT	19987215		88	275	0	1\n"
				"CIRCLE	88888		100	475	0	1	40\n"
				"TRI	16777777		300	100	0	1		"
				"250	277	0	1		222	202	0	1\n"
				"POLY	12345678		55 205 99 1		"
				"77 227 283 1	105 305 88 1	129 309 84 1	"
				"55 369 45 1		88 88 88 1 		123 321 1 1");

		GraphicsContext* gc = new X11Context(800, 600, GraphicsContext::BLACK);

		// create a circle
		circle* theBigOlCircle = new circle(200.0, 175.0, 0.5, 50.0,
				GraphicsContext::GREEN);

		// create a point
		point* whatsThePoint = new point(100.0, 300.0, 0.0,
				GraphicsContext::WHITE);

		// create a line
		line* theBestLineEver = new line(20.0, 75.0, 0.0, 300.0, 288.0, 0.0,
				GraphicsContext::BLUE);

		// create a triangle
		triangle* theTriHard = new triangle(400.0, 400.0, 0.0, 450.0, 577.0,
				0.0, 432.0, 588.0, 0.0, GraphicsContext::YELLOW);

		// create a polygon with the matrices from earlier.
		poly* myPolygon = new poly(myVect, GraphicsContext::CYAN);

		// create a new image.
		image* theImage = new image();

		// add all of the shapes to the image.
		theImage->add(theBigOlCircle);
		theImage->add(whatsThePoint);
		theImage->add(theBestLineEver);
		theImage->add(theTriHard);
		theImage->add(myPolygon);

		// Add shapes to the image from the raw istream.
		theImage->in(pointToReadIn);

		// make a copy of the image.
		image* attackOfTheClones = new image(*theImage);

		// draw the copied image and print contents to console.
		attackOfTheClones->draw(gc);
		attackOfTheClones->out(std::cout);

		sleep(6);

		// delete the old image.
		theImage->erase();
		delete theImage;

		// output the new image to a text file.
		fileOut.open("demo.txt");
		if(fileOut.is_open()){
			attackOfTheClones->out(fileOut);

			std::cout << "DEMO OUTPUT FILE WAS SAVED AS demo.txt\n";

		} else {
			std::cout << "COULD NOT OUTPUT DATA TO DEMO FILE!!!\n";
		}

		fileOut.close();

		// erase and delete the new image.
		attackOfTheClones->erase();
		delete attackOfTheClones;
		delete gc;

		return 0;
	} else {
		//Load a specified file into an image.

		std::ifstream input;

		input.open(arg2);

		if(input.is_open()){
			GraphicsContext* gc = new X11Context(800, 600, GraphicsContext::BLACK);
			image* theImage = new image();

			theImage->in(input);

			theImage->draw(gc);

			sleep(6);

			theImage->erase();
			delete theImage;
			delete gc;

			return 0;
		} else {
			std::cout << "FILE READ ERROR: COULD NOT OPEN " << arg2;
			return 0;
		}

		return 0;
	}
}
