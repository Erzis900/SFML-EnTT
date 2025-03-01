#pragma once

#include "pch.hpp"

namespace common
{
	namespace entities
	{
		enum Scope : int
		{
			Flat = 100,
			PercentAdd = 200,
			PercentMult = 300,
			FlatLast = 350,
			Set = 400,
		};

		static std::unordered_map<std::string, Scope> const mapScope = {
			{"flat", Scope::Flat}, {"percent-add", Scope::PercentAdd}, {"percent-mult", Scope::PercentMult},
			{"set", Scope::Set},   {"flat-last", Scope::FlatLast},
		};
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