import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

class HelloWorldApp extends Component {
  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>Welcome to React</h2>
        </div>
        <p className="App-intro">
          This is a Hello World App
        </p>
      </div>
    );
  }
}

export default HelloWorldApp;
