// note that the compiled addon is placed under following path
const nativeAddon = require('../stage/node_modules/native_addon');

// `Hello` function returns a string, so we have to console.log it!
console.log(nativeAddon.Run());
console.log(nativeAddon.Run("String from JavaScript!"));
