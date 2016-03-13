#pragma once
#include "Leap.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include "tutorwidget.h"

using namespace Leap;

class SignListener : public Listener {
public:
	SignListener(tutorwidget &wdg);

	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
	virtual void onDeviceChange(const Controller&);
	virtual void onServiceConnect(const Controller&);
	virtual void onServiceDisconnect(const Controller&);

private:
	bool isInVector(int k, std::vector<int> &v);

private:
	std::vector<int> keysDown;
	tutorwidget &wgt;
};
