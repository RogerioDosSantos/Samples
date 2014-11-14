exports.ArrayToJason = function (array) {
    var jason = Object();
    try {
        jason = JSON.parse('{ ' + array.toString() + ' }');
    } catch (error) {
        //JASON failed, parse the parameters to create the JASON object.
        var prefix = '{';
        var jason_string = String();
        for (var array_id in array) {
            var name = array[array_id].split(':');
            var value = '';
            switch (name.length) {
                case 2:
                    value = String(name[1]);
                case 1:
                    name = String(name[0]);
                    break;
                default:
                    jason_string += prefix + ' "item' + array_id.toString() + '":"Invalid item (' + array[array_id].toString() + ')"';
                    prefix = ',';
                    continue;
            }
            
            name = name.replace(/"/g, '');
            value = value.replace(/"/g, '');
            name = name.replace(/ /g, '_');
            jason_string += prefix + ' "' + name + '":"' + value + '"';
            prefix = ',';
        }
        
        jason_string += ' }';
        jason = JSON.parse(jason_string);
    }
    
    return jason;
}
