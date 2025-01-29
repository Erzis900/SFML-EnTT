#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/healthRegen.hpp"
#include "components/renderable.hpp"
#include "config.hpp"
#include "entities/unit.hpp"
#include "features/player/components/cooldown.hpp"
#include "features/player/components/playerControlled.hpp"
#include "pch.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, Config config);
}