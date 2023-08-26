#ifndef __INPUT_WITH_MOUSE_MANAGER_H__
#define __INPUT_WITH_MOUSE_MANAGER_H__

#include "InputManager.h"

class InputWithMouseManager : public InputManager
{
public:
	static InputWithMouseManager* getInstance();
};

#endif // !__INPUT_WITH_MOUSE_MANAGER_H__
