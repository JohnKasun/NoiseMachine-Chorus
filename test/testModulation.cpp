#pragma once

#include <memory>
#include <vector>

#include "catch.hpp"
#include "ErrorDef.h"
#include "Synthesis.h"
#include "CatchUtil.h"
#include "Vector.h"
#include "ModulationIf.h"

TEST_CASE("Flanger") {
	auto sampleRate = float{ 44100 };
	auto numSamples = int{ 10000 };
	auto flanger = std::make_unique<ModulationIf>();
	flanger->init(sampleRate, ModulationIf::Type::Flanger);
	auto inputBuffer = std::make_unique<float[]>(numSamples);
	auto outputBuffer = std::make_unique<float[]>(numSamples);
	auto groundBuffer = std::make_unique<float[]>(numSamples);
	auto depthParam = float{ 0 };
	auto speedParam = float{ 0 };
	SECTION("Zero Depth") {
		speedParam = 1;
		CSynthesis::generateSine(inputBuffer.get(), 440, sampleRate, numSamples);
		auto delayInSamp = int{ CUtil::float2int<int>(20.0f * sampleRate / 1000) / 2};
		CVectorFloat::copy(groundBuffer.get(), inputBuffer.get(), numSamples);
		CVectorFloat::add_I(groundBuffer.get() + delayInSamp, inputBuffer.get(), numSamples - delayInSamp);
		CVectorFloat::mulC_I(groundBuffer.get(), 0.5f, numSamples);
		flanger->setDepth(depthParam);
		flanger->setSpeed(speedParam);
		flanger->process(inputBuffer.get(), outputBuffer.get(), numSamples);
		CatchUtil::compare(outputBuffer.get(), groundBuffer.get(), numSamples);
	}
	SECTION("Zero Speed") {
		depthParam = 20.0f;
		CSynthesis::generateSine(inputBuffer.get(), 440, sampleRate, numSamples);
		CVectorFloat::copy(groundBuffer.get(), inputBuffer.get(), numSamples);
		CVectorFloat::add_I(groundBuffer.get(), inputBuffer.get(), numSamples);
		CVectorFloat::mulC_I(groundBuffer.get(), 0.5f, numSamples);
		flanger->setDepth(depthParam);
		flanger->setSpeed(speedParam);
		flanger->process(inputBuffer.get(), outputBuffer.get(), numSamples);
		CatchUtil::compare(outputBuffer.get(), groundBuffer.get(), numSamples);
	}
	flanger.reset();
	inputBuffer.reset();
	outputBuffer.reset();
	groundBuffer.reset();
}