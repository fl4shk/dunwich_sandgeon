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

#include "input_kind_enum.hpp"

namespace <dunwich_sandgeon>
{

const std::map<InputKind, std::string> INPUT_KIND_TO_STR_MAP
= {
	{InputKind::None, "None"},

	{InputKind::Left, "Left"},
	{InputKind::Up, "Up"},
	{InputKind::Right, "Right"},
	{InputKind::Down, "Down"},

	{InputKind::UpLeft, "UpLeft"},
	{InputKind::UpRight, "UpRight"},
	{InputKind::DownRight, "DownRight"},
	{InputKind::DownLeft, "DownLeft"},

	{InputKind::Escape, "Escape"},
	{InputKind::Enter, "Enter"},

	{InputKind::SwitchWindow, "SwitchWindow"},

	{InputKind::OpenInventoryWindow, "OpenInventoryWindow"},
	{InputKind::OpenMiscActionsWindow, "OpenMiscActionsWindow"},
	{InputKind::OpenSaveWindow, "OpenSaveWindow"},

	{InputKind::BeginAttack, "BeginAttack"},
	{InputKind::BeginRangedAttack, "BeginRangedAttack"},
	{InputKind::BeginThrow, "BeginThrow"},

	{InputKind::Lim, "Lim"},
};

} // namespace <dunwich_sandgeon>
