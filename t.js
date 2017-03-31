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
	//console.log(inc);
	for( n = 0; n < a.length; ++n){
		phase += inc;
		a[n] = phase;
		if(phase >= 1)
			phase -= 2;
	}
}

var len = 128;
var arr = Array.from({ length: len }, () => 0);
ne.callback(arr, saw);
