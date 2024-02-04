module;

#include <proxy/proxy.h>

export module Helium.Commands.CommandArgument.CommandArgumentFloatingPoint;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

import <concepts>;
import <memory>;
import <string>;

export namespace helium::commands {
	template<concepts::IsFloatingPoint FPType_>
	class CommandArgumentFloatingPoint
		: public CommandBase<CommandArgumentFloatingPoint<FPType_>>, public details::TagCommandArgument {
	public:
		using FloatingPointType = FPType_;
		using super = CommandBase<CommandArgumentFloatingPoint<FloatingPointType>>;

	private:
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

		CommandArgumentFloatingPoint()
			:
			node_descriptor_(std::make_shared<CommandNodeDescriptor>())
		{
			this->node_descriptor_->self = pro::make_proxy<poly::CommandNodeFacade>(*this);
		}
	};
}