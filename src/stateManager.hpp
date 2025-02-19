#pragma once
#include "pch.hpp"

enum State
{
	Game,
	Settings,
	GameOver
};

class StateManager
{
  public:
	StateManager();
	void setState(State state, bool active);
	bool isActive(State state);

  private:
	std::unordered_map<State, bool> states;
};