# morsecode_arduino

Aim of this application is to create a system that can encrypt characters that will be entered via a keyboard in the corresponding Morse code and then decode the Morse code and return the text that was originally entered. To achieve this two Arduino Uno are used one as a transmitter and the other as
receiver of Morse signals. The Morse code transmitter is connected to the computer so that text can be entered into the system via a keyboard.

<img src="https://github.com/kellypat1/morsecode_arduino/blob/main/transmitter.jpg" width="700">

On the contrary, the Morse receiver draws the necessary energy from simple batteries (AA 1.5V). Thus, the transmitter of the Morse signals reads the
characters entered from the keyboard, which are converted to “.” and “-” and transfers them using Bluetooth to the other Arduino Uno. 

<img src="https://github.com/kellypat1/morsecode_arduino/blob/main/receiver.jpg" width="700">

The Bluetooth of the two Arduino Uno communicate with each other in master mode for transmitter and slave mode for the receiver. In practice this means that although the transmitter can theoretically communicate with up to seven Bluetooth simultaneously, the receiver of the system recognizes and accepts information only from specific transmitter to ensure a steady flow of data. In this way, the Morse receiver receives the signal and reproduces it visually (LED light), by audio
(passive buzzer) and with a 12mm vibration motor, while it transmits the originals characters entered using an LCD monitor.


