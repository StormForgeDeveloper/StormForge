////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio service
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Service/SFService.h"

namespace SF
{
    // base classes
    class AudioDevice
    {
    public:
        AudioDevice() = default;
        virtual ~AudioDevice() = default;
    };


    class AudioRecorder
    {
    public:
        AudioRecorder() = default;
        virtual ~AudioRecorder() = default;
    };


    class AudioPlayer
    {
    public:
        AudioPlayer() = default;
        virtual ~AudioPlayer() = default;
    };


    // Audio service interface
    class AudioService
    {
    public:
        AudioService() = default;
        virtual ~AudioService() {}


    };


    namespace Service
    {
        extern ServiceInstance<AudioService> Audio;
    }
}
