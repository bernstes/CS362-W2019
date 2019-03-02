/************************************
* Author: Samuel Bernstein
* Date: February 24, 2019
* Description: random tests for
* adventurer card in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
//bug - drawntreasure will register smithy, adventurer, or gardens as treasure cards rather than copper, silver, and gold
int adventurer_function(struct gameState *state, int drawntreasure, int currentPlayer, int cardDrawn, int temphand[], int z){
    while(drawntreasure<2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, state);
        }
        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        //if (cardDrawn == copper || cardDrawn == silver|| cardDrawn == gold)
        //drawntreasure will register smithy, adventurer, or gardens as treasure cards
        if (cardDrawn == smithy || cardDrawn == adventurer || cardDrawn == gardens)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }
    return 0;
}
*/

int main(){

    srand(time(NULL));
    printf("\n*** Initializing random tests for adventurer_function() ***\n");

    printf("\nList of Tests:\n");
    printf("\nTest 0: Check for >1 treasure cards in the player's deck\n");
    printf("\nTest 1: Play Adventurer and Gain 2 Cards (net +1 after discard)\n");
    printf("\nTest 2: Test for proper change in current player's deck count\n");
    printf("\nTest 3: Test for proper change in current player's discard pile (including played card)\n");
    printf("\nTest 4: Test for +1 increase in played card count\n");
    printf("\nTest 5: Test for no change in opponent's hand\n");
    printf("\nTest 6: Test for no change in opponent's deck\n");
    printf("\nTest 7: Test for no changes in victory card piles\n");
    printf("\nTest 8: Test for no changes in kingdom card piles\n");
    printf("\nTest 9: Test for no changes in coin card piles\n");


    printf("\nSome game variables will be initialized with random values for testing purposes\n");
    printf("*** Only failing test results will be printed to consolidate results***\n");

    //Variables for gameStates and calculating random testing percentages
    struct gameState state, testState;
    float test0 = 0, test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0, test6 = 0, test7 = 0, test8 = 0, test9 = 0;
    float falsePass = 0, falseFail = 0;

    //Loop to control number of random test iterations
    int i;
    int numTests = 1000;
    for(i = 0; i < numTests; i++) {

        //Variables for random number of players and kingdom cards
        int randSeed = rand() % 1000 + 1;
        int numPlayers = (rand() % 3) + 2;

        //Randomize the 9 remaining kingdom cards (must include card being tested)
        int k[10], r, s, randKing, valid;
        k[0] = adventurer;
        for(r = 1; r < 10; r++){
            do{
                valid = 1;
                randKing = rand() % 20 + 7;
                for(s = 0; s < r; s++){
                    if(k[s] == randKing){
                        valid = 0;
                    }
                 }
            }while(valid == 0);
            k[r] = randKing;
        }

        //Initialize game with random player, kingdom card, and seed inputs
        initializeGame(numPlayers, k, randSeed, &state);

        //Randomize deck for player 1, including randomly placed adventure card in hand
        //Both the deckCount and handCount cannot be initialized to 0 --> floating point exception: 8
        state.deckCount[0] = rand() % 50 + 1;
        state.handCount[0] = rand() % 25 + 1;
        int pos = rand() % state.handCount[0];
        state.hand[0][pos] = adventurer;
        int j;
        for(j = 0; j < state.deckCount[0]; j++){
            if(j == pos){
                continue;
            }
            int cardType = rand() % 2;
            if(cardType == 0){
                //put random Treasure or Victory card into deck
                state.deck[0][j] = rand() % 7;
            }
            else{
                //put random Kingdom Card into deck
                state.deck[0][j] = k[rand() % 10];
            }
        }

        printf("\nTest Iteration: %d\n", i + 1);
        printf("--------------------\n");

        //print player's hand count and deck count
        printf("Player 1 Starting Hand Count: %d\n", state.handCount[0]);
        printf("Player 1 Starting Deck Count: %d\n", state.deckCount[0]);
        printf("Player 1 Starting Discard Count: %d\n", state.discardCount[0]);

        //Copy the data to additional gameState for testing
        memcpy(&testState, &state, sizeof(struct gameState));

        //Play the Adventurer card for first player using cardEffect()
        cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);

        //Check for treasure cards in the player's deck
        int numTreasures = 0;
        int t;
        for(t = 0; t < testState.deckCount[0]; t++){
            if(testState.deck[0][t] == copper || testState.deck[0][t] == silver || testState.deck[0][t] == gold){
                numTreasures++;
            }
        }
        if(numTreasures < 2){
            printf("\nTest 0: Check for >1 treasure cards in the player's deck\n");
            printf("TEST FAILED: Not enough treasure cards in player's deck!\n");
            printf("Desired Value: >=%d, Actual Value: %d\n", 2, numTreasures);
            test0++;
        }

        //Adventurer should reveal cards until player gains 2 treasure cards to their hand
        //Bug in adventurer card looks for kingdom cards instead of treasure cards
        //Revealed cards that are not treasures should be placed in the discard pile
        if(assert_true(compareInt(state.handCount[0] + 1, testState.handCount[0]))){
            printf("\nTest 1: Play Adventurer and Gain 2 (Treasure) Cards (net +1 after discard)\n");
            expectation(state.handCount[0] + 1, testState.handCount[0]);
            test1++;
            //Check if test fails even though player has 2 treasures in hand
            if(numTreasures >= 2){
                falseFail++;
            }
        }
        //Check if test passes even though player has less than 2 treasures in hand
        else if(numTreasures < 2){
            falsePass++;
        }

        //Make sure the correct number of cards are drawn from the player's own deck
        int adventurerDiscard = testState.discardCount[0];
        if(assert_true(compareInt(state.deckCount[0] - adventurerDiscard, testState.deckCount[0]))){
            printf("\nTest 2: Test for proper change in current player's deck count\n");
            expectation(state.deckCount[0] - adventurerDiscard, testState.deckCount[0]);
            test2++;
        }

        //Make sure the unused cards are discarded to the player's own pile, including used Adventurer card
        //Bug in adventurer card function: card never discarded after being played
        if(assert_true(compareInt(state.discardCount[0] + adventurerDiscard + 1, testState.discardCount[0]))){
            printf("\nTest 3: Test for proper change in current player's discard pile (including played card)\n");
            expectation(state.discardCount[0] + adventurerDiscard + 1, testState.discardCount[0]);
            test3++;
        }

        //Make sure the card increased the played card count after use
        //Bug in adventurer card function: card never discarded after being played
        if(assert_true(compareInt(state.playedCardCount + 1, testState.playedCardCount))){
            printf("\nTest 4: Test for +1 increase in played card count\n");
            expectation(state.playedCardCount + 1, testState.playedCardCount);
            test4++;
        }

        //Make sure opponent hand(s) remains unchanged
        int p;
        for(p = 1; p < numPlayers; p++){
            //printf("Testing player %d\n", p + 1);
            if(assert_true(compareInt(state.handCount[p], testState.handCount[p]))){
                printf("\nTest 5: Test for no change in opponent's hand\n");
                expectation(state.handCount[p], testState.handCount[p]);
                test5++;
            }
        }

        //Make sure opponent deck(s) remains unchanged
        for(p = 1; p < numPlayers; p++) {
            //printf("Testing player %d\n", p + 1);
            if(assert_true(compareInt(state.deckCount[p], testState.deckCount[p]))){
                printf("\nTest 6: Test for no change in opponent's deck\n");
                expectation(state.deckCount[p], testState.deckCount[p]);
                test6++;
            }
        }

        //Make sure there's no change to victory cards
        //printf("\nTest 7: Test for no changes in victory card piles\n");
        if(assert_true(compareInt(state.supplyCount[estate], testState.supplyCount[estate]))){
            printf("Test 7: Estate Card Count Mismatch\n");
            expectation(state.supplyCount[estate], testState.supplyCount[estate]);
            test7++;
        }
        if(assert_true(compareInt(state.supplyCount[duchy], testState.supplyCount[duchy]))){
            printf("Test 7: Duchy Card Count Mismatch\n");
            expectation(state.supplyCount[duchy], testState.supplyCount[duchy]);
            test7++;
        }
        if(assert_true(compareInt(state.supplyCount[province], testState.supplyCount[province]))){
            printf("Test 7: Province Card Count Mismatch\n");
            expectation(state.supplyCount[province], testState.supplyCount[province]);
            test7++;
        }

        //Make sure there's no change to kingdom card piles
        //printf("\nTest 8: Test for no changes in kingdom card piles\n");
        if(assert_true(compareInt(state.supplyCount[adventurer], testState.supplyCount[adventurer]))){
            printf("Test 8: Kingdom Card 1 Mismatch\n");
            expectation(state.supplyCount[adventurer], testState.supplyCount[adventurer]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[1]], testState.supplyCount[k[1]]))){
            printf("Test 8: Kingdom Card 2 Mismatch\n");
            expectation(state.supplyCount[k[1]], testState.supplyCount[k[1]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[2]], testState.supplyCount[k[2]]))){
            printf("Test 8: Kingdom Card 3 Mismatch\n");
            expectation(state.supplyCount[k[2]], testState.supplyCount[k[2]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[3]], testState.supplyCount[k[3]]))){
            printf("Test 8: Kingdom Card 4 Mismatch\n");
            expectation(state.supplyCount[k[3]], testState.supplyCount[k[3]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[4]], testState.supplyCount[k[4]]))){
            printf("Test 8: Kingdom Card 5 Mismatch\n");
            expectation(state.supplyCount[k[4]], testState.supplyCount[k[4]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[5]], testState.supplyCount[k[5]]))){
            printf("Test 8: Kingdom Card 6 Mismatch\n");
            expectation(state.supplyCount[k[5]], testState.supplyCount[k[5]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[6]], testState.supplyCount[k[6]]))){
            printf("Test 8: Kingdom Card 7 Mismatch\n");
            expectation(state.supplyCount[k[6]], testState.supplyCount[k[6]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[7]], testState.supplyCount[k[7]]))){
            printf("Test 8: Kingdom Card 8 Mismatch\n");
            expectation(state.supplyCount[k[7]], testState.supplyCount[k[7]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[8]], testState.supplyCount[k[8]]))){
            printf("Test 8: Kingdom Card 9 Mismatch\n");
            expectation(state.supplyCount[k[8]], testState.supplyCount[k[8]]);
            test8++;
        }
        if(assert_true(compareInt(state.supplyCount[k[9]], testState.supplyCount[k[9]]))){
            printf("Test 8: Kingdom Card 10 Mismatch\n");
            expectation(state.supplyCount[k[9]], testState.supplyCount[k[9]]);
            test8++;
        }

        //Make sure there's no change to coin card piles
        //printf("\nTest 9: Test for no changes in coin card piles\n");
        if(assert_true(compareInt(state.supplyCount[copper], testState.supplyCount[copper]))){
            printf("Test 9: Copper Card Count Mismatch\n");
            expectation(state.supplyCount[copper], testState.supplyCount[copper]);
            test9++;
        }
        if(assert_true(compareInt(state.supplyCount[silver], testState.supplyCount[silver]))){
            printf("Test 9: Silver Card Count Mismatch\n");
            expectation(state.supplyCount[silver], testState.supplyCount[silver]);
            test9++;
        }
        if(assert_true(compareInt(state.supplyCount[gold], testState.supplyCount[gold]))){
            printf("Test 9: Gold Card Count Mismatch\n");
            expectation(state.supplyCount[gold], testState.supplyCount[gold]);
            test9++;
        }

        printf("\nIteration %d is Complete\n", i + 1);
    }

    printf("\n*** Random Testing for adventurer_function() is Complete ***\n\n");

    printf("Test Results - %d Iterations\n", i);
    printf("Test 0 Pass Rate: %.2f\n", ((numTests-test0)/numTests*100));
    printf("Test 1 Pass Rate: %.2f\n", ((numTests-test1)/numTests*100));
    printf("   False Pass Rate (test passes with < 2 treasures in deck): %.2f\n", falsePass/(numTests-test0)*100);
    printf("   False Failure Rate (test fails with >= 2 treasures in deck): %.2f\n", falseFail/test0*100);
    printf("Test 2 Pass Rate: %.2f\n", ((numTests-test2)/numTests*100));
    printf("Test 3 Pass Rate: %.2f\n", ((numTests-test3)/numTests*100));
    printf("Test 4 Pass Rate: %.2f\n", ((numTests-test4)/numTests*100));
    printf("Test 5 Pass Rate: %.2f\n", ((numTests-test5)/numTests*100));
    printf("Test 6 Pass Rate: %.2f\n", ((numTests-test6)/numTests*100));
    printf("Test 7 Pass Rate: %.2f\n", ((numTests-test7)/numTests*100));
    printf("Test 8 Pass Rate: %.2f\n", ((numTests-test8)/numTests*100));
    printf("Test 9 Pass Rate: %.2f\n\n\n", ((numTests-test9)/numTests*100));

    return 0;
}