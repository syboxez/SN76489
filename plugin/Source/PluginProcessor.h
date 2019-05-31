/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sms_Apu.h"
#include "Stereo_Buffer.h"

//==============================================================================
/**
*/
class SN76489AudioProcessorEditor;
class SN76489AudioProcessor : public gin::GinProcessor
{
public:
    //==============================================================================
    SN76489AudioProcessor();
    ~SN76489AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    
    static const char* paramPulse1Level;
    static const char* paramPulse2Level;
    static const char* paramPulse3Level;
    static const char* paramNoiseLevel;
    static const char* paramNoiseWhite;
    static const char* paramNoiseShift;

    void setEditor (SN76489AudioProcessorEditor* editor_)
    {
        ScopedLock sl (editorLock);
        editor = editor_;
    }

private:
    void runUntil (int& done, AudioSampleBuffer& buffer, int pos);
    
    int lastNote = -1;
    int velocity = 0;
    Array<int> noteQueue;
    
    LinearSmoothedValue<float> outputSmoothed;
    CriticalSection editorLock;
    SN76489AudioProcessorEditor* editor = nullptr;
    
    Sms_Apu apu;
    Stereo_Buffer buf;
    const long clocks_per_sec = 3579545;
    
    struct ChannelInfo
    {
        int note = -1;
        int velocity = 0;
        bool dirty = false;
    };
    
    ChannelInfo channelInfo[3];
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SN76489AudioProcessor)
};
