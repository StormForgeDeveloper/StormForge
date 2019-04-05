#!/bin/bash






cd Protocol

make -f makefile.mak $1

cd ..

#cp ./Temp/Lib/Protocol/CSharp/*.cs ../../../../../Conspiracy/trunk/Client/Conspiracy/Conspiracy/Net/Message

cd ResultCode

make -f makefile.mak $1

cd ..



