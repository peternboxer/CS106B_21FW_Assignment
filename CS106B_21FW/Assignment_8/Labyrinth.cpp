#include "Labyrinth.h"
using namespace std;

int spell=0;
int potion=0;
int wand=0;

void findItem(MazeCell* ptr, int &spell, int &potion, int &wand);

bool isPathToFreedom(MazeCell* start, const string& moves) {

    /* initialize / reset */
    spell=0;
    potion=0;
    wand=0;

    int flag = 0, i=0;
    int len = moves.length();
    /* check initial position */
    findItem(start,spell,potion,wand);

    while(i<len && flag<3)
    {
        char dir = moves[i];
        switch(dir)
        {
        case 'N':
            if(start->north==nullptr)
            {
                return false;
            }
            start = start->north;
            findItem(start,spell,potion,wand);
            i++;
            break;
        case 'E':
            if(start->east==nullptr)
            {
                return false;
            }
            start = start->east;
            findItem(start,spell,potion,wand);
            i++;
            break;
        case 'S':
            if(start->south==nullptr)
            {
                return false;
            }
            start = start->south;
            findItem(start,spell,potion,wand);
            i++;
            break;
        case 'W':
            if(start->west==nullptr)
            {
                return false;
            }
            start = start->west;
            findItem(start,spell,potion,wand);
            i++;
            break;
        }
    }
    if(spell*potion*wand == 1)
    {
        return true;
    }
    return false;
}

/* helper function to determine which item */
void findItem(MazeCell* ptr, int &spell, int &potion, int &wand)
{
    switch(ptr->whatsHere)
    {
    case Item::SPELLBOOK:
        spell=1;
        break;
    case Item::POTION:
        potion=1;
        break;
    case Item::WAND:
        wand=1;
        break;
    case Item::NOTHING:
        break;
    }
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */


/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

