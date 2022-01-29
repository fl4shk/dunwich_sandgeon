// This file is part of Dungwich Sandeon.
// 
// Copyright 2022 FL4SHK
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

#ifndef src_game_engine_comp_general_comp_classes_hpp
#define src_game_engine_comp_general_comp_classes_hpp

// src/game_engine/comp/general_comp_classes.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"
#include "../font_color_enum.hpp"
#include "../playfield_layer_prio_enum.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

class Engine;

namespace comp
{

class Drawable final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
public:		// types
	class Data final
	{
	public:		// variables
		#define MEMB_LIST_COMP_DRAWABLE_DATA(X) \
			X(c) \
			X(color_pair) \
			X(gs_color_pair)
		int c = ' ';
		FgBgColorPair
			color_pair = FontColor::White,

			// Grayscale color pair
			gs_color_pair = FontColor::White;
	public:		// functions
		static inline Data from_jv(const Json::Value& jv)
		{
			Data ret;

			MEMB_LIST_COMP_DRAWABLE_DATA(MEMB_FROM_JV_DESERIALIZE);

			return ret;
		}
		operator Json::Value () const;

		inline bool operator == (Data to_cmp) const
		{
			return ((c == to_cmp.c)
				&& (color_pair == to_cmp.color_pair)
				&& (gs_color_pair == to_cmp.gs_color_pair));
		}
		inline bool operator != (Data to_cmp) const
		{
			return (!(*this == to_cmp));
		}
	};
private:		// variables
	#define MEMB_LIST_COMP_DRAWABLE(X) \
		X(_data) \
		X(_non_blink_color_pair) \
		X(_non_blink_gs_color_pair) \
		X(_in_blink)
	Data _data;
	FgBgColorPair
		_non_blink_color_pair = FontColor::White,
		_non_blink_gs_color_pair = FontColor::White;
	bool _in_blink = false;
public:		// functions
	inline Drawable() = default;
	//inline Drawable(int s_c, const FgBgColorPair& s_color)
	//	: data{.c=s_c, .color=s_color}
	//{
	//}
	inline Drawable(Data s_data)
	{
		set_data(s_data);
	}
	Drawable(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Drawable);
	virtual ~Drawable() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;

	void blink()
	{
		if (!_in_blink)
		{
			_data.color_pair.fg = _non_blink_color_pair.bg;
			_data.gs_color_pair.fg = _non_blink_gs_color_pair.bg;
			_in_blink = true;
		}
		else // if (_in_blink)
		{
			_data.color_pair.fg = _non_blink_color_pair.fg;
			_data.gs_color_pair.fg = _non_blink_gs_color_pair.fg;
			_in_blink = false;
		}
	}

	inline Data& set_data(Data n_data)
	{
		_data = n_data;
		_non_blink_color_pair = _data.color_pair;
		_non_blink_gs_color_pair = _data.gs_color_pair;

		return _data;
	}
	GEN_GETTER_BY_CON_REF(data);
};

// Note that this is a 3D position within the game world.
// Which floor the entity is on is what the Z axis represents.
class Position final: public ecs::Comp
{
	friend class dungwich_sandeon::game_engine::Engine;
public:		// constants
	static const std::string KIND_STR;
private:		// variables
	#define MEMB_AUTOSER_LIST_COMP_POSITION(X) \
		X(_ent_id) \
		X(_pos)
	ecs::EntId _ent_id = ecs::ENT_NULL_ID;
	PosVec3 _pos;
public:		// variables
	PlayfieldLayerPrio priority = PlayfieldLayerPrio::Block;
public:		// functions
	Position() = default;
	Position(ecs::EntId s_ent_id, const PosVec3& s_pos,
		PlayfieldLayerPrio s_priority);
	Position(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Position);
	virtual ~Position();

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;

	GEN_GETTER_BY_VAL(ent_id);
	GEN_GETTER_BY_CON_REF(pos);
	void set_pos(const PosVec3& n_pos);
};

//class Weight final: public ecs::Comp
//{
//public:		// constants
//	static const std::string KIND_STR;
//public:		// variables
//	uint val = 0;
//public:		// functions
//	Weight() = default;
//	inline Weight(uint s_val)
//		: val(s_val)
//	{
//	}
//	Weight(const Json::Value& jv);
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Weight);
//	virtual ~Weight() = default;
//
//	virtual std::string kind_str() const;
//	virtual operator Json::Value () const;
//};

// These are stats that increase or stay the same upon level up.
class BaseStats final: public ecs::Comp
{
public:		// constants
	static const std::string KIND_STR;
	static constexpr uint
		MAX_VAL = 999,
		DEFAULT_HP = 50,
		DEFAULT_ATK = 20,
		DEFAULT_DEF = 0,
		DEFAULT_MAG_ATK = 20,
		DEFAULT_MAG_DEF = 0;
public:		// variables
	#define MEMB_LIST_COMP_BASE_STATS(X) \
		X(hp) \
		X(atk) \
		X(def) \
		X(mag_atk) \
		X(mag_def)
	uint
		hp = DEFAULT_HP,
		atk = DEFAULT_ATK,
		def = DEFAULT_DEF,
		mag_atk = DEFAULT_MAG_ATK,
		mag_def = DEFAULT_MAG_DEF;
public:		// functions
	BaseStats() = default;
	inline BaseStats(uint s_hp, uint s_atk, uint s_def, uint s_mag_atk,
		uint s_mag_def)
		: hp(s_hp), atk(s_atk), def(s_def), mag_atk(s_mag_atk),
		mag_def(s_mag_def)
	{
	}
	BaseStats(const Json::Value& jv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(BaseStats);
	virtual ~BaseStats() = default;

	virtual std::string kind_str() const;
	virtual operator Json::Value () const;
};

//class OtherStats final: public ecs::Comp
//{
//public:		// constants
//	static const std::string KIND_STR;
//	static constexpr uint
//		MAX_VAL = 999,
//		DEFAULT_WEIGHT = 40;
//public:		// variables
//	uint
//		weight = DEFAULT_WEIGHT;
//public:		// functions
//	OtherStats
//};



} // namespace comp
} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_comp_general_comp_classes_hpp
