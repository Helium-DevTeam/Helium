module;

#include <proxy/proxy.h>

export module Helium.Commands.CommandArgument.CommandArgumentQuotedString;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

import <memory>;
import <string>;

export namespace helium::commands {
	class CommandArgumentQuotedString
		: public CommandBase<CommandArgumentQuotedString>, public details::TagCommandArgument {
	public:
		using super = CommandBase<CommandArgumentQuotedString>;
	
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

		CommandArgumentQuotedString()
			:
			node_descriptor_(std::make_shared<CommandNodeDescriptor>())
		{
			this->node_descriptor_->self = pro::make_proxy<poly::CommandNodeFacade>(*this);
		}
	};
}