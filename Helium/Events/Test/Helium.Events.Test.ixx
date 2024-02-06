/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Events.Test;

import <print>;

export namespace helium::events::test
{
	using namespace boost::ut;

	auto testModule() -> void
	{
		boost::ut::test("Helium.Events Module Test #1") = []
		{
			expect(true);
		};
	}
}