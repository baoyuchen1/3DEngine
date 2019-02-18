#pragma once
namespace myrender {
	class Object
	{
	public:
		Object();
		virtual ~Object();
		Object(const Object&);
		virtual void Release() = 0;
	private:

	};

}