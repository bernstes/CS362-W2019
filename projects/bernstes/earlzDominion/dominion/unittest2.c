/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * getCost() in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int test_getCost(int expected_cost, int card_cost){
    printf("Expected Cost: %d\n", expected_cost);
    printf("Actual Cost: %d\n", card_cost);
    if(card_cost == expected_cost){
        return 0;
    }
    else{
        return -1;
    }
}

int main(){
    printf("\n*** Initializing unit tests for cardCost() ***\n");

    struct gameState A;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 32, &A);

    printf("\nTest 1: Adventurer\n");
    int result1 = test_getCost(6, getCost(adventurer));
    assert_true(result1);

    printf("\nTest 2: Embargo\n");
    int result2 = test_getCost(2, getCost(embargo));
    assert_true(result2);

    printf("\nTest 3: Minion\n");
    int result3 = test_getCost(5, getCost(minion));
    assert_true(result3);

    printf("\nTest 4: Cutpurse\n");
    int result4 = test_getCost(4, getCost(cutpurse));
    assert_true(result4);

    printf("\nTest 5: Tribute\n");
    int result5 = test_getCost(5, getCost(tribute));
    assert_true(result5);

    printf("\nTest 6: Index out of range (below)\n");
    int card_index = -1;
    int result6 = test_getCost(NULL, getCost(k[card_index]));
    assert_true(result6);

    printf("\nTest 7: Index out of range (above)\n");
    card_index = 10;
    int result7 = test_getCost(NULL, getCost(k[card_index]));
    assert_true(result7);

    printf("\n*** Unit testing for cardCost is complete ***\n\n");
    return 0;
}