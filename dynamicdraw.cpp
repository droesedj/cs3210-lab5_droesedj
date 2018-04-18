/**
 *	LAB WEEK 6: DRAWING EVENTS
 *	CS3210
 *	@author Dennis Droese
 *	@date April 18, 2018
 *  @file dynamicdraw.h
 */

#include "dynamicdraw.h"
#include "math.h"

/// Helper methods
int getDistance(int x0, int y0, int x1, int y1);


//=================================================

dynamicdraw::dynamicdraw() {
	theImage = new image();
	drawingMode = DRAWMODE_POINT;
	state = STATE_NEWTRI;
	isDragging = false;
	x0 = 0;
	x1 = 0;
	y0 = 0;
	y1 = 0;
}

dynamicdraw::~dynamicdraw(){
	delete theImage;
}

void dynamicdraw::paint(GraphicsContext* gc) {
	theImage->draw(gc);
}

void dynamicdraw::mouseButtonDown(GraphicsContext* gc, unsigned int button,
		int x, int y) {
	if (drawingMode == DRAWMODE_LINE) {
		x0 = x;
		y0 = y;
		x1 = x;
		y1 = y;

		gc->setMode(GraphicsContext::MODE_XOR);
		gc->drawLine(x0, y0, x1, y1);

		isDragging = true;
	} else if(drawingMode == DRAWMODE_POINT){
		theImage->add(new point(x,y,0));
		paint(gc);
	} else if(drawingMode == DRAWMODE_CIRCLE){
		x0 = x;
		y0 = y;
		x1 = x;
		y1 = y;

		gc->setMode(GraphicsContext::MODE_XOR);
		gc->drawCircle(x0,y0,1);

		isDragging = true;
	}
}

void dynamicdraw::mouseButtonUp(GraphicsContext* gc, unsigned int button, int x,
		int y) {
	if (drawingMode == DRAWMODE_LINE) {
		if (isDragging) {
			gc->drawLine(x0, y0, x1, y1);
			x1 = x;
			y1 = y;

			gc->setMode(GraphicsContext::MODE_NORMAL);

			theImage->add(new line(x0,y0,0,x1,y1,0));

			paint(gc);

			isDragging = false;
		}
	} else if (drawingMode == DRAWMODE_POINT) {
		if (isDragging) {

			isDragging = false;
		}
	} else if (drawingMode == DRAWMODE_CIRCLE) {
		if (isDragging) {
			gc->drawCircle(x0, y0, getDistance(x0,y0,x1,y1));
			x1 = x;
			y1 = y;
			gc->setMode(GraphicsContext::MODE_NORMAL);
			theImage->add(new circle(x0,y0,0,getDistance(x0,y0,x1,y1)));
			paint(gc);
			isDragging = false;
		}
	}
}

void dynamicdraw::mouseMove(GraphicsContext* gc, int x, int y) {
	if (drawingMode == DRAWMODE_LINE) {
		if (isDragging) {
			gc->drawLine(x0, y0, x1, y1);
			x1 = x;
			y1 = y;
			gc->drawLine(x0, y0, x1, y1);
		}
	} else if (drawingMode == DRAWMODE_CIRCLE) {
		if (isDragging) {
			gc->drawCircle(x0, y0, getDistance(x0,y0,x1,y1));
			x1 = x;
			y1 = y;
			gc->drawCircle(x0, y0, getDistance(x0,y0,x1,y1));
		}
	}
}

void dynamicdraw::keyDown(GraphicsContext* gc, unsigned int keycode) {
	if (!isDragging) {
		// not allowed to change tools while dragging.
		if (keycode == 'p') {
			drawingMode = DRAWMODE_POINT;
		} else if (keycode == 'l') {
			drawingMode = DRAWMODE_LINE;
		} else if (keycode == 'c') {
			drawingMode = DRAWMODE_CIRCLE;
		}
	}

}





/// "Helper" methods

/**
 * Gets the distance between two 2D points.
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @return distance in pixels.
 */
int getDistance(int x0, int y0, int x1, int y1){

	int x;
	int y;

	if(x0 > x1){
		x = x0 - x1;
	} else {
		x = x1 - x0;
	}

	if(y0 > y1){
		y = y0 - y1;
	} else {
		y = y1 - y0;
	}

	return (sqrt((x*x)+(y*y)));

}
