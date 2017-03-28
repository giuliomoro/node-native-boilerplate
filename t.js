var ne = require('./');

function doPrint()
{
  console.log('done');
}
ne.aNumber();
process.nextTick(doPrint);
