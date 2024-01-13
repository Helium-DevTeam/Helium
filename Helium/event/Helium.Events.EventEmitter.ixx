module;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
	#define BOOST_UUID_RANDOM_PROVIDER_FORCE_WINCRYPT
#endif

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

export namespace helium::events {
	template 
		<
			EventEmitterPolicy _Policies = EventEmitterPolicyList<>,
			EventEmitterMixin _Mixins = EventEmitterMixinList<>
		>
	class EventEmitterBase 
	{
	protected:
		using ThisType = EventEmitterBase<_Policies, _Mixins>;

		using Policies = _Policies;

		using Mixins = _Mixins;
	};

	template 
		<
			EventEmitterPolicy _Policies = EventEmitterPolicyList<>,
			EventEmitterMixin _Mixins = EventEmitterMixinList<>
		>
	class EventEmitter : public InheritFromMixins<EventEmitterBase<_Policies, _Mixins>, _Mixins>::Type {
	private:
		using super = InheritFromMixins<EventEmitterBase<_Policies, _Mixins>, _Mixins>::Type;
	public:
	};

	template <typename Base> struct A : public Base {int a;};
	template <typename Base> struct B : public Base {double b;};
	template <typename Base> struct C : public Base {bool c;};

	void foo() {
		EventEmitter<EventEmitterPolicyList<>, EventEmitterMixinList<A, B, C>> emitter;
	}
}

/*
export namespace helium::events
{
	template <typename EventType>
	concept Event = requires() {
		{ EventType::getName() }	-> std::convertible_to<std::string>;
	};

	template <typename EventType>
	concept CancellableEvent = Event<EventType> && requires(EventType e, bool b) {
		{ e.isCancelled() }			-> std::same_as<bool>;
		{ e.setCancelled(b) }		-> std::same_as<void>;
		{ e.cancel() }				-> std::same_as<void>;
	};

	template <typename ListenerType, typename EventType>
	concept EventListener = requires(ListenerType l, EventType& e) {
		{ l.handle(e) }				-> std::same_as<void>;
		{ l.getPriority() }			-> std::same_as<std::size_t>;
	};

	class EventManager {
	private:
		struct Handler_ {
			std::size_t priority;
			boost::uuids::uuid uuid;
			std::function<void(std::any)> handler;
			[[nodiscard]] constexpr auto operator<=>(Handler_ const& that) const noexcept -> std::strong_ordering {
				return this->priority <=> that.priority;
			}
		};
		std::unordered_map<std::string, std::vector<Handler_>> event_map_;
		mutable std::mutex mutex_;

		EventManager() = default;

	public:
		using Handle = boost::uuids::uuid;

		[[nodiscard]] static auto getInstance() -> EventManager& {
			static EventManager instance;
			return instance;
		}

		template <Event EventType, EventListener<EventType> ListenerType>
		auto registerEventListener(ListenerType & listener) -> Handle {
			std::lock_guard<std::mutex> lock(this->mutex_);

			Handle listener_handle = boost::uuids::random_generator()();

			this->event_map_[EventType::getName()].push_back(
				Handler_{
					listener.getPriority(),
					listener_handle,
					std::function<void(std::any)>(
						[&listener](std::any event) {
							listener.handle(std::any_cast<EventType&>(event));
						}
					)
				}
			);

			std::ranges::sort(this->event_map_[EventType::getName()], std::less<Handler_>{});

			return listener_handle;
		}

		template <Event EventType>
		auto registerEventListener(std::function<void(EventType&)> const& listener, std::size_t priority = 0) -> Handle {
			std::lock_guard<std::mutex> lock(this->mutex_);

			Handle listener_handle = boost::uuids::random_generator()();

			this->event_map_[EventType::getName()].push_back(
				Handler_{
					priority,
					listener_handle,
					std::function<void(std::any)>(
						[listener](std::any event) {
							listener(std::any_cast<EventType&>(event));
						}
					)
				}
			);

			std::ranges::sort(this->event_map_[EventType::getName()], std::less<Handler_>{});

			return listener_handle;
		}

		template <Event EventType>
		auto unregisterEventListener(Handle const& handle) -> void 
		{
			std::lock_guard<std::mutex> lock(this->mutex_);

			this->event_map_[EventType::getName()] | std::ranges::remove_if(
				[&handle](Handler_ const& event_) {
					if(event_.uuid == handle) {
						return true;
					}
				}
			);
		}

		template <Event EventType>
		auto triggerEvent(EventType & event) -> void {
			for(auto& handler : this->event_map_[EventType::getName()]) {
				handler.handler(event);
				if constexpr(CancellableEvent<EventType>) {
					if(event.isCancelled()) {
						return ;
					}
				}
			}
			return ;
		}
	};
}*/