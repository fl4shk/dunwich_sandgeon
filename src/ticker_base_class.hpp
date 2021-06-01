// This file is part of Dungwich Sandeon.
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

#ifndef src_ticker_base_class_hpp
#define src_ticker_base_class_hpp

// src/ticker_base_class.hpp

#include "misc_includes.hpp"

namespace dungwich_sandeon
{

// A base class for a class that has its `tick()` function run on every
// iteration of the main loop.
class TickerBase
{
public:		// functions
	TickerBase() = default;
	virtual ~TickerBase() = default;

	virtual void tick() = 0;
};

} // namespace dungwich_sandeon

#endif		// src_ticker_base_class_hpp