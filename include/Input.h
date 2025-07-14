#pragma once

#include <wtypesbase.h>
class Input {
	public:
		void update();
		bool keyDown(int vkCode) const;

	private:
		SHORT keyStates[256] = {};
};

