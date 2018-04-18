/**
 *	LAB WEEK 6: DRAWING EVENTS
 *	CS3210
 *	@author Dennis Droese
 *	@date April 18, 2018
 *  @file dynamicdraw.h
 */

#include "dynamicdraw.h"

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

		return;
	} else if(drawingMode == DRAWMODE_POINT){
		theImage->add(new point(x,y,0));

		paint(gc);
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
