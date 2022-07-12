#include "header.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "Enemy.hpp"
#include "menu.hpp"
#include "bomb.hpp"

bool gameExit = false;
class Game
{
private:
    int tilePosX = 0;
    int tilePosY = 0;

    // Iitializing the required objects
    RenderWindow window;
    RectangleShape background;
    Texture backgroundTexture;
    Player player;
    Enemy enemies;
    Bullet bulletObj;
    Bullets BulletPack;
    Enemies allEnemies;
    mainGunda maingunda;
    Bomb granite;
    Bombs granite_pack;
    Menu menu;
    RectangleShape Bush;
     Texture bushTexture;
    int seconds;
    // int enemyspawnTimeInterval = 20;
    bool mainMenu = true;
    // Declaring the required game rendering and updating functions
    void processEvents();
    void update();
    void render();
    Screen screen = Main_Menu;

public:
 
    struct obstacle
    {
        float x;
        float y;
    } obstaclePos[5] = {
        {20, 20},
        {336, 442},
        {20, 20},
        {20, 20},
        {20, 20}};
    Game();
    void run();
};

// Initializing Game object with neccessary texture and setting up their size and position
Game::Game() : window(VideoMode(720, 720), "Dave in the Zombie World"), background(Vector2f(40.0f, 40.0f)), Bush(Vector2f(250.0f, 200.0f))
            //    Rock(Vector2f(200.0f, 200.0f))

{

  bushTexture.loadFromFile(IMG_PATH "/bush.png");
    Bush.setTexture(&bushTexture);
    Bush.setPosition(Vector2f(500.0f,520.0f));

    backgroundTexture.loadFromFile(IMG_PATH "/greengrass.jpg");
    background.setTexture(&backgroundTexture);
    maingunda.initiateVillan();
    allEnemies.enemySpawnNo = 7;
};

// function for starting all action
void Game::run()
{
    while (window.isOpen())
    {
        window.setFramerateLimit(60);
        processEvents();
        render();
        update();
        if (gameExit == true)
        {
            break;
        }
    }
}

// function for checking window close events
void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
    }
}
// Game update function
void Game::update()
{

    // For starting Game
    if (Mouse::isButtonPressed(Mouse::Left))
    {

        if (Mouse::getPosition(window).x >= menu.playBtn.getPosition().x && Mouse::getPosition(window).x <= (menu.playBtn.getPosition().x + menu.playBtn.getSize().x) && Mouse::getPosition(window).x >= menu.playBtn.getPosition().y && Mouse::getPosition(window).y <= (menu.playBtn.getPosition().y + menu.playBtn.getSize().y))
        {
            screen = Game_Play;
        }
    }

    // For Exit
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        
        if (Mouse::getPosition(window).x >= menu.exitBtn.getPosition().x && Mouse::getPosition(window).x <= (menu.exitBtn.getPosition().x + menu.exitBtn.getSize().x) && Mouse::getPosition(window).y >= menu.exitBtn.getPosition().y && Mouse::getPosition(window).y <= (menu.exitBtn.getPosition().y + menu.exitBtn.getSize().y))
        {
            gameExit = true;
        
        }
    }




    // Player bomb timer 
    if (granite_pack.shootTimer < 10)
        granite_pack.shootTimer++;





    // Enemies

    if (allEnemies.enemySpawnNo > 0)
    {
        switch (allEnemies.enemySpawnNo)
        {
        case 7:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[6].x, enemies.enemypositions[6].y));
            break;
        case 6:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[5].x, enemies.enemypositions[5].y));
            break;
        case 5:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[4].x, enemies.enemypositions[4].y));
            break;
        case 4:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[3].x, enemies.enemypositions[3].y));
            break;
        case 3:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[2].x, enemies.enemypositions[2].y));
            break;
        case 2:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[1].x, enemies.enemypositions[1].y));
            break;
        case 1:
            enemies.enemy.setPosition(Vector2f(enemies.enemypositions[0].x, enemies.enemypositions[0].y));
            cout << "I am fine till here" << endl;
            break;
        }
        enemies.enemyLife.setFillColor(Color::Blue);
        enemies.enemyLife.setSize(Vector2f(enemies.EnemylifeSize, 10.0f));
        enemies.enemyLife.setPosition(Vector2f(enemies.enemy.getPosition().x, enemies.enemy.getPosition().y - enemies.enemyLife.getSize().y));
        enemies.enemy.setTexture(&enemies.enemyTexture);
        allEnemies.enemyGroup.push_back(enemies);
        allEnemies.enemySpawnNo--;
        cout << "enemies no : " << allEnemies.enemySpawnNo << endl;

        // allEnemies.enemyspawnTimer = 0;
        // }
    }
    player.updatePlayerposition();

    // Setting bullet origin position
    BulletPack.bulletOrigin = Vector2f(player.dave.getPosition().x + (player.dave.getSize().x / 2) + 10.0f, player.dave.getPosition().y + (player.dave.getSize().y / 2) + 10.0f);

    // Player Bullet timer
    if (BulletPack.shootTimer < 10)
        BulletPack.shootTimer++;

    // Bullet initialization, movement and Direction control
    if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)))
    {
        if (BulletPack.shootTimer >= 10)
        {
            // For every Rectangleshape bullet object which is to added to its vector structure is given origin as center of player
            bulletObj.bullet.setPosition(BulletPack.bulletOrigin);
            // Setting texture for every Rectangleshape bullet object
            bulletObj.bullet.setTexture(&bulletObj.bulletTexture);
            // For changing bullet moving and texture direction by passing player direction enum as argument

            bulletObj.changeDirection(player.playerDirection, bulletObj.bullet, bulletObj.speed);

            // Loading ready Rectangleshape bullet object to ammunations vector
            BulletPack.ammunations.push_back(bulletObj);

            // resetting shoottimer to zero
            BulletPack.shootTimer = 0;
        }
    }



  //Bomb initialization, movement and Direction control 
    if ((Keyboard::isKeyPressed(Keyboard::Space) ))
    {
      
        if( granite_pack.shootTimer >= 10){
        // For every Rectangleshape bullet object which is to added to its vector structure is given origin as center of player
        granite.bomb.setPosition(BulletPack.bulletOrigin);
        // Setting texture for every Rectangleshape bullet object
        granite.bomb.setTexture(&granite.bombTexture);
        // For changing bullet moving and texture direction by passing player direction enum as argument

        granite.changeDirection(player.playerDirection, granite.bomb, granite.speed);

        // Loading ready Rectangleshape bullet object to ammunations vector
        granite_pack.barood.push_back(granite);

        // resetting shoottimer to zero
        granite_pack.shootTimer = 0;
    }

}











// Updating main Villain

    maingunda.updateMainGundaPosition(Vector2f(player.dave.getPosition().x, player.dave.getPosition().y), maingunda.enemySpeed,maingunda.Gunda);
    maingunda.Gunda.move(maingunda.enemySpeed);
    maingunda.GundaLifeSize.move(maingunda.enemySpeed);

    // For enemies movement
    for (size_t i = 0; i < allEnemies.enemyGroup.size(); i++)
    {
        // For following the player
        allEnemies.enemyGroup[i].updateEnemyPosition(Vector2f(player.dave.getPosition().x, player.dave.getPosition().y), allEnemies.enemyGroup[i].enemySpeed, allEnemies.enemyGroup[i].enemy);

        // Making the every enemy move by changing position of all enemy inside vector
        allEnemies.enemyGroup[i].enemy.move(allEnemies.enemyGroup[i].enemySpeed);
        allEnemies.enemyGroup[i].enemyLife.move(allEnemies.enemyGroup[i].enemySpeed);
    }

    // For bullet movement and removing bullet
    for (size_t i = 0; i < BulletPack.ammunations.size(); i++)
    {
        // Making the every bullet move by changing position of all bullet inside vector
        BulletPack.ammunations[i].bullet.move(BulletPack.ammunations[i].speed);

        // condition for erasing bullet if the cross the screen
        if (BulletPack.ammunations[i].getPosition().y < 0 || BulletPack.ammunations[i].getPosition().y >= window.getSize().y ||
            BulletPack.ammunations[i].getPosition().x < 0 || BulletPack.ammunations[i].getPosition().x >= window.getSize().x)
            BulletPack.ammunations.erase(BulletPack.ammunations.begin() + i);
    }





// For bomb movement and removing bomb
    for (size_t i = 0; i < granite_pack.barood.size(); i++)
    {

        // Making the every bomb move by changing position of all bomb inside vector
        granite_pack.barood[i].bomb.move( granite_pack.barood[i].speed);

        // condition for erasing bullet if the cross the screen
        if ( granite_pack.barood[i].bomb.getPosition().y < 0 ||  granite_pack.barood[i].bomb.getPosition().y >= window.getSize().y ||
             granite_pack.barood[i].bomb.getPosition().x < 0 ||  granite_pack.barood[i].bomb.getPosition().x >= window.getSize().x)
             granite_pack.barood.erase(granite_pack.barood.begin() + i);
    }







    // For Main Gunda and Bullet collision
    for (size_t i = 0; i < BulletPack.ammunations.size(); i++)
    {
        if (allEnemies.enemyGroup.size() == 0 && maingunda.GundaLifeSize.getSize().x <= 0)
        {
            screen = Win;
        }

        // Main Gunda collision with bullet
        if(BulletPack.ammunations[i].bullet.getGlobalBounds().intersects(maingunda.Gunda.getGlobalBounds())){
            if(maingunda.GundaLifeSize.getSize().x > 0)
            {
                 BulletPack.ammunations.erase(BulletPack.ammunations.begin() + i);
                maingunda.GundaLifeSize.setSize(Vector2f(maingunda.GundaLifeSize.getSize().x -12.5,maingunda.GundaLifeSize.getSize().y));
            }else
            {
            BulletPack.ammunations.erase(BulletPack.ammunations.begin() + i);
            maingunda.Gunda.setSize(Vector2f(0.0f,0.0f));
            maingunda.Gunda.setPosition(Vector2f(2222.0f,5555.0f));
            maingunda.GundaLifeSize.setPosition(Vector2f(2222.0f,5000.0f));
            }     
        }



    // Normal enemy collision
        for (size_t j = 0; j < allEnemies.enemyGroup.size(); j++)
        {
            if (BulletPack.ammunations[i].bullet.getGlobalBounds().intersects(allEnemies.enemyGroup[j].enemy.getGlobalBounds()))
            {
                BulletPack.ammunations.erase(BulletPack.ammunations.begin() + i);
                if (allEnemies.enemyGroup[j].enemyLife.getSize().x <= 0)
                {
                    allEnemies.enemyGroup.erase(allEnemies.enemyGroup.begin() + j);
                }
                else
                {
                    allEnemies.enemyGroup[j].enemyLife.setSize(Vector2f(allEnemies.enemyGroup[j].enemyLife.getSize().x - 50.0f, 10.0f));
                }
            }
        }
    }



    // Enemy and bomb collision
 
for (size_t i = 0; i < granite_pack.barood.size(); i++)
{
    

   if (allEnemies.enemyGroup.size() == 0 && maingunda.GundaLifeSize.getSize().x <= 0)
        {
            screen = Win;
        }

        // Main Gunda collision with bullet
        if(granite_pack.barood[i].bomb.getGlobalBounds().intersects(maingunda.Gunda.getGlobalBounds())){
            if(maingunda.GundaLifeSize.getSize().x > 0)
            {
                 granite_pack.barood.erase(granite_pack.barood.begin() + i);
                maingunda.GundaLifeSize.setSize(Vector2f(maingunda.GundaLifeSize.getSize().x -25,maingunda.GundaLifeSize.getSize().y));
            }else
            {
            granite_pack.barood.erase(granite_pack.barood.begin() + i);
            maingunda.Gunda.setSize(Vector2f(0.0f,0.0f));
            maingunda.Gunda.setPosition(Vector2f(2222.0f,5555.0f));
            maingunda.GundaLifeSize.setPosition(Vector2f(2222.0f,5000.0f));
            }     
        }





    for (size_t j = 0; j < allEnemies.enemyGroup.size(); j++)
    {
       if(granite_pack.barood[i].bomb.getGlobalBounds().intersects(allEnemies.enemyGroup[j].enemy.getGlobalBounds()))
        {
            granite_pack.barood.erase(granite_pack.barood.begin() + i);
            allEnemies.enemyGroup.erase(allEnemies.enemyGroup.begin() + j);
        }
    }
    
}

    // For Player and Enemy Collision

    for (size_t i = 0; i < allEnemies.enemyGroup.size(); i++)
    {
        if (player.dave.getGlobalBounds().intersects(allEnemies.enemyGroup[i].enemy.getGlobalBounds()))
        {

            player.daveLifesize -= 25;
            player.dave.setPosition(player.originalPos.x, player.originalPos.y);
            player.davelife.setPosition(Vector2f(player.dave.getPosition().x, player.dave.getPosition().y - player.davelife.getSize().y));
            player.davelife.setSize(Vector2f(player.davelife.getSize().x - 25, player.davelife.getSize().y));
            allEnemies.enemyGroup.erase(allEnemies.enemyGroup.begin() + i);
            if (player.davelife.getSize().x <= 0)
            {
                screen = Lose;
            }
        }
    }


    // For main Gunda and player collision
if(player.dave.getGlobalBounds().intersects(maingunda.Gunda.getGlobalBounds()))
{
            player.daveLifesize -= 25;
            player.dave.setPosition(player.originalPos.x, player.originalPos.y);
            player.davelife.setPosition(Vector2f(player.dave.getPosition().x, player.dave.getPosition().y - player.davelife.getSize().y));
            player.davelife.setSize(Vector2f(player.davelife.getSize().x - 25, player.davelife.getSize().y));
            maingunda.Gunda.setPosition(500.0f,500.0f);
            maingunda.GundaLifeSize.setPosition(Vector2f(maingunda.Gunda.getPosition().x,maingunda.Gunda.getPosition().y - 10));
            if (player.davelife.getSize().x <= 0)
            {
                screen = Lose;
            }

}

}

// Game rendering function
void Game::render()
{
    window.clear();

    if (screen == Main_Menu)
    {
        window.draw(menu.menuBackground);
        window.draw(menu.playBtn);
        window.draw(menu.soundBtn);
        window.draw(menu.exitBtn);
        window.draw(menu.logo);
    }

    if (screen == Game_Play)
    {

        // Drawing background from grass Texture
        for (int i = 0; i < 18; i++)
        {
            for (int j = 0; j < 18; j++)
            {
                tilePosX = i;
                tilePosY = j;
                background.setPosition(Vector2f(40.0f * tilePosX, 40.0f * tilePosY));
                window.draw(background);
            }
        }

  
        // Adding player in the game
        window.draw(player.dave);
        window.draw(player.davelife);

      // Adding Bushes in the backgrounds
        window.draw(Bush);
        //    Adding Enemies
        window.draw(maingunda.Gunda);
        window.draw(maingunda.GundaLifeSize);
        for (size_t i = 0; i < allEnemies.enemyGroup.size(); i++)
        {

            window.draw(allEnemies.enemyGroup[i].enemy);
            window.draw(allEnemies.enemyGroup[i].enemyLife);
        }
        for (size_t i = 0; i < BulletPack.ammunations.size(); i++)
        {
            window.draw(BulletPack.ammunations[i].bullet);
        }
    }

    if (screen == Lose)
    {
        window.draw(menu.youLose);
    }

    if (screen == Win)
    {
        window.draw(menu.MissionComplete);
    }

      // Adding Bombs
    for (size_t i = 0; i < granite_pack.barood.size(); i++)
    {
        window.draw(granite_pack.barood[i].bomb);
    }

    window.display();
}

int main()
{

    Game game;
    game.run();
    return 0;
}