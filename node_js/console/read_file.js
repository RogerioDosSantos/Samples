var file_system = require('fs');
var contents = file_system.readFile('./hello.txt', 'utf8', function (err, contents) {
    console.log(contents);
});

console.log("Hello from Node!");