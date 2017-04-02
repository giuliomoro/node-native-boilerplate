var ne = require('./');

var phase = 0;

var frequency = 100;
var inc = 2 * frequency / 44100;
var n = 0;
function saw(a)
{
	// getting in the frequency as the first value in the array
	frequency = a[0];

	inc = 2 * frequency / 44100;
	for( n = 0; n < a.length; ++n){
		//console.log("[", n, "]: ", a[n]);
		phase += inc;
		a[n] = phase;
		if(phase >= 1)
			phase -= 2;
	}
}

var len = 128;
var arr = Array.from({ length: len }, () => 0);
var arr32 = new Float32Array(128);
arr32[0] = 9;
arr32[127] = 9999;
ne.callback(arr32, saw);
