/*
 * Helium is an open source software distributed under the MIT license.
 * Please refer to Helium.Main.ixx for full license info.
 */

export module Helium.Base.Version;

import <neargye/semver.hpp>;

export namespace helium::version {
	constexpr semver::version helium_version{0, 0, 1, semver::prerelease::alpha, 0};
}