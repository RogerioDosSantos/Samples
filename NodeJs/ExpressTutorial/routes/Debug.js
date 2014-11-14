exports.DisplayParameters = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayParameters;file_name:"Text.txt"
    //http://localhost:1337/test/Debug;DisplayParameters;Name:Rogerio,Last_Name:dos Santos,Mother:Elza dos Santos
    
    var html_resp = 'Debug::DisplayParameters:<br><br>';
    for (var parameter_id in parameters) {
        var name = parameters[parameter_id].split(':');
        var value = '';
        switch (name.length) {
            case 2:
                value = String(name[1]);
            case 1:
                name = String(name[0]);
                break;
            default:
                html_resp += parameter_id.toString() + ' - Invalid parameter (' + parameter.toString() + ')<br>';
                continue;
        }
        
        html_resp += parameter_id.toString() + ' - ' + name + ' = ' + value + ' <br>';
    }
    
    html_resp += '<br>Debug::DisplayParameters - End';
    response.send(html_resp);
    response.end();
}

exports.DisplayParametersJason = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayParametersJason;file_name:"Text.txt"
    //http://localhost:1337/test/Debug;DisplayParametersJason;Name:Rogerio,Last_Name:dos Santos,Mother:Elza dos Santos
    //http://localhost:1337/test/Debug;DisplayParametersJason;"Name":"Rogerio","Last_Name":"dos Santos","Mother":"Elza dos Santos","Number":10

    var jason;
    try {
        jason = JSON.parse('{ ' + parameters.toString() + ' }');
    } catch (error) {
        //JASON failed, parse the parameters to create the JASON object.
        var jason_string = '{"DisplayParametersJason":"The parameters passed are not JASON. This JASON were created by parsing all parameters as JASON object!"'        
        for (var parameter_id in parameters) {
            var name = parameters[parameter_id].split(':');
            var value = '';
            switch (name.length) {
                case 2:
                    value = String(name[1]);
                case 1:
                    name = String(name[0]);
                    break;
                default:
                    jason_string += ', "parameter' + parameter_id.toString() + '":"Invalid parameter (' + parameters[parameter_id].toString() + ')"';
                    continue;
            }
            
            name = name.replace(/"/g, '');
            value = value.replace(/"/g, '');
            name = name.replace(/ /g, '_');
            jason_string += ', "' + name + '":"' + value + '"';
        }
        
        jason_string += '}';
        jason = JSON.parse(jason_string);
    }

    response.send(jason);
    response.end();
}

exports.DisplayQueryStrings = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayQueryStrings;?query1=10
    //http://localhost:1337/test/Debug;DisplayQueryStrings;?Key1=1&Key2=20,30
    
    var html_resp = 'Debug::DisplayQueryStrings:<br><br>';
    
    for (var query_key in request.query) {
        html_resp += query_key.toString() + ' = ' + request.query[query_key].toString() + '<br>';
    }

    html_resp += '<br>Debug::DisplayQueryStrings - End';
    response.send(html_resp);
    response.end();
}

exports.DisplayRoute = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayRoute
        
    response.send(request.route);
    response.end();
}

exports.DisplayCookies = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayCookies
    
    response.send(request.cookies);
    response.end();
}

exports.DisplaySignedCookies = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplaySignedCookies
    
    response.send(request.signedCookies);
    response.end();
}

exports.DisplayClientIP = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayClientIP
    
    var html_resp = 'Debug::DisplayClientIP:<br><br>';
    
    html_resp += 'Client IP: ' + request.ip + '<br>'
    html_resp += 'Forwarded Proxies: ' + request.ips + '<br>'
    
    html_resp += '<br>Debug::DisplayClientIP - End';
    
    response.send(html_resp);
    response.end();
}

exports.DisplayPath = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayPath
    
    var html_resp = 'Debug::DisplayPath:<br><br>';
    
    html_resp += 'Path: ' + request.path + '<br>'
    
    html_resp += '<br>Debug::DisplayPath - End';
    
    response.send(html_resp);
    response.end();
}

exports.DisplayHost = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Debug;DisplayHost
    
    var html_resp = 'Debug::DisplayHost:<br><br>';
    
    html_resp += 'Host: ' + request.host + '<br>'
    html_resp += 'Sub Domains: ' + request.subdomains + '<br>'
    html_resp += 'Original Url: ' + request.originalUrl + '<br>'
    
    html_resp += '<br>Debug::DisplayHost - End';
    
    response.send(html_resp);
    response.end();
}