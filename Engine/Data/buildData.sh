#!/bin/bash

pushd Protocol

make -f makefile.mak $1

popd

pushd ProtocolDef

make -f makefile.mak $1

popd


pushd ResultCode

make -f makefile.mak $1

popd

