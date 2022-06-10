#include "HumanPyramids.h"
#include<error.h>
#include<grid.h>
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */

double ret(Grid<double> &grid, int row, int col, int pyramidHeight);
double weightOnBackOf(int row, int col, int pyramidHeight) {

    /* table to store known value */
    Grid<double> map(pyramidHeight, pyramidHeight,0);

     double weight = ret(map,row, col, pyramidHeight);

    return weight;
}

double ret(Grid<double> &grid, int row, int col, int pyramidHeight)
{
    double base = 160;
    double weight = 0;

    /* out of bound */
    if(col>row || row<0 ||col<0|| row >= pyramidHeight)
    {
        error("invalid input.");
    }
    /* base case */
    if(row==0)
    {
        return 0;
    }
    /* recursive case */
    /* row >0 col=0 */
    else if(col == 0 )
    {
        if(grid[row-1][col] == 0)
        {
            weight = 0.5*(base + ret(grid, row-1, col, pyramidHeight));
            grid[row-1][col] = weight;
        }
        else
        {
            weight = grid[row-1][col];
        }

    }
    else if(row == col)
    {
        if(grid[row-1][col-1] == 0)
        {
            weight = 0.5*( base + ret(grid,row-1, col-1, pyramidHeight));
            grid[row-1][col-1] = weight;
        }
        else
        {
            weight = grid[row-1][col-1];
        }
    }
    /* row >0 col >0 */
    else
    {
        /* both unknown */
        if(grid[row-1][col]==0 && grid[row-1][col-1]==0)
        {
            weight = 0.5*( 2*base + ret(grid,row-1, col, pyramidHeight) + ret(grid,row-1, col-1, pyramidHeight));
            grid[row-1][col] = 0.5*(base + ret(grid,row-1, col, pyramidHeight));
            grid[row-1][col-1] = 0.5*(base+ret(grid, row-1, col-1, pyramidHeight));
        }
        else if(grid[row-1][col]==0 && grid[row-1][col-1]!=0)
        {
            grid[row-1][col] = 0.5*(base + ret(grid,row-1, col, pyramidHeight));
            weight = grid[row-1][col] + grid[row-1][col-1];
        }
        else if(grid[row-1][col]!=0 && grid[row-1][col-1]==0)
        {
            grid[row-1][col-1] = 0.5*(base+ret(grid, row-1, col-1, pyramidHeight));
            weight = grid[row-1][col] + grid[row-1][col-1];
        }
        /* both known in the table */
        else
        {
            weight = grid[row-1][col] + grid[row-1][col-1];
        }
    }
    return weight;
}


/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */





/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */
    //SHOW_ERROR("This test is configured to always fail until you delete this line from\n         HumanPyramids.cpp. Once you have implemented memoization and want\n         to check whether it works correctly, remove the indicated line.");

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
