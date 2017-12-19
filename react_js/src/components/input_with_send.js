import React, {Component} from 'react';
// import ReactDOM from "react-dom";
import {TextInput} from 'react-desktop/windows';
import {Button} from 'react-desktop/windows';
import {Text} from 'react-desktop/windows';

class InputWithSend extends Component
{
    constructor()
    {
        super();
        this.state = {data: [], name: ""};
        this.onClick = this.onClick.bind(this);
    };

    callServer(url)
    {
        return fetch(url).then((promisse) => {
            return promisse.json();
        });
    }

    onClick(e)
    {
        e.stopPropagation();
        // fetch("https://randomuser.me/api/").then((response) => {return response.json()}).then((json) => {
        //     console.log(json);
        //     this.setState({data: json});
        // });

        this.callServer("https://randomuser.me/api/").then((response) => {
            console.log(response);
            this.setState({data: response, name: response.results["0"].name.first});
        });
    };


    render()
    {
    return (
          <div className="ReactDesktop-InputWithSend">

            <TextInput className="ReactDesktop-TextInput" label="Title"/>

            <Button onClick={this.onClick}>
              Request
            </Button>

            <Text>
              Response: 
						</Text>

            User:
            <div><pre>{this.state.name}</pre></div>

            Json:
            <div><pre>{JSON.stringify(this.state.data, null, 2) }</pre></div>

        </div>

    );
  }
  
}

export default InputWithSend;
