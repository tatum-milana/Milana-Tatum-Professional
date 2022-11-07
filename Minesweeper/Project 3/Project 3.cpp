#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Board.h"
#include "tile.h"
#include "Random.h"
#include "TextureManager.h"
using namespace std;


int main()
{
    Board board = Board();
    ifstream inFile("boards/config.cfg");
    if (inFile.is_open())
    {
        cout << "Config file opened!" << endl;
        string line = "null";
        istringstream stream(line);
        vector <int> boardData;
        int data;
        while (inFile >> data)
        {
            boardData.push_back(data);
            cout << data << endl;

           

        }
        board.SetStats(boardData[0], boardData[1], boardData[2]);
        
    }
    else
    {
        cout << "config file could not open!" << endl;
    }

    sf::RenderWindow window(sf::VideoMode(board.GetWidth(), board.GetHeight()), "Minesweeper!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        

        window.clear();

        
        vector<sf::Sprite> tileVisuals;
        int tileVal = 0;
        for (int i = 0; i < board.GetTileHeight(); i++)
        {          
            for (int j = 0; j < board.GetTileWidth(); j++)
            {
                
                sf::Sprite tile;
                if (board.tiles[tileVal].isCovered == false)
                {
                    tile = board.tiles[tileVal].tileBackground;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);
                }
                
                if (board.tiles[tileVal].isFlagged == true && board.loss == true)
                {
                    tile = board.tiles[tileVal].flag;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);
                }

                if (board.tiles[tileVal].bombStatus == true && board.tiles[tileVal].isCovered != true)
                {
                    tile= board.tiles[tileVal].bomb;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);
                }

                if (board.tiles[tileVal].bombCount != 0 && board.tiles[tileVal].isCovered != true && board.tiles[tileVal].bombStatus != true)
                {
                    tile = board.tiles[tileVal].number;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);

                }       

                if (board.tiles[tileVal].isCovered == true)
                {
                    tile = board.tiles[tileVal].tileCover;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);
                }

                if (board.tiles[tileVal].isFlagged == true && board.tiles[tileVal].isCovered == true)
                {
                    tile = board.tiles[tileVal].flag;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);
                }

                if ((board.tiles[tileVal].bombStatus == true && board.tiles[tileVal].isCovered == true && board.debugMode == true)|| (board.tiles[tileVal].bombStatus == true && board.tiles[tileVal].isCovered == true && board.loss == true))
                {
                    tile = board.tiles[tileVal].bomb;
                    tile.setPosition(j * 32, i * 32);
                    window.draw(tile);
                }
                tileVisuals.push_back(tile);
                             
                tileVal++;
               
            }        

        }    
     
     
        
     
        
       
       
        vector<sf::Sprite> specialButtons;
        sf::Sprite dbutton;
        dbutton = board.debugButton;
        dbutton.setPosition((((board.GetWidth() / 2) - 32) + 2 * (64)), (board.GetTileHeight() * 32));
        window.draw(dbutton);
        specialButtons.push_back(dbutton);

        sf::Sprite t1;
        t1 = board.test1Butt;
        t1.setPosition((((board.GetWidth() / 2) - 32) + 3 * (64)), (board.GetTileHeight() * 32));
        window.draw(t1);
        specialButtons.push_back(t1);

        sf::Sprite t2;
        t2 = board.test2Butt;
        t2.setPosition((((board.GetWidth() / 2) - 32) + 4 * (64)), (board.GetTileHeight() * 32));
        window.draw(t2);
        specialButtons.push_back(t2);

        sf::Sprite t3;
        t3 = board.test3Butt;
        t3.setPosition(((board.GetWidth() / 2) - 32) + 5*64, (board.GetTileHeight() * 32));
        window.draw(t3);
        specialButtons.push_back(t3);

        sf::Sprite face;
        if (board.win == true)
        {
            face = board.winFace;
            face.setPosition((board.GetWidth() / 2) - 32, (board.GetTileHeight() * 32));
        }
        else if (board.loss == true)
        {
            face = board.lossFace;
            face.setPosition((board.GetWidth() / 2) - 32, (board.GetTileHeight() * 32));
        }
        else
        {
            face = board.smile;
            face.setPosition((board.GetWidth() / 2) - 32 , (board.GetTileHeight() * 32));
        }
        window.draw(face);
        specialButtons.push_back(face);


        sf::Sprite num1;
        sf::Sprite num2;
        sf::Sprite num3;
        sf::Sprite sign;

        if (board.pos == false)
        {
            sign.setTexture(TextureManager::GetTexture("digits"));
            sign.setTextureRect(sf::IntRect((10 * 21), 0, 21, 32));
            sign.setPosition(0, (board.GetTileHeight() * 32));
            window.draw(sign);

        }

        num1.setTexture(TextureManager::GetTexture("digits"));
        num1.setTextureRect(sf::IntRect( (board.hundredsPlace * 21),  0, 21, 32));
        num1.setPosition(21, (board.GetTileHeight() * 32));
        window.draw(num1);

        num2.setTexture(TextureManager::GetTexture("digits"));
        num2.setTextureRect(sf::IntRect((board.tensPlace * 21), 0, 21, 32));
        num2.setPosition(42, (board.GetTileHeight() * 32));
        window.draw(num2);

        num3.setTexture(TextureManager::GetTexture("digits"));
        num3.setTextureRect(sf::IntRect((board.onesPlace * 21), 0, 21, 32));
        num3.setPosition(63, (board.GetTileHeight() * 32));
        window.draw(num3);

      
        // getting mouse position and mouse related events
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        //cout << mousePosition.x << ", " << mousePosition.y << endl;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // getting mouse position and mouse related events
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            //cout << mousePosition.x << ", " << mousePosition.y << endl;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (board.loss == false && board.win == false)
                    {
                        for (int i = 0; i < tileVisuals.size(); i++)
                        {
                            sf::FloatRect rectangle = tileVisuals[i].getGlobalBounds();
                            if (rectangle.contains(mousePosition.x, mousePosition.y) && board.tiles[i].isFlagged == false)
                            {
                                board.tiles[i].revealTile();

                                if (board.tiles[i].bombStatus == true)
                                {
                                    board.LossActions();

                                }
                                board.CheckWin();
                            }
                        }
                    }
                    for (int i = 0; i < specialButtons.size(); i++)
                    {
                        sf::FloatRect rectangle = specialButtons[i].getGlobalBounds();
                        if (rectangle.contains(mousePosition.x, mousePosition.y))
                        {
                            board.loadBoard(i);
                        }

                    }
                   
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    if (board.loss == false && board.win == false)
                    {
                        for (int i = 0; i < tileVisuals.size(); i++)
                        {
                            sf::FloatRect rectangle = tileVisuals[i].getGlobalBounds();
                            if (rectangle.contains(mousePosition.x, mousePosition.y))
                            {
                                if (board.tiles[i].isFlagged == true)
                                {
                                    board.tiles[i].isFlagged = false;
                                    board.flagCount--;
                                }
                                else if (board.tiles[i].isFlagged == false && board.tiles[i].isCovered == true)
                                {
                                    board.tiles[i].isFlagged = true;
                                    board.flagCount++;

                                }
                                cout << "flag count is : " << board.flagCount << endl;
                            }
                        }

                    }
                    
                    board.ValuesForTileCounter();


                }             


            }
        }
        window.display();

    }

    return 0;
}


