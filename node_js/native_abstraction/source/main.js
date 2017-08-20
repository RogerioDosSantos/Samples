// note that the compiled addon is placed under following path
const nativeAddon = require('../stage/node_modules/native_addon');

// `Hello` function returns a string, so we have to console.log it!
console.log(nativeAddon.Run());
console.log(nativeAddon.Run("1 - SyncCall"));

nativeAddon.RunAsync("1 - AsyncCall", function(err, result) {
    console.log(result);
});

nativeAddon.RunAsync("2 - AsyncCall", function(err, result) {
    console.log(result);
});

console.log(nativeAddon.Run("2 - SyncCall"));
console.log(nativeAddon.Run("3 - SyncCall"));
