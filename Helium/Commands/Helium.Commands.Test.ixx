module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Commands.Test;

export import Helium.Commands.CommandArgument;
export import Helium.Commands.CommandBase;
export import Helium.Commands.CommandDispatcher;
export import Helium.Commands.CommandLiteral;
export import Helium.Commands.Concepts;

namespace helium::commands::test {
	using namespace boost::ut;

	auto testModule() -> void {
		"Helium.Command Module Test #1"_test = [] {
			CommandDispatcher dispatcher;

			dispatcher.registerCommand(
				CommandStringLiteral{"awa"}.then(
					CommandStringLiteral{"owo"}.then(
						CommandArgumentInteger<std::uint64_t>{}
					)
				)
			);
		};
	}
}