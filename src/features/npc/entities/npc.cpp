#include "npc.hpp"
#include "../components/npc.hpp"
#include "components/direction.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/shape.hpp"

namespace features::npc::entities
{
	entt::entity createNPC(entt::registry &registry, sf::Sound &sound)
	{
		auto entity = registry.create();

		sf::CircleShape shape(50.f);
		shape.setOrigin({shape.getRadius(), shape.getRadius()});
		registry.emplace<common::components::shape>(entity, shape);

		registry.emplace<common::components::position>(entity, 800.f, 600.f);
		registry.emplace<common::components::renderable>(entity);
		registry.emplace<common::components::direction>(entity, 0.f, 0.f, false);

		registry.emplace<npc::components::npc>(entity, sound);

		return entity;
	}
}  // namespace features::npc::entities