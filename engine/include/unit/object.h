#pragma once
namespace myrender {
	class Object
	{
	public:
		Object();
		~Object();
		virtual void Release() = 0;
	private:

	};

}