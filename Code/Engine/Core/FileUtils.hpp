//----------------------------------------------------------------------------------------------------
// FileUtils.hpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once
#include <vector>

#include "StringUtils.hpp"

//----------------------------------------------------------------------------------------------------
bool FileReadToBuffer(std::vector<uint8_t>& out_buffer, String const& fileName);
bool FileReadToString(String& out_string, String const& fileName);
