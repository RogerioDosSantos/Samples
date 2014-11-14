
var http = require('http');
var express = require('express');
var socket = require('socket.io');

var app = express();

// all environments
app.set('port', process.env.PORT || 8080);


var io = socket.listen(app);

io.sockets.on('connection', function (client) {
    console.log('Client connected...');
    client.emit('messages', { hello: 'world' });
});

