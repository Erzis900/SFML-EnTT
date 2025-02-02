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
			{"Flat", Scope::Flat}, {"PercentAdd", Scope::PercentAdd}, {"PercentMult", Scope::PercentMult}, {"Set", Scope::Set}};
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