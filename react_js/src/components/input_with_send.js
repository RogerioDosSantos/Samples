import React, { Component } from 'react';

import { TextInput  } from 'react-desktop/windows';
import { Button  } from 'react-desktop/windows';
import { Text  } from 'react-desktop/windows';

class InputWithSend extends Component {
  render() {
    return (
          <div className="ReactDesktop-InputWithSend">

            <TextInput className="ReactDesktop-TextInput" label="Title"/>

            <Button push 
              onClick={
                () => console.log('Clicked!')
                }
              >
              Request
            </Button>

            <Text>
						  Response
						</Text>

        </div>

    );
  }
}

export default InputWithSend;
