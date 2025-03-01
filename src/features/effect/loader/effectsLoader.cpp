#include "effectsLoader.hpp"

namespace features::effect
{
	EffectsLoader::EffectsLoader()
	{
		for (const auto &entry : std::filesystem::directory_iterator("../../src/content/effects"))
		{
			auto id = static_cast<Effects>(std::stoi(entry.path().filename().replace_extension().string()));
			if (entry.path().extension() == ".json")
			{
				std::ifstream effectFile(entry.path());
				nlohmann::json effectJson = nlohmann::json::parse(effectFile);

				std::vector<common::entities::Modifier> modifiers = {};
				for (auto &modifierJson : effectJson["modifiers"])
				{
					auto attribute = modifierJson["value"];
					auto stat = common::entities::getStat(attribute["attribute"]);
					auto scope = common::entities::getScope(attribute["scope"]);
					auto val = attribute["value"];
					common::entities::Modifier modifier({stat, scope, val});
					modifiers.push_back(modifier);
				}
				Effect effectData = {effectJson["name"],
									 modifiers,
									 effectJson["duration"],
									 effectJson["stacks"],
									 effectJson["refresh"],
									 id,
									 effectJson["sprite"]["x"],
									 effectJson["sprite"]["y"],
									 effectJson["sprite"]["width"],
									 effectJson["sprite"]["height"]};
				effectsData[id] = effectData;
			}
		}
		texture = sf::Texture("../../public/items.png", false, sf::IntRect({0, 0}, {512, 512}));
	}
}  // namespace features::effect