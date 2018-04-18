/**
 *	LAB WEEK 6: DRAWING EVENTS
 *	CS3210
 *	@author Dennis Droese
 *	@date April 18, 2018
 *  @file dynamicdraw.h
 */
#ifndef DYNAMICDRAW_H_
#define DYNAMICDRAW_H_

#include "drawbase.h"
#include "gcontext.h"
#include "image.h"
#include "shape.h"
#include "matrix.h"

/// Draw modes
#define DRAWMODE_POINT 	0
#define DRAWMODE_LINE 	1
#define DRAWMODE_TRI	2
#define DRAWMODE_POLY	3
#define DRAWMODE_CIRCLE	4

/// Triangle states
#define STATE_NEWTRI 0
#define STATE_ENDTRI 1


class dynamicdraw : public DrawingBase
{
public:

	image* theImage;

	dynamicdraw();
	~dynamicdraw();
	virtual void paint(GraphicsContext* gc);
	virtual void keyDown(GraphicsContext* gc, unsigned int keycode);
	virtual void mouseButtonDown(GraphicsContext* gc,
					unsigned int button, int x, int y);
	virtual void mouseButtonUp(GraphicsContext* gc,
					unsigned int button, int x, int y);
	virtual void mouseMove(GraphicsContext* gc, int x, int y);

private:
	unsigned int drawingMode;
	unsigned int state;
	int x0;
	int y0;
	int x1;
	int y1;
	bool isDragging;
};



#endif /* DYNAMICDRAW_H_ */
