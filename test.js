// var nbind = require('nbind');
// var lib = nbind.init().lib;
 
// lib.clipboard.writeToClipboard('you');

const addon = require('./build/Release/addon');

console.log(addon.writeToClipboard("2233"));