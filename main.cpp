#include "MicroBit.h"

/********************************************************
  *                 Declarations                        *
  *******************************************************/

//Create an instance of the MicroBit class
MicroBit uBit;

/** 
  * Name: Sprite
  * Description: A class to abstract the entities of this game
  */
class Sprite{
    public:
        int col; //column or x-value of position
        int row; //row or y-value of position
};

/** 
  * Name: Asteroid
  * Description: A class to create multiple instances of asteroids
  */
class Asteroid: public Sprite{
    public:
        bool active;
        
        void moveAsteroid();
        void activateAsteroid();
};

Sprite spaceship;
Sprite missile;
Asteroid asteroidArray[5];

int score;
bool gameOver;

void updateAsteroids();
void checkCollision(int column);
void fire(MicroBitEvent);
void moveLeft(MicroBitEvent);
void moveRight(MicroBitEvent);
void checkHit(int column);
void updateMissile();
void displayGameOver();
void startGame();

/********************************************************
  *                 Implementation                      *
  *******************************************************/

/** 
  * Name: moveAsteroid
  * Description: Moves the asteroid down a pixel with each cycle of execution 
  * if active. If not active, calls the activateAsteroid function.
  * Parameters: none
  * Returns: void
  */
void Asteroid::moveAsteroid(){
    if (active){
        row += 1;
        
        if(row > 4){
            //When the asteroid is at the last row
            //Bring it back to the top and deactivate
            score += 1;
            row = -1;
            active = false;
        }
    }else{
        //If the asteroid is inactive run the random activating function each cycle
        activateAsteroid();
    }
}

/** 
  * Name: activateAsteroid
  * Description: Activates the asteroid randomly.
  * Parameters: none
  * Returns: void
  */
void Asteroid::activateAsteroid(){
    int randomNum = uBit.random(5);
    if(randomNum == 1){
        active = true;
    }
}

/** 
  * Name: updateAsteroids
  * Description: Calls the move function for each asteroid and maintains speed of movement
  * Parameters: none
  * Returns: void
  */
void updateAsteroids(){
    while(!gameOver){
        uBit.sleep(500);
        //Call moveAsteroid for each asteroid
        for(int j = 0; j < 5; j++){
            asteroidArray[j].moveAsteroid();
        }
    }
}

/** 
  * Name: checkCollision
  * Description: Checks collision by checking whether the asteroid and spaceship occupy the same spot
  * Parameters: int column - the column the spaceship currently occupies
  * Returns: void
  */
void checkCollision(int column){
    if(asteroidArray[column].active && asteroidArray[column].row == 4){
        gameOver = true;
    }
}

/** 
  * Name: moveLeft
  * Description: Moves spaceship to the left when button A is pressed
  * Parameters: MicroBitEvent
  * Returns: void
  */
void moveLeft(MicroBitEvent){
    if(spaceship.col > 0){
        spaceship.col -= 1;
    }
}

/** 
  * Name: moveRight
  * Description: Moves spaceship to the right when button B is pressed
  * Parameters: MicroBitEvent
  * Returns: void
  */
void moveRight(MicroBitEvent){
    if(spaceship.col < 4){
        spaceship.col += 1;
    }
}

/** 
  * Name: fire
  * Description: Fires(activates) a missile when both buttons are pressed
  * Parameters: MicroBitEvent 
  * Returns: void
  */
void fire(MicroBitEvent){
    if (missile.row == -1){
        score -= 1;
        missile.row = 4;
        missile.col = spaceship.col;
    }
}

/** 
  * Name: checkHit
  * Description: Deactivates asteroids hit by missile
  * Parameters: int column - the column the missile currently occupies 
  * Returns: void
  */
void checkHit(int column){
    if(asteroidArray[column].active && asteroidArray[column].row >= missile.row){
        asteroidArray[column].active = false;
        asteroidArray[column].row = -1;
        missile.row = -1;
        missile.col = -1;
    }
}

/** 
  * Name: updateMissile
  * Description: Moves missile upwards and checks for hit with asteroid
  * Parameters: none
  * Returns: void
  */
void updateMissile(){
    while (!gameOver)
    {
        uBit.sleep(500);
        if (missile.row != -1){
            missile.row -= 1;
        }
        checkHit(missile.col);
    }
}

/** 
  * Name: displayGameOver
  * Description: Clear the screen and display score
  * Parameters: none
  * Returns: void
  */
void displayGameOver(){
    uBit.display.clear();
    
    MicroBitImage cross("255, 0, 0, 0, 255\n0, 255, 0, 255, 0\n0, 0, 255, 0, 0\n0, 255, 0, 255, 0\n255, 0, 0, 0, 255\n");
    uBit.display.print(cross);
    uBit.sleep(1500);
    uBit.display.clear();

    uBit.display.scroll("SCORE:");
    uBit.display.scroll(score);
}

/** 
  * Name: startGame
  * Description: Initialises the game and keeps it running until game is over
  * Parameters: none
  * Returns: void
  */
void startGame(){
    // Register event handlers for button presses
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, fire);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, moveLeft);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, moveRight);
    
    //Refresh values for a new game
    gameOver = false;
    spaceship.row = 4;
    spaceship.col = 2;
    missile.row = -1;
    missile.col = -1;
    
    //Initialise values for each asteroid
    for(int i = 0; i < 5; i++){
        asteroidArray[i].active = false;
        asteroidArray[i].col = i;
        asteroidArray[i].row = -1;
    }
    
    // Spawn independent fibers to handle the movement of each entity
    create_fiber(updateAsteroids);
    create_fiber(updateMissile);
    
    //Refresh the screen and display spaceship and asteroids in their new positions
    while (!gameOver){
        uBit.sleep(10);
        uBit.display.clear();
        uBit.display.image.setPixelValue(spaceship.col, spaceship.row, 255);
        uBit.display.image.setPixelValue(missile.col, missile.row, 255);
        for(int i = 0; i < 5; i++){
            if(asteroidArray[i].active){
                uBit.display.image.setPixelValue(asteroidArray[i].col, asteroidArray[i].row, 255);
            }
        }
        checkCollision(spaceship.col);
    }
    
    displayGameOver();
}

/********************************************************
  *                     Main                            *
  *******************************************************/

/** 
  * Name: main
  * Description: The main function, where execution begins.
  * Parameters: none
  * Returns: int
  */
int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();

    // Get ready!
    uBit.display.scroll("ASTEROID BELT!");
    //Start game!
    startGame();

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}
