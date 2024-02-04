export module Helium.Commands.CommandArgument.CommandArgumentQuotedString;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

export namespace helium::commands {
	class CommandArgumentQuotedString
		: public CommandBase<CommandArgumentQuotedString>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentQuotedString>;
	};
}