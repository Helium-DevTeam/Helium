export module Helium.Commands.CommandLiteral.CommandStringLiteral;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

import <string>;

export namespace helium::commands {
	class CommandStringLiteral
		: public CommandBase<CommandStringLiteral>, details::TagCommandLiteral {
	private:
		std::string string_literal_;
	public:
		constexpr CommandStringLiteral(std::string_view string_literal) : string_literal_(string_literal) 
		{}
	};
}