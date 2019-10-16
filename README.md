# Ouija-Board
##### nower than ESP-Now
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## What's it for?

The code describes the main function of a digital implementation of a ouija-board.
Just as it works with a classical oldschool wooden device, this board provides you an opportunity to communicate with the other side.
Long story short- you can call ghosts with it an receive messages from them.

The ghosts will show up in different ways. They can either send you direct feedback when you realise the controller is vibrating or they can send you any kind of sign via the LED-stripes hidden in the board an controller.
As well is it possible that the different characters on the board will be light up, so you can read messages from the ghosts.

## How?

Our Ouija-Board functions via two ESP8266 devices connected with the [nExtSP](https://github.com/Lyniat/nExtSP) library by [lyniat] (https://github.com/Lyniat) 
The Application consists of two physical devices - the board and the controller. Each is connected to a ESP8266 microcontroller and gives as well haptic as visual feedback when interacting with the board.

The specific functions and the circuit layout of the board and controller and their behaviour can be retreived from the code and the documentation.

## Contribution

Improvement suggestions and contributions always welcome ♥
this project is still in a prototypical state and has a lot of bugs mainly caused by the remote connection between the two devices and the interference between the RFID-Reader and the library. 

## License
* MIT
* by [Elisa Valetta](https://github.com/vallettina) and [Laura Zeilbeck](https://github.com/ladyViolet)
