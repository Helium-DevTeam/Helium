module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Commands.Test;

export import Helium.Commands.CommandArgument;
export import Helium.Commands.CommandBase;
export import Helium.Commands.CommandDispatcher;
export import Helium.Commands.CommandLiteral;
export import Helium.Commands.Concepts;

import <print>;

namespace helium::commands::test {
	using namespace boost::ut;

	auto testModule() -> void {
		"Helium.Command Module Test #1"_test = [] {
			CommandDispatcher dispatcher;

			dispatcher.registerCommand(
				CommandStringLiteral{"#helium"}.then(
					CommandStringLiteral{"user"}.then(
						CommandArgumentInteger<std::uint64_t>{}.require(
							[]() { 
								return true; 
							}
						).execute(
							[]() { 
								std::println("awa"); 
							}
						)
					)
				).then(
					CommandStringLiteral{"event"}.then(
						CommandArgumentInteger<std::uint64_t>{}.execute(
							[]() { 
								std::println("owo"); 
							}
						)
					)
				)
			);
		};
	}
}