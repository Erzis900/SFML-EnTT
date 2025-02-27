#include "inputManager.hpp"

namespace features::player
{
	InputManager::InputManager() {}

	bool InputManager::isKeyPressed(sf::Keyboard::Key key)
	{
		return (CurrentKeyState[static_cast<std::size_t>(key)] && !PreviousKeyState[static_cast<std::size_t>(key)]);
	}

	bool InputManager::isKeyReleased(sf::Keyboard::Key key)
	{
		return (!CurrentKeyState[static_cast<std::size_t>(key)] && PreviousKeyState[static_cast<std::size_t>(key)]);
	}

	bool InputManager::isKeyHeld(sf::Keyboard::Key key)
	{
		return (CurrentKeyState[static_cast<std::size_t>(key)] && PreviousKeyState[static_cast<std::size_t>(key)]);
	}

	bool InputManager::isButtonPressed(sf::Mouse::Button button)
	{
		return (CurrentButtonState[static_cast<std::size_t>(button)] && !PreviousButtonState[static_cast<std::size_t>(button)]);
	}

	bool InputManager::isButtonReleased(sf::Mouse::Button button)
	{
		return (!CurrentButtonState[static_cast<std::size_t>(button)] && PreviousButtonState[static_cast<std::size_t>(button)]);
	}

	bool InputManager::isButtonHeld(sf::Mouse::Button button)
	{
		return (CurrentButtonState[static_cast<std::size_t>(button)] && PreviousButtonState[static_cast<std::size_t>(button)]);
	}

	void InputManager::processEvents(sf::RenderWindow &window)
	{
		// Save the state of each keyboard key (must be done before any Key* function is executed)
		for (unsigned int i = 0; i < sf::Keyboard::KeyCount; ++i)
		{
			// Save the keyboard's state from the previous frame
			PreviousKeyState[i] = CurrentKeyState[i];

			// And save the keyboard's state in the current frame
			CurrentKeyState[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
		}

		for (unsigned int j = 0; j < sf::Mouse::ButtonCount; ++j)
		{
			PreviousButtonState[j] = CurrentButtonState[j];
			CurrentButtonState[j] = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(j));
		}

		// if (isKeyPressed(sf::Keyboard::Key::Q))
		// 	printf("Key Q has been pressed\n");
		// else if (isKeyHeld(sf::Keyboard::Key::Q))
		// 	printf("Key Q is held\n");
		// else if (isKeyReleased(sf::Keyboard::Key::Q))
		// 	printf("Key Q has been released\n");
	}
}  // namespace features::player