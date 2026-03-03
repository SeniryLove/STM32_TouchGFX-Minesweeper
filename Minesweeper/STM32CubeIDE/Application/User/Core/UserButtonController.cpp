#include <UserButtonController.hpp>
#include <main.h>
#include <touchgfx/hal/HAL.hpp>

extern "C" {
	extern uint8_t User_ButtonState;
}

void UserButtonController::init() {

};

bool UserButtonController::sample(uint8_t &key) {
	if (User_ButtonState) {
		User_ButtonState = 0x00;
		key = 0;
		return true;
	}
	return false;
}
