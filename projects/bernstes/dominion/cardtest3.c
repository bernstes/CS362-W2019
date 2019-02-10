/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * outpost card in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*no bugs introduced to this function
int outpost_function(struct gameState *state, int handPos, int currentPlayer){
    //set outpost flag
    state->outpostPlayed++;

    //discard card
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
*/

int main(){
    printf("\n*** Initializing unit tests for outpost_function() ***\n");
    printf("Game will be initialized with 2 players for testing purposes\n");

    //Initialize game and copy the data to another gameState for testing
    struct gameState state;
    struct gameState testState;
    int k[10] = {adventurer, outpost, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};
    initializeGame(2, k, 32, &state);
    memcpy(&testState, &state, sizeof(struct gameState));

    //Play the Outpost card for first player using cardEffect() and remove 1 Outpost from pile
    cardEffect(outpost, 0, 0, 0, &testState, 0, 0);
    testState.supplyCount[outpost]--;

    //Outpost should be discarded from the player's hand after it's played
    printf("\nTest 1: Play Outpost from player's hand (net -1 after discard)\n");
    assert_true(compareInt(state.handCount[0] - 1, testState.handCount[0]));
    expectation(state.handCount[0] - 1, testState.handCount[0]);

    //Outpost flag should be incremented by 1
    printf("\nTest 2: Test for outpost flag to be incremented by 1\n");
    assert_true(compareInt(state.outpostPlayed + 1, testState.outpostPlayed));
    expectation(state.outpostPlayed + 1, testState.outpostPlayed);

    //Make sure the card increased the played card count after use
    printf("\nTest 3: Test for +1 increase in played card count\n");
    assert_true(compareInt(state.playedCardCount + 1, testState.playedCardCount));
    expectation(state.playedCardCount + 1, testState.playedCardCount);

    //Make sure opponent's hand remains unchanged
    printf("\nTest 4: Test for no change in opponent's hand\n");
    assert_true(compareInt(state.handCount[1], testState.handCount[1]));
    expectation(state.handCount[1], testState.handCount[1]);

    //Make sure opponent's deck remains unchanged
    printf("\nTest 5: Test for no change in opponent's deck\n");
    assert_true(compareInt(state.deckCount[1], testState.deckCount[1]));
    expectation(state.deckCount[1], testState.deckCount[1]);

    //Make sure there's no change to victory cards
    printf("\nTest 6: Test for no changes in victory card piles\n");
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
    //There should be 1 less Outpost in card pile for testState
    printf("\nTest 7: Test for no changes in kingdom card piles\n");
    printf("** The Outpost card should have 1 less card in the pile **\n");
    printf("Adventurer\n");
    assert_true(compareInt(state.supplyCount[adventurer], testState.supplyCount[adventurer]));
    expectation(state.supplyCount[adventurer], testState.supplyCount[adventurer]);
    printf("Outpost\n");
    assert_true(compareInt(state.supplyCount[outpost] - 1, testState.supplyCount[outpost]));
    expectation(state.supplyCount[outpost] - 1, testState.supplyCount[outpost]);
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

    printf("*** Unit Testing for outpost_function() is Complete ***\n\n");
    return 0;
}