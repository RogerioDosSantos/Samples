import React, {Component} from 'react';

class Button extends Component
{
	render()
	{
		return (
			<div>
        <button onClick={this.handleClick}>button</button>
      </div>
     );
	}
}

export default Button;
