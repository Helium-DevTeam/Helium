/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2024 Helium DevTeam
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 */

module;

//#include <boost/cobalt.hpp>

#include <cxxopts.hpp>

export module Helium.Main;

export import Helium.Base;
export import Helium.Commands;
export import Helium.Config;
export import Helium.Events;
export import Helium.Exceptions;
export import Helium.Logger;
export import Helium.Modules;
export import Helium.Utils;

import <format>;
import <exception>;
import <variant>;

//namespace cob = boost::cobalt;

namespace helium::main {
	//auto logger = logger::Logger::getLogger("MainThread");
}

export namespace helium::main {
	auto heliumMain(int argc, const char* argv[]) 
		-> int {
		cxxopts::Options options{"Helium", "A lightweight extension system for any console applications"};
		options.add_options()
			("runTest", "Execute tests", cxxopts::value<bool>()->default_value("false"))
		;
		options.allow_unrecognised_options();

		auto result = options.parse(argc, argv);
		
		if(result["runTest"].as<bool>())
		{
			base::test::testModule();
			commands::test::testModule();
			config::test::testModule();
			events::test::testModule();
			logger::test::testModule();
			modules::test::testModule();
			utils::test::testModule();
		}
		return 0;
	}
}

export auto main(int argc, const char* argv[]) 
	-> int {
	return helium::main::heliumMain(argc, argv);
}
