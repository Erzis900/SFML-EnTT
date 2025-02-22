#pragma once

#include "pch.hpp"

namespace features::effect
{
	enum Type : int
	{
		NoEffect = 0,
		Bleed = 1,
		Fortify = 2
	};

	struct Effect
	{
		float duration;
		int stacks;
		bool refresh;
	};

	const std::unordered_map<std::string, Type> mapType = {{"bleed", Type::Bleed}, {"fortify", Type::Fortify}};

	class EffectLoader
	{
	  public:
		EffectLoader(std::string configPath);
		Type getType(std::string effect);
		Effect getEffect(Type type) { return effects[type]; }

	  private:
		nlohmann::json data;
		std::unordered_map<Type, Effect> effects;
	};
}  // namespace features::effect