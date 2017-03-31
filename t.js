var ne = require('./');

function doPrint(a)
{
	var inv = 1/a.length;
	for(var n = 0; n < a.length; ++n){
		//console.log(n+" "+a[n]);
		a[n] += n * inv;
	}
}
//ne.aNumber();
var len = 64;
var arr = Array.from({ length: len }, () => 0);
ne.callback(arr, doPrint);
