#include "processHitbox.hpp"
#include "../components/hitbox.hpp"
#include "../entities/hitbox.hpp"
#include "components/area.hpp"
#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/position.hpp"
#include "components/relationship.hpp"
#include "components/remove.hpp"
#include "components/unit.hpp"

namespace features::hitbox::systems
{
	void processHitbox(entt::registry &registry)
	{
		auto hitboxView = registry.view<components::hitbox, common::components::faction, common::components::position, common::components::area>();
		auto unitView = registry.view<common::components::unit, common::components::faction, common::components::position, common::components::collider>();

		for (auto [hitboxEntity, hitbox, hitboxFaction, hitboxPos, area] : hitboxView.each())
		{
			if (hitbox.hitCount < 1.f)
			{
				registry.emplace_or_replace<common::components::remove>(hitboxEntity);
				spdlog::info("Hitbox {} removed", static_cast<int>(hitboxEntity));
				continue;
			}
			for (auto [unitEntity, unit, unitFaction, unitPos, coll] : unitView.each())
			{

				if (std::find(hitbox.doneEntities.begin(), hitbox.doneEntities.end(), unitEntity) != hitbox.doneEntities.end())
				{
					continue;
				}
				if (hitbox.hitCount < 1.f)
				{
					spdlog::debug("Hitbox {} removed", static_cast<int>(hitboxEntity));
					registry.emplace_or_replace<common::components::remove>(hitboxEntity);
					break;
				}
				float deltaX = hitboxPos.x - unitPos.x;
				float deltaY = hitboxPos.y - unitPos.y;
				float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

				if (distance < (area.radius + coll.radius) && (unitFaction.affiliation & hitboxFaction.foes).any())
				{
					hitbox.hitCount -= 1;
					spdlog::debug("Hitbox {} collided with unit {}", static_cast<int>(hitboxEntity), static_cast<int>(unitEntity));
					hitbox.entities.push_back(unitEntity);
					registry.replace<components::hitbox>(hitboxEntity, hitbox.hitCount, hitbox.entities, hitbox.doneEntities);
					if (hitbox.hitCount < 1.f)
					{
						spdlog::debug("Hitbox {} removed", static_cast<int>(hitboxEntity));
						registry.emplace_or_replace<common::components::remove>(hitboxEntity);
					}
				}
			}
		}
	}
}  // namespace features::hitbox::systems