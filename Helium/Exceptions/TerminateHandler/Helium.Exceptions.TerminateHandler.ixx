module;

#define BACKWARD_HAS_DWARF 1
#include <backward.hpp>

export module Helium.Exceptions.TerminateHandler;

import <exception>;
import <print>;
import <stacktrace>;
import <source_location>;

namespace helium::exceptions
{
	backward::SignalHandling sh;
}