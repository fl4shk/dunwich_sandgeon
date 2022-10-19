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

#ifndef src_game_engine_global_shape_constants_etc_hpp
#define src_game_engine_global_shape_constants_etc_hpp

// src/game_engine/global_shape_constants_etc.hpp

#include "../misc_includes.hpp"
#include "../misc_types.hpp"
#include "misc_constants.hpp"
#include "w_bbox_base_classes.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
static constexpr float
	CDIFF = 0.1f;
static constexpr FltVec2
	CDIFF_V2{.x=CDIFF, .y=CDIFF};
//--------
// This constant has values in the amount of tilemap entries
static constexpr IntVec2
	W_BRDR_SCREEN_SIZE_2D{
		//.x=82, .y=62,
		.x=80, .y=60,
		//.x=62, .y=42,
		//.x=42, .y=42,
	},
	SCREEN_SIZE_2D(W_BRDR_SCREEN_SIZE_2D - IntVec2{2, 2});
//static constexpr IntRect2
//	SCREEN_RECT2{.pos{0, 0}, .size_2d=SCREEN_SIZE_2D},
//	W_BRDR_SCREEN_RECT2
//		{.pos{0, 0}, .size_2d=W_BRDR_SCREEN_SIZE_2D};
//--------
static constexpr IntVec2
	PFIELD_WINDOW_POS{.x=0, .y=0},
	PFIELD_WINDOW_END_POS{
		.x=W_BRDR_SCREEN_SIZE_2D.x - 1 - 20, // 59
		.y=W_BRDR_SCREEN_SIZE_2D.y - 1 - 10, // 49
		//.x=W_BRDR_SCREEN_SIZE_2D.x - 1 - 10, // 69
		//.y=W_BRDR_SCREEN_SIZE_2D.y - 1 - 10, // 49
	};
	//NO_BRDR_PFIELD_WINDOW_POS(PFIELD_WINDOW_POS + IntVec2{1, 1}),
	//NO_BRDR_PFIELD_WINDOW_END_POS
	//	(PFIELD_WINDOW_END_POS - IntVec2{1, 1}),
	//PFIELD_PHYS_POS(NO_BRDR_PFIELD_WINDOW_POS - IntVec2{1, 1}),
	//PFIELD_PHYS_END_POS
	//	(NO_BRDR_PFIELD_WINDOW_END_POS - IntVec2{1, 1});
static constexpr IntRect2
	PFIELD_WINDOW_RECT2=IntRect2::build_in_grid
		(PFIELD_WINDOW_POS, PFIELD_WINDOW_END_POS);
static constexpr IntVec2
	PFIELD_WINDOW_SIZE_2D
		//{
		//	.x=PFIELD_WINDOW_END_POS.x
		//		- PFIELD_WINDOW_POS.x + 1,
		//	.y=PFIELD_WINDOW_END_POS.y
		//		- PFIELD_WINDOW_POS.y + 1
		//};
		= PFIELD_WINDOW_RECT2.size_2d;
//--------
static constexpr IntVec2
	//PFIELD_PHYS_POS(PFIELD_WINDOW_POS.x, PFIELD_WINDOW_POS.y),
	PFIELD_PHYS_POS{.x=0, .y=0},
	PFIELD_PHYS_END_POS(
		//IntVec2{PFIELD_WINDOW_END_POS.x, PFIELD_WINDOW_END_POS.y}
		//	- IntVec2{2, 2}
		PFIELD_WINDOW_END_POS - IntVec2{2, 2}
	);
static constexpr IntRect2
	PFIELD_PHYS_RECT2=IntRect2::build_in_grid
		(PFIELD_PHYS_POS, PFIELD_PHYS_END_POS),
	PFIELD_PHYS_NO_BRDR_RECT2=IntRect2::build_in_grid
		(PFIELD_PHYS_POS + IntVec2{1, 1},
		PFIELD_PHYS_END_POS - IntVec2{1, 1});
//extern const IntVec2Ex
//	PFIELD_EX_RANGE;
static constexpr IntVec2
	PFIELD_PHYS_SIZE_2D
		= PFIELD_PHYS_RECT2.size_2d;
//--------
static constexpr IntVec2
	CGC2D_GRID_ELEM_SIZE_2D{.x=10, .y=10},
	CGC2D_NUM_GRID_ELEMS_2D
		(i32(std::ceil(double(PFIELD_PHYS_SIZE_2D.x)
			/ double(CGC2D_GRID_ELEM_SIZE_2D.x))),
		i32(std::ceil(double(PFIELD_PHYS_SIZE_2D.y)
			/ double(CGC2D_GRID_ELEM_SIZE_2D.y))));
using CollGridT
	= math::CollGridCsz2d<i32, WIntBboxBase, CGC2D_GRID_ELEM_SIZE_2D,
		CGC2D_NUM_GRID_ELEMS_2D>;
//--------
constexpr inline bool r2_intersects_pfield_nb(const IntRect2& rect) {
	return PFIELD_PHYS_NO_BRDR_RECT2.intersect(rect);
}
constexpr inline bool r2_fits_in_pfield_nb(const IntRect2& rect) {
	//return (rect.pos.x >= 0
	//	&& rect.pos.x <= PFIELD_SIZE_2D.x);
	//return PFIELD_PHYS_RECT2.arg_inside(rect, false,
	//	IntVec2());
	//return PFIELD_PHYS_RECT2.arg_inside(rect, CDIFF_V2);
	//return PFIELD_PHYS_RECT2.arg_inside(rect);
	//return PFIELD_PHYS_RECT2.arg_inside<true>(rect);
	return PFIELD_PHYS_NO_BRDR_RECT2.arg_inside<false>(rect);
}
//--------
//constexpr inline bool r2_local_pos_in_border(
//	const IntRect2& rect, const IntVec2& local_pos
//) {
//	//return (!
//	//	(local_pos.x > 0
//	//	&& local_pos.x < rect.size_2d.x + 1
//	//	&& local_pos.y > 0
//	//	&& local_pos.y < rect.size_2d.y + 1)
//	//);
//	if (local_pos.x == 0 || local_pos.x == rect.size_2d.x + 1) {
//		return true;
//	} else {
//		return (local_pos.y == 0 || local_pos.y == rect.size_2d.y + 1);
//	}
//}
//constexpr inline IntRect2 r2_shrink_to_internal_border(
//	const IntRect2& rect
//) {
//	return rect.build_in_grid_inflated_lim
//		(IntVec2{-1, -1}, IntVec2{-1, -1},
//		PFIELD_PHYS_NO_BRDR_RECT2);
//}
//constexpr inline bool r2_local_pos_in_internal_border(
//	const IntRect2& rect, const IntVec2& local_pos
//) {
//	//&& (!
//	//	(local_pos.x > 1
//	//	&& local_pos.x < rect.size_2d.x
//	//	&& local_pos.y > 1
//	//	&& local_pos.y < rect.size_2d.y)
//	//);
//	//return r2_local_pos_in_border
//	//	(r2_shrink_to_internal_border(rect), local_pos);
//
//	if (local_pos.x == 1 || local_pos.x == rect.size_2d.x) {
//		return true;
//	} else {
//		return (local_pos.y == 1 || local_pos.y == rect.size_2d.y);
//	}
//}
constexpr inline IntRect2 r2_build_in_pfield(
	const IntVec2& tl_corner, const IntVec2& br_corner
) {
	return IntRect2::build_in_grid_lim
		(tl_corner, br_corner, PFIELD_PHYS_RECT2);
}
constexpr inline IntRect2 r2_build_in_pfield_nb(
	const IntVec2& tl_corner, const IntVec2& br_corner
) {
	return IntRect2::build_in_grid_lim
		(tl_corner, br_corner, PFIELD_PHYS_NO_BRDR_RECT2);
}
constexpr inline bool r2_pos_in_internal_border(
	const IntRect2& rect, const IntVec2& pos
) {
	return (
		((pos.x == rect.left_x() || pos.x == rect.right_x())
			&& pos.y >= rect.top_y() && pos.y <= rect.bottom_y())
		|| ((pos.y == rect.top_y() || pos.y == rect.bottom_y())
			&& pos.x >= rect.left_x() && pos.x <= rect.right_x())
	);
}
constexpr inline bool r2_pos_in_border(
	const IntRect2& rect, const IntVec2& pos
) {
	return (
		((pos.x == rect.left_x() - 1 || pos.x == rect.right_x() + 1)
			&& pos.y >= rect.top_y() - 1 && pos.y <= rect.bottom_y() + 1)
		|| ((pos.y == rect.top_y() - 1 || pos.y == rect.bottom_y() + 1)
			&& pos.x >= rect.left_x() - 1 && pos.x <= rect.right_x() + 1)
	);
}

constexpr inline IntRect2 r2_left_side_1ge_past_in_pfield_nb(
	const IntRect2& rect
) {
	return rect.left_side_1ge_past_lim
		(PFIELD_PHYS_NO_BRDR_RECT2);
}
constexpr inline IntRect2 r2_top_side_1ge_past_in_pfield_nb(
	const IntRect2& rect
) {
	return rect.top_side_1ge_past_lim
		(PFIELD_PHYS_NO_BRDR_RECT2);
}
constexpr inline IntRect2 r2_right_side_1ge_past_in_pfield_nb(
	const IntRect2& rect
) {
	return rect.right_side_1ge_past_lim
		(PFIELD_PHYS_NO_BRDR_RECT2);
}
constexpr inline IntRect2 r2_bottom_side_1ge_past_in_pfield_nb(
	const IntRect2& rect
) {
	return rect.bottom_side_1ge_past_lim
		(PFIELD_PHYS_NO_BRDR_RECT2);
}
//--------
static constexpr IntVec2
	LOG_WINDOW_POS{.x=0, .y=PFIELD_WINDOW_END_POS.y},
	//LOG_WINDOW_POS{.x=0, .y=PFIELD_WINDOW_SIZE_2D.y},
	LOG_WINDOW_END_POS
		{.x=PFIELD_WINDOW_SIZE_2D.x, .y=W_BRDR_SCREEN_SIZE_2D.y - 1},

	HUD_WINDOW_POS{
		.x=PFIELD_WINDOW_END_POS.x, .y=PFIELD_WINDOW_POS.y
		//.x=PFIELD_WINDOW_SIZE_2D.x, .y=PFIELD_WINDOW_POS.y,
	},
	HUD_WINDOW_END_POS
		{.x=W_BRDR_SCREEN_SIZE_2D.x - 1,
		.y=W_BRDR_SCREEN_SIZE_2D.y - 1},

	POPUP_WINDOW_POS{.x=13, .y=10},
	POPUP_WINDOW_END_POS
		{.x=HUD_WINDOW_POS.x - 1, .y=W_BRDR_SCREEN_SIZE_2D.y - 15},

	YES_NO_WINDOW_POS{.x=2, .y=W_BRDR_SCREEN_SIZE_2D.y / 2},
	YES_NO_WINDOW_END_POS
		{.x=YES_NO_WINDOW_POS.x + 3
			+ MSG_LOG_WIDGET_SELECTED_SPACING_SIZE
			+ MSG_LOG_WIDGET_SPACING_SIZE
			+ 1,
		.y=YES_NO_WINDOW_POS.y + 2 + 1 + 2},

	TEXT_YES_NO_WINDOW_POS
		{.x=2, .y=W_BRDR_SCREEN_SIZE_2D.y / 2},
	TEXT_YES_NO_WINDOW_END_POS
		{.x=TEXT_YES_NO_WINDOW_POS.x + 30 + 1 + 2,
		.y=TEXT_YES_NO_WINDOW_POS.y + 4 + 1 + 2};
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon

#endif		// src_game_engine_global_shape_constants_etc_hpp
