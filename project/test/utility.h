////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 4/12/2020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../error.h"
#include "../exception_handler.h"
#include <string>
#include <boost/dll/runtime_symbol_info.hpp>

namespace testutility
{
	static std::string RuleSampleFilePath(const std::string& file_name)
	{
		boost::filesystem::path boost_path = boost::dll::program_location().parent_path();
		std::string path_string(boost_path.string());
		return path_string + file_name;
	}
}