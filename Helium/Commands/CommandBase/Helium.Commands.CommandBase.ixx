module;

#define FWD(x) ::std::forward<decltype(x)>(x)

#include <proxy/proxy.h>

export module Helium.Commands.CommandBase;

import Helium.Commands.Concepts;

import <memory>;
import <utility>;
import <string>;

import <plf_hive.h>;

namespace helium::commands::details {
	template <typename Derived_>
	class CRTPHelper {
	public:
		using Derived = Derived_;
		auto underlyingClass() -> Derived& { return static_cast<Derived&>(*this); }
		auto underlyingClass() const -> Derived const& { return static_cast<Derived const&>(*this); }
	};
}

export namespace helium::commands {
	struct CommandNodeDescriptor {
		std::shared_ptr<CommandNodeDescriptor> parent_node;
		plf::hive<std::shared_ptr<CommandNodeDescriptor>> child_nodes;
		pro::proxy<poly::CommandNodeFacade> self;
	};

	template <typename Derived_>
	class CommandBase : public details::CRTPHelper<Derived_> {
	public:
		using Derived = Derived_;

		template <typename Next>
		[[nodiscard]] constexpr auto then(Next&& next_node) && {
			FWD(next_node).setParentNode(this->underlyingClass().getNodeDescriptor());
			this->underlyingClass().addChildNode(FWD(next_node).getNodeDescriptor());
			return Derived(std::move(this->underlyingClass()));
		}

		template <std::invocable Callback>
			requires concepts::IsCommandArgument<Derived>
		[[nodiscard]] constexpr auto execute(Callback&& callback) && {
			return Derived(std::move(this->underlyingClass()));
		}

		template <std::invocable Pred>
		[[nodiscard]] constexpr auto require(Pred&& pred) && {
			return Derived(std::move(this->underlyingClass()));
		}
	};
}