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

int main(int argc, char* argv[]) {
	////static_assert(is_specialization<std::array<i32, 5>, std::array>());
	//static_assert(is_std_array<std::array<std::array<i32, 5>, 3>>());
	//static_assert(is_std_array<std::array<i32, 5>>());
	//static_assert(!is_std_array<std::vector<i32>>());
	////static_assert(is_std_vector<std::vector<i32>>());
	////static_assert(is_std_vector<i32>());
	//static_assert(!is_std_vector<i32>());

	////static_assert(is_std_vector<i32, std::allocator<i32>>());
	//static_assert(!is_std_vector<i32>());

	//static_assert(is_std_vector<std::vector<i32>>());
	////static_assert(!is_std_vector<std::vector<i32>>());

	//static_assert(is_std_vector<std::vector<i32, std::allocator<i32>>>());
	////static_assert(!is_std_vector<std::vector<i32, std::allocator<i32>,
	////	std::allocator<i32>>());

	//printout("main()");
	//dunwich_sandgeon::game_engine::engine->dbg_check_ecs_engine();

	//pcg32
	////pcg64
	//	rng3(3), rng4(4);
	//const std::string
	//	rng3_init_str(sconcat("6364136223846793005 ",
	//		"1442695040888963407 ", "2521675601639303865")),
	//	rng4_init_str(sconcat("6364136223846793005 ",
	//		"1442695040888963407 ", "8885811825486096870"));
	//printout("states: ", rng3, "\t\t", rng4, "\n");
	//printout("values: ", rng3(), " ", rng4(), "\n\n");

	//printout("states: ", rng3, "\t\t", rng4, "\n");
	//printout("values: ", rng3(), " ", rng4(), "\n\n");

	//printout("states: ", rng3, "\t\t", rng4, "\n");
	//printout("\n\n");

	//inv_sconcat(rng3_init_str, rng3);
	//inv_sconcat(rng4_init_str, rng4);

	//printout("states: ", rng3, "\t\t", rng4, "\n");
	//printout("values: ", rng3(), " ", rng4(), "\n\n");

	//printout("states: ", rng3, "\t\t", rng4, "\n");
	//printout("values: ", rng3(), " ", rng4(), "\n\n");

	//printout("states: ", rng3, "\t\t", rng4, "\n");
	//printout("\n");

	//temp_ostm << sconcat(
	//	//"47026247687942121848144207491837523525 ",
	//	"47026247687942121848144207491837523520 ",
	//	"117397592171526113268558934119004209487 ",
	//	"237373757935471646366144288263181576297"
	//	);

	//temp_ostm << pcg32(4);
	//temp_ostm >> rng;
	//printout(rng, "\n");

	//temp_ostm << pcg32(3);
	//temp_ostm >> rng;
	//printout(rng, "\n");

	//temp_ostm << pcg32(4);
	//temp_ostm >> rng;
	//printout(rng, "\n");
	//printout(pcg32(3), "\n", pcg32(4), "\n\n");

	//{
	//	std::stringstream temp_ostm;
	//	temp_ostm << pcg32(4);
	//	temp_ostm >> rng3;
	//}
	//printout(rng3, "\n", rng4, "\n\n");

	//{
	//	std::stringstream temp_ostm;
	//	temp_ostm << pcg32(3);
	//	temp_ostm >> rng4;
	//}
	//printout(rng3, "\n", rng4, "\n\n");

	//{
	//	std::stringstream temp_ostm;
	//	temp_ostm << pcg32(3);
	//	temp_ostm >> rng3;
	//}
	//printout(rng3, "\n", rng4, "\n\n");

	//{
	//	std::stringstream temp_ostm;
	//	temp_ostm << pcg32(4);
	//	temp_ostm >> rng4;
	//}
	//printout(rng3, "\n", rng4, "\n\n");

	//{
	//	std::stringstream temp_ostm;
	//	temp_ostm << rng3;
	//	temp_ostm >> rng4;
	//}
	//printout(rng3, "\n", rng4, "\n\n");

	return dunwich_sandgeon::io::RealMainSdl(argc, argv).run();
}
