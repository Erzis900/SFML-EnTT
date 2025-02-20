#include "effectLoader.hpp"

namespace features::effect
{
	EffectLoader::EffectLoader(std::string configPath)
	{
		std::ifstream effectsFile(configPath);
		if (!effectsFile.is_open())
		{
			spdlog::error("Failed to load {}", configPath);
			std::exit(EXIT_FAILURE);
		}
		spdlog::info("Loaded {}", configPath);

		try
		{
			data = nlohmann::json::parse(effectsFile);
			spdlog::info("Parsed {}", configPath);
		}
		catch (const nlohmann::json::parse_error &e)
		{
			spdlog::error("Failed to parse {}. Error: {}", configPath, e.what());
			std::exit(EXIT_FAILURE);
		}

		for (auto &[effectName, effectData] : data.items())
		{
			EffectData effect;
			effect.duration = effectData["duration"];
			effect.stacks = effectData["stacks"];
			effect.refresh = effectData["refresh"];

			effects[effectName] = effect;
		}
	}
}  // namespace features::effect