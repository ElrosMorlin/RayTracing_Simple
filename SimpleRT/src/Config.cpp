#include "Config.hpp"

#include "OpenCLConfig.hpp"


#include "Utility.hpp"

std::unique_ptr<Config> createConfig(int width, int height, SupportType type) {

	switch (type) {

	case SupportType::OpenCL:

		return std::make_unique<OpenCLConfig>(width, height);


	default:
		throw "Error";

	}


}

Config::Config(int width, int height) : mWidth(width), mHeight(height) {
}

void Config::updateRendering() {

	double startTime = WallClockTime();
	int startSampleCount = mCurrentSample;

	setArguments();

	execute();
	++mCurrentSample;


	const double elapsedTime = WallClockTime() - startTime;
	const int samples = mCurrentSample - startSampleCount;
	const double sampleSec = samples * mHeight * mWidth / elapsedTime;
	sprintf(pCaptionBuff, "Rendering time %.3f sec (pass %d)  Sample/sec  %.1fK\n",
		elapsedTime, mCurrentSample, sampleSec / 1000.f);


}
