export module Helium.Commands.CommandBase;

import Helium.Commands.Concepts;

import <utility>;

namespace helium::commands::details {
	template <typename Derived>
	class CRTPHelper {
	public:
		auto underlyingClass() -> Derived& { return static_cast<Derived&>(*this); }
		auto underlyingClass() const -> Derived const& { return static_cast<Derived const&>(*this); }
	};
}

export namespace helium::commands {	
	template <typename Derived>
	class CommandBase : public details::CRTPHelper<Derived> {
	public:
		template <typename Next>
		[[nodiscard]] constexpr auto then(Next&& next_node) && {
			return Derived(std::move(this->underlyingClass()));
		}

		template <std::invocable Callback>
			requires concepts::IsCommandArgument<Derived>
		[[nodiscard]] constexpr auto execute(Callback&& callback) && {
			return Derived(std::move(this->underlyingClass()));
		}
	};
}