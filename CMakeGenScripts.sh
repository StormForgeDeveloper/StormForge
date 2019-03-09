#!/bin/bash


export GENCMAKE=./Bin/SFConvertVSProj2CMake.exe



$GENCMAKE +in=Engine/Src/SFCore/SFCore.vcxitems  +makein=Engine/Src/SFCore/CMakeList.in
$GENCMAKE +in=Engine/Src/SFEngine/SFEngine.vcxitems  +makein=Engine/Src/SFEngine/CMakeList.in
$GENCMAKE +in=Engine/Src/Protocol/SFProtocol.vcxitems  +makein=Engine/Src/Protocol/CMakeList.in



echo Done

read -n1 -r -p "Press space to continue..." key
