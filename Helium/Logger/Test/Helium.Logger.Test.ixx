module;

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Helium.Logger.Test;

export namespace helium::logger::test
{
	using namespace boost::ut;

	auto testModule() -> void
	{
		"Helium.Logger Module Test #1"_test = []
		{
			expect(true);
		};
	}
}