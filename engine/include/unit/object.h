#pragma once
namespace myrender {
	class Object
	{
	public:
		Object();
		~Object();
		Object(const Object&);
		virtual void Release() = 0;
	private:

	};

}