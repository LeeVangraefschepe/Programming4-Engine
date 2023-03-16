#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath, int width = 640, int height = 480);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}