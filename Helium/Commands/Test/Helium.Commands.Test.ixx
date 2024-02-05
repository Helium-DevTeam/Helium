/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Commands.Test;

export import Helium.Commands.CommandArgument;
export import Helium.Commands.CommandBase;
export import Helium.Commands.CommandDispatcher;
export import Helium.Commands.CommandLiteral;
export import Helium.Commands.Concepts;
export import Helium.Commands.Lexer;

import <print>;

export namespace helium::commands::test {
	using namespace boost::ut;
	
	auto testModule() -> void {
		"Helium.Command Module Test #1"_test = [] {
			CommandDispatcher dispatcher;
			CommandLexer<std::string> lex;
			lex.parseCommand("#helium set true get -135 awa 157.22 -12654.123.59");
			expect(lex.isParsed());

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