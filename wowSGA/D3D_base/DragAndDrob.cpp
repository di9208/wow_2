#include "stdafx.h"
#include "DragAndDrob.h"


DragAndDrob::DragAndDrob()
{
}


DragAndDrob::~DragAndDrob()
{
}

void DragAndDrob::Setting(POINT pt,RECT rc)
{
	left = pt.x - rc.left;
	top = pt.y - rc.top;
	right = rc.right - pt.x;
	bottom = rc.bottom - pt.y;

	is_key = true;
}

void DragAndDrob::Update(POINT pt, RECT & RC)
{
	if (is_key)
	{
		SetRect(&RC, pt.x - left, pt.y - top, pt.x + right, pt.y + bottom);
	}
}

void DragAndDrob::reset()
{
	left = top = right = bottom = 0;
	is_key = false;
	Rc = { 0,0,0,0 };
}
