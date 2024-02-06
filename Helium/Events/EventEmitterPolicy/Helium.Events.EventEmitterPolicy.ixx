/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

export module Helium.Events.EventEmitterPolicy;

import <concepts>;

import Helium.Events.Concepts;

export namespace helium::events {
	template <template <typename> class ... Mixins>
	struct EventEmitterMixinList
	{};
}

export namespace helium::events::internal {
	template <EventEmitterPolicy Policy>
	consteval auto hasTypeMixins() -> bool {
		if constexpr(requires { Policy::Mixins; }) {
			return true;
		}
		return false;
	}

	template <EventEmitterPolicy Policy, bool>
	struct SelectMixins 
	{
		using Type = Policy::Mixins;
	};
	template <EventEmitterPolicy Policy>
	struct SelectMixins<Policy, false>
	{
		using Type = EventEmitterMixinList<>;
	};

	template 
		<
			typename Base, 
			typename MixinList
		> 
	struct InheritFromMixins;

	template 
		<
			typename Base, 
			template <typename> class T, 
			template <typename> class ... Args
		> 
	struct InheritFromMixins<Base, EventEmitterMixinList<T, Args...>>
	{
		using Type = T<typename InheritFromMixins<Base, EventEmitterMixinList<Args...>>::Type>;
	};

	template <typename Base>
	struct InheritFromMixins<Base, EventEmitterMixinList<>>
	{
		using Type = Base;
	};
}