module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Utils.Test;

export namespace helium::utils::test
{
	using namespace boost::ut;

	auto testModule() -> void
	{
		"Helium.Utils Module Test #1"_test = []
		{
			expect(true);
		};
	}
}