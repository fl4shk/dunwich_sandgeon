// This file is part of Dunwich Sandgeon.
// 
// Copyright 2023 FL4SHK
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

#ifndef src_game_engine_comp_general_comp_classes_hpp
#define src_game_engine_comp_general_comp_classes_hpp

// src/game_engine/comp/general_comp_classes.hpp

#include "../../misc_includes.hpp"
#include "../../misc_types.hpp"
#include "../font_color_enum.hpp"
#include "../pfield_layer_prio_enum.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
class Engine;

namespace comp {
//--------
class Drawable final: public ecs::Comp {
public:		// constants
	static const std::string KIND_STR;
public:		// types
	class Data final {
	public:		// variables
		#define MEMB_LIST_COMP_DRAWABLE_DATA(X) \
			X(c, std::nullopt) \
			X(color_pair, std::nullopt) \
			X(gs_color_pair, std::nullopt)
		i32 c = ' ';
		FgBgColorPair
			color_pair = FontColor::White,

			// Grayscale color pair
			gs_color_pair = FontColor::White;
	public:		// functions
		static Data from_bv(const binser::Value& bv);
		operator binser::Value () const;

		//inline bool operator == (Data to_cmp) const {
		//	return ((c == to_cmp.c)
		//		&& (color_pair == to_cmp.color_pair)
		//		&& (gs_color_pair == to_cmp.gs_color_pair));
		//}
		//inline bool operator != (Data to_cmp) const {
		//	return (!(*this == to_cmp));
		//}
		inline auto operator <=> (const Data& to_cmp) const = default;
	};
private:		// variables
	#define MEMB_LIST_COMP_DRAWABLE(X) \
		X(_data, std::nullopt) \
		X(_non_blink_color_pair, std::nullopt) \
		X(_non_blink_gs_color_pair, std::nullopt) \
		X(_in_blink, std::nullopt)
	Data _data;
	FgBgColorPair
		_non_blink_color_pair = FontColor::White,
		_non_blink_gs_color_pair = FontColor::White;
	bool _in_blink = false;
public:		// functions
	inline Drawable() = default;
	//inline Drawable(i32 s_c, const FgBgColorPair& s_color)
	//	: data{.c=s_c, .color=s_color} {
	//}
	inline Drawable(Data s_data) {
		set_data(s_data);
	}
	Drawable(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Drawable);
	virtual ~Drawable() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;

	void blink() {
		if (!_in_blink) {
			_data.color_pair.fg = _non_blink_color_pair.bg;
			_data.gs_color_pair.fg = _non_blink_gs_color_pair.bg;
			_in_blink = true;
		} else { // if (_in_blink)
			_data.color_pair.fg = _non_blink_color_pair.fg;
			_data.gs_color_pair.fg = _non_blink_gs_color_pair.fg;
			_in_blink = false;
		}
	}

	inline Data& set_data(Data n_data) {
		_data = n_data;
		_non_blink_color_pair = _data.color_pair;
		_non_blink_gs_color_pair = _data.gs_color_pair;

		return _data;
	}
	GEN_GETTER_BY_CON_REF(data);
};

// Note: this is a 3D position within the game world.
// Which floor the entity is on is what the Z axis represents.
//
// Note: this is not used for the `Player`'s position; see
// `game_engine::Engine::NonEcsSerData`'s `player_pos2` and `floor` for
// that.
class Position final: public ecs::Comp {
	friend class dunwich_sandgeon::game_engine::Engine;
public:		// types
	//enum class EntKind {
	//	Item,
	//	Trap,
	//	Monster,
	//	Player,
	//};
public:		// constants
	static const std::string KIND_STR;
private:		// variables
	#define MEMB_AUTOSER_LIST_COMP_POSITION(X) \
		X(_ent_id, std::nullopt) \
		X(_pos3, std::nullopt) \
		X(_prev_floor, std::nullopt) \
		/* X(_ent_kind, std::nullopt) */
	ecs::EntId _ent_id = ecs::ENT_NULL_ID;
	PrevCurrPair<IntVec3> _pos3 = {
		// The elements of these are initialized to `-1` as a debugging aid
		// in case initialization didn't happen
		IntVec3{.x=-1, .y=-1, .z=-1}, IntVec3{.x=-1, .y=-1, .z=-1} 
	};
	i32 _prev_floor = -1;

	// The elements of these are initialized to `-1` as a debugging aid
	// in case initialization didn't happen
	//PrevCurrPair<IntVec2> _pos2 = {
	//	{.x=-1, .y=-1}, {.x=-1, .y=-1}
	//};
	//PrevCurrPair<i32> _floor = {-1, -1};
	//EntKind _ent_kind;
public:		// variables
	PfieldLayerPrio priority = PfieldLayerPrio::Bakgnd;
public:		// functions
	Position() = default;
	Position(
		ecs::EntId s_ent_id, const IntVec3& s_pos3,
		PfieldLayerPrio s_priority//, EntKind s_ent_kind
	);
	Position(
		ecs::EntId s_ent_id, const IntVec2& s_pos2,
		PfieldLayerPrio s_priority//, EntKind s_ent_kind
	);
private:		// functions
	void _init(
		ecs::EntId s_ent_id, const IntVec3& s_pos,
		PfieldLayerPrio s_priority//, EntKind s_ent_kind
	);
public:		// functions
	Position(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Position);
	virtual ~Position();

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;

	inline const IntVec3& pos3() const {
		return _pos3();
		//return {.x=_pos2().x, .y=_pos2().y, .z=_floor()};
	}
	inline const IntVec3& prev_pos3() const {
		return _pos3.prev();
		//return {.x=_pos2.prev().x, .y=_pos2.prev().y, .z=_floor.prev()};
	}

	inline IntVec2 pos2() const {
		return {.x=pos3().x, .y=pos3().y};
		//return _pos2();
	}
	inline IntVec2 prev_pos2() const {
		return {.x=prev_pos3().x, .y=prev_pos3().y};
		//return _pos2.prev();
	}
	inline const i32& floor() const {
		//return _floor();
		return prev_pos3().z;
	}
	//inline const i32& prev_floor() const {
	//	return _floor.prev();
	//}

	void set_pos3(const IntVec3& n_pos3);
	void set_pos2(const IntVec2& n_pos2);
	//{
	//	(_pos3.x, _pos3.y) = n_pos2.x, n_pos2.y;
	//}

	GEN_GETTER_BY_VAL(ent_id);
	GEN_GETTER_BY_VAL(prev_floor);
	//GEN_GETTER_BY_VAL(ent_kind);
	//GEN_GETTER_BY_CON_REF(pos2);
	//GEN_GETTER_BY_CON_REF(floor);
};

inline std::ostream& operator << (
	std::ostream& os, const Position& position
) {
	return osprintout(os,
		"{", "ent_id", position.ent_id(), " ",
		"pos3", position.pos3(), " ",
		"prev_pos3", position.prev_pos3(), " "
		"prev_floor", position.prev_floor(), "}");
}

//class NonSerPosition final: public ecs::Comp {
//	friend class dunwich_sandgeon::game_engine::Engine;
//public:		// constants
//	static const std::string KIND_STR;
//private:		// variables
//	#define MEMB_AUTOSER_LIST_COMP_NON_SER_POSITION(X)
//		X(_ent_id, std::nullopt)
//		X(_pos, std::nullopt)
//	ecs::EntId _ent_id = ecs::ENT_NULL_ID;
//	IntVec3 _pos;
//public:		// variables
//	PfieldLayerPrio priority = PfieldLayerPrio::Block;
//public:		// functions
//	NonSerPosition() = default;
//	NonSerPosition(ecs::EntId s_ent_id, const IntVec3& s_pos,
//		PfieldLayerPrio s_priority);
//	NonSerPosition(const binser::Value& bv);
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(NonSerPosition);
//	virtual ~NonSerPosition();
//
//	virtual std::string kind_str() const;
//	virtual operator binser::Value () const;
//
//	GEN_GETTER_BY_VAL(ent_id);
//	GEN_GETTER_BY_CON_REF(pos);
//	void set_pos(const IntVec3& n_pos);
//};

//class Weight final: public ecs::Comp {
//public:		// constants
//	static const std::string KIND_STR;
//public:		// variables
//	i32 val = 0;
//public:		// functions
//	Weight() = default;
//	inline Weight(i32 s_val)
//		: val(s_val) {}
//	Weight(const binser::Value& bv);
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Weight);
//	virtual ~Weight() = default;
//
//	virtual std::string kind_str() const;
//	virtual operator binser::Value () const;
//};

// These are stats that increase or stay the same upon level up. They are
// the stats that an entity would have if not wearing armor and don't have
// buffs applied.
class BaseStats final: public ecs::Comp {
public:		// constants
	static const std::string KIND_STR;
	static constexpr i32
		MAX_VAL = 999,
		DEFAULT_HP = 50,
		DEFAULT_ATK = 20,
		DEFAULT_DEF = 0,
		DEFAULT_MAG_ATK = 20,
		DEFAULT_MAG_DEF = 0;
public:		// variables
	#define MEMB_LIST_COMP_BASE_STATS(X) \
		X(hp, std::nullopt) \
		X(atk, std::nullopt) \
		X(def, std::nullopt) \
		X(mag_atk, std::nullopt) \
		X(mag_def, std::nullopt)
	i32
		hp = DEFAULT_HP,
		atk = DEFAULT_ATK,
		def = DEFAULT_DEF,
		mag_atk = DEFAULT_MAG_ATK,
		mag_def = DEFAULT_MAG_DEF;
public:		// functions
	BaseStats() = default;
	inline BaseStats(
		i32 s_hp, i32 s_atk, i32 s_def, i32 s_mag_atk,
		i32 s_mag_def
	)
		: hp(s_hp), atk(s_atk), def(s_def), mag_atk(s_mag_atk),
		mag_def(s_mag_def) {}
	BaseStats(const binser::Value& bv);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(BaseStats);
	virtual ~BaseStats() = default;

	virtual std::string kind_str() const;
	virtual operator binser::Value () const;
};

//class OtherStats final: public ecs::Comp {
//public:		// constants
//	static const std::string KIND_STR;
//	static constexpr i32
//		MAX_VAL = 999,
//		DEFAULT_WEIGHT = 40;
//public:		// variables
//	i32
//		weight = DEFAULT_WEIGHT;
//public:		// functions
//	OtherStats
//};
//--------
} // namespace comp
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_comp_general_comp_classes_hpp
