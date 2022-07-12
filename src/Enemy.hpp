#pragma once


class Enemy : public Character
{
protected:
    RectangleShape enemy;
    RectangleShape enemyLife;
    Texture enemyTexture;
    float EnemylifeSize = 100.0f;

    float posDiffx;
    float posDiffy;
    Vector2f enemySpeed = Vector2f(-10.0f, 0.0f);
    pos enemypositions[7] = {
         {900.0f,900.0f},
        {-100.0f,-80.0f},
        {333.0f,67.0f},
        {90.0f,44.0f},
        {811.0f,50.0f},
        {-200.0f,-400.0f},
        {100.0f,-300.0f}    
        
    };

public:
    Enemy();
    void updateEnemyPosition(Vector2f, Vector2f &,RectangleShape &);
    friend class Game;
};

Enemy ::Enemy() : enemy(Vector2f(100.0f, 100.0f)) , enemyLife(Vector2f(EnemylifeSize,10.0f))
{
    enemy.setPosition(Vector2f(100.0f, 100.0f));
    enemyTexture.loadFromFile(IMG_PATH "/enemy2Up.png");
    enemy.setTexture(&enemyTexture);
    enemyLife.setPosition(Vector2f(enemy.getPosition().x,enemy.getPosition().y-enemyLife.getSize().y));
    enemyLife.setFillColor(Color::Red);
    

}

void Enemy ::updateEnemyPosition(Vector2f p, Vector2f &s,RectangleShape &e)
{
    posDiffx = e.getPosition().x - p.x;
    posDiffy = e.getPosition().y - p.y;


    if (posDiffx >= 50)
    {
        s.x = -1.0f;
        s.y = 0.0f;
        enemyTexture.loadFromFile(IMG_PATH"/enemy2Left.png");
        e.setTexture(&enemyTexture);
    }
    else if (posDiffx <= -50)
    {
        s.x = 1.0f;
        s.y = 0.0f;
        enemyTexture.loadFromFile(IMG_PATH"/enemy2Right.png");
        e.setTexture(&enemyTexture);
    }
    else
    {
        if (posDiffy >= 50)
        {
            s.x = 0.0f;
            s.y = -1.0f;
            enemyTexture.loadFromFile(IMG_PATH"/enemy2Up.png");
            e.setTexture(&enemyTexture);
        }
        else if (posDiffy <= -50)
        {
            s.x = 0.0f;
            s.y = 1.0f;
            enemyTexture.loadFromFile(IMG_PATH"/enemy2Down.png");
            e.setTexture(&enemyTexture);
        }
        else
        {
            s.x = 0.0f;
            s.y = 0.0f;
        }
    }
}

class Enemies
{
protected:
    vector<Enemy> enemyGroup;
    int enemyspawnTimer = 0;
    int enemyShootTimer = 50;
    int enemySpawnNo = 7;
    friend class Game;
    friend class Enemy;
};


class mainGunda :public Enemy
{
    protected:
    RectangleShape Gunda;
    Texture GundaTexture;
    RectangleShape GundaLifeSize;
    float MposDiffx;
    float MposDiffy;
    Vector2f mainGundaSpeed = Vector2f(-10.0f, 0.0f);
    public:
    void initiateVillan()
    {
        Gunda.setSize(Vector2f(150.0f,150.0f));
        Gunda.setPosition(Vector2f(1000.0f,1000.0f));
        GundaTexture.loadFromFile(IMG_PATH"/bigEnemy.png");
        Gunda.setTexture(&GundaTexture);
        GundaLifeSize.setSize(Vector2f(200.0f,10.0f));
        GundaLifeSize.setFillColor(Color::Blue);
        GundaLifeSize.setPosition(Vector2f(Gunda.getPosition().x,Gunda.getPosition().y - 10));
    }
   void updateMainGundaPosition(Vector2f, Vector2f &,RectangleShape &);
    friend class Game;
};


void mainGunda ::updateMainGundaPosition(Vector2f p, Vector2f &s,RectangleShape &e)
{
    MposDiffx = e.getPosition().x - p.x;
    MposDiffy = e.getPosition().y - p.y;
  

    if (MposDiffx >= 50)
    {
        s.x = -1.0f;
        s.y = 0.0f;
        enemyTexture.loadFromFile(IMG_PATH"/bigEnemyLeft.png");
        e.setTexture(&enemyTexture);
    }
    else if (MposDiffx <= -50)
    {
        s.x = 1.0f;
        s.y = 0.0f;
        enemyTexture.loadFromFile(IMG_PATH"/bigEnemyRight.png");
        e.setTexture(&enemyTexture);
    }
    else
    {
        if (MposDiffy >= 50)
        {
            s.x = 0.0f;
            s.y = -1.0f;
            enemyTexture.loadFromFile(IMG_PATH"/bigEnemy.png");
            e.setTexture(&enemyTexture);
        }
        else if (MposDiffy <= -50)
        {
            s.x = 0.0f;
            s.y = 1.0f;
            enemyTexture.loadFromFile(IMG_PATH"/bigEnemyDown.png");
            e.setTexture(&enemyTexture);
        }
        else
        {
            s.x = 0.0f;
            s.y = 0.0f;
        }
    }
}