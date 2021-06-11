<!--
SPDX-FileCopyrightText: 2016-2021 Comcast Cable Communications Management, LLC
SPDX-License-Identifier: Apache-2.0
-->
# trower-base64

C implementation of base64 encode/decode.

[![Build Status](https://github.com/xmidt-org/trower-base64/workflows/CI/badge.svg)](https://github.com/xmidt-org/trower-base64/actions)
[![codecov.io](http://codecov.io/github/xmidt-org/trower-base64/coverage.svg?branch=master)](http://codecov.io/github/xmidt-org/trower-base64?branch=master)
[![coverity](https://img.shields.io/coverity/scan/23253.svg)](https://scan.coverity.com/projects/xmidt-org-trower-base64)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=xmidt-org_trower-base64&metric=alert_status)](https://sonarcloud.io/dashboard?id=xmidt-org_trower-base64)
[![Language Grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/xmidt-org/trower-base64.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/xmidt-org/trower-base64/context:cpp)
[![GitHub release](https://img.shields.io/github/release/xmidt-org/trower-base64.svg)](CHANGELOG.md)

This started as a fork of the implementation Bob Trower produced and released in
2001.  You can find the original here: http://base64.sourceforge.net/

## Why fork?

As we started using the library we found it was hugely handy, but had a few bugs
and not as many tests as we wanted.  As the upstream project seems to have lost
steam, we decided to fork, improve, release and ship.

# Building and Testing Instructions

```
mkdir build
cd build
cmake ..
make
make test
make coverage
firefox index.html
