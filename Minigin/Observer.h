#pragma once
namespace dae
{
	template <typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(unsigned int, T*){}
		virtual void OnDestroy(){}
	};
}