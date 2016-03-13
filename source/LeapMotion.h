#ifndef LEAP_MOTION_H
#define LEAP_MOTION_H

#include <iostream>
#include <string>

#include <Leap.h>

using namespace Leap;
using namespace std;

class LeapMotion {

	public:
		LeapMotion(Listener &l);
		~LeapMotion();


	private:
		Listener &listener;
		Controller controller;
};

#endif
