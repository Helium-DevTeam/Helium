/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Config.Test;

export namespace helium::config::test
{
	using namespace boost::ut;

	auto testModule() -> void
	{
		"Helium.Config Module Test #1"_test = []
		{
			expect(true);
		};
	}
}