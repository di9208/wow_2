#pragma once
class DragAndDrob
{
private:
	float left, top, right, bottom;
	SYNTHESIZE(bool, is_key,key);
	RECT Rc;
public:
	DragAndDrob();
	~DragAndDrob();

	void Setting(POINT pt, RECT rc);
	void Update(POINT pt,RECT & RC);
	void reset();
};

