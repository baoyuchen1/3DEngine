#include"../../include/event/event.h"
myrender::Event::Event()
{
}
myrender::Event::~Event()
{
}
myrender::Event::Event(const Event &)
{
}
void myrender::Event::Release()
{

}

myrender::KeyBoardEvent::KeyBoardEvent()
{
}

myrender::KeyBoardEvent::~KeyBoardEvent()
{
}

void myrender::KeyBoardEvent::SetKeyCode(const int& key)
{
	_key = key;
}

myrender::MouseMoveEvent::MouseMoveEvent()
{
	_first_mouse = true;
}

myrender::MouseMoveEvent::~MouseMoveEvent()
{
}

myrender::MouseMoveEvent::MouseMoveEvent( MouseMoveEvent &m)
{
	_x_offset = m.GetXOffset();
	_y_offset = m.GetYOffset();
	_constrain_pitch = m.GetConstrainPitch();
	_first_mouse = true;
}

void myrender::MouseMoveEvent::InitEvent(FLOAT x, FLOAT y, BOOL C=true)
{
	if (_first_mouse)
	{
		_x_last = x;
		_y_last = y;
	}
	_x_offset = x - _x_last;
	_y_offset = _y_last - y;
	_x_last = x;
	_y_last = y;
	_constrain_pitch = C;
	_first_mouse = false;
}

FLOAT myrender::MouseMoveEvent::GetXOffset()
{
	return _x_offset;
}

FLOAT myrender::MouseMoveEvent::GetYOffset()
{
	return _y_offset;
}

BOOL myrender::MouseMoveEvent::GetConstrainPitch()
{
	return _constrain_pitch;
}

BOOL myrender::MouseMoveEvent::GetFirstMouse()
{
	return _first_mouse;
}

myrender::MouseScrollEvent::MouseScrollEvent()
{
}

myrender::MouseScrollEvent::~MouseScrollEvent()
{
}


myrender::MouseScrollEvent::MouseScrollEvent(MouseScrollEvent &m)
{
	_zoom = m.GetZoom();
}

FLOAT myrender::MouseScrollEvent::GetZoom()
{
	return _zoom;
}

void myrender::MouseScrollEvent::InitEvent(FLOAT z)
{
	_zoom = z;
}
