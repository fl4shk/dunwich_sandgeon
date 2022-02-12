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

#ifndef src_game_engine_window_classes_hpp
#define src_game_engine_window_classes_hpp

// src/game_engine/window_classes.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"
#include "../input_kind_enum.hpp"
#include "font_color_enum.hpp"
#include "ticker_base_class.hpp"
#include "comp/general_comp_classes.hpp"
//#include "engine_class.hpp"

namespace dungwich_sandeon
{
namespace game_engine
{

class Engine;
class Menu;
class MsgLog;
//class Hud;

//class LayeredWindow;

// A window made out of `Entity`s
class Window
{
public:		// constants
	static const std::string
		BORDER_CORNER_KIND_STR,
		BORDER_HORIZ_KIND_STR,
		BORDER_VERT_KIND_STR,
		BLANK_KIND_STR;
	//static const comp::Drawable::Data
	//	BORDER_CORNER_DRAWABLE_DATA,
	//	BORDER_HORIZ_DRAWABLE_DATA,
	//	BORDER_VERT_DRAWABLE_DATA,
	//	BLANK_DRAWABLE_DATA;
	//static constexpr comp::Drawable::Data
	//	BORDER_CORNER_DRAWABLE_DATA{.c='+',
	//		.color_pair=FontColor::Green,
	//		.gs_color_pair=FontColor::White},
	//	BORDER_HORIZ_DRAWABLE_DATA{.c='-',
	//		.color_pair=FontColor::Green,
	//		.gs_color_pair=FontColor::White},
	//	BORDER_VERT_DRAWABLE_DATA{.c='|',
	//		.color_pair=FontColor::Green,
	//		.gs_color_pair=FontColor::White},
	//	BLANK_DRAWABLE_DATA{.c=' ',
	//		.color_pair=FontColor::Black,
	//		.gs_color_pair=FontColor::Black};

	static const comp::Drawable::Data& BORDER_CORNER_DRAWABLE_DATA();
	static const comp::Drawable::Data& BORDER_HORIZ_DRAWABLE_DATA();
	static const comp::Drawable::Data& BORDER_VERT_DRAWABLE_DATA();
	static const comp::Drawable::Data& BLANK_DRAWABLE_DATA();
protected:		// variables
	Engine* _engine = nullptr;
	//int _priority = 0;
	PosVec2 _pos;
	ecs::EntIdVec2d _ent_id_v2d, _cleared_ent_id_v2d;
	int _file_num = -1;
public:		// functions
	Window();
	Window(Engine* s_engine, const PosVec2& s_some_pos,
		const SizeVec2& s_some_size_2d, int s_file_num,
		bool prev_args_are_with_border=true);
	Window(Engine* s_engine, const PosVec2& s_some_pos,
		const PosVec2& s_some_end_pos, int s_file_num,
		bool prev_args_are_with_border=true);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Window);
	virtual ~Window();

	void init_set_border();

	virtual void tick(InputKind input_kind);

	inline auto& with_border_ent_id_at(const PosVec2& index)
	{
		return _ent_id_v2d.at(index.y).at(index.x);
	}
	inline const auto& with_border_ent_id_at(const PosVec2& index) const
	{
		return _ent_id_v2d.at(index.y).at(index.x);
	}
	inline auto& with_border_ent_id_at(const SizeVec2& index)
	{
		return _ent_id_v2d.at(index.y).at(index.x);
	}
	inline const auto& with_border_ent_id_at(const SizeVec2& index) const
	{
		return _ent_id_v2d.at(index.y).at(index.x);
	}

	inline auto& ent_id_at(const PosVec2& index)
	{
		return with_border_ent_id_at(index + PosVec2(1, 1));
	}
	inline const auto& ent_id_at(const PosVec2& index) const
	{
		return with_border_ent_id_at(index + PosVec2(1, 1));
	}
	inline auto& ent_id_at(const SizeVec2& index)
	{
		return with_border_ent_id_at(index + SizeVec2(1, 1));
	}
	inline const auto& ent_id_at(const SizeVec2& index) const
	{
		return with_border_ent_id_at(index + SizeVec2(1, 1));
	}

	inline SizeVec2 with_border_size_2d() const
	{
		return SizeVec2(ent_id_v2d().at(0).size(),
			ent_id_v2d().size());
	}
	inline SizeVec2 size_2d() const
	{
		return with_border_size_2d() - SizeVec2(2, 2);
	}

	void clear();

	// This draws the border as well.
	void draw(const Window& win, bool leave_corner=false);
	void draw(const Menu& menu);
	void draw(const MsgLog& msg_log);
	//void draw(const Hud& hud);
	//void draw(const LayeredWindow& layered_win);
	//void draw_text(const PosVec2& where, const std::string& what);
	
	//GEN_GETTER_AND_SETTER_BY_VAL(priority);
	GEN_GETTER_BY_CON_REF(pos);
	GEN_GETTER_BY_CON_REF(ent_id_v2d);
	GEN_GETTER_BY_VAL(file_num);
};

//class LayeredWindow
//{
//protected:		// variables
//	std::map<std::string, Window> _layer_map;
//	std::map<std::string, uint> _layer_prio_map;
//public:		// functions
//	LayeredWindow();
//	LayeredWindow(const PosVec2& s_pos, const SizeVec2& s_size_2d,
//		const std::map<std::string, uint>& s_layer_prio_map);
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(LayeredWindow);
//	virtual ~LayeredWindow();
//
//	virtual void tick(InputKind input_kind);
//
//	inline Window& layer_at(const std::string& key)
//	{
//		return _layer_map.at(key);
//	}
//	inline const Window& layer_at(const std::string& key) const
//	{
//		return _layer_map.at(key);
//	}
//	inline SizeVec2 size_2d() const
//	{
//		for (const auto& pair: layer_map())
//		{
//			// All layers have the same size
//			return pair.second.size_2d();
//		}
//	}
//
//	GEN_GETTER_BY_CON_REF(layer_map);
//	GEN_GETTER_BY_CON_REF(layer_prio_map);
//};

} // namespace game_engine
} // namespace dungwich_sandeon

#endif		// src_game_engine_window_classes_hpp
