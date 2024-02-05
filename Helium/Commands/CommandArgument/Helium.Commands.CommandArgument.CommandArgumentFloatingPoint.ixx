/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#include <proxy/proxy.h>

export module Helium.Commands.CommandArgument.CommandArgumentFloatingPoint;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

import <concepts>;
import <limits>;
import <memory>;
import <string>;

export namespace helium::commands {
	template <concepts::IsFloatingPoint FPType_>
	struct FloatingPointMax { FPType_ max = std::numeric_limits<FPType_>::max(); };

	template <concepts::IsFloatingPoint FPType_>
	struct FloatingPointMin { FPType_ min = std::numeric_limits<FPType_>::min(); };

	template <concepts::IsFloatingPoint FPType_>
	class FloatingPointBound
	{
	public:
		using FloatingPointType = FPType_;
		using FloatingPointMaxType = FloatingPointMax<FloatingPointType>;
		using FloatingPointMinType = FloatingPointMin<FloatingPointType>;

	private:
		FloatingPointMaxType max_{};
		FloatingPointMinType min_{};

	public:
		constexpr explicit FloatingPointBound(FloatingPointMaxType max, FloatingPointMinType min) : max_(max), min_(min)
		{}
		constexpr explicit FloatingPointBound(FloatingPointMinType min) : FloatingPointBound(FloatingPointMaxType{}, min)
		{}
		constexpr explicit FloatingPointBound(FloatingPointMaxType max) : FloatingPointBound(max, FloatingPointMinType{})
		{}
		constexpr explicit FloatingPointBound(FloatingPointMinType min, FloatingPointMaxType max) : FloatingPointBound(max, min) 
		{}
		constexpr explicit FloatingPointBound() : FloatingPointBound(FloatingPointMaxType{}, FloatingPointMinType{})
		{}
	};

	template <concepts::IsFloatingPoint FPType_>
	class CommandArgumentFloatingPoint
		: public CommandBase<CommandArgumentFloatingPoint<FPType_>>, public details::TagCommandArgument {
	public:
		using FloatingPointType = FPType_;
		using FloatingPointBoundType = FloatingPointBound<FloatingPointType>;
		using super = CommandBase<CommandArgumentFloatingPoint<FloatingPointType>>;

	private:
		FloatingPointBoundType bound_;
		std::shared_ptr<CommandNodeDescriptor> node_descriptor_;

	public:
		auto getNodeDescriptor() const -> std::weak_ptr<CommandNodeDescriptor> { 
			return this->node_descriptor_; 
		}
		auto setParentNode(std::weak_ptr<CommandNodeDescriptor> parent) -> void { 
			if(auto ptr = parent.lock()) {
				this->node_descriptor_->parent_node = ptr; 
			}
		}
		auto addChildNode(std::weak_ptr<CommandNodeDescriptor> child) -> void {
			if(auto ptr = child.lock()) {
				this->node_descriptor_->child_nodes.insert(ptr);
			}
		}

		auto tryAcceptCommand(std::string_view cmd) -> void {

		}

		CommandArgumentFloatingPoint(FloatingPointBound<FloatingPointType> bound)
			:
			bound_(bound),
			node_descriptor_(std::make_shared<CommandNodeDescriptor>())
		{
			this->node_descriptor_->self = pro::make_proxy<poly::CommandNodeFacade>(*this);
		}
	};
}