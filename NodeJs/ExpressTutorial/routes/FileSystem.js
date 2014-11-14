exports.SendFile = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/FileSystem;SendFile;file_name:"Text.txt"
    //http://localhost:1337/test/FileSystem;SendFile;file_name:"Image.jpg"
    //http://localhost:1337/test/FileSystem;SendFile;file_name:"PDF.pdf"
    //http://localhost:1337/test/FileSystem;SendFile;file_name:"Zip.7z"

    var parameters = require('./JasonHelper').ArrayToJason(parameters);
    if (!parameters.hasOwnProperty('file_name')) {
        response.send('Exprected parameter (file_name)');
        return;
    }
    
    var file_name = String(parameters['file_name']);        
    var file_path = './Files/' + file_name;
    file_path = require('path').resolve(file_path);
    require('fs').exists(file_path, function (exist) {
        if (!exist) {
            response.send('File does not exist (' + file_path + ')');
            response.end();
            return;
        }
        
        response.sendfile(file_path);
        //response.end();
    });         
}

exports.DownloadFile = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/FileSystem;DownloadFile;file_name:"Text.txt",save_as:"Text1.txt"
    //http://localhost:1337/test/FileSystem;DownloadFile;file_name:"Image.jpg"
    //http://localhost:1337/test/FileSystem;DownloadFile;file_name:"PDF.pdf"
    //http://localhost:1337/test/FileSystem;DownloadFile;file_name:"Zip.7z"
    
    var parameters = require('./JasonHelper').ArrayToJason(parameters);
    if (!parameters.hasOwnProperty('file_name')) {
        response.send('Exprected parameter (file_name)');
        return;
    }
    
    var file_name = String(parameters['file_name']);
    var save_as = file_name;
    if (parameters.hasOwnProperty('save_as')) {
        save_as = parameters['save_as'];
    }
    
    var file_path = './Files/' + file_name;
    file_path = require('path').resolve(file_path);
    require('fs').exists(file_path, function (exist) {
        if (!exist) {
            response.send('File does not exist (' + file_path + ')');
            response.end();
            return;
        }
        
        response.download(file_path, save_as, function (error) {
            if (error) {
                return;
            }

        });
    });
}
