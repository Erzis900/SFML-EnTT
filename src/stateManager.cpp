#include "stateManager.hpp"

StateManager::StateManager()
{
	states[State::Game] = true;
	states[State::Settings] = false;
}

void StateManager::setState(State state, bool active) { states[state] = active; }

bool StateManager::isActive(State state)
{
	auto it = states.find(state);
	if (it != states.end())
	{
		return it->second;
	}

	return false;
}
