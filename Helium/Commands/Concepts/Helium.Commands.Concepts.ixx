module;

#include <proxy/proxy.h>

export module Helium.Commands.Concepts;

import <concepts>;
import <type_traits>;
import <string>;

namespace helium::commands {
	template <typename Derived>
	class CommandBase;
}

export namespace helium::commands::poly {
	PRO_DEF_MEMBER_DISPATCH(tryAcceptCommand, void(std::string_view));
	PRO_DEF_FACADE(CommandNodeFacade, tryAcceptCommand);
}

export namespace helium::commands::details {
	struct TagCommandLiteral {};
	struct TagCommandArgument {};

	//If you want to make your own fp/integer type work with Helium's Command modules
	//then you must specialize the following fp/integer type traits for your own types.
	//Specializing the standard type traits would mostly work, but strongly discouraged.
	//Because according to the C++ standard, programs that contains any user 
	//specializations of the standard type traits would have undefined behaviors.
	template <typename FPType_>
	struct IsFloatingPointTypeTrait : std::conditional_t<std::floating_point<FPType_>, std::true_type, std::false_type> {};

	template <typename FPType_>
	constexpr bool IsFloatingPointTypeTraitV = IsFloatingPointTypeTrait<FPType_>::value;

	template <typename IType_>
	struct IsIntegerTypeTrait : std::conditional_t<std::integral<IType_>, std::true_type, std::false_type> {};

	template <typename IType_>
	constexpr bool IsIntegerTypeTraitV = IsIntegerTypeTrait<IType_>::value;
}

export namespace helium::commands::concepts {
	template <typename Command>
	concept IsCommandBase = std::derived_from<Command, CommandBase<Command>>;

	template <typename Command>
	concept IsCommandLiteral = std::derived_from<Command, details::TagCommandLiteral>;

	template <typename Command>
	concept IsCommandArgument = std::derived_from<Command, details::TagCommandArgument>;

	template <typename FPType_>
	concept IsFloatingPoint = details::IsFloatingPointTypeTraitV<FPType_>;
	
	template <typename IType_>
	concept IsInteger = details::IsIntegerTypeTraitV<IType_>;
}