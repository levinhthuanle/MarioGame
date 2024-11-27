#pragma once
#include <iostream>
class GamePlayState
{
private:
	bool isRunning;
	bool isPause;
	bool isOver;
public:
	GamePlayState() {
		isRunning = true;
		isPause = false;
		isOver = false;
	}

	std::string getState() {
		if (isRunning)
			return "Running";
		if (isPause)
			return "Pause";
		return "Over";
	}

	void setState(std::string state) {
		if (state == "Running") {
			isRunning = true;
			isPause = false;
			isOver = false;
		}
		else if (state == "Pause") {
			isRunning = false;
			isPause = true;
			isOver = false;
		}
		else {
			isRunning = false;
			isPause = false;
			isOver = true;
		}
	}
};

