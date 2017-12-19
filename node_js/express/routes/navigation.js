exports.GotoLink = function (request, response, parameters) {
    
    //Call Examples
    //http://localhost:1337/test/Navigation;GotoLink;url:"www.google.com"
    
    var parameters = require('./JasonHelper').ArrayToJason(parameters);
    if (!parameters.hasOwnProperty('url')) {
        response.send('Expected parameter (url)');
        return;
    }
    
    var url = String(parameters['url']);
    response.links({ next: '"' + url + '"' });
    response.end();
}
