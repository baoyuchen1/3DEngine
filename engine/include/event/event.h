#pragma once
#include"eventhandle.h"
#include"../constant/engine_constant.h"
namespace myrender
{
	class Event :public Object
	{
	public:
		Event();
		~Event();
		Event(const Event&);
		virtual void Release();
	};
	class KeyBoardEvent
	{
	public:

		KeyBoardEvent();
		~KeyBoardEvent();
		void SetKeyCode(const int&);
	private:
		int _key;
	};
	class MouseMoveEvent:public Event
	{
	public:
		MouseMoveEvent();
		~MouseMoveEvent();
		MouseMoveEvent( MouseMoveEvent&);
		void InitEvent(FLOAT x, FLOAT y, BOOL C);
		FLOAT GetXOffset();
		FLOAT GetYOffset();
		BOOL  GetConstrainPitch();
		BOOL  GetFirstMouse();
	private:
		FLOAT _x_offset;
		FLOAT _y_offset;
		FLOAT _x_last;
		FLOAT _y_last;
		BOOL  _constrain_pitch;
		BOOL  _first_mouse;
	};
	class MouseScrollEvent :public Event
	{
	public:
		MouseScrollEvent();
		~MouseScrollEvent();
		MouseScrollEvent(MouseScrollEvent&);
		FLOAT GetZoom();
		void InitEvent(FLOAT z);
	public:
		FLOAT _zoom;
	};
}