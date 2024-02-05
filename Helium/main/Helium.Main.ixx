module;

#include <boost/cobalt.hpp>

#include <cxxopts.hpp>

export module Helium.Main;

export import Helium.Base;
export import Helium.Commands;
export import Helium.Config;
export import Helium.Events;
export import Helium.Logger;
export import Helium.Modules;
export import Helium.Utils;

import <format>;
import <variant>;

namespace cob = boost::cobalt;

namespace helium::main {
	//auto logger = logger::Logger::getLogger("MainThread");
}

export namespace helium::main {
	auto heliumMain(int argc, const char* argv[]) 
		-> cob::task<int> {
		cxxopts::Options options{"Helium", "A lightweight extension system for any console applications"};
		options.add_options()
			("t,test", "Execute tests", cxxopts::value<bool>()->default_value("false"))
		;
		options.allow_unrecognised_options();

		auto result = options.parse(argc, argv);

		if(result["test"].as<bool>())
		{
			base::test::testModule();
			commands::test::testModule();
			config::test::testModule();
			events::test::testModule();
			logger::test::testModule();
			modules::test::testModule();
			utils::test::testModule();
		}

		co_return 0;
	}
}

export auto main(int argc, const char* argv[]) 
	-> int {
	return cob::run(helium::main::heliumMain(argc, argv));
}
