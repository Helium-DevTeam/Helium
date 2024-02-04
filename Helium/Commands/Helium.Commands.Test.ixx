module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Commands.Test;

import Helium.Commands.CommandDispatcher;
import Helium.Commands.CommandLiteral;
import Helium.Commands.CommandArgument;

namespace helium::commands::test {
	using namespace boost::ut;

	auto testModule() -> void {
		"Helium.Command Module Test #1"_test = [] {
			CommandDispatcher dispatcher;

			dispatcher.registerCommand(
				CommandStringLiteral{"awa"}.then(
					CommandStringLiteral{"owo"}.then(
						CommandArgumentInteger{}
					)
				)
			);
		};
	}
}