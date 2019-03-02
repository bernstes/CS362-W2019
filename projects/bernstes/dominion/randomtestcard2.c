/************************************
* Author: Samuel Bernstein
* Date: February 24, 2019
* Description: random tests for
* council room card in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
//bug - 1 buy will be removed instead of being incremented
int council_room_function(struct gameState *state, int i, int currentPlayer, int handPos){
    //+4 Cards
    for (i = 0; i < 4; i++)
    {
        drawCard(currentPlayer, state);
    }

    //+1 Buy
    //state->numBuys++;

    //remove 1 buy instead of incrementing
    state->numBuys--;

    //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
    {
        if ( i != currentPlayer )
        {
            drawCard(i, state);
        }
    }

    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}
*/

int main(){

    srand(time(NULL));
    printf("\n*** Initializing random tests for council_room_function() ***\n");

    printf("\nList of Tests:\n");
    printf("\nTest 1: Play Council Room and Draw 4 Cards (net +3 after discard)\n");
    printf("\nTest 2: Test for proper change in current player's deck count\n");
    printf("\nTest 3: Test for +1 increase in player's buy count\n");
    printf("\nTest 4: Test for +1 increase in played card count\n");
    printf("\nTest 5: Test for +1 change in opponent's hand\n");
    printf("\nTest 6: Test for -1 change in opponent's deck\n");
    printf("\nTest 7: Test for no changes in victory card piles\n");
    printf("\nTest 8: Test for no changes in kingdom card piles\n");
    printf("\nTest 9: Test for no changes in coin card piles\n");

    printf("\nSome game variables will be initialized with random values for testing purposes\n");
    printf("*** Only failing test results will be printed to consolidate results***\n");

    //Variables for gameStates and calculating random testing percentages
    struct gameState state, testState;
    float test1 = 0, test2 = 0, test3 = 0, test4 = 0, test5 = 0, test6 = 0, test7 = 0, test8 = 0, test9 = 0;

    //Loop to control number of random test iterations
    int i;
    int numTests = 1000;
    for(i = 0; i < numTests; i++) {

        //Variables for random number of players and kingdom cards
        int randSeed = rand() % 1000 + 1;
        int numPlayers = (rand() % 3) + 2;

        //Randomize the 9 remaining kingdom cards (must include card being tested)
        int k[10], r, s, randKing, valid;
        k[0] = council_room;
        for (r = 1; r < 10; r++) {
            do {
                valid = 1;
                randKing = rand() % 20 + 7;
                for (s = 0; s < r; s++) {
                    if (k[s] == randKing) {
                        valid = 0;
                    }
                }
            } while (valid == 0);
            k[r] = randKing;
        }

        //Initialize game with random player, kingdom card, and seed inputs
        initializeGame(numPlayers, k, randSeed, &state);

        //Randomize deck for player 1, including randomly placed council room card in hand
        //Both the deckCount and handCount cannot be initialized to 0 --> floating point exception: 8
        state.deckCount[0] = rand() % 50 + 1;
        state.handCount[0] = rand() % 25 + 1;
        int pos = rand() % state.handCount[0];
        state.hand[0][pos] = council_room;
        int j;
        for (j = 0; j < state.deckCount[0]; j++) {
            if (j == pos) {
                continue;
            }
            int cardType = rand() % 2;
            if (cardType == 0) {
                //put random Treasure or Victory card into deck
                state.deck[0][j] = rand() % 7;
            } else {
                //put random Kingdom Card into deck
                state.deck[0][j] = k[rand() % 10];
            }
        }

        //Randomize deck and hand counts for other players
        int p;
        for(p = 1; p < numPlayers; p++){
            state.deckCount[p] = rand() % 50 + 1;
            state.handCount[p] = rand() % 25 + 1;
        }

        //Randomize the number of buys for player 1
        state.numBuys = rand() % 10;

        printf("\nTest Iteration: %d\n", i + 1);
        printf("--------------------\n");

        //print player's hand count and deck count
        printf("Player 1 Starting Hand Count: %d\n", state.handCount[0]);
        printf("Player 1 Starting Deck Count: %d\n", state.deckCount[0]);
        printf("Player 1 Starting Discard Count: %d\n", state.discardCount[0]);
        printf("Player 1 Starting Buy Count: %d\n", state.numBuys);

        //Copy the data to additional gameState for testing
        memcpy(&testState, &state, sizeof(struct gameState));

        //Play the Adventurer card for first player using cardEffect()
        cardEffect(council_room, 0, 0, 0, &testState, 0, 0);

        //Council Room should draw 4 from player's deck and discard itself after use
        if(assert_true(compareInt(state.handCount[0] + 3, testState.handCount[0]))){
            printf("\nTest 1: Play Council Room and Draw 4 Cards (net +3 after discard)\n");
            expectation(state.handCount[0] + 3, testState.handCount[0]);
            test1++;
        }

        //Make sure the 4 cards are drawn from the player's own deck
        if(assert_true(compareInt(state.deckCount[0] - 4, testState.deckCount[0]))){
            printf("\nTest 2: Test for proper change in current player's deck count\n");
            expectation(state.deckCount[0] - 4, testState.deckCount[0]);
            test2++;
        }

        //Make sure Player's buy count is increased by 1
        if(assert_true(compareInt(state.numBuys + 1, testState.numBuys))){
            printf("\nTest 3: Test for +1 increase in player's buy count\n");
            expectation(state.numBuys + 1, testState.numBuys);
            test3++;
        }

        //Make sure the card increased the played card count after use
        if(assert_true(compareInt(state.playedCardCount + 1, testState.playedCardCount))){
            printf("\nTest 4: Test for +1 increase in played card count\n");
            expectation(state.playedCardCount + 1, testState.playedCardCount);
            test4++;
        }

        //Make sure opponent hands increases by 1
        for(p = 1; p < numPlayers; p++){
            //printf("Testing player %d\n", p + 1);
            if(assert_true(compareInt(state.handCount[p] + 1, testState.handCount[p]))){
                printf("\nTest 5: Test for +1 change in opponent's hand\n");
                expectation(state.handCount[p] + 1, testState.handCount[p]);
                test5++;
            }
        }

        //Make sure opponent decks decreases by 1
        for(p = 1; p < numPlayers; p++) {
            //printf("Testing player %d\n", p + 1);
            if(assert_true(compareInt(state.deckCount[p] - 1, testState.deckCount[p]))){
                printf("\nTest 6: Test for -1 change in opponent's deck\n");
                expectation(state.deckCount[p] - 1, testState.deckCount[p]);
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
        if(assert_true(compareInt(state.supplyCount[council_room], testState.supplyCount[council_room]))){
            printf("Test 8: Kingdom Card 1 Mismatch\n");
            expectation(state.supplyCount[council_room], testState.supplyCount[council_room]);
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

    printf("\n*** Random Testing for council_room_function() is Complete ***\n\n");

    printf("Test Results - %d Iterations\n", i);
    printf("Test 1 Pass Rate: %.2f\n", ((numTests-test1)/numTests*100));
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