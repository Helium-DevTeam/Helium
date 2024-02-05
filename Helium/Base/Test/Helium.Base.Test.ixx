module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Base.Test;

export namespace helium::base::test
{
	using namespace boost::ut;

	auto testModule() -> void
	{
		"Helium.Base Module Test #1"_test = []
		{
			expect(true);
		};
	}
}