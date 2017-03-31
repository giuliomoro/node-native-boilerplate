#include <Bela.h>
#include <cmath>
#include <nan.h>
#include "render.h"

v8::Local<v8::Array> arr;
v8::Local<v8::Function> callbackHandle;
const int argc = 1;
v8::Local<v8::Value> argv[argc];

bool setup(BelaContext *context, void *userData)
{
	struct JsArgs* jsArgs = (struct JsArgs*)userData;
	arr = *(v8::Local<v8::Array>*)jsArgs->arr;
	callbackHandle = *(v8::Local<v8::Function>*)jsArgs->callback;
	printf("We are using %d frames per block\n", context->audioFrames);
	argv[0] = arr;
	return true;
}

void render(BelaContext *context, void *userData)
{
	float freq = analogRead(context, 0, 0) * 300 + 150;
	// writing the frequency to js in the first element of the js array
	Nan::Set(arr, 0, Nan::New(freq));
	// calling the js callback
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, argc, argv);
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		// reading the content of the js array
		float out = Nan::Get(arr, n).ToLocalChecked()->NumberValue();
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, out);
		}
	}
}

void cleanup(BelaContext *context, void *userData)
{ }

