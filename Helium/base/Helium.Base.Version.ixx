export module Helium.Base.Version;

import <neargye/semver.hpp>;

export namespace helium::version {
	constexpr semver::version helium_version{0, 0, 1, semver::prerelease::alpha, 0};
}