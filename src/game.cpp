#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include "math.h"

#include "game.h"

#define TileSize 32

void Game::start()
{
    generate(30);
    interval = 7000;
}

GameEvent Game::update(WindowManager& window, ResourceManager& resource, SoundManager& sound, ControllerManager& controller)
{
    interval--;

    int playerX = window.getWidth() / 2 - (TileSize / 2);
    int playerY = window.getHeight() / 2 - (TileSize / 2);

    GameKey key = controller.getKeyPressed();

    if(key == GameKey::B)
    {
        if(!backgroundPressed)
        {
            backgroundPressed = true;
            if(background == ColorKey::Blue)
                background = ColorKey::Red;
            else if(background == ColorKey::Red)
                background = ColorKey::Green;
            else if(background == ColorKey::Green)
                background = ColorKey::Blue;
        }
    }

    if(key == GameKey::None)
    {
        backgroundPressed = false;
    }

    window.clear();

    if(loading)
    {
    	window.renderTextCenter(0, sin(window.getTicks()/100) * 2 - 4, "Escape!!", resource.getFont(FontKey::Font24), resource.getColor(ColorKey::White));
    }
    else
    {
        if(interval <= 0)
        {
            if(abs(interval) / 50 > 5)
            {
                return GameEvent::Stopped;
            }

            window.renderTextCenter(0, sin(window.getTicks()/100) * 2 - 4, "GAMEOVER", resource.getFont(FontKey::Font24), resource.getColor(ColorKey::White));    
        }
        else 
        {
            renderLevel(window, resource);

            if(player.getMovement() != PlayerMovement::StandBy)
            {
                if(moveX % TileSize == 0 && moveY % TileSize == 0)
                {
                    player.setMovement(PlayerMovement::StandBy);
                }
                else
                {
                    move(player.getMovement());
                    //sound.playSound(resource.getSound(SoundKey::FootStep));
                }
            }
            
            if(key != GameKey::None && moveX % TileSize == 0 && moveY % TileSize == 0)
            {
                player.setMovement(mapKeyToMovement(key));

                if(canMove(mapKeyToMovement(key)))
                {
                    move(player.getMovement());
                    sound.playSound(resource.getSound(SoundKey::FootStep));
                }
            }

            if(abs(moveX) == size * 32 - TileSize)
            {
                generate(size + 10);
                interval += 1000;
            }

            //Render Player
            window.renderTexture(playerX, playerY, resource.getTexture(player.getTexture(interval / 7)));

            //Render statusbar
            renderStatusBar(window, resource);
        }
    }
    
    if(interval > 0 && interval / 50 <= 10)
    {
        window.fade(100 - (interval / 50) * 10);
    }

    window.display();

    return GameEvent::Running;
}

/* Private */
void Game::renderLevel(WindowManager& window, ResourceManager& resource)
{
    int offsetX = window.getWidth() / 2;
    int offsetY = window.getHeight() / 2;

    int i,j;/*i On behalf of the line, j On behalf of the column, i*n+j Is the ordinal number of that point in the array */
    for(i=0 ;i < size;i++)
    {
        for(j=0; j < size; j++)
        {
            int x = j * TileSize + offsetX - (TileSize / 2) + moveX; 
            int y = i * TileSize + offsetY - (TileSize / 2) + moveY;

            window.renderRectangle(x, y, TileSize, TileSize, resource.getColor(background));

            if(map[i * size + j] == '#')
            {
                TextureKey t = TextureKey::WallTop;

                if(map[(i + 1) * size + j] == '.')
                {
                    t = TextureKey::Wall;
                }

                window.renderTexture(x, y, resource.getTexture(t));
            }
        }
    }
}

void Game::renderStatusBar(WindowManager& window, ResourceManager& resource)
{
    std::string zeros = "";
    int time = interval / 50;

    if(time < 100)
    {
        if(time < 10)
        {
            zeros = "00";
        }
        else
        {
            zeros = "0";
        }
    }

    std::string s = std::to_string(interval / 50);
	s = "Time: " + zeros + s;

    window.renderText(window.getWidth() - 100, TileSize / 2, s.c_str(), resource.getFont(FontKey::Font16), resource.getColor(ColorKey::White));
}

void Game::generate(int p_s)
{
    loading = true;

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

    loading = false;
}

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

