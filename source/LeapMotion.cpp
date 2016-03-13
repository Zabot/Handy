#include "LeapMotion.h"

LeapMotion::LeapMotion(Listener &l) 
	:listener(l)
{
	controller.addListener(listener);
}

LeapMotion::~LeapMotion() {
	controller.removeListener(listener);
}
