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

#include "gm_dungeon_gen_class.hpp"
#include "../engine_class.hpp"

namespace dunwich_sandgeon
{
namespace game_engine
{
namespace sys
{

const std::string
	GmDungeonGen::KIND_STR("GmDungeonGen");

std::string GmDungeonGen::kind_str() const
{
	return KIND_STR;
}

void GmDungeonGen::clear_dungeon_gen(ecs::Engine* ecs_engine)
{
	auto* dungeon_gen
		= ecs_engine->casted_comp_at<comp::DungeonGen>(*_dungeon_gen_id);
	dungeon_gen->clear();
}
void GmDungeonGen::_init(ecs::Engine* ecs_engine)
{
	_init_start();

	const std::string func_name("game_engine::sys::GmDungeonGen::_init");

	//if (ecs_engine->has_ent_w_comp(make_key_set
	//	<ecs::NonSerializable, comp::StaticBgTileMap>()))
	//{
	//}
	if (!_bg_tile_map_id)
	{
		_bg_tile_map_id = ecs_engine->create_singleton_all
			(ecs::make_comp_map_ks
				(ecs::CompSptr(new ecs::NonSerializable()),
				ecs::CompSptr(new comp::StaticBgTileMap())),
			func_name);
	}
	if (!_dungeon_gen_id)
	{
		_dungeon_gen_id = ecs_engine->create_singleton_all
			(ecs::make_comp_map_ks
				(ecs::CompSptr(new ecs::NonSerializable()),
				ecs::CompSptr(new comp::DungeonGen())),
			func_name);

		printout("game_engine::sys::GmDungeonGen::_init(): ",
			*_dungeon_gen_id, "\n");
	}
}

void GmDungeonGen::tick(ecs::Engine* ecs_engine)
{
	if (_tick_helper(ecs_engine,
		engine->game_mode() == GameMode::DungeonGen))
	{
		// TODO: add procedural dungeon generation
		auto* bg_tile_map
			= ecs_engine->casted_comp_at<comp::StaticBgTileMap>
				(*_bg_tile_map_id);
		auto* dungeon_gen
			= ecs_engine->casted_comp_at<comp::DungeonGen>
				(*_dungeon_gen_id);

		if (engine->key_status.key_just_went_down(KeyKind::DownR))
		{
			_gen_single_rp(dungeon_gen);
		}

		dungeon_gen->draw(bg_tile_map);
		bg_tile_map->draw();
		engine->screen_window.clear();

		engine->screen_window.draw(engine->pfield_window);
		engine->screen_window.draw(engine->log_window);
		engine->screen_window.draw(engine->hud_window);
	}
}

void GmDungeonGen::_gen_single_rp(comp::DungeonGen* dungeon_gen)
{
	//GenInfo gen_info;
	comp::DungeonGen::RoomPath rp;

	if (dungeon_gen->size() == 0)
	{
		_attempted_num_rp = engine->layout_rand<i32>
			(i32(MIN_NUM_ROOM_PATHS), i32(MAX_NUM_ROOM_PATHS));

		// We always generate a room in this case.
		//for (i32 tries=0; tries<GEN_RP_MAX_TRIES; ++tries)
		// Force there to be at least one room
		for (;;)
		{
			//--------
			//printout("testificate 2\n");
			//--------
			rp.rect.pos.x = engine->layout_rand<i32>
				(PFIELD_PHYS_RECT2.left_x(),
				PFIELD_PHYS_RECT2.right_x() - ROOM_MIN_SIZE_2D.x - 1);
			rp.rect.pos.y = engine->layout_rand<i32>
				(PFIELD_PHYS_RECT2.top_y(),
				PFIELD_PHYS_RECT2.bottom_y() - ROOM_MIN_SIZE_2D.y - 1);

			rp.rect.size_2d.x = engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
			rp.rect.size_2d.y = engine->layout_rand<i32>
				(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y);
			//--------
			if (rp.fits_in_pfield())
			{
				break;
			}
			//--------
		}
	}
	//else if (dungeon_gen->size() < MAX_NUM_ROOM_PATHS)
	else if (i32(dungeon_gen->size()) < _attempted_num_rp)
	{
		auto temp_func = [&]() -> bool
		{
			//--------
			const i32 
				_gen_type() = engine->layout_rand<i32>
					(MIN_GEN_TYPE, MAX_GEN_TYPE),
				//_gen_type() = GEN_TYPE_ROOM,
				_gen_side() = engine->layout_rand<i32>
					(MIN_GEN_SIDE, MAX_GEN_SIDE);
			//--------
			i32
				thickness = 0,
				length = 0;

			if (_gen_type()() == GEN_TYPE_PATH)
			{
				thickness = PATH_THICKNESS;
				length = engine->layout_rand<i32>
					(PATH_MIN_LEN, PATH_MAX_LEN);
			}
			else // if (_gen_type() == GEN_TYPE_ROOM)
			{
				const IntVec2 temp_vec2
					{.x=engine->layout_rand<i32>
						(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x),
					.y=engine->layout_rand<i32>
						(ROOM_MIN_SIZE_2D.y, ROOM_MAX_SIZE_2D.y)};

				if (_gen_side() == GEN_SIDE_L || _gen_side() == GEN_SIDE_R)
				{
					thickness = temp_vec2.y;
					length = temp_vec2.x;
				}
				else // if (_gen_side() == GEN_SIDE_T
					//|| _gen_side() == GEN_SIDE_B)
				{
					//thickness = engine->layout_rand<i32>
					//	(ROOM_MIN_SIZE_2D.x, ROOM_MAX_SIZE_2D.x);
					thickness = temp_vec2.x;
					length = temp_vec2.y;
				}
			}
			//--------
			// Which `RoomPath` are we connecting to?
			//printout("test 0\n");
			const i32 conn_rp_index = engine->layout_rand<i32>
				(0, i32(dungeon_gen->size()) - 1);

			//const i32 conn_rp_index = engine->layout_rand<i32>
			//	(0, 0);
			//printout("test 1\n");
			auto& conn_rp = dungeon_gen->at(conn_rp_index);

			const i32
				conn_rp_lsx = conn_rp.rect.left_x(),
				conn_rp_tsy = conn_rp.rect.top_y(),
				conn_rp_rsx = conn_rp.rect.right_x(),
				conn_rp_bsy = conn_rp.rect.bottom_y();

			if (_gen_side() == GEN_SIDE_L)
			{
				rp.rect.pos = IntVec2
					{.x=conn_rp_lsx,
					.y=engine->layout_rand<i32>
						(conn_rp_tsy, conn_rp_bsy)}
					- IntVec2{length, 0};
				rp.rect.size_2d = {.x=length, .y=thickness};
			}
			else if (_gen_side() == GEN_SIDE_T)
			{
				rp.rect.pos = IntVec2
					{.x=engine->layout_rand<i32>
						(conn_rp_lsx, conn_rp_rsx),
					.y=conn_rp_tsy}
					- IntVec2{0, length};
				rp.rect.size_2d = {.x=thickness, .y=length};
			}
			else if (_gen_side() == GEN_SIDE_R)
			{
				rp.rect.pos = IntVec2
					{.x=conn_rp_rsx,
					.y=engine->layout_rand<i32>
						(conn_rp_tsy, conn_rp_bsy)}
					+ IntVec2{1, 0};
				rp.rect.size_2d = {.x=length, .y=thickness};
			}
			else // if (_gen_side() == GEN_SIDE_B)
			{
				rp.rect.pos = IntVec2
					{.x=engine->layout_rand<i32>
						(conn_rp_lsx, conn_rp_rsx),
					.y=conn_rp_bsy}
					+ IntVec2{0, 1};
				rp.rect.size_2d = {.x=thickness, .y=length};
			}
			//--------
			// This is a simple algorithm that could be made faster and
			// more complicated, but I figure any platform running this
			// game will have fast enough hardware considering the maximum
			// numbers of rooms/paths.
			if (!rp.fits_in_pfield())
			{
				return false;
			}
			printout("rp.fits_in_pfield(): ", rp.rect, "\n");

			for (size_t i=0; i<dungeon_gen->size(); ++i)
			{
				if (dungeon_gen->at(i).rect.intersect(rp.rect))
				{
					return false;
				}
			}

			rp.conn_index_set.insert(conn_rp_index);
			conn_rp.conn_index_set.insert(dungeon_gen->size());
			printout("`_gen_type()`: ", _gen_type(), "\n");

			return true;
			//--------
		};

		if (dungeon_gen->size() < MIN_NUM_ROOM_PATHS)
		{
			for (;;)
			{
				if (temp_func())
				{
					break;
				}
			}
		}
		else
		{
			for (i32 tries=0; tries<GEN_RP_MAX_TRIES; ++tries)
			{
				if (temp_func())
				{
					break;
				}
			}
		}
	}
	#ifdef DEBUG
	printout("Generated this `RoomPath`: ",
		rp.rect, "; ",
		rp.is_horiz_path(), " ", rp.is_vert_path(), " ", rp.is_room(),
		"\n");
	#endif		// DEBUG

	dungeon_gen->push_back(std::move(rp));
}
//void GmDungeonGen::_connect_room_paths(comp::StaticBgTileMap* bg_tile_map,
//	comp::DungeonGen* dungeon_gen)
//{
//}

} // namespace sys
} // namespace game_engine
} // namespace dunwich_sandgeon
