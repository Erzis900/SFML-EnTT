#include "tileCollider.hpp"
#include "../components/rectCollider.hpp"
#include "components/position.hpp"

namespace features::map::entities
{
	entt::entity createColliderTile(unsigned int id, int x, int y, int tileSize, float scalingFactor, entt::registry &registry)
	{
		auto entity = registry.create();
		registry.emplace<features::map::components::rectCollider>(entity, tileSize * scalingFactor, tileSize * scalingFactor);
		registry.emplace<common::components::position>(entity, (x * tileSize + (tileSize / 2)) * scalingFactor,
													   (y * tileSize + (tileSize / 2)) * scalingFactor);

		return entity;
	}
}  // namespace features::map::entities