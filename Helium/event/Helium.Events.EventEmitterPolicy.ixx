module;

export module Helium.Events.EventEmitterPolicy;

export namespace helium::events {
	template 
		<
			template <typename> class ... Mixins
		>
	struct EventEmitterMixinList
	{};

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
		using Type = T<InheritFromMixins<Base, EventEmitterMixinList<Args...>>>::Type;
	};

	template <typename Base>
	struct InheritFromMixins<Base, EventEmitterMixinList<>>
	{
		using Type = Base;
	};

	template <typename ... Policies>
	struct EventEmitterPolicyList 
	{};
}