#include <iostream>
#include <string.h>
#include "Leap.h"
#include <math.h>
#include <vector>
#include "SignListener.h"

const std::string fingerNames[] = { "Thumb", "Index", "Middle", "Ring", "Pinky" };
const std::string boneNames[] = { "Metacarpal", "Proximal", "Middle", "Distal" };

using namespace Leap;
using namespace std;

SignListener::SignListener(tutorwidget &wgt)
:wgt(wgt)
{
}

void SignListener::onInit(const Controller& controller) {
	std::cout << "Initialized" << std::endl;
}

void SignListener::onConnect(const Controller& controller) {
	std::cout << "Connected" << std::endl;
	//controller.enableGesture(Gesture::TYPE_CIRCLE);
	//controller.enableGesture(Gesture::TYPE_KEY_TAP);
	//controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	//controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SignListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
	std::cout << "Disconnected" << std::endl;
}

void SignListener::onExit(const Controller& controller) {
	std::cout << "Exited" << std::endl;
}

void SignListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();

	HandList hands = frame.hands();
	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		const Hand hand = *hl;
		const FingerList fingers = hand.fingers();
		std::vector<int> keysThisFrame;
		unsigned int extendedFingers = 0;
		Finger fingersOnHand[5];

		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {	
			const Finger finger = *fl;
			fingersOnHand[finger.type()]=finger;
			if (finger.isExtended()) {
				extendedFingers++;
			}
		}
		if (extendedFingers == 5) wgt.setLetter("-");
		else if (fingersOnHand[3].isExtended()) {
			if (fingersOnHand[1].isExtended()) {
				if (fingersOnHand[4].isExtended()) wgt.setLetter("B");
				else wgt.setLetter("W");
			}
			else wgt.setLetter("F");
		}
		else if(fingersOnHand[4].isExtended()) {
			if (fingersOnHand[0].isExtended()) wgt.setLetter("Y");
				else if (fingersOnHand[4].tipVelocity().magnitude() < 125) wgt.setLetter("I");
				else wgt.setLetter("J");
		}
		else if (fingersOnHand[0].isExtended()) {
			if (fingersOnHand[1].isExtended()) wgt.setLetter("L");
			else wgt.setLetter("A");
		}
		else if (fingersOnHand[2].isExtended()) {
			if (fingersOnHand[1].tipPosition().distanceTo(fingersOnHand[2].tipPosition()) < fingersOnHand[1].bone(Bone::TYPE_DISTAL).length()*2) {
				if (abs(fingersOnHand[1].direction().normalized().dot(Vector::left()))>.75) wgt.setLetter("H"); 
				else if (fingersOnHand[1].direction().cross(fingersOnHand[2].direction()).magnitude() < .2) wgt.setLetter("U");
					else wgt.setLetter("R");
			}	
			else if (fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[3].tipPosition()) < fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[1].bone(Bone::TYPE_PROXIMAL).prevJoint()))
					wgt.setLetter("V");
				else wgt.setLetter("K");
			}
		else if (fingersOnHand[1].isExtended()) {
			if (fingersOnHand[1].direction().normalized().cross(fingersOnHand[2].direction().normalized()).magnitude()>.8) wgt.setLetter("P");
			else {
				const Vector direction = fingersOnHand[1].direction();
				if (abs(direction.z) > abs(direction.x)) {
					if (direction.z < 0) {
						if (fingersOnHand[4].tipVelocity().magnitude() < 125) wgt.setLetter("D");
						else wgt.setLetter("Z");
					}
					else wgt.setLetter("Q");
				}
				else if (direction.x < 0) wgt.setLetter("G");
			}
		}
		else //////////////MMMMM NNNNNNN TTTTTTT
		{			
		    const float angle1= fingersOnHand[2].bone(Bone::TYPE_DISTAL).direction().angleTo(fingersOnHand[2].bone(Bone::TYPE_INTERMEDIATE).direction());
			const float angle2= fingersOnHand[2].bone(Bone::TYPE_INTERMEDIATE).direction().angleTo(fingersOnHand[2].bone(Bone::TYPE_PROXIMAL).direction());
			if (abs(angle1 - 1.4) < .2&& abs(angle2 - 1.4) < .2) wgt.setLetter("E");
			else
			{
				const float angle3 = fingersOnHand[1].bone(Bone::TYPE_DISTAL).direction().angleTo(fingersOnHand[1].bone(Bone::TYPE_INTERMEDIATE).direction());
				const float angle4 = fingersOnHand[1].bone(Bone::TYPE_INTERMEDIATE).direction().angleTo(fingersOnHand[1].bone(Bone::TYPE_PROXIMAL).direction());
				if (abs(angle3 - .7) < .2&& abs(angle4 - 1.0) < .2) wgt.setLetter("X");
				else if (fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[2].bone(Bone::TYPE_DISTAL).prevJoint()) < fingersOnHand[2].bone(Bone::TYPE_DISTAL).length()) wgt.setLetter("S");
				else if (fingersOnHand[0].tipPosition().distanceTo(fingersOnHand[1].tipPosition()) < 30) wgt.setLetter("O");
				else if (abs(angle1 - .8) < .4&& abs(angle2 - 1.2) < .3) wgt.setLetter("C");
			}
			


		}
	}
}

void SignListener::onFocusGained(const Controller& controller) {
	std::cout << "Focus Gained" << std::endl;
}

void SignListener::onFocusLost(const Controller& controller) {
	std::cout << "Focus Lost" << std::endl;
}

void SignListener::onDeviceChange(const Controller& controller) {
	std::cout << "Device Changed" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "id: " << devices[i].toString() << std::endl;
		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

void SignListener::onServiceConnect(const Controller& controller) {
	std::cout << "Service Connected" << std::endl;
}

void SignListener::onServiceDisconnect(const Controller& controller) {
	std::cout << "Service Disconnected" << std::endl;
}
