export module Helium.Commands.Concepts;

import <concepts>;

namespace helium::commands {
	template <typename Derived>
	class CommandBase;
}

export namespace helium::commands::details {
	struct TagCommandLiteral {};
	struct TagCommandArgument {};
}

export namespace helium::commands::concepts {
	template <typename Command>
	concept IsCommandBase = std::derived_from<Command, CommandBase<Command>>;

	template <typename Command>
	concept IsCommandLiteral = std::derived_from<Command, details::TagCommandLiteral>;

	template <typename Command>
	concept IsCommandArgument = std::derived_from<Command, details::TagCommandArgument>;
}