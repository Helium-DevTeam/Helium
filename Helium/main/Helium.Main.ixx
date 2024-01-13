module;

export module Helium.Main;

export import Helium.Base;
export import Helium.Config;
export import Helium.Events;
export import Helium.Logger;
export import Helium.Modules;
export import Helium.Utils;

import <print>;
import <string>;

helium::logger::Logger logger = helium::logger::Logger::getLogger("Helium++");

export auto main(int argc, const char* argv[]) -> int {
	return 0;
}
