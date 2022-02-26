// This file is part of Dunwich Sandgeon.
// 
// Copyright 2022 FL4SHK
//
// Dunwich Sandgeon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// Dunwich Sandgeon is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along
// with Dunwich Sandgeon.  If not, see <https://www.gnu.org/licenses/>.

#ifndef src_game_engine_comp_status_comp_classes_hpp
#define src_game_engine_comp_status_comp_classes_hpp

// src/game_engine/comp/status_comp_classes.hpp

#include "../../misc_includes.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace comp
{

static constexpr int STATUS_TIMER_DEFAULT_VAL = 20;

class StatusOnFire final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_COMP_STATUS_ON_FIRE(X) \
		X(timer, 0)
	int timer = STATUS_TIMER_DEFAULT_VAL;
public:		// functions
	StatusOnFire() = default;
	inline StatusOnFire(int s_timer)
		: timer(s_timer)
	{
	}
	StatusOnFire(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusOnFire);
	virtual ~StatusOnFire() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

// Take damage slowly
class StatusPoisoned final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_COMP_STATUS_POISONED(X) \
		X(timer, 0)
	int timer = STATUS_TIMER_DEFAULT_VAL;
public:		// functions
	StatusPoisoned() = default;
	inline StatusPoisoned(int s_timer)
		: timer(s_timer)
	{
	}
	StatusPoisoned(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusPoisoned);
	virtual ~StatusPoisoned() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

// Can do nothing
class StatusAsleep final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
public:		// variables
	#define MEMB_LIST_COMP_STATUS_ASLEEP(X) \
		X(timer, 0)
	int timer = STATUS_TIMER_DEFAULT_VAL;
public:		// functions
	StatusAsleep() = default;
	inline StatusAsleep(int s_timer)
		: timer(s_timer)
	{
	}
	StatusAsleep(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusAsleep);
	virtual ~StatusAsleep() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

// Speed of movement
class StatusTravelSpeed final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
	static constexpr int ABS_MIN_MAX_VAL = 6;
public:		// variables
	#define MEMB_LIST_COMP_STATUS_TRAVEL_SPEED(X) \
		X(timer, 0) \
		X(val, 0)
	int
		timer = STATUS_TIMER_DEFAULT_VAL,
		val = 0;
public:		// functions
	StatusTravelSpeed() = default;
	inline StatusTravelSpeed(int s_timer, int s_val)
		: timer(s_timer), val(s_val)
	{
	}
	StatusTravelSpeed(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusTravelSpeed);
	virtual ~StatusTravelSpeed() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

// Speed of actions besides movement
class StatusActionSpeed final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
	static constexpr int ABS_MIN_MAX_VAL = 6;
public:		// variables
	#define MEMB_LIST_COMP_STATUS_ACTION_SPEED(X) \
		X(timer, 0) \
		X(val, 0)
	int
		timer = STATUS_TIMER_DEFAULT_VAL,
		val = 0;
public:		// functions
	StatusActionSpeed() = default;
	inline StatusActionSpeed(int s_timer, int s_val)
		: timer(s_timer), val(s_val)
	{
	}
	StatusActionSpeed(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusActionSpeed);
	virtual ~StatusActionSpeed() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_status_comp_classes_hpp
