
exports.PageSelection = function (request, response) {
    
    //Call Example:
    //http://localhost:1337/pages?view=View01
    //http://localhost:1337/pages?view=View01&title=Title&name=Rogerio
    //http://localhost:1337/pages?view=View01&title=Title&name=Rogerio&user=User01
    //http://localhost:1337/pages?view=View01&title=Title&name=Elza&usingJade=false

    var parameters = request.query;
    //var parameters = new Object();
    var view = 'index';
    if (parameters.hasOwnProperty('view'))
        view = parameters['view'];
       
    response.render(view, parameters);
};
