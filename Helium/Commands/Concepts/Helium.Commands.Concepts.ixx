/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

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

	template <typename StrType_>
	concept IsStdString = 
		std::same_as<StrType_, std::string> or
		std::same_as<StrType_, std::wstring> or
		std::same_as<StrType_, std::u8string> or
		std::same_as<StrType_, std::u16string> or
		std::same_as<StrType_, std::u32string> or
		std::same_as<StrType_, std::pmr::string> or
		std::same_as<StrType_, std::pmr::wstring> or
		std::same_as<StrType_, std::pmr::u8string> or
		std::same_as<StrType_, std::pmr::u16string> or
		std::same_as<StrType_, std::pmr::u32string>;

	template <typename StrType_>
	struct IsStringTypeTrait : std::conditional_t<IsStdString<StrType_>, std::true_type, std::false_type> {};

	template <typename StrType_>
	constexpr bool IsStringTypeTraitV = IsStringTypeTrait<StrType_>::value;
}

export namespace helium::commands::concepts {
	template <typename Command_>
	concept IsCommandBase = std::derived_from<Command_, CommandBase<Command_>>;

	template <typename Command_>
	concept IsCommandLiteral = std::derived_from<Command_, details::TagCommandLiteral>;

	template <typename Command_>
	concept IsCommandArgument = std::derived_from<Command_, details::TagCommandArgument>;

	template <typename FPType_>
	concept IsFloatingPoint = details::IsFloatingPointTypeTraitV<FPType_>;
	
	template <typename IType_>
	concept IsInteger = details::IsIntegerTypeTraitV<IType_>;

	template <typename StrType_>
	concept IsString = details::IsStringTypeTraitV<StrType_>;
}