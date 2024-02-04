module;

#include <boost/cobalt.hpp>

export module Helium.Main;

export import Helium.Base;
export import Helium.Commands;
export import Helium.Config;
export import Helium.Events;
export import Helium.Logger;
export import Helium.Modules;
export import Helium.Utils;

import <variant>;

namespace cob = boost::cobalt;

namespace helium::main {
	//auto logger = logger::Logger::getLogger("MainThread");
}

export namespace helium::main {
	auto heliumMain(int argc, const char* argv[]) 
		-> cob::task<int> {
		co_return 0;
	}
}

export auto main(int argc, const char* argv[]) 
	-> int {
	return cob::run(helium::main::heliumMain(argc, argv));
}
