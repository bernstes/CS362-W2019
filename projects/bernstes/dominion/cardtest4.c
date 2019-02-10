/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * council room card in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*bug - 1 buy will be removed instead of being incremented
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
    printf("\n*** Initializing unit tests for council_room_function() ***\n");
    printf("Game will be initialized with 2 players for testing purposes\n");

    //Initialize game and copy the data to another gameState for testing
    struct gameState state;
    struct gameState testState;
    int k[10] = {adventurer, council_room, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 32, &state);
    memcpy(&testState, &state, sizeof(struct gameState));

    //Play the Council Room card for first player using cardEffect() and remove 1 Council Room from pile
    cardEffect(council_room, 0, 0, 0, &testState, 0, 0);
    testState.supplyCount[council_room]--;


    //Council Room should draw 4 from player's deck and discard itself after use
    printf("\nTest 1: Play Council Room and Draw 4 Cards (net +3 after discard)\n");
    assert_true(compareInt(state.handCount[0] + 3, testState.handCount[0]));
    expectation(state.handCount[0] + 3, testState.handCount[0]);

    //Make sure the 4 cards are drawn from the player's own deck
    printf("\nTest 2: Test for proper change in current player's deck count\n");
    assert_true(compareInt(state.deckCount[0] - 4, testState.deckCount[0]));
    expectation(state.deckCount[0] - 4, testState.deckCount[0]);

    //Make sure Player's buy count is increased by 1
    printf("\nTest 3: Test for +1 increase in player's buy count\n");
    assert_true(compareInt(state.numBuys + 1, testState.numBuys));
    expectation(state.numBuys + 1, testState.numBuys);

    //Make sure the card increased the played card count after use
    printf("\nTest 4: Test for +1 increase in played card count\n");
    assert_true(compareInt(state.playedCardCount + 1, testState.playedCardCount));
    expectation(state.playedCardCount + 1, testState.playedCardCount);

    //Make sure opponent's hand increases by 1
    printf("\nTest 5: Test for +1 change in opponent's hand\n");
    assert_true(compareInt(state.handCount[1] + 1, testState.handCount[1]));
    expectation(state.handCount[1] + 1, testState.handCount[1]);

    //Make sure opponent's deck decreases by 1
    printf("\nTest 6: Test for -1 change in opponent's deck\n");
    assert_true(compareInt(state.deckCount[1] - 1, testState.deckCount[1]));
    expectation(state.deckCount[1] - 1, testState.deckCount[1]);

    //Make sure there's no change to victory cards
    printf("\nTest 7: Test for no changes in victory card piles\n");
    printf("Estate\n");
    assert_true(compareInt(state.supplyCount[estate], testState.supplyCount[estate]));
    expectation(state.supplyCount[estate], testState.supplyCount[estate]);
    printf("Duchy\n");
    assert_true(compareInt(state.supplyCount[duchy], testState.supplyCount[duchy]));
    expectation(state.supplyCount[duchy], testState.supplyCount[duchy]);
    printf("Province\n");
    assert_true(compareInt(state.supplyCount[province], testState.supplyCount[province]));
    expectation(state.supplyCount[province], testState.supplyCount[province]);

    //Make sure there's no change to kingdom card piles
    //There should be 1 less Council Room in card pile for testState
    printf("\nTest 8: Test for no changes in kingdom card piles\n");
    printf("** The Council Room card should have 1 less card in the pile **\n");
    printf("Adventurer\n");
    assert_true(compareInt(state.supplyCount[adventurer], testState.supplyCount[adventurer]));
    expectation(state.supplyCount[adventurer], testState.supplyCount[adventurer]);
    printf("Council Rool\n");
    assert_true(compareInt(state.supplyCount[council_room] - 1, testState.supplyCount[council_room]));
    expectation(state.supplyCount[council_room] - 1, testState.supplyCount[council_room]);
    printf("Embargo\n");
    assert_true(compareInt(state.supplyCount[embargo], testState.supplyCount[embargo]));
    expectation(state.supplyCount[embargo], testState.supplyCount[embargo]);
    printf("Village\n");
    assert_true(compareInt(state.supplyCount[village], testState.supplyCount[village]));
    expectation(state.supplyCount[village], testState.supplyCount[village]);
    printf("Minion\n");
    assert_true(compareInt(state.supplyCount[minion], testState.supplyCount[minion]));
    expectation(state.supplyCount[minion], testState.supplyCount[minion]);
    printf("Mine\n");
    assert_true(compareInt(state.supplyCount[mine], testState.supplyCount[mine]));
    expectation(state.supplyCount[mine], testState.supplyCount[mine]);
    printf("Cutpurse\n");
    assert_true(compareInt(state.supplyCount[cutpurse], testState.supplyCount[cutpurse]));
    expectation(state.supplyCount[cutpurse], testState.supplyCount[cutpurse]);
    printf("Sea Hag\n");
    assert_true(compareInt(state.supplyCount[sea_hag], testState.supplyCount[sea_hag]));
    expectation(state.supplyCount[sea_hag], testState.supplyCount[sea_hag]);
    printf("Tribute\n");
    assert_true(compareInt(state.supplyCount[tribute], testState.supplyCount[tribute]));
    expectation(state.supplyCount[tribute], testState.supplyCount[tribute]);
    printf("Smithy\n");
    assert_true(compareInt(state.supplyCount[smithy], testState.supplyCount[smithy]));
    expectation(state.supplyCount[smithy], testState.supplyCount[smithy]);

    //Make sure there's no change to coin card piles
    printf("\nTest 8: Test for no changes in coin card piles\n");
    printf("Copper\n");
    assert_true(compareInt(state.supplyCount[copper], testState.supplyCount[copper]));
    expectation(state.supplyCount[copper], testState.supplyCount[copper]);
    printf("Silver\n");
    assert_true(compareInt(state.supplyCount[silver], testState.supplyCount[silver]));
    expectation(state.supplyCount[silver], testState.supplyCount[silver]);
    printf("Gold\n");
    assert_true(compareInt(state.supplyCount[gold], testState.supplyCount[gold]));
    expectation(state.supplyCount[gold], testState.supplyCount[gold]);

    printf("\n*** Unit Testing for council_room_function() is Complete ***\n\n");
    return 0;
}