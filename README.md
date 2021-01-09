# Asteroid Belt [IoT-Challenge-01]
Asteroid Belt is a game developed for the BBC microbit as a submission for Challenge 01 from the module Internet of Things.


## Installation
Asteroid Belt was created using the [micro:bit runtime](https://lancaster-university.github.io/microbit-docs/) developed by Lancaster University. 

To run the game on your microbit, \
**Using the hex file:** 
1. Connect the microbit to your computer via a USB cable (Micro-USB). The microbit will appear as a drive.
2. Download the [AsteroidBelt-microbit.hex](AsteroidBelt-microbit.hex) file.
3. Drop the hex file into the microbit drive. The copy triggers the orange LED on the back of the micro:bit to flash; it will stop flashing when the download is complete.
4. Once the download process is completed, the game will start running on your microbit.

**Using the C++ source code:** \
If you would like to make any changes to the game, the altered source file has to be compiled to create a hex file.
1. Decide on a development environment from the micro:bit documentation [Getting Started](https://lancaster-university.github.io/microbit-docs/#getting-started) page.
2. Compile the source code to generate a hex file.
3. Download the hex file and follow the steps from above.

## Usage
You, as the player control a spacheship, out in space. Unfortunately this spaceship has to maneuver through an asteroid belt.

Move the spaceship out of the way of the asteroids using the two buttons on the microbit.\
Button `A` to move left \
Button `B` to move right

Each asteroid avoided counts towards your score.

But what if it's becoming too much? There's just too many asteroids and not enough time. Well, here's the good news; the spaceship is equipped with missiles capable of blowing these asteroids to smithereens. The bad news though, is that these missiles are precious ammunition and so your score will decrease by 1 each time you fire.\
Press both buttons `A+B` to fire

If the player fails to keep the spaceship safe and an asteroid hits it, the game will end and the score will be displayed (with which the player may boast to their friends). 

Press `RESET` at the back of the microbit to start a new game.

### TL;DR
- Move spaceship out of the way of asteroids 
- Press \
`A` to move left \
`B` to move right \
`A+B` to fire a missile 
- Each asteroid avoided = score +1 
- Each missile fired -> score -1 

## License
[MIT](https://choosealicense.com/licenses/mit/)


