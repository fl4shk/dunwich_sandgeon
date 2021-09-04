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

#ifndef src_game_engine_comp_status_comp_classes_hpp
#define src_game_engine_comp_status_comp_classes_hpp

// src/game_engine/comp/status_comp_classes.hpp

#include "../../misc_includes.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{
namespace comp
{

static constexpr int STATUS_TIMER_DEFAULT_VAL = 20;

class StatusOnFire final: public ecs::Comp
{
public:		// variables
	int timer = STATUS_TIMER_DEFAULT_VAL;
public:		// functions
	StatusOnFire() = default;
	inline StatusOnFire(int s_timer)
		: timer(s_timer)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusOnFire);
	virtual ~StatusOnFire() = default;

	virtual std::string kind_str() const;
};

// Take damage slowly
class StatusPoisoned final: public ecs::Comp
{
public:		// variables
	int timer = STATUS_TIMER_DEFAULT_VAL;
public:		// functions
	StatusPoisoned() = default;
	inline StatusPoisoned(int s_timer)
		: timer(s_timer)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusPoisoned);
	virtual ~StatusPoisoned() = default;

	virtual std::string kind_str() const;
};

// Can do nothing
class StatusAsleep final: public ecs::Comp
{
public:		// variables
	int timer = STATUS_TIMER_DEFAULT_VAL;
public:		// functions
	StatusAsleep() = default;
	inline StatusAsleep(int s_timer)
		: timer(s_timer)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusAsleep);
	virtual ~StatusAsleep() = default;

	virtual std::string kind_str() const;
};

// Speed of movement
class StatusTravelSpeed final: public ecs::Comp
{
public:		// constants
	static constexpr int ABS_MIN_MAX_VAL = 6;
public:		// variables
	int val = 0;
public:		// functions
	StatusTravelSpeed() = default;
	inline StatusTravelSpeed(int s_val)
		: val(s_val)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusTravelSpeed);
	virtual ~StatusTravelSpeed() = default;

	virtual std::string kind_str() const;
};

// Speed of actions besides movement
class StatusActionSpeed final: public ecs::Comp
{
public:		// constants
	static constexpr int ABS_MIN_MAX_VAL = 6;
public:		// variables
	int val = 0;
public:		// functions
	StatusActionSpeed() = default;
	inline StatusActionSpeed(int s_val)
		: val(s_val)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(StatusActionSpeed);
	virtual ~StatusActionSpeed() = default;

	virtual std::string kind_str() const;
};

} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_comp_status_comp_classes_hpp
