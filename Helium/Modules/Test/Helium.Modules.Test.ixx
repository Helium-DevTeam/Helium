/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Modules.Test;

export namespace helium::modules::test
{
	using namespace boost::ut;

	auto testModule() -> void
	{
		"Helium.Modules Module Test #1"_test = []
		{
			expect(true);
		};
	}
}