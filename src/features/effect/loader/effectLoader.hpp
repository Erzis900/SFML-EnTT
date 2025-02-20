#pragma once

#include "pch.hpp"

namespace features::effect
{
	struct EffectData
	{
		float duration;
		int stacks;
		bool refresh;
	};

	class EffectLoader
	{
	  public:
		EffectLoader(std::string configPath);
		EffectData getEffect(std::string effectName) { return effects[effectName]; };

	  private:
		nlohmann::json data;
		std::unordered_map<std::string, EffectData> effects;
	};
}  // namespace features::effect