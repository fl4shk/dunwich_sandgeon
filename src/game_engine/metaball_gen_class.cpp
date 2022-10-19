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

#include "metaball_gen_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
MetaballGen::MetaballGen(const IntVec2& s_size_2d) 
	: _size_2d(s_size_2d) {
}
MetaballGen& MetaballGen::add(const IntVec2& pos, float range) {
	_ball_vec.push_back({.pos=FltVec2(pos), .size_2d{.x=range, .y=range}});
	return *this;
}
MetaballGen& MetaballGen::add(const IntVec2& pos, const FltVec2& range) {
	_ball_vec.push_back({.pos=FltVec2(pos), .size_2d=range});
	return *this;
}
auto MetaballGen::gen(float thresh_0, float thresh_1) -> GenDyna2d {
	//result.resize(size, 0);
	//for(auto p : Rect2i({0, 0}, size)) {
	//	float value = 0.0;
	//	for(auto& ball : balls) {
	//		auto diff = glm::vec{ball.position - p};
	//		diff.y = diff.y / ball.size.y * ball.size.x;
	//		auto dist2 = (diff.x * diff.x) + (diff.y * diff.y);
	//		value += (ball.size.x * ball.size.x) / dist2;
	//	}
	//	result(p) = value;
	//}

	//printout("MetaballGen::gen(): ", _size_2d, "\n");
	//GenDyna2d ret(_size_2d.y, GenDynarr(_size_2d.x, 0.0f));
	GenDyna2d ret(_size_2d.y, GenDynarr(_size_2d.x, 0));
	//printout("{", ret.size(), " ", ret.front().size(), "}\n");

	FltVec2 pos;
	for (pos.y=0; pos.y<_size_2d.y; ++pos.y) {
		for (pos.x=0; pos.x<_size_2d.x; ++pos.x) {
			float val = 0.0f;
			for (const auto& ball: _ball_vec) {
				//auto diff = ball.pos - pos;
				auto diff = ball.cntr_pos() - (pos - (_size_2d / 2));
				//auto diff = ball.cntr_pos() - pos;
				// Try modifying the below two changes to `diff`
				//diff.x = diff.x / ball.size_2d.x * ball.size_2d.y;
				diff.y = diff.y / ball.size_2d.y * ball.size_2d.x;
				const auto
					dist2 = (diff.x * diff.x) + (diff.y * diff.y);
					//dist2 = std::sqrt((diff.x * diff.x)
					//	+ (diff.y * diff.y));
				val += (ball.size_2d.x * ball.size_2d.x) / dist2;

				//const FltVec2 temp_diff = FltVec2(ball.pos);
				//FltVec2 diff = temp_diff;
				//diff.y = (diff.y / ball.size_2d.x) * ball.size_2d.x;
				//float dist2 = (diff.x * diff.x) + (diff.y * diff.y);
				//const auto
				//	to_add = (ball.size_2d.x + ball.size_2d.y) / dist2;
				//val += to_add;
			}
			//if (std::isnormal(val) && val <= threshold) {
			//	printout("MetaballGen::gen(): val: ", val, "\n");
			//}
			ret.at(pos.y).at(pos.x)
				//= val;
				//= val <= 10.0f;
				= val >= math::min_va(thresh_0, thresh_1)
				&& val <= math::max_va(thresh_0, thresh_1);
		}
	}

	return ret;
}
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
