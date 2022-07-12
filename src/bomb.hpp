#pragma once
#include "header.hpp"

class Bomb;

class Bombs
{
protected:
    vector<Bomb> barood;
    // vector<Bullet> enemyammunations;

    Vector2f bulletOrigin;
    //  Vector2f enemyBulletOrigin;
    // int enemyshootTimer = 0;
    int shootTimer = 0;
    friend class Game;
    friend class Bomb;
};




class Bomb
{
protected:
    // Bullet damage rate
    float damage = 20;
    // Bullet speed
    Vector2f speed = Vector2f(10.0f, 10.0f);
    //used or unused flag
    bool fired = false;
        

    // Bullet position
    struct bombPos
    {
        float x;
        float y;
    } position;

    CircleShape bomb;
    Texture bombTexture;

public:
    Bomb();
    ~Bomb(){};
    void changeDirection(Direction,CircleShape &,Vector2f &);
    Vector2f getPosition();
    friend class Game;
};





Bomb ::Bomb() 
{
    position.x = 200.0f;
    position.y = 200.0f;
    bomb.setRadius(10.0f);
    bomb.setPosition(position.x, position.y);
    bombTexture.loadFromFile(IMG_PATH "/bomb.png");
    bomb.setTexture(&bombTexture);
}


void Bomb ::changeDirection(Direction playerDirection, CircleShape & R, Vector2f & s)
{
 
    
        switch (playerDirection)
        {
        case Left:
            s.x = -10.0f;
            s.y = 0.0f;
            R.setRotation(-90);
            break;
        case Up:
            s.x = 0.0f;
            s.y = -10.0f;
            R.setRotation(0);
            break;
        case Down:
            s.x = 0.0f;
            s.y = 10.0f;
            R.setRotation(180);
            break;
        case Right:
            s.x = 10.0f;
            s.y = 0.0f;
            R.setRotation(90);
            break;
        }
   
}
Vector2f Bomb :: getPosition()
{
    return bomb.getPosition();
}



