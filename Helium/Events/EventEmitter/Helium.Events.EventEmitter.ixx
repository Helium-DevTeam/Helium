/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

module;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
	#define BOOST_UUID_RANDOM_PROVIDER_FORCE_WINCRYPT
#endif

#include <boost/mp11.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

export module Helium.Events.EventEmitter;

import <compare>;
import <algorithm>;
import <concepts>;
import <type_traits>;
import <string>;

import Helium.Events.Concepts;
import Helium.Events.EventEmitterPolicy;

export namespace helium::events::internal {
	template 
		<
			EventEmitterPolicy _Policy,
			typename _MixinRoot
		>
	class EventEmitterBase
	{
	protected:
		using ThisType = EventEmitterBase<_Policy, _MixinRoot>;

		using MixinRoot = typename std::conditional_t<
			std::same_as<_MixinRoot, void>,
			ThisType,
			_MixinRoot
		>;

		using Policy = _Policy;

		using Mixins = typename SelectMixins<
			Policy,
			internal::hasTypeMixins<Policy>()
		>::Type;

	public:
		EventEmitterBase() = default;
		EventEmitterBase(EventEmitterBase const& that) = default;
		EventEmitterBase(EventEmitterBase && that) noexcept = default;
		auto operator=(EventEmitterBase const& that) -> EventEmitterBase& = default;
		auto operator=(EventEmitterBase && that) noexcept -> EventEmitterBase& = default;
	};
}

export namespace helium::events {
	template <EventEmitterPolicy _Policy>
	class EventEmitter
		: public 
		internal::InheritFromMixins<
			internal::EventEmitterBase<_Policy, void>, 
			typename internal::SelectMixins<_Policy, internal::hasTypeMixins<_Policy>()>::Type
		>::Type 
	{
	private:
		using super = internal::InheritFromMixins<
			internal::EventEmitterBase<_Policy, void>, 
			typename internal::SelectMixins<_Policy, internal::hasTypeMixins<_Policy>()>::Type
		>::Type;
	public:
		using super::super;
	};

	template <typename Base> struct A : public Base 
	{
		using super = Base;
		int a() { return 0; };
	};
	template <typename Base> struct B : public Base 
	{
		using super = Base;
		double b() { return 1.0f; };
	};
	template <typename Base> struct C : public Base 
	{
		using super = Base;
		bool c() { return true; };
	};
	struct MyPolicy {
		using Mixins = EventEmitterMixinList<A, B, C>;
	};

	void foo() {
		EventEmitter<MyPolicy> emitter;
		//emitter.a();
	}
}