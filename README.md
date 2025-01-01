
| Winows | [![Build Status](http://dev-build.fishing-on.com:8080/buildStatus/icon?job=StormForge%2FCodeCI_Win)](http://dev-build.fishing-on.com:8080/buildStatus/icon?job=StormForge%2FCodeCI_Win) |
| Linux | [![Build Status](http://dev-build.fishing-on.com:8080/buildStatus/icon?job=StormForge%2FCodeCI_Linux)](http://dev-build.fishing-on.com:8080/job/StormForge/job/CodeCI_Linux/) |
 


# StormForge

StormForge is a base system for game which is supporting Windows, Android, and working on Linux support.
For now the development is still going on and have many missing modules, however, it has system wrapper with useful middle wares, implementations of algorithms and tools. On one day, I hope it became a nice in-house engine.

# Prerequisites
1. Linux sub system for WIndows. 
	- It's tested on Ubuntu 24.02 with dotnet8.
1. Visual Studio 2022 with dotnet 6. 
1. CMake 3.27.1 or later
1. VulkanSDK

We have moved onto vcpkg for 3rdparty libraries. Only few left for custom build.


For now, StormForge has,
1. Hierarchical Memory management. Hierarchical memory management gives you better track of memory ownership so that you can easily track down memory leak and usage. See memory management article.
1. Component based engine module management.
1. Basic functions for wrapped interface or safe string operations.
1. Shared pointer/object with detained release.
1. FixedString with db generation. Still need to work on on VS debugger plugin.
1. Thread library with lock free algorithm support.
1. Generic container implementations.
1. Lock free container implementations.
1. File system wrapper. File device virtualization still need to be done, but simple access include buffered access has done.
1. Data packaging system. Still working on tools and stuffs.
1. LOG system.
1. Asynchronous task management system.
1. 3D Math with SIMD support.
1. Engine object with sync/async tick management.
1. Fully implemented network system including P2P, Relay, and massive multiplayer connection management. UDP and TCP
1. Supporting Zookeeper connection for dev/rel support.
1. UnitTest with gtest
1. Websocket support
1. Kafka Stream interface



Check wiki for more other details for build and setup

https://github.com/blue3k/StormForge/wiki




