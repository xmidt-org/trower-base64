# trower-base64

C implementation of base64 encode/decode.

[![Build Status](https://travis-ci.org/Comcast/trower-base64.svg?branch=master)](https://travis-ci.org/Comcast/trower-base64) [![codecov.io](http://codecov.io/github/Comcast/trower-base64/coverage.svg?branch=master)](http://codecov.io/github/Comcast/trower-base64?branch=master)
[![coverity](https://img.shields.io/coverity/scan/17585.svg)](https://scan.coverity.com/projects/trower-base64)

This is a fork of the implementation Bob Trower produced and released in 2001.
You can find the original here: http://base64.sourceforge.net/

# Why fork?

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
