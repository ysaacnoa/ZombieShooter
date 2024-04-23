// ZombieShooter.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"

using namespace sf;

int main()
{
    //states of the game, always start with one of them
    enum class State
    {
        PAUSED, LEVELING_UP, GAME_OVER, PLAYING
    };

    //start with the game state GAME_OVER
    State state = State::PLAYING;

    //get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(
        VideoMode(resolution.x, resolution.y),
        "Zombie Arena", Style::Fullscreen
    );

    //create a SFML view for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //clock for timing everything
    Clock clock;

    //how long has the PLAYING state been active
    Time gameTimeTotal;

    //where is the mouse in relation to the world coordinates
    Vector2f mouseWorldPosition; 

    //where is the mouse in relation to the screen coordinates
    Vector2i mouseScreenPosition;

    //create an instance of the player class
    Player player;

    //Limits  of the arena 
    IntRect arena;

    //create a background
    VertexArray background;
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background_sheet.png");

    //main loop
    while (window.isOpen()) {
        /*
        ************
            Entrada de
            asa
            ************
        */
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                //pause a game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING) {
                    state = State::PAUSED;
                }

                //restart while paused 
                else if(event.key.code == Keyboard::Return && state == State::PAUSED){
                    state == State::PLAYING;
                    //reset the clock so there isn't a frame jump
                    clock.restart();
                }

                //start a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING) {

                }
            } //end event polling

            //handle the player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }

            //handle the player moving WSAD
            if (state == State::PLAYING) {
                
                //handle the pressing and releasing of the WASD keys
                if (Keyboard::isKeyPressed(Keyboard::W)) {
                    player.moveUp();
                }
                else {
                    player.stopUp(); 
                }

                if (Keyboard::isKeyPressed(Keyboard::D)) {
                    player.moveRight();
                }
                else {
                    player.stopRight(); 
                }

                if (Keyboard::isKeyPressed(Keyboard::S)) {
                    player.moveDown();
                }
                else {
                    player.stopDown();
                }

                if (Keyboard::isKeyPressed(Keyboard::A)) {
                    player.moveLeft();
                }
                else {
                    player.stopLeft(); 
                }
            }//end WASD while playing

            if (state == State::LEVELING_UP) {
                
                //handle the player leveling up
                if (event.key.code == Keyboard::Num1) {
    	            state = State::PLAYING;
                }

                if (event.key.code == Keyboard::Num2) {
                    state = State::PLAYING;
                }

                if (event.key.code == Keyboard::Num3) {
                    state = State::PLAYING;
                }

                if (event.key.code == Keyboard::Num4) {
                    state = State::PLAYING;
                }

                if (event.key.code == Keyboard::Num5) {
                    state = State::PLAYING; 
                }

                if (event.key.code == Keyboard::Num6) {
                    state = State::PLAYING;
                }

                if (state == State::PLAYING) {
                    
                    //prepare the level
                    //we will modify this later
                    arena.width = 500;
                    arena.height = 500;
                    arena.left = 0;
                    arena.top = 0;

                    //pass the vertex array by reference
                    int tileSize = createBackground(background, arena);

                    //spawn the player in the middle of the arena
                    player.spawn(arena, resolution, tileSize);

                    //reset the clock so there isn't a frame jump
                    clock.restart();
                }
            }//end leveling up

        /*
        ****************
        ACTUALIZAR EL
        FRAME
        ****************
        */
        if (state == State::PLAYING) {

            //update the frame delta time
            Time dt = clock.restart();

            //Update the total game time
            gameTimeTotal += dt;

            //make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            //where is the mouse pointer
            mouseScreenPosition = Mouse::getPosition();

            //convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            //update the player
            player.update(dtAsSeconds, Mouse::getPosition());

            //set the new position of the player
            Vector2f playerPosition(player.getCenter());

            //center the view around the player
            mainView.setCenter(player.getCenter());
        }//end updating the scene

        } //end game loop

        /*
        **************
        Dibujar la
        escena
        **************
        */
        if (state == State::PLAYING) {
            window.clear();

            //set view to main view and draw everything related to it
            window.setView(mainView);
                
            //draw the background
            window.draw(background, &textureBackground);

            //draw the player
            window.draw(player.getSprite()); 
        }

        if (state == State::LEVELING_UP) {

        }

        if (state == State::PAUSED) {

        }

        if (state == State::GAME_OVER) {

        }

        window.display();
    }

    return 0;
}

