#pragma once

#include "ODVM/Core/Platform.hpp"

#include <GLFW/glfw3.h>

namespace ODVM
{
	class Windows : public Platform
	{
	private:
		virtual float GetTimeImpl() override { return (float)glfwGetTime(); }

	};
}
