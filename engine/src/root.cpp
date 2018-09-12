#include"../include/root.h"
using namespace myrender;
Root* Root::instance = nullptr;
Root* Root::getInstance()
{
	if (instance == nullptr)
		instance = new Root();
	return instance;
}

Render* myrender::Root::getRender()
{
	return Render::getInstance();
}
Image* myrender::Root::getImage()
{
	return Image::getInstance();
}
Root::Root()
{

}