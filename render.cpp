#include <Bela.h>
#include <cmath>
#include <nan.h>
#include "render.h"

float gFrequency = 440.0;
float gPhase;
float gInverseSampleRate;

v8::Local<v8::Array> arr;
v8::Local<v8::Function> callbackHandle;
const int argc = 1;
v8::Local<v8::Value> argv[argc];

bool setup(BelaContext *context, void *userData)
{
	struct JsArgs* jsArgs = (struct JsArgs*)userData;
	arr = *(v8::Local<v8::Array>*)jsArgs->arr;
	callbackHandle = *(v8::Local<v8::Function>*)jsArgs->callback;
	printf("Calling callback from within setup()\n");
	int length = arr->Length();
	for(int n = 0; n < length; ++n){
		//Nan::Maybe<double> val = Nan::To<double>(Nan::Get(arr, n).ToLocalChecked());
		Nan::Set(arr, n, Nan::New(1));
	}
	argv[0] = arr;
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, argc, argv);
	for(int n = 0; n < length; ++n){
		//Nan::Maybe<double> val = Nan::To<double>(Nan::Get(arr, n).ToLocalChecked());
		double num = Nan::Get(arr, n).ToLocalChecked()->NumberValue();
		printf("Here: %f\n", num);
	}
	gInverseSampleRate = 1.0 / context->audioSampleRate;
	gPhase = 0.0;

	return true;
}

void render(BelaContext *context, void *userData)
{
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, argc, argv);
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		float out = 0.8 * sinf(gPhase);
		gPhase += 2.0 * M_PI * gFrequency * gInverseSampleRate;
		if(gPhase > 2.0 * M_PI)
			gPhase -= 2.0 * M_PI;

		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, out);
		}
	}
}

void cleanup(BelaContext *context, void *userData)
{

}

