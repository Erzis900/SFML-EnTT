#pragma once
#include "pch.hpp"

namespace features::player
{
	class InputManager
	{
	  public:
		InputManager();
		// See function bodies below
		void processEvents(sf::RenderWindow &window);
		bool isKeyPressed(sf::Keyboard::Key Key);
		bool isKeyReleased(sf::Keyboard::Key Key);
		bool isKeyHeld(sf::Keyboard::Key Key);

		bool isButtonPressed(sf::Mouse::Button Button);
		bool isButtonReleased(sf::Mouse::Button Button);
		bool isButtonHeld(sf::Mouse::Button Button);

	  private:
		// The keyboard's state in the current- and the previous frame
		std::array<bool, sf::Keyboard::KeyCount> CurrentKeyState;
		std::array<bool, sf::Keyboard::KeyCount> PreviousKeyState;

		std::array<bool, sf::Mouse::ButtonCount> CurrentButtonState;
		std::array<bool, sf::Mouse::ButtonCount> PreviousButtonState;
	};
}  // namespace features::player
