#include "applyUnitStat.hpp"
#include "components/attribute.hpp"
#include "components/children.hpp"
#include "components/health.hpp"
#include "components/healthRegen.hpp"
#include "components/maxHealth.hpp"
#include "components/speed.hpp"
#include "components/unit.hpp"
#include "entities/attribute.hpp"

namespace common::systems
{
	void applyUnitStat(entt::registry &registry)
	{
		common::systems::applyUnitSpeed(registry);
		common::systems::applyUnitHealth(registry);
	}

	void applyUnitSpeed(entt::registry &registry)
	{
		auto view = registry.view<common::components::unit, common::entities::Attributes, common::components::speed>();

		for (auto [entity, unit, children, speed] : view.each())
		{
			auto &child_speed = registry.get<common::components::attribute>(children.entities[common::entities::Stat::Speed]);
			registry.replace<common::components::speed>(entity, child_speed.value);
		}
	}

	void applyUnitHealth(entt::registry &registry)
	{
		auto view = registry.view<common::components::unit, common::entities::Attributes, common::components::health, common::components::maxHealth>();

		for (auto [entity, unit, children, health, maxHealth] : view.each())
		{
			auto &hp = registry.get<common::components::attribute>(children.entities[common::entities::Stat::Health]);
			auto &maxHp = registry.get<common::components::attribute>(children.entities[common::entities::Stat::MaxHealth]);
			auto &healthRegen = registry.get<common::components::attribute>(children.entities[common::entities::Stat::HealthRegen]);

			auto maxHpDiff = std::clamp(maxHp.value - maxHealth.value, 0.f, maxHp.value);
			auto addedHealth = std::clamp(health.value + maxHpDiff, 0.f, hp.value);
			registry.replace<common::components::health>(entity, addedHealth);
			registry.replace<common::components::maxHealth>(entity, maxHp.value);
			registry.replace<common::components::healthRegen>(entity, healthRegen.value);
		}
	}
}  // namespace common::systems