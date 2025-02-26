#pragma once

#include "../managers/inputManager.hpp"
#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "features/ability/components/castEvent.hpp"
#include "features/ability/components/pointsAt.hpp"
#include "features/item/components/equipped.hpp"
#include "features/player/components/playerControlled.hpp"

#include "pch.hpp"

namespace features::player::systems
{
	constexpr std::array<std::tuple<sf::Keyboard::Key, features::item::components::SlotType>, 7> keyToSlotType = {
		std::make_tuple(sf::Keyboard::Key::Q, features::item::components::SlotType::Mainhand),
		std::make_tuple(sf::Keyboard::Key::E, features::item::components::SlotType::Offhand),
		std::make_tuple(sf::Keyboard::Key::R, features::item::components::SlotType::Cape),
		std::make_tuple(sf::Keyboard::Key::W, features::item::components::SlotType::NoSlot),  // used to reset movement
		std::make_tuple(sf::Keyboard::Key::S, features::item::components::SlotType::NoSlot),  // used to reset movement
		std::make_tuple(sf::Keyboard::Key::A, features::item::components::SlotType::NoSlot),  // used to reset movement
		std::make_tuple(sf::Keyboard::Key::D, features::item::components::SlotType::NoSlot),  // used to reset movement
	};

	void playerInput(entt::registry &registry, sf::RenderWindow &window, InputManager &inputManager);
}  // namespace features::player::systems