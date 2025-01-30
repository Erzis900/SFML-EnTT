#include "components/cooldown.hpp"
#include "components/lookDirection.hpp"
#include "features/hitbox/entities/hitbox.hpp"
#include "pch.hpp"

#include "../components/initialCooldown.hpp"
#include "../components/playerControlled.hpp"

namespace features::player::systems
{
	void playerShoot(entt::registry &registry);
}