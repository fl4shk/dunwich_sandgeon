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
#include "engine_class.hpp"

namespace dunwich_sandgeon {
namespace game_engine {
//--------
MetaballGen::MetaballGen(const IntVec2& s_size_2d) 
	: _size_2d(s_size_2d) {
}
//MetaballGen::MetaballGen(const IntVec2& s_size_2d) 
//	: _bounds({.pos={0, 0}, .size_2d=s_size_2d}) {
//}
//MetaballGen::MetaballGen(const IntRect2& s_bounds)
//	: _bounds(s_bounds) {
//}
//--------
MetaballGen& MetaballGen::add(const IntVec2& pos, float range) {
	_ball_vec.push_back({.pos=FltVec2(pos), .size_2d{.x=range, .y=range}});
	return *this;
}
MetaballGen& MetaballGen::add(const IntVec2& pos, const FltVec2& range) {
	_ball_vec.push_back({.pos=FltVec2(pos), .size_2d=range});
	return *this;
}
//--------
float MetaballGen::gen_single(const IntVec2& pos) const {
	float ret = 0.0f;

	for (const auto& ball: _ball_vec) {
		//const FltRect2& temp_r2
		//	{.pos=FltVec2(pos), .size_2d=FltVec2(_size_2d)};
		//auto diff = ball.cntr_pos() - temp_r2.cntr_pos();
		//auto diff = ball.cntr_pos()
		//	- (FltVec2(pos) + (FltVec2(_size_2d) / 2));
		//auto diff = ball.cntr_pos()
		//	- (FltVec2(pos) - (FltVec2(_size_2d) / 2));
		//auto diff = (ball.pos - pos) - (FltVec2(_size_2d) / 2);
		auto diff = ball.pos - pos;
		//auto diff = ball.cntr_pos() - pos;
		// Try modifying the below two changes to `diff`
		//diff.x = diff.x / ball.size_2d.x * ball.size_2d.y;
		diff.y = (diff.y / ball.size_2d.y) * ball.size_2d.x;
		const float
			dist2 = (diff.x * diff.x) + (diff.y * diff.y);
			//dist2 = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));
		ret += (ball.size_2d.x * ball.size_2d.x) / dist2;

		//const FltVec2 temp_diff = FltVec2(ball.pos);
		//FltVec2 diff = temp_diff;
		//diff.y = (diff.y / ball.size_2d.x) * ball.size_2d.x;
		//float dist2 = (diff.x * diff.x) + (diff.y * diff.y);
		//const auto
		//	to_add = (ball.size_2d.x + ball.size_2d.y) / dist2;
		//ret += to_add;
	}
	//engine->log("MetaballGen::gen_single(): ", ret, "\n");
	return ret;
}
bool MetaballGen::gen_single(
	const IntVec2& pos, float thresh_0, float thresh_1
) const {
	const auto ret_flt = gen_single(pos);
	//return ret_flt;
	//return ret_flt <= 10.0f;
	return ret_flt >= math::min_va(thresh_0, thresh_1)
		&& ret_flt <= math::max_va(thresh_0, thresh_1);
	//return !(ret_flt >= math::min_va(thresh_0, thresh_1)
	//	&& ret_flt <= math::max_va(thresh_0, thresh_1));
	//return ret_flt <= thresh_0;
}
FltDyna2d MetaballGen::gen() const {
	FltDyna2d ret(_size_2d.y, FltDynarr(_size_2d.x, 0));

	IntVec2 pos;
	for (pos.y=0; pos.y<_size_2d.y; ++pos.y) {
		for (pos.x=0; pos.x<_size_2d.x; ++pos.x) {
			//if (std::isnormal(val) && val <= threshold) {
			//	printout("MetaballGen::gen(): val: ", val, "\n");
			//}
			ret.at(pos.y).at(pos.x)
				= gen_single(pos);
		}
	}

	return ret;
}
BoolDyna2d MetaballGen::gen(float thresh_0, float thresh_1) const {
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
	BoolDyna2d ret(_size_2d.y, BoolDynarr(_size_2d.x, 0));
	//printout("{", ret.size(), " ", ret.front().size(), "}\n");

	IntVec2 pos;
	for (pos.y=0; pos.y<_size_2d.y; ++pos.y) {
		for (pos.x=0; pos.x<_size_2d.x; ++pos.x) {
			//if (std::isnormal(val) && val <= threshold) {
			//	printout("MetaballGen::gen(): val: ", val, "\n");
			//}
			ret.at(pos.y).at(pos.x)
				= gen_single(pos, thresh_0, thresh_1);
		}
	}

	return ret;
}
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
