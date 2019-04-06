#!/bin/bash


SF_PATH=$(dirname "$0")

git clone https://github.com/blue3k/ATFClone.git $SF_PATH..\ATF


git clone https://github.com/blue3k/StormForge3rdParties.git $SF_PATH/../StormForge3rdParties

ln -s $SF_PATH/../StormForge3rdParties/3rdParties $SF_PATH/3rdParties 


