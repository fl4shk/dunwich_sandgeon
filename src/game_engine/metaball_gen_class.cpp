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
	_ball_vec.push_back({.pos=pos, .size_2d{.x=range, .y=range}});
	return *this;
}
MetaballGen& MetaballGen::add(const IntVec2& pos, const FltVec2& range) {
	_ball_vec.push_back({.pos=pos, .size_2d=range});
	return *this;
}
//MetaballGen& add(const Ball& to_push) {
//	_ball_vec.push_back(to_push);
//	return *this;
//}
auto MetaballGen::gen() -> GenDyna2d {
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

	GenDyna2d ret(_size_2d.y, std::vector<float>(_size_2d.x, 0.0f));

	IntVec2 pos;
	for (pos.y=0; pos.y<_size_2d.y - i32(1); ++pos.y) {
		for (pos.x=0; pos.x<_size_2d.x - i32(1); ++pos.x) {
			float val = 0.0f;
			for (const auto& ball: _ball_vec) {
				auto diff = FltVec2(ball.pos - pos);
				diff.y = diff.y / ball.size_2d.y * ball.size_2d.x;
				const auto dist2 = (diff.x * diff.x) + (diff.y * diff.y);
				val += (ball.size_2d.x * ball.size_2d.x) / dist2;
			}
			ret.at(pos.y).at(pos.x) = val;
		}
	}

	return ret;
}
//--------
} // namespace game_engine
} // namespace dunwich_sandgeon
