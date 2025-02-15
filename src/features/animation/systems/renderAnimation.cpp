#include "renderAnimation.hpp"
#include "../components/color.hpp"
#include "../components/timer.hpp"
#include "area.hpp"
#include "components/position.hpp"
#include "features/hitbox/components/hitbox.hpp"

namespace features::animation::renderers
{
	void renderAnimations(entt::registry &registry, sf::RenderWindow &window, features::animation::AnimationLoader &animationLoader)
	{
		auto view =
			registry
				.view<features::animation::components::timer, common::components::position, features::animation::components::Color, common::components::area>();

		for (auto [entity, timer, position, color, area] : view.each())
		{
			float time = timer.value / animationLoader.getTotalTime();
			sf::Sprite sprite = animationLoader.getSprite(time, color);

			sprite.setPosition({position.x, position.y});

			float scalingFactor = (area.radius / (animationLoader.getFrameSize() / 2)) * 1.5f;
			sprite.setScale({scalingFactor, scalingFactor});

			window.draw(sprite);
		}
	}
}  // namespace features::animation::renderers