/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#include <proxy/proxy.h>

export module Helium.Commands.CommandLiteral.CommandStringLiteral;

import Helium.Commands.CommandBase;
import Helium.Commands.Concepts;

import <memory>;
import <string>;

export namespace helium::commands {
	class CommandStringLiteral
		: public CommandBase<CommandStringLiteral>, details::TagCommandLiteral {
	public:
		using super = CommandBase<CommandStringLiteral>;

	private:
		std::string string_literal_;
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
	
		CommandStringLiteral(std::string_view string_literal)
			: 
			string_literal_(string_literal), 
			node_descriptor_(std::make_shared<CommandNodeDescriptor>())
		{
			this->node_descriptor_->self = pro::make_proxy<poly::CommandNodeFacade>(*this);
		}
	};
}