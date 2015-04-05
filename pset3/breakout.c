//
// breakout.c
//
// By: Gon MorVen
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

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// width, height and corner of the paddle
#define PWIDTH 70
#define PHEIGHT 15
#define CORNER 2

// width and height of each bricks
#define BWIDTH 27
#define BHEIGHT 20

// width and height of the ball
#define BALLWID 20
#define BALLHEI 20

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void removeGWindow(GWindow window, GObject gobj);

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

    // vertical and horizontal ball speed
    double xvelocity = drand48() * 2;
    double yvelocity = 2.0;

    // start
    GLabel start = newGLabel("Click to start. You have 3 lives.");
    setFont(start, "SansSerif-25");
    double x = (WIDTH - getWidth(start)) / 2;
    double y = ((HEIGHT / 2) - getHeight(start));
    setLocation(start, x, y);
    add(window, start);

    waitForClick(window);
    removeGWindow(window, start);
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // paddle movement
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - PWIDTH / 2;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
        
        // ball movement and wall collision
        move(ball, xvelocity, yvelocity);

        if (getX(ball) + BALLWID >= WIDTH || getX(ball) <= 0 )
            xvelocity = -xvelocity;
            
        else if (getY(ball) <= 0)
            yvelocity = -yvelocity;
        
        // if ball misses paddle
        if (getY(ball) + BALLHEI >= HEIGHT)
        {
            setLocation(ball, 200 - (BALLWID / 2), 300 - (BALLHEI / 2));
            lives--;
            waitForClick(window);
        }
        
        // detects collisions and applies the desired changes
        GObject object = detectCollision(window, ball);
        
        if (object == paddle)        
            yvelocity = -yvelocity;
        
        if (object != NULL)
        {
            // detects collision with bricks and removes them if hit
            if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                points++;
                bricks--;
                yvelocity = -yvelocity;
                yvelocity = yvelocity + 0.1;
                updateScoreboard(window, label, points);
            }
        }
        
        pause(10);
    }
    
    if (bricks == 0)
    {
        GLabel win = newGLabel("YOU WON!");
        setFont(win, "SansSerif-48");
        setColor(win, "3D970D");
        double x = (WIDTH - getWidth(win)) / 2;
        double y = ((HEIGHT / 3) - getHeight(win));
        setLocation(win, x, y);
        add(window, win);
    }
    else if (lives == 0)
    {
        GLabel over = newGLabel("-GAME OVER-");
        setFont(over, "SansSerif-44");
        setColor(over, "981612");
        double x = (WIDTH - getWidth(over)) / 2;
        double y = (HEIGHT - getHeight(over));
        setLocation(over, x, y);
        add(window, over);
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
    int x = 5;
    int y = 30;
    string color[5];
    color[0] = "981612";
    color[1] = "E06F0D";
    color[2] = "C2AA15";
    color[3] = "3D970D";
    color[4] = "143773";

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++, x = x + 40)
        {
            GRect brick = newGRect(x, y, BWIDTH, BHEIGHT);
            setFilled(brick, true);
            setColor(brick, color[i]);
            add(window, brick);
        }
        y = y + 30;
        x = 5;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(200 - (BALLWID / 2), 300 - (BALLHEI / 2), BALLWID, BALLHEI);
    setFilled(ball, true);
    setFillColor(ball, "2D1A40");
    setColor(ball, "241E2A");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRoundRect(200 - (PWIDTH / 2), 570, PWIDTH, PHEIGHT, CORNER);
    setFilled(paddle, true);
    setFillColor(paddle, "2A2A2A");
    setColor(paddle, "BABABA");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
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
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (WIDTH - getWidth(label)) / 2;
    double y = (HEIGHT - getHeight(label)) / 2;
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
