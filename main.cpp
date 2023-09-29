/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>

#include <ctime>

#include <iostream>

#include <time.h>

#include "utils.h"

#include "pieces.h"

#include "functionality.h"

using namespace std;
using namespace sf;
int main() {
    srand(time(0));
    RenderWindow window(VideoMode(500, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5;
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/unique.png");
    obj5.loadFromFile("img/blast.png");

    //------------------Adding background music------------------//
    sf::Music music;
    music.openFromFile("tetris.ogg"); //opening file
    music.setPosition(0, 1, 30);
    music.setVolume(40);
    music.setLoop(true);
    music.play(); //calling function to play music 
    //------------------------------------//

    Sprite sprite(obj1), background(obj2), frame(obj3), unique(obj4), bomb(obj5);
    int delta_x = 0, colorNum = 1, bombBlastingThreshholdScore = 0;
    float timer = 0, delay = 0.3;
    bool rotate = 0;
    bool bombBlast = 0;
    float bombtimer = 0;
    int colorForBomb = 3;

    Clock clock;
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        delta_x = 0, rotate = 0;
        bombtimer += time;
        timer += time;
        delay = fast;
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)) { //Event is occurring - until the game is in running state
            if (e.type == Event::Closed) //If cross/close is clicked/pressed
                window.close(); //Opened window disposes
            if (e.type == Event::KeyPressed) { //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up) //Check if the other key pressed is UP key
                    rotate = true; //Rotation gets on
                else if (e.key.code == Keyboard::Left) //Check if the other key pressed is LEFT key
                    delta_x = -1; //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right) //Check if the other key pressed is RIGHT key
                    delta_x = 1; //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)
                    spacefeature(); //calling spacebar function for instatly down
                else if (e.key.code == Keyboard::H)
                    mainmenu();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) //Just another way to detect key presses without event listener
            delay = fast / 6; //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

        if (stopfalling()) // condition if game stops
        {
            //bombBlastingAgent(bombBlastingThreshholdScore, colorForBomb ,  bombBlast, bombtimer);
            fallingPiece(timer, delay, colorNum); //Example: fallingPiece() function is called here
            movement(delta_x); //calling left or right movement function
            rotation(rotate); // calling rotate function
            levelno();
            shadow(); //to display shadow
            levelhard(delay); //increase speed of blocks after each level
        } else {
            music.stop(); //stop music 
            mainmenu(); //calling main menu 
        }
        lineclear(); // calling line clearing function   
        //  scorecounter();
        restart(fast);
        //-----------------------------------------Font-------------------------------------------//
        sf::Font font;
        font.loadFromFile("/home/mrhassan/Downloads/Montserrat/static/Montserrat-Bold.ttf");
        sf::Text text, score, text1, Lineclear, level, text2, text3;

        //-----------score--------------//
        text.setFont(font);
        text.setString("Score");
        text.setPosition(320, 10);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);

        score.setFont(font);
        score.setString(to_string(sco));
        score.setPosition(320, 50);
        score.setCharacterSize(25);
        score.setFillColor(sf::Color::Green);

        //-----------level--------------//
        text1.setFont(font);
        text1.setString("Level");
        text1.setPosition(320, 100);
        text1.setCharacterSize(25);
        text1.setFillColor(sf::Color::White);

        level.setFont(font);
        level.setString(to_string(levelog));
        level.setPosition(320, 150);
        level.setCharacterSize(25);
        level.setFillColor(sf::Color::Green);

        //-----------Lines--------------//
        text2.setFont(font);
        text2.setString("Lines Cleared");
        text2.setPosition(320, 200);
        text2.setCharacterSize(25);
        text2.setFillColor(sf::Color::White);

        Lineclear.setFont(font);
        Lineclear.setString(to_string(offcount));
        Lineclear.setPosition(320, 250);
        Lineclear.setCharacterSize(25);
        Lineclear.setFillColor(sf::Color::Green);
        //-----------------------------------------!-------------------------------------------// 

        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); //offset
                //--------------SHADOW DRAWING---------------//
                unique.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                unique.setPosition(j * 18, i * 18);
                unique.move(28, 31);
                //----------bombdrawing---------//
                bomb.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                bomb.setPosition(j * 18, i * 18);
                bomb.move(28, 31);
                window.draw(bomb);
                window.draw(unique);
                window.draw(sprite);

            }
        }
        for (int i = 0; i < 4; i++) {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            unique.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            unique.setPosition(unique1[i][0] * 18, unique1[i][1] * 18);
            unique.move(28, 31);
            //----------bombdrawing---------//
            bomb.setTextureRect(IntRect(colorForBomb * 18, 0, 18, 18));
            bomb.setPosition(arryForBomb[i][0] * 18, arryForBomb[i][0] * 18);
            bomb.move(28, 31);
            window.draw(bomb);
            window.draw(unique);
            window.draw(sprite);

        }
        //--The side text is being displayed--//
        window.draw(text);
        //--The score is being displayed--//
        window.draw(score);
        //--The  no of linecleared is being displayed--//
        window.draw(Lineclear);
        //--The level font is being displayed--//
        window.draw(text1);
        //--The level no is being displayed--//
        window.draw(level);
        //--The lines cleared heading is being displayed--//
        window.draw(text2);
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();

    }
    return 0;
}
