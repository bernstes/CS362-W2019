/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * isGameOver() in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int test_isGameOver(int expected_result, int game_status){
    printf("Expected Result: %d\n", expected_result);
    printf("Actual Result: %d\n", game_status);
    if(game_status == expected_result){
        return 0;
    }
    else{
        return -1;
    }
}

int main(){
    printf("\n*** Initializing unit tests for isGameOver() ***\n");
    printf("isGameOver returns 1 if true, 0 if false\n");

    struct gameState A;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 32, &A);

    printf("\nTest 1: Piles Initialized to Begin Gameplay\n");
    int game_status = isGameOver(&A);
    int result1 = test_isGameOver(0, game_status);
    assert_true(result1);

    printf("\nTest 2: Province Cards Empty\n");
    A.supplyCount[province] = 0;
    game_status = isGameOver(&A);
    int result2 = test_isGameOver(1, game_status);
    assert_true(result2);
    //reset supply count for province cards
    A.supplyCount[province] = 8;

    printf("\nTest 3: 2 Supply Piles Empty\n");
    A.supplyCount[adventurer] = 0;
    A.supplyCount[embargo] = 0;
    game_status = isGameOver(&A);
    int result3 = test_isGameOver(0, game_status);
    assert_true(result3);
    //reset supply count for adventurer and embargo cards
    A.supplyCount[adventurer] = 10;
    A.supplyCount[embargo] = 10;

    printf("\nTest 4: 3 Supply Piles Empty\n");
    A.supplyCount[adventurer] = 0;
    A.supplyCount[embargo] = 0;
    A.supplyCount[village] = 0;
    game_status = isGameOver(&A);
    int result4 = test_isGameOver(1, game_status);
    assert_true(result4);
    //reset supply count for adventurer, embargo, and village cards
    A.supplyCount[adventurer] = 10;
    A.supplyCount[embargo] = 10;
    A.supplyCount[village] = 10;

    printf("\nTest 5: Province Cards Empty and 3 Supply Piles Empty\n");
    A.supplyCount[province] = 0;
    A.supplyCount[adventurer] = 0;
    A.supplyCount[embargo] = 0;
    A.supplyCount[village] = 0;
    game_status = isGameOver(&A);
    int result5 = test_isGameOver(1, game_status);
    assert_true(result5);
    //reset supply count for all cards
    A.supplyCount[province] = 8;
    A.supplyCount[adventurer] = 10;
    A.supplyCount[embargo] = 10;
    A.supplyCount[village] = 10;

    printf("\nTest 6: 3 Supply Piles Empty, one of which isn't used for current game\n");
    printf("Unused supply cards should have a supply count of -1 instead of 0\n");
    A.supplyCount[adventurer] = 0;
    A.supplyCount[embargo] = 0;
    A.supplyCount[steward] = 0;
    game_status = isGameOver(&A);
    int result6 = test_isGameOver(0, game_status);
    assert_true(result6);
    //reset supply count for adventurer, embargo, and village cards
    A.supplyCount[adventurer] = 10;
    A.supplyCount[embargo] = 10;
    A.supplyCount[steward] = -1;


    printf("\n*** Unit testing for isGameOver is complete ***\n\n");
    return 0;
}