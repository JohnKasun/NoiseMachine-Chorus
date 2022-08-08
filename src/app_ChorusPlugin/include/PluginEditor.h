#pragma once

#include "PluginProcessor.h"
#include "MyLookAndFeel.h"

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:

    enum Dimen_t {
        paramControlWidth = 250,
        paramControlHeight = 250,

        paramLinearSliderWidth = 450,
        paramLinearSliderHeight = 50,
        paramLinearSliderLabelWidth = 50,

        paramLabelHeight = 50
    };

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    MyLookAndFeel mMyLookAndFeel;
    juce::AudioProcessorValueTreeState& mValueTreeState;

    AudioPluginAudioProcessor& processorRef;

    juce::Slider mDepthSlider;
    std::unique_ptr<SliderAttachment> mDepthSliderAttachment;

    juce::Slider mSpeedSlider;
    std::unique_ptr<SliderAttachment> mSpeedSliderAttachment;

    juce::Slider mVoicesSlider;
    std::unique_ptr<SliderAttachment> mVoicesSliderAttachment;

    juce::Slider mWaveformSlider;
    std::unique_ptr<SliderAttachment> mWaveformSliderAttachment;    
    
    juce::Slider mGainSlider;
    std::unique_ptr<SliderAttachment> mGainSliderAttachment;

    juce::Slider mMixSlider;
    std::unique_ptr<SliderAttachment> mMixSliderAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};