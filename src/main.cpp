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

#include "misc_includes.hpp"
#include "sdl/real_main_sdl_class.hpp"

int main(int argc, char* argv[])
{
	////static_assert(is_specialization<std::array<int, 5>, std::array>());
	//static_assert(is_std_array<std::array<std::array<int, 5>, 3>>());
	//static_assert(is_std_array<std::array<int, 5>>());
	//static_assert(!is_std_array<std::vector<int>>());
	////static_assert(is_std_vector<std::vector<int>>());
	////static_assert(is_std_vector<int>());
	//static_assert(!is_std_vector<int>());

	////static_assert(is_std_vector<int, std::allocator<int>>());
	//static_assert(!is_std_vector<int>());

	//static_assert(is_std_vector<std::vector<int>>());
	////static_assert(!is_std_vector<std::vector<int>>());

	//static_assert(is_std_vector<std::vector<int, std::allocator<int>>>());
	////static_assert(!is_std_vector<std::vector<int, std::allocator<int>,
	////	std::allocator<int>>());

	//printout("main()");
	//dunwich_sandgeon::game_engine::engine->dbg_check_ecs_engine();
	return dunwich_sandgeon::io::RealMainSdl(argc, argv).run();
}
