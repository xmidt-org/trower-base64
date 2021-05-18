<!--
SPDX-FileCopyrightText: 2016-2021 Comcast Cable Communications Management, LLC
SPDX-License-Identifier: Apache-2.0
-->
# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [v1.1.4]
- Update the license to use SPDX
- Update the build infrastructure

## [v1.1.3]
- Added a more durable release artifact process.
- Fixed a few code smells according to sonarcloud.io

## [v1.1.2] - 2019-01-07
- Added valgrind to travis-ci linux builds
- Fixed output buffer overrun error due to incorrect buffer size answer
- Fixed output buffer overrun error due to limited characters
- Fixed input buffer read overrun error

## [v1.1.1] - 2018-10-18
- Added travis-ci
- Travis build for MacOSX
- Fixed build on Mac and Centos
- Added APIs for base64url buffer sizes
- Uses CTest module to build with test disabled
- Add the trower-base64 directory into the include to fix consumers of this project
- Changed cmake minimum version required from 3.3.2 to 2.8.7

## [v1.1] - 2016-02-15
### Added
- Add base64url decode implementaion
### Changed
- Improve cmake files

## [v1.0] - 2016-02-15
### Added
- Initial creation

## [0.1] - 2016-02-05
### Added
- Initial creation

[Unreleased]: https://github.com/Comcast/trower-base64/compare/v1.1.4...HEAD
[v1.1.4]: https://github.com/Comcast/trower-base64/compare/v1.1.3...v1.1.4
[v1.1.3]: https://github.com/Comcast/trower-base64/compare/v1.1.2...v1.1.3
[v1.1.2]: https://github.com/Comcast/trower-base64/compare/v1.1.1...v1.1.2
[v1.1.1]: https://github.com/Comcast/trower-base64/compare/v1.1...v1.1.1
[v1.1]: https://github.com/Comcast/trower-base64/compare/v1.0...v1.1
[v1.0]: https://github.com/Comcast/trower-base64/compare/3e997140737790d284de03a5ef6f497798673750...v1.0
