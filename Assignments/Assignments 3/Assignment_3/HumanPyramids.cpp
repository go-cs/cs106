#include "HumanPyramids.h"
#include "error.h"
#include "gridlocation.h"
#include "vector.h"
#include "map.h"

using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */
Map<GridLocation, double> table;
double weightOnBackOf(int row, int col, int pyramidHeight) {
    GridLocation a;
    a.row = row; a.col = col;
    if (a.row < 0 || a.col < 0) error("out of bounds.");
    else if (a.row >= pyramidHeight || a.col > a.row) error("out of bounds");
    else if (a.row == 0 && a.col == 0) return 0;
    else if (a.row == 1) return 80;
    else {
        GridLocation b, c;
        b.row = a.row - 1; b.col = a.col;
        c.row = a.row - 1; c.col = a.col - 1;
        if (a.col == 0) {
            if (table.containsKey(b)) return table[b]/2 + 80;
            else{
                table[b]=weightOnBackOf(a.row - 1, 0, pyramidHeight);
                return 80 +table[b]/2;
            }
        }
        else if (a.col == a.row) {
            if (table.containsKey(c)) return table[c]/2 + 80;
            else{
                table[c] = weightOnBackOf(a.row - 1, a.col - 1, pyramidHeight);
                return 80 + table[c]/2;
            }
        }
        else {
            double sum = 0.0;
            if (table.containsKey(b)) sum += table[b]/2 + 80;
            else{
                table[b] = weightOnBackOf(a.row - 1, a.col, pyramidHeight);
                sum+=table[b]/2+80;
            }
            if (table.containsKey(c)) sum += table[c]/2 + 80;
            else{
                table[c] = weightOnBackOf(a.row - 1, a.col - 1, pyramidHeight);
                sum += table[c]/2 +80;
            }
            return sum;
        }
    }

}


/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
STUDENT_TEST("Check to see if it is within range.") {
    EXPECT_ERROR(weightOnBackOf(-1, 2, 3));
    EXPECT_ERROR(weightOnBackOf(1, 2, 5));
    EXPECT_ERROR(weightOnBackOf(6, 1, 5));
}

STUDENT_TEST("Check some persons from the handout.") {
    EXPECT_EQUAL(weightOnBackOf(0, 0, 5), 0);//A
    EXPECT_EQUAL(weightOnBackOf(1,0,5), 80);//B or C
    EXPECT_EQUAL(weightOnBackOf(2, 0, 5), 120);//D
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);//E
    EXPECT_EQUAL(weightOnBackOf(3, 1, 5), 340);//H
    EXPECT_EQUAL(weightOnBackOf(4, 2, 5), 500);//M

}













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
