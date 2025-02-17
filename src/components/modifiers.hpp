#pragma once

namespace common
{
	namespace entities
	{
		enum Scope : int
		{
			NoneScope = 0,
			Flat = 100,
			PercentAdd = 200,
			PercentMult = 300,
			Set = 400,
		};

		static std::unordered_map<std::string, Scope> const mapScope = {
			{"flat", Scope::Flat}, {"percent-add", Scope::PercentAdd}, {"percent-mult", Scope::PercentMult}, {"set", Scope::Set}};
	}  // namespace entities

	namespace components
	{
		struct modifier
		{
			float value;
			entities::Scope scope;
		};

	}  // namespace components
}  // namespace common