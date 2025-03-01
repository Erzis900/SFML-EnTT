#pragma once

#include "pch.hpp"

#include "components/modifiers.hpp"
#include "entities/attribute.hpp"

#include "../components/equipped.hpp"

namespace features::item
{

	enum class Type : int
	{
		None = 0,
		Sword = 1,
		Club,
		Quiver,
		Shield,
		Scepter,
		Shoulder,
		Head,
		Cape,
		Bow
	};

	struct Item
	{
		std::string name;
		std::vector<common::entities::Modifier> modifiers;
		components::SlotType slot;
		Type type;
		int id;
		int x;
		int y;
		int width;
		int height;
		float dropChance;
	};
	enum class Place : int
	{
		None = 0,
		Ground = 1,
		Target = 2,
	};
	static std::unordered_map<std::string, Place> const mapPlace = {
		{"ground", Place::Ground},
		{"target", Place::Target},
	};

	float getPlace(std::string place);

	enum class Group : int
	{
		None = 0,
		Self = 1,
		Ally = 2,
		Enemy = 3,
	};

	static std::unordered_map<std::string, Group> const mapGroup = {
		{"self", Group::Self},
		{"ally", Group::Ally},
		{"enemy", Group::Enemy},

	};

	float getGroup(std::string group);

	enum class Travel : int
	{
		None = 0,
		Stand = 1,
		Blink = 2,
		Roll = 3,
		Dash = 4,
		Leap = 5
	};

	static std::unordered_map<std::string, Travel> const mapTravel = {
		{"stand", Travel::Stand}, {"blink", Travel::Blink}, {"roll", Travel::Roll}, {"dash", Travel::Dash}, {"leap", Travel::Leap},
	};

	float getTravel(std::string travel);

	enum class Moment : int
	{
		None = 0,
		Active = 1,
		Step = 2,
		Cooldown = 3,
	};

	static std::unordered_map<std::string, Moment> const mapMoment = {
		{"active", Moment::Active},
		{"step", Moment::Step},
		{"cooldown", Moment::Cooldown},
	};

	float getMoment(std::string moment);

	enum class Trigger : int
	{
		None = 0,
		OnAttack = 1,
		OnShot = 2,
		OnCast = 3,
		OnRoll = 4,
		OnDash = 5,
		OnBlink = 6,
		OnHit = 7,
	};
	static std::unordered_map<std::string, Trigger> const mapTrigger = {
		{"on-attack", Trigger::OnAttack}, {"on-shot", Trigger::OnShot},	  {"on-cast", Trigger::OnCast}, {"on-roll", Trigger::OnRoll},
		{"on-dash", Trigger::OnDash},	  {"on-blink", Trigger::OnBlink}, {"on-hit", Trigger::OnHit}};

	float getTrigger(std::string trigger);

	enum class Area : int
	{
		None = 0,
		Point = 1,
		Circle = 2,
		Cone = 3,
		Rectanble = 4,
	};

	static std::unordered_map<std::string, Area> const mapArea = {
		{"point", Area::Point},
		{"circle", Area::Circle},
		{"cone", Area::Cone},
		{"rectangle", Area::Rectanble},
	};

	float getArea(std::string area);

	enum class Kind : int
	{
		None = 0,
		Damage = 1,
		Heal = 2,
		Shield = 3,
		Energy = 4,
	};

	static std::unordered_map<std::string, Kind> const mapKind = {
		{"damage", Kind::Damage},
		{"heal", Kind::Heal},
		{"shield", Kind::Shield},
		{"energy", Kind::Energy},
	};

	float getKind(std::string kind);

	static std::unordered_map<std::string, Type> const mapType = {{"sword", Type::Sword},	{"club", Type::Club},		{"quiver", Type::Quiver},
																  {"shield", Type::Shield}, {"scepter", Type::Scepter}, {"shoulder", Type::Shoulder},
																  {"head", Type::Head},		{"cape", Type::Cape},		{"bow", Type::Bow}};

	static std::unordered_map<std::string, components::SlotType> const mapSlot = {
		{"head", components::SlotType::Head},
		{"chest", components::SlotType::Chest},
		{"main-shoulder", components::SlotType::MainShoulder},
		{"off-shoulder", components::SlotType::OffShoulder},
		{"mainhand", components::SlotType::Mainhand},
		{"offhand", components::SlotType::Offhand},
		{"cape", components::SlotType::Cape},
	};

	Type getType(std::string type);
	components::SlotType getSlot(std::string slot);
	class ItemsLoader
	{
	  public:
		ItemsLoader();
		Item getItem(int id);
		sf::Sprite getSprite(int id);

	  private:
		std::map<int, Item> itemsData = {};
		sf::Texture texture;
	};

}  // namespace features::item