#include"../../include/render/viewport.h"
myrender::ViewPort* myrender::ViewPort::instance = nullptr;
myrender::MouseMoveEvent myrender::ViewPort::_mousemove_event = MouseMoveEvent();
myrender::MouseScrollEvent myrender::ViewPort::_mousescroll_event = MouseScrollEvent();
myrender::ViewPort * myrender::ViewPort::getInsatnce()
{
	if (instance == nullptr)
		instance = new ViewPort();
	return instance;
}
void myrender::ViewPort::Release()
{
	delete instance;
}
void myrender::ViewPort::SetScreenSize(const int & w, const int & h)
{
	_view_width = w;
	_view_height = h;
}
void myrender::ViewPort::SetScreenName(const STRING & n)
{
	_view_name = n;
}
void myrender::ViewPort::InitViewPort()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	_windows = glfwCreateWindow(_view_width, _view_height, _view_name.c_str(), NULL, NULL);
	if (_windows == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(_windows);
	glfwSetFramebufferSizeCallback(_windows, ViewPort::_framebuffer_size_callback);
	glfwSetKeyCallback(_windows, ViewPort::_processInput);
	glfwSetScrollCallback(_windows, ViewPort::_mousescroll_callback);
	glfwSetCursorPosCallback(_windows, ViewPort::_mousemove_callback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	// Define the viewport dimensions
	glViewport(0, 0, _view_width, _view_height);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);
	_last_frame = glfwGetTime();
}
bool myrender::ViewPort::WindowShouldClose()
{
	return glfwWindowShouldClose(_windows);
}
void myrender::ViewPort::_processInput(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	auto viewport = ViewPort::getInsatnce();
	for (auto&it: viewport->_keyboard_funclist)
	{
		it(key);
	}
}
void myrender::ViewPort::SwapBuffers()
{
	glfwSwapBuffers(_windows);
}
void myrender::ViewPort::RegistKeyboardCallback(KEYBOARDFUNC func)
{
	_keyboard_funclist.push_back(func);
}
void myrender::ViewPort::RegistMouseMoveCallback(MOUSEMOVEFUNC func)
{
	_mousemove_funclist.push_back(func);
}
void myrender::ViewPort::RegistMouseScroolCallback(MOUSESCROLLFUNC func)
{
	_mousescroll_funclist.push_back(func);
}
void myrender::ViewPort::UpdateDeltaTime()
{
	GLfloat currentFrame = glfwGetTime();
	_delta_time = currentFrame - _last_frame;
	_last_frame = currentFrame;
}
GLfloat myrender::ViewPort::GetDeltaTime()
{
	return _delta_time;
}
int myrender::ViewPort::GetScreenWidth()
{
	return _view_width;
}
int myrender::ViewPort::GetScreenHeight()
{
	return _view_height;
}
void myrender::ViewPort::_framebuffer_size_callback(GLFWwindow * windows, int width, int height)
{
	 
}
void myrender::ViewPort::_mousemove_callback(GLFWwindow * window, double xpos, double ypos)
{
	ViewPort::_mousemove_event.InitEvent(xpos, ypos,true);
	auto viewport = ViewPort::getInsatnce();
	for (auto&it : viewport->_mousemove_funclist)
	{
		it(ViewPort::_mousemove_event);
	}
}
void myrender::ViewPort::_mousescroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{  
	ViewPort::_mousescroll_event.InitEvent(yoffset);
	auto viewport = ViewPort::getInsatnce();
	for (auto&it : viewport->_mousescroll_funclist)
	{
		it(ViewPort::_mousescroll_event);
	}
}
myrender::ViewPort::ViewPort()
{
	_view_width = 960;
	_view_height = 720;
	_view_name = "test";
	_mousemove_event = MouseMoveEvent(); 
}

myrender::ViewPort::~ViewPort()
{
}
