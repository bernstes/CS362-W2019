/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * updateCoins() in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int test_updateCoins(int expected_coins, struct gameState *g){
    printf("Expected Coins: %d\n", expected_coins);
    printf("Actual Coins: %d\n", g->coins);
    if(g->coins == expected_coins){
        return 0;
    }
    else{
        return -1;
    }
}

int main(){
    printf("\n*** Initializing unit tests for updateCoins() ***\n");

    struct gameState A;
    A.coins = 0;
    A.handCount[0] = 6;
    A.hand[0][0] = copper;
    A.hand[0][1] = copper;
    A.hand[0][2] = silver;
    A.hand[0][3] = silver;
    A.hand[0][4] = gold;
    A.hand[0][5] = gold;
    updateCoins(0, &A, 0);
    printf("\nTest 1: 2 copper, 2 silver, 2 gold, no bonus\n");
    int result1 = test_updateCoins(12, &A);
    assert_true(result1);

    struct gameState B;
    B.coins = 0;
    B.handCount[0] = 6;
    B.hand[0][0] = copper;
    B.hand[0][1] = copper;
    B.hand[0][2] = silver;
    B.hand[0][3] = silver;
    B.hand[0][4] = gold;
    B.hand[0][5] = gold;
    updateCoins(0, &B, 1);
    printf("\nTest 2: 2 copper, 2 silver, 2 gold, +1 bonus\n");
    int result2 = test_updateCoins(13, &B);
    assert_true(result2);

    struct gameState C;
    C.coins = 0;
    C.handCount[0] = 5;
    C.hand[0][0] = smithy;
    C.hand[0][0] = adventurer;
    C.hand[0][0] = embargo;
    C.hand[0][0] = village;
    C.hand[0][0] = minion;
    updateCoins(0, &C, 0);
    printf("\nTest 3: No coins, no bonus\n");
    int result3 = test_updateCoins(0, &C);
    assert_true(result3);

    struct gameState D;
    D.coins = 0;
    D.handCount[0] = 5;
    D.hand[0][0] = smithy;
    D.hand[0][0] = adventurer;
    D.hand[0][0] = embargo;
    D.hand[0][0] = village;
    D.hand[0][0] = minion;
    updateCoins(0, &D, 2);
    printf("\nTest 4: No coins, +2 bonus\n");
    int result4 = test_updateCoins(2, &D);
    assert_true(result4);

    struct gameState E;
    E.coins = 0;
    E.handCount[0] = 5;
    E.hand[0][0] = smithy;
    E.hand[0][0] = adventurer;
    E.hand[0][0] = embargo;
    E.hand[0][0] = village;
    E.hand[0][0] = minion;
    updateCoins(0, &E, -2);
    printf("\nTest 5: No coins, -2 bonus\n");
    int result5 = test_updateCoins(-2, &E);
    assert_true(result5);

    printf("\n*** Unit testing for updateCoins is complete ***\n\n");
    return 0;
}