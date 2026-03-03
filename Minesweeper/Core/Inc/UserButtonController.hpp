#ifndef USERBUTTONCONTROLLER_HPP_
#define USERBUTTONCONTROLLER_HPP_

#include <platform/driver/button/ButtonController.hpp>

class UserButtonController : public touchgfx::ButtonController
{
	virtual void init();
	virtual bool sample(uint8_t& key);
	
private:
	uint8_t previousState;
};
#endif
