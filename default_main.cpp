/*
 * default_main.cpp
 *
 *  Created on: Oct 24, 2014
 *      Author: parallels
 */
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <libgen.h>
#include <signal.h>
#include <getopt.h>
#include "../include/Bela.h"
#include "render.h"

using namespace std;

// Handle Ctrl-C by requesting that the audio rendering stop
void interrupt_handler(int var)
{
	gShouldStop = true;
}

// Print usage information
void usage(const char * processName)
{
	cerr << "Usage: " << processName << " [options]" << endl;

	Bela_usage();

	cerr << "   --help [-h]:                        Print this menu\n";
}

int defaultMain(int argc, char *argv[], void* jsArr, void* jsCallback)
{
	BelaInitSettings settings;	// Standard audio settings

	struct option customOptions[] =
	{
		{"help", 0, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	// Set default settings
	Bela_defaultSettings(&settings);
	settings.periodSize = 128;

	// Parse command-line arguments
	while (1) {
		int c;
		if ((c = Bela_getopt_long(argc, argv, "h", customOptions, &settings)) < 0)
				break;
		switch (c) {
		case 'h':
				usage(basename(argv[0]));
				exit(0);
		case '?':
		default:
				usage(basename(argv[0]));
				exit(1);
		}
	}

	// Initialise the PRU audio device
	struct JsArgs jsArgs = {jsArr, jsCallback};
	if(Bela_initAudio(&settings, &jsArgs) != 0) {
		cout << "Error: unable to initialise audio" << endl;
		return -1;
	}

	// Set up interrupt handler to catch Control-C and SIGTERM
	signal(SIGINT, interrupt_handler);
	signal(SIGTERM, interrupt_handler);

	// Start the audio device running
	if(Bela_runInSameThread()) {
		cout << "Error: unable to start real-time audio" << endl;
		return -1;
	}
	Bela_cleanupAudio();

	// All done!
	return 0;
}
