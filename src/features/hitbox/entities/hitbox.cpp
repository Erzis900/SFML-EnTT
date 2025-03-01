#include "hitbox.hpp"
#include "features/animation/entities/animation.hpp"

namespace features::hitbox::entities
{
	entt::entity createHitbox(entt::registry &registry, entt::entity source)
	{
		auto hitboxEntity = registry.create();
		auto ability = registry.get<ability::components::ability>(source);

		if (registry.valid(ability.source))	 // TODO: consider rewriting this check to avoid creating hitbox entity
		{
			auto attributes = registry.get<common::entities::Attributes>(source);

			float radius = 0.f;
			auto &trigger = registry.get<common::components::attribute>(attributes.entities[common::entities::Stat::Trigger]);

			float lifeSpan = 0.f;

			switch (static_cast<item::Trigger>(trigger.value))
			{
			case item::Trigger::OnHit:
			case item::Trigger::OnAttack:
				registry.emplace<common::components::attach>(hitboxEntity, ability.source);
				lifeSpan = 0.3f;
				registry.emplace<components::hitbox>(hitboxEntity, INFINITY, std::vector<entt::entity>(), std::vector<entt::entity>());
				radius = 150.f;
				break;
			case item::Trigger::OnShot:
			case item::Trigger::OnCast:
				registry.emplace<common::components::speed>(hitboxEntity, 500.f);
				lifeSpan = 0.7f;
				registry.emplace<components::hitbox>(hitboxEntity, 2.f, std::vector<entt::entity>(), std::vector<entt::entity>());
				radius = 50.f;
				break;
			default:
				spdlog::warn("Incorrect state for entity {}, probably item has incorrect trigger or wrong item assigned", static_cast<int>(source));
				break;
			}
			registry.emplace<common::components::lifespan>(hitboxEntity, lifeSpan, lifeSpan);
			registry.emplace<common::components::source>(hitboxEntity, ability.source);

			auto pos = registry.get<common::components::position>(ability.source);
			auto lookDir = registry.get<common::components::lookDirection>(ability.source);
			registry.emplace<common::components::direction>(hitboxEntity, lookDir.x, lookDir.y, true);
			registry.emplace<common::components::position>(hitboxEntity, pos.x, pos.y);
			registry.emplace<common::components::damage>(hitboxEntity, 10.f);
			auto faction = registry.get<common::components::faction>(ability.source);
			registry.emplace<common::components::faction>(hitboxEntity, faction.affiliation, faction.allies, faction.foes);

			sf::CircleShape hitboxShape(radius);
			hitboxShape.setFillColor(sf::Color::White);
			hitboxShape.setOrigin({hitboxShape.getRadius(), hitboxShape.getRadius()});

			registry.emplace<common::components::renderable>(hitboxEntity);
			registry.emplace<common::components::shape>(hitboxEntity, hitboxShape);
			registry.emplace<common::components::area>(hitboxEntity, radius);

			entt::entity animation = animation::entities::createAnimation(registry, hitboxEntity, radius, lifeSpan);
			spdlog::debug("Animation entity created, ID {}", static_cast<int>(animation));
		}

		return hitboxEntity;
	}
}  // namespace features::hitbox::entities
