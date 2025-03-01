#include "renderAnimation.hpp"
#include "../components/color.hpp"
#include "area.hpp"
#include "components/lifespan.hpp"
#include "components/position.hpp"
#include "features/hitbox/components/hitbox.hpp"

namespace features::animation::renderers
{
	void renderAnimations(entt::registry &registry, sf::RenderWindow &window, AnimationLoader &animationLoader)
	{
		auto view = registry.view<common::components::lifespan, common::components::position, components::Color, common::components::area>();

		for (auto [entity, lifespan, position, color, area] : view.each())
		{
			float time = lifespan.time / lifespan.totalTime;
			sf::Sprite sprite = animationLoader.getSprite(time, color);

			sprite.setPosition({position.x, position.y});

			float scalingFactor = (area.radius / (animationLoader.getFrameSize() / 2)) * 1.5f;
			sprite.setScale({scalingFactor, scalingFactor});

			window.draw(sprite);
		}
	}
}  // namespace features::animation::renderers