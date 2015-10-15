//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

//height and width of bricks
#define HBRI 10
#define WBRI 30

// radius of ball in pixels
#define RADIUS 10

// height and width of paddle
#define HPAD 10
#define WPAD 50
#define PADDLE_Y 550

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        double velocityX = drand48() * 5.0;
        double velocityY = 4.0;
                
        while (true)
        {
            GEvent mouse = getNextEvent(MOUSE_EVENT);
            
            if (mouse != NULL)
            {
                if (getEventType(mouse) == MOUSE_MOVED)
                {
                    double x = getX(mouse) - WPAD / 2;
                    setLocation(paddle, x, PADDLE_Y);
                }
            }
            
            
            move (ball, velocityX, velocityY);
            
            if (getX(ball) + RADIUS * 2 >= WIDTH)
            {
                velocityX = -velocityX;
            }
            
            else if (getX(ball) <= 0)
            {
                velocityX = -velocityX;
            }
            
            else if (getY(ball) + RADIUS * 2 >= HEIGHT)
            {
                lives--;
                
                if (lives <= 0)
                {
                    updateScoreboard(window, label, lives);
                    removeGWindow(window, ball);
                    removeGWindow(window, paddle);
                }
                else
                {
                    setLocation(ball, (WIDTH / 2 - RADIUS), HEIGHT / 2 + RADIUS);
                    setLocation(paddle, (WIDTH - WPAD) / 2, PADDLE_Y);
                    waitForClick();
                    velocityX = drand48() * 5.0;
                }
            }
            
            else if (getY(ball) <= 0)
            {
                velocityY = -velocityY;
            }
            
            GObject object = detectCollision(window, ball);
            
            if (detectCollision(window, ball))
            {
                if (object == paddle)
                {
                    velocityY = -velocityY;
                }
                
                else if (strcmp(getType(object), "GRect") == 0)
                {
                    if (strcmp(getType(object), "GLabel") != 0)
                    {
                        velocityY = -velocityY;
                        removeGWindow(window, object);
                        bricks--;
                        points++;
                        updateScoreboard(window, label, points);
                        
                        if(bricks <= 0)
                        {
                            removeGWindow(window, ball);
                            removeGWindow(window, paddle);
                            return false;
                        }
                        
                    }
                }
            }
            
            pause(10);         
        }
    }
    
    
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int bricksX = 5;
    int bricksY = 60;
    char* brickColor[10] = {"#00FFFF", "#00FA9A", "#98FB98", "#7FFFD4", "#40E0D0", "#FFC0CB", 
                            "#DDA0DD", "#FF69B4", "#EE82EE", "#BA55D3"};
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect R1 = newGRect(bricksX + j * (WIDTH / COLS), bricksY + i * (HBRI + 5), WBRI, HBRI);
            setFilled(R1, true);
            setColor(R1, brickColor[i]);
            add(window, R1);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval ((WIDTH / 2 - RADIUS), HEIGHT / 2 + RADIUS, (RADIUS * 2), (RADIUS * 2));
    setFilled(ball, true);
    setColor(ball, "#00BFFF");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH - WPAD) / 2, PADDLE_Y, WPAD, HPAD);
    setFilled(paddle, true);
    setColor(paddle, "GRAY");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("hello");
    setFont(label, "SansSerif-50");
    setColor(label, "GRAY");
    double x = (WIDTH - getWidth(label)) / 2;
    double y = HEIGHT / 2 - 100;
    setLocation(label, x, y);
    add(window, label);
        
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{    
    // update label
    char s[12];
    
    if(points <= 0)
    {
        sprintf(s, "You died :(");
        setLabel(label, s);
    }
    
    else if(points == (COLS * ROWS))
    {
        sprintf(s, "You won :D");
        setLabel(label, s);
    }    
    
    else
    {
        char s[12];
        sprintf(s, "%i", points);
        setLabel(label, s);
    }

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
