import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

import InputWithSend from './components/input_with_send.js';

class App extends Component {
  render() {
    return (
      <div className="App">

        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
        </div>

        <div className="App-body">

          <InputWithSend />
          <InputWithSend />

        </div>

      </div>
    );
  }
}

export default App;
