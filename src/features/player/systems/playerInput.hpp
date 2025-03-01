#pragma once

#include "../managers/inputManager.hpp"
#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/pointsAt.hpp"
#include "components/position.hpp"
#include "features/ability/components/castEvent.hpp"
#include "features/ability/entities/event.hpp"
#include "features/item/components/equipped.hpp"
#include "features/player/components/playerControlled.hpp"

#include "pch.hpp"

namespace features::player::systems
{
	constexpr std::array<std::tuple<sf::Keyboard::Key, item::components::SlotType>, 7> keyToSlotType = {
		std::make_tuple(sf::Keyboard::Key::Q, item::components::SlotType::Mainhand),
		std::make_tuple(sf::Keyboard::Key::E, item::components::SlotType::Offhand),
		std::make_tuple(sf::Keyboard::Key::R, item::components::SlotType::Cape),
		std::make_tuple(sf::Keyboard::Key::W, item::components::SlotType::NoSlot),	// used to reset movement
		std::make_tuple(sf::Keyboard::Key::S, item::components::SlotType::NoSlot),	// used to reset movement
		std::make_tuple(sf::Keyboard::Key::A, item::components::SlotType::NoSlot),	// used to reset movement
		std::make_tuple(sf::Keyboard::Key::D, item::components::SlotType::NoSlot),	// used to reset movement
	};

	void playerInput(entt::registry &registry, sf::RenderWindow &window, InputManager &inputManager);
}  // namespace features::player::systems