#pragma once
#include "pch.hpp"

enum class State
{
	Game = true,
	Settings = false
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