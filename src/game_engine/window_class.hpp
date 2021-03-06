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

namespace dunwich_sandgeon
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
public:		// types
	using DrawData = comp::Drawable::Data;
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

	static const DrawData& BORDER_CORNER_DRAWABLE_DATA();
	static const DrawData& BORDER_HORIZ_DRAWABLE_DATA();
	static const DrawData& BORDER_VERT_DRAWABLE_DATA();
	static const DrawData& BLANK_DRAWABLE_DATA();
protected:		// non-serialized variables
	//Engine* _engine = nullptr;
protected:		// serialized variables
	/* #define MEMB_SER_LIST_WINDOW(X) */ \
		/* X(_pos, std::nullopt) */ \
		/* X(_drawable_data_v2d, std::nullopt) */ \

	//int _priority = 0;
	PosVec2 _pos;
	std::vector<std::vector<DrawData>> _drawable_data_v2d;
public:		// functions
	Window();
	Window(const PosVec2& s_some_pos, const SizeVec2& s_some_size_2d,
		bool prev_args_are_with_border=true);
	Window(const PosVec2& s_some_pos, const PosVec2& s_some_end_pos,
		bool prev_args_are_with_border=true);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Window);
	virtual ~Window();

	//operator binser::Value () const;

	//void deserialize(const binser::Value& bv);
	//void init_set_border();

	inline DrawData& with_border_drawable_data_at(const PosVec2& index)
	{
		return _drawable_data_v2d.at(index.y).at(index.x);
	}
	inline const DrawData& with_border_drawable_data_at
		(const PosVec2& index) const
	{
		return _drawable_data_v2d.at(index.y).at(index.x);
	}
	inline DrawData& with_border_drawable_data_at(const SizeVec2& index)
	{
		return _drawable_data_v2d.at(index.y).at(index.x);
	}
	inline const DrawData& with_border_drawable_data_at
		(const SizeVec2& index) const
	{
		return _drawable_data_v2d.at(index.y).at(index.x);
	}

	inline DrawData& drawable_data_at(const PosVec2& index)
	{
		return with_border_drawable_data_at(index + PosVec2(1, 1));
	}
	inline const DrawData& drawable_data_at(const PosVec2& index) const
	{
		return with_border_drawable_data_at(index + PosVec2(1, 1));
	}
	inline DrawData& drawable_data_at(const SizeVec2& index)
	{
		return with_border_drawable_data_at(index + SizeVec2(1, 1));
	}
	inline const DrawData& drawable_data_at(const SizeVec2& index) const
	{
		return with_border_drawable_data_at(index + SizeVec2(1, 1));
	}

	inline SizeVec2 with_border_size_2d() const
	{
		return SizeVec2(drawable_data_v2d().front().size(),
			drawable_data_v2d().size());
	}
	inline SizeVec2 size_2d() const
	{
		return with_border_size_2d() - SizeVec2(2, 2);
	}

	void clear();

	// This draws the border as well.
	void draw(const Window& src, bool leave_corner=false);
	void draw(const Menu& menu);
	void draw(const MsgLog& msg_log);
	//void draw(const Hud& hud);
	//void draw(const LayeredWindow& layered_win);
	//void draw_text(const PosVec2& where, const std::string& what);
	
	//GEN_GETTER_AND_SETTER_BY_VAL(priority);
	//GEN_GETTER_AND_SETTER_BY_VAL(engine);
	GEN_GETTER_BY_CON_REF(pos);
	GEN_GETTER_BY_CON_REF(drawable_data_v2d);
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
} // namespace dunwich_sandgeon

#endif		// src_game_engine_window_classes_hpp
