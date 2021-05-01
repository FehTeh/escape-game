#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include "math.h"

#include "game.h"

#define TileSize 32

GameEvent Game::update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller)
{
    interval--;

    int offsetX = window.getWidth() / 2;
    int offsetY = window.getHeight() / 2;

    int playerX = offsetX - (TileSize / 2);
    int playerY = offsetY - (TileSize / 2);

    GameKey key = controller.getKeyPressed();

    window.clear();

    int i,j;/*i On behalf of the line, j On behalf of the column, i*n+j Is the ordinal number of that point in the array */
    for(i=0 ;i < size;i++)
    {
        for(j=0; j < size; j++)
        {
            /*int lenght_x = 0;
            int lenght_y = 0;
            if(player_x > j)
            {
                lenght_x = player_x - j;
            }
            else 
            {
                lenght_x = j - player_x;
            }

            if(player_y > i)
            {
                lenght_y = player_y - i;
            }
            else 
            {
                lenght_y = i - player_y;
            }*/

            //if(lenght_y < 3 && lenght_x < 3)
            //{
                if(map[i * size + j] == '#')
                {
                    window.renderTexture(j * TileSize + offsetX - (TileSize / 2) + moveX, i * TileSize + offsetY - (TileSize / 2) + moveY, resource.getTexture(TextureKey::Wall));
                }

                if(map[i * size + j] == '.')
                {
                    window.renderTexture(j * TileSize + offsetX - (TileSize / 2) + moveX, i * TileSize + offsetY - (TileSize / 2) + moveY, resource.getTexture(TextureKey::Floor));
                }
            //}
        }
    }

    if(player.getMovement() != PlayerMovement::StandBy)
    {
        if(moveX % TileSize == 0 && moveY % TileSize == 0)
        {
            player.setMovement(PlayerMovement::StandBy);
        }
        else
        {
            move(player.getMovement());
        }
    }
    
    if(key != GameKey::None && moveX % TileSize == 0 && moveY % TileSize == 0 && canMove(mapKeyToMovement(key)))
    {
        player.setMovement(mapKeyToMovement(key));
        move(player.getMovement());
    }

    /*if(abs(moveX) == 320)
    {
        return GameEvent::LevelUp;
    }*/

    //Render Player
    window.renderTexture(playerX, playerY, resource.getTexture(player.getChar(interval / 25)));

    //Render Powerup
    window.renderRectangle(window.getWidth() - (TileSize + (TileSize / 2)), TileSize / 2, TileSize, TileSize, resource.getColor(ColorKey::Red));

    window.display();

    return GameEvent::Running;
}

void Game::generate(int p_s)
{
    size = p_s;

    int i,j,k;  /* counter */
    char *p = new char[size * size];    /* With length of m*n Array store mxn A maze of size */
    srand(int(time(0)));    /* Used to generate random Numbers */
    
    for(i=0;i < size * size; i++)
    {
        if(rand() % 2 == 0)
        { 
            p[i]='.';
        }/* When the random number is even, the point in the maze is defined as the path */
        else 
        {
            p[i]='#';
        }
    }

    /* Seal both the left and the top of the boundary except for one 1 Six entrances, only from the right and the bottom, 
    Make the maze more challenging */
    for(i=0; i < size; i++)
    {
        p[i]='#';
    }
    for(i=0;i< size * size; i += size)
    {
        p[i]='#';
    }
     for(i = size-1; i< size * size; i += size)
    {
        p[i]='#';
    }
    
    for(i = size * (size - 1); i< size * size; i++)
    {
        p[i]='#';
    }
    /* Let's put the front 3 The order structure of T font */
    p[0]=p[1]=p[2]=p[2*size]=p[2*size+2]='#';
    p[size]=p[size+1]=p[size+2]=p[2*size+1]='.';

    /* Mazes are random and need to be constructed 1 pathway */
    /* This is a 1 Each article 3 Turn, 1 The access of the time */
    for(j=3;j<size;j+=3)
    {
        for(k=0;k<3;k++)
        {
            i=(j-3)+k+1;
            if(i*size+j<size*size)
            {
                p[i*size+j]='.';
            }
        }
    }

    for(i=4;i<size;i+=3)
    {
        for(k=0;k<3;k++)
        {
            j=(i-3)+k+2;
            if(i*size+j<size*size)
            {
                p[i*size+j]='.';
            } 
        }
    }

    map = p;

    moveX = 0;
    moveY = -TileSize;

    showmaze();
}

/* Private */
void Game::showmaze()
{
    char* p = map;
    int m = size;
    int n = size;

    int i,j;/*i On behalf of the line, j On behalf of the column, i*n+j Is the ordinal number of that point in the array */
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            std::cout<<std::setw(2)<<p[i*m+j];/* Each character takes two to square the maze */
        }
        std::cout<<std::endl;
    }
}

void Game::move(PlayerMovement movement)
{
    switch(player.getMovement())
    {
        case(PlayerMovement::Up):
        {
            moveY += 2;
            break;
        }
        case(PlayerMovement::Down):
        {
            moveY += -2;
            break;
        }
        case(PlayerMovement::Left):
        {
            moveX += 2;
            break;
        }
        case(PlayerMovement::Right):
        {
            moveX += -2;
            break;
        }
        default:
            break;
    }
}

bool Game::canMove(PlayerMovement movement)
{
    int x = abs(moveX / TileSize);
    int y = abs(moveY / TileSize);

    if(movement == PlayerMovement::Right)
    {
        x++;
    }

    if(movement == PlayerMovement::Left)
    {
        x--;
    }

    if(movement == PlayerMovement::Up)
    {
        y--;
    }

    if(movement == PlayerMovement::Down)
    {
        y++;
    }

    if(map[y*size+x] == '.')
    {
        return true;
    }

    return false;
}

PlayerMovement Game::mapKeyToMovement(GameKey key)
{
    switch(key)
    {
        case GameKey::Up:
            return PlayerMovement::Up;
        case GameKey::Down:
            return PlayerMovement::Down;        
        case GameKey::Left:
            return PlayerMovement::Left;        
        case GameKey::Right:
            return PlayerMovement::Right;        
        default:
            return PlayerMovement::StandBy; 
    }
}

