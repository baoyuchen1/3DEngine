#pragma once
#include"../unit/object.h"
#include"../constant/engine_constant.h"
#include"../event/event.h"
namespace myrender
{
	class MouseMoveEvent;
	class ViewPort :public Object
	{
	public:
		static ViewPort* getInsatnce();
		virtual void Release();
		void SetScreenSize(const int&w,const int&h);
		void SetScreenName(const STRING &n);
		void InitViewPort();
		bool WindowShouldClose();
		
		void SwapBuffers();
		void RegistKeyboardCallback(KEYBOARDFUNC func);
		void RegistMouseMoveCallback(MOUSEMOVEFUNC func);
		void RegistMouseScroolCallback(MOUSESCROLLFUNC func);
		void UpdateDeltaTime();
		GLfloat GetDeltaTime();
		int  GetScreenWidth();
		int  GetScreenHeight();
		GLFWwindow* GetWindows();
	private:
		static ViewPort* instance;
		GLFWwindow* _windows;
		VECTOR<KEYBOARDFUNC> _keyboard_funclist;
		VECTOR<MOUSEMOVEFUNC> _mousemove_funclist;
		VECTOR<MOUSESCROLLFUNC> _mousescroll_funclist;
		static void _processInput(GLFWwindow* window, int key, int scancode, int action, int mode);
		static void _framebuffer_size_callback(GLFWwindow* windows, int width, int height);
		static void _mousemove_callback(GLFWwindow* window, double xpos, double ypos);
		static void _mousescroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		ViewPort();
		~ViewPort();
		int _view_width;
		int _view_height;
		STRING _view_name;
		GLfloat _delta_time;
		GLfloat _last_frame;
		static MouseMoveEvent _mousemove_event;
		static MouseScrollEvent _mousescroll_event;
	};
}

