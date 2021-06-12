// This file is part of Dungwich Sandeon.
// 
// Dungwich Sandeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dungwich Sandeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dungwich Sandeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_game_engine_entity_etc_classes_hpp
#define src_game_engine_entity_etc_classes_hpp

// src/game_engine/entity_etc_classes.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"

namespace dungwich_sandeon
{

namespace game_engine
{
//--------
class Window;
class System;
class Entity;
class Engine;

using EntityId = i64;
static constexpr EntityId ENTITY_NULL_ID = static_cast<EntityId>(-1);

using EntityIdVec2d = std::vector<std::vector<EntityId>>;
using EntityIdMap = std::map<std::string, EntityIdVec2d>;
using EntityIdMapFullIndex = std::pair<std::string, PosVec2>;

using ComponentUptr = std::unique_ptr<Component>;
using EntityComponentMap = std::map<std::string, ComponentUptr>;
using EntityComponentMapUptr = std::unique_ptr<EntityComponentMap>;
using EngineComponentMap = std::map<EntityId, EntityComponentMapUptr>;

using SystemUptr = std::unique_ptr<System>;
using SystemMap = std::map<std::string, SystemUptr>;
//--------
class Entity final
{
	friend class Window;
private:		// variables
	Engine* _engine = nullptr;
	EntityId _id = ENTITY_NULL_ID;
public:		// functions
	inline Entity(Engine* s_engine=nullptr, EntityId s_id=ENTITY_NULL_ID)
		: _engine(s_engine), _id(s_id)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Entity);
	~Entity() = default;

	void destroy() const;

	bool insert_comp(const std::string& key, ComponentUptr&& comp) const;
	bool insert_or_replace_comp(const std::string& key,
		ComponentUptr&& comp) const;
	size_t erase_comp(const std::string& key) const;

	EntityComponentMap& comp_map() const;
	const EntityComponentMap& comp_map() const;

	GEN_GETTER_AND_SETTER_BY_VAL(id);
	GEN_GETTER_AND_SETTER_BY_VAL(engine);
};
//--------
class Component
{
public:		// functions
	Component() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Component);
	virtual ~Component() = default;

	inline std::string kind_str(size_t index) const
	{
		return sconcat(base_kind_str(), index);
	}
	inline std::string kind_str(const std::string& elem="") const
	{
		return sconcat(base_kind_str(), elem);
	}
	// This is used as the base key for individual `EntityComponentMap`
	// elements of an `Entity`.
	virtual std::string base_kind_str() const;
};
//--------
class System
{
public:		// functions
	System() = default;
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(System);
	virtual ~System() = default;

	virtual void tick(const std::vector<Entity>& vec);
};
//--------
} // namespace game_engine

} // namespace dungwich_sandeon

#endif		// src_game_engine_entity_etc_classes_hpp
