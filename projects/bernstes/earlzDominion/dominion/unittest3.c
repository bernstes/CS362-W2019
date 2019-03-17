/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * whoseTurn() in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int test_whoseTurn(int expected_player, int actual_player){
    printf("Expected Player: %d\n", expected_player);
    printf("Actual Player: %d\n", actual_player);
    if(actual_player == expected_player){
        return 0;
    }
    else{
        return -1;
    }
}

int main() {
    printf("\n*** Initializing unit tests for whoseTurn() ***\n");
    printf("whoseTurn is initialized to begin with Player 0\n");

    struct gameState A;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(4, k, 32, &A);
    printf("The game has been initialized with %d players - 0, 1, 2, and 3\n", A.numPlayers);

    printf("\nTest 1: First Turn after Game is Initialized\n");
    int turn = whoseTurn(&A);
    int result = test_whoseTurn(0, turn);
    assert_true(result);

    printf("\nTest 2: Change Turn to Third Player\n");
    A.whoseTurn = 2;
    turn = whoseTurn(&A);
    result = test_whoseTurn(2, turn);
    assert_true(result);

    printf("\nTest 3: Change Turn to Nonexistent 5th Player\n");
    A.whoseTurn = 4;
    turn = whoseTurn(&A);
    result = test_whoseTurn(4, turn);
    assert_true(result);

    printf("\nTest 4: Return to First Player\n");
    A.whoseTurn = 0;
    turn = whoseTurn(&A);
    result = test_whoseTurn(0, turn);
    assert_true(result);

    printf("\n*** Unit testing for whoseTurn is complete ***\n\n");
    return 0;
}