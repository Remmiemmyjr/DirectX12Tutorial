#include "pch.h"
#include "Utilities.h"


namespace Engine {
	namespace Utils {

		UINT Engine::Utils::CalculateConstantBufferAlignment(const UINT allocation)
		{
			return (allocation + 255) & ~255;
		}

	}
}
