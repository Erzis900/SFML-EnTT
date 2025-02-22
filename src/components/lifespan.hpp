#pragma once

namespace common::components
{
	/**
	 * @brief Lifespan component
	 * @brief
	 * This component is used to determine the lifespan of an entity.
	 * The entity will be marked as removed when the time reaches 0.
	 *
	 * @param time Current time
	 * @param totalTime Total time
	 *
	 *
	 * @note
	 * This component is used in the following systems:
	 * - common::systems::processLifespan
	 *
	 */
	struct lifespan
	{
		float time;
		float totalTime;
	};
}  // namespace common::components
