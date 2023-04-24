// Algorithm test.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "MemoryManager/SFStackHeap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFToString.h"
#include "Container/SFArray.h"
#include "UnitTest_Audio.h"
#include "Audio/SFAudioService.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


TEST_F(AudioTest, Enumeration)
{
    String defaultPlayDeviceName = Service::Audio->GetDefaultDeviceName(true);
    String defaultRecordingDeviceName = Service::Audio->GetDefaultDeviceName(false);
    SFLog(Game, Info, "Default device, play:'{0}', recording:'{1}'", defaultPlayDeviceName, defaultRecordingDeviceName);

    DynamicArray<String> devices;

    Result hr = Service::Audio->GetDeviceList(true, devices);
    EXPECT_TRUE(hr);
    SFLog(Game, Info, "Play devices");
    for (const String& deviceName : devices)
    {
        SFLog(Game, Info, "\t{0}", deviceName);
    }


    devices.Reset();
    hr = Service::Audio->GetDeviceList(false, devices);
    EXPECT_TRUE(hr);
    SFLog(Game, Info, "Recording devices");
    for (const String& deviceName : devices)
    {
        SFLog(Game, Info, "\t{0}", deviceName);
    }
}

TEST_F(AudioTest, Initialization)
{
    Result hr = Service::Audio->SetPlaybackDevice(Service::Audio->GetDefaultDeviceName(true));
    EXPECT_TRUE(hr);

    AudioRecorderPtr recorder = Service::Audio->CreateRecorder(Service::Audio->GetDefaultDeviceName(false));
    EXPECT_TRUE(recorder.IsValid());

    hr = recorder->Initialize(1, EAudioFormat::Float, 44100);
    EXPECT_TRUE(hr);

    hr = recorder->StartRecording();
    EXPECT_TRUE(hr);

    hr = recorder->StopRecording();
    EXPECT_TRUE(hr);

    recorder->Dispose();
}


static void ApplySin(Array<float>& data, double magnitude, uint srate, uint freq)
{
    double smps_per_cycle = (double)srate / freq;
    for (uint i = 0; i < srate; i++)
    {
        double integral;
        double fraction = modf(i / smps_per_cycle, &integral);
        data[i] += (float)(sin(fraction * 2.0 * M_PI) * magnitude);
    }
}


TEST_F(AudioTest, Playback)
{
    Result hr;
    uint recordingDurationSec = 10;
    uint samplesPerSec = 44100;
    uint numChannels = 1;
    EAudioFormat format = EAudioFormat::Float;
    size_t sampleFrameSize = Audio::GetBytesPerSample(numChannels, format);
    size_t dataSizePerSec = samplesPerSec * sampleFrameSize;

    DynamicArray<float> testBuffer;
    testBuffer.resize(recordingDurationSec * samplesPerSec);
    memset(testBuffer.data(), 0, testBuffer.capacity());

    ApplySin(testBuffer, 50.0, recordingDurationSec * samplesPerSec, recordingDurationSec / 2);

    SFLog(Game, Info, "Playing sin wave");

    Service::Audio->GetListener()->SetGain(2);

    AudioBufferPtr audioBuffer = Service::Audio->CreateBuffer(numChannels, format, samplesPerSec, testBuffer.size());
    AudioSourcePtr player = Service::Audio->CreateSource(audioBuffer);
    player->SetGain(10);
    player->Play();

    for (size_t dataOffset = 0; dataOffset < testBuffer.size(); dataOffset += samplesPerSec)
    {
        audioBuffer->EnqueueBlock(ArrayView<uint8_t>(dataSizePerSec, reinterpret_cast<uint8_t*>(testBuffer.data() + dataOffset)));
    }

    ThisThread::SleepFor(DurationMS(recordingDurationSec * 1000));

    player->Stop();

    SFLog(Game, Info, "Playing sin wave finished");
}

TEST_F(AudioTest, RecordingNPlayback)
{
    Result hr;
    DynamicArray<String> devices;
    uint samplesPerSec = 44100;
    uint numChannels = 1;
    EAudioFormat format = EAudioFormat::Float;
    size_t sampleFrameSize = Audio::GetBytesPerSample(numChannels, format);
    size_t dataSizePerSec = samplesPerSec * sampleFrameSize;

    AudioRecorderPtr recorder = Service::Audio->CreateRecorder(Service::Audio->GetDefaultDeviceName(false));
    EXPECT_TRUE(recorder.IsValid());

    hr = recorder->Initialize(numChannels, format, samplesPerSec);
    EXPECT_TRUE(hr);

    hr = recorder->StartRecording();
    EXPECT_TRUE(hr);

    SFLog(Game, Info, "Recording started");

    uint recordingDurationSec = 20;
    DynamicArray<uint8_t> testBuffer;
    testBuffer.reserve(recordingDurationSec * recorder->GetSamplesPerSec() * recorder->GetSampleFrameSize());
    memset(testBuffer.data(), 0, testBuffer.capacity());
    auto startTime = Util::Time.GetRawTimeMs();
    while (Util::TimeSinceRaw(startTime) < DurationMS(recordingDurationSec * 1000))
    {
        hr = recorder->ReadSamples(testBuffer);
        EXPECT_TRUE(hr);
    }

    SFLog(Game, Info, "Recording finished");

    hr = recorder->StopRecording();
    EXPECT_TRUE(hr);

    recorder->Dispose();

    SFLog(Game, Info, "Playback recording");

    Service::Audio->GetListener()->SetGain(2);

    AudioBufferPtr audioBuffer = Service::Audio->CreateBuffer(numChannels, format, samplesPerSec, testBuffer.size());
    AudioSourcePtr player = Service::Audio->CreateSource(audioBuffer);
    player->SetGain(10);
    player->Play();

    for (size_t dataOffset = 0; (dataOffset + dataSizePerSec) <= testBuffer.size(); dataOffset += dataSizePerSec)
    {
        audioBuffer->EnqueueBlock(ArrayView<uint8_t>(dataSizePerSec, reinterpret_cast<uint8_t*>(testBuffer.data()) + dataOffset));
    }

    SFLog(Game, Info, "Waiting Playback");

    ThisThread::SleepFor(DurationMS(recordingDurationSec * 1000));

    player->Stop();
}
