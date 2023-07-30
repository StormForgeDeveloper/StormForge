#!/bin/bash

#This is only for c# referencing

if [ ! -d "flatbuffers" ]; then
	git clone https://github.com/google/flatbuffers.git
else
	cd flatbuffers && git pull
fi


