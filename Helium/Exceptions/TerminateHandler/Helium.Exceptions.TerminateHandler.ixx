module;

#define BACKWARD_HAS_DWARF 1
#include <backward.hpp>

export module Helium.Exceptions.TerminateHandler;

import <exception>;
import <stacktrace>;
import <source_location>;

export namespace helium::exceptions
{	
	auto terminateHandler() -> void
	{
		backward::StackTrace st;
		st.load_here();

		backward::Printer printer;
		printer.address = true;
		printer.object = true;
		printer.snippet = true;
		printer.color_mode = backward::ColorMode::always;
		printer.print(st, stderr);
		
		std::abort();
	}
	auto setupExceptionHandlers() -> void
	{
		backward::SignalHandling sh;
		std::set_terminate(terminateHandler);
	}
}