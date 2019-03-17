/************************************
 * Author: Samuel Bernstein
 * Date: February 9, 2019
 * Description: unit test for
 * adventurer card in dominion.c
************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*bug - drawntreasure will register smithy, adventurer, or gardens as treasure cards rather than copper, silver, and gold
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
    printf("\n*** Initializing unit tests for adventurer_function() ***\n");
    printf("Game will be initialized with 2 players for testing purposes\n");

    //Variables for gameState and kingdom cards
    struct gameState state;
    struct gameState testState;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    //Initialize game and copy the data to another gameState for testing
    initializeGame(2, k, 32, &state);
    memcpy(&testState, &state, sizeof(struct gameState));
    //Play the Adventurer card for first player using cardEffect() and remove 1 Adventurer from pile
    cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);
    testState.supplyCount[adventurer]--;
    //Hardcode player's hand to test for adventurer accuracy
    testState.hand[0][0] = smithy;
    testState.hand[0][1] = duchy;
    testState.hand[0][2] = estate;
    testState.hand[0][3] = province;
    testState.hand[0][4] = cutpurse;
    testState.deck[0][0] = copper;
    testState.deck[0][1] = silver;
    testState.deck[0][2] = gold;
    testState.deck[0][3] = copper;
    testState.deck[0][4] = silver;

    //Adventurer should reveal cards until player gains 2 treasure cards to their hand
    //Revealed cards that are not treasures should be placed in the discard pile
    printf("\nTest 1a: Play Adventurer and Gain 2 Treasure Cards (net +1 after discard)\n");
    assert_true(compareInt(state.handCount[0] + 1, testState.handCount[0]));
    expectation(state.handCount[0] + 1, testState.handCount[0]);

    //Make sure the 2 cards are drawn from the player's own deck
    printf("\nTest 1b: Test for proper change in current player's deck count (-2)\n");
    assert_true(compareInt(state.deckCount[0] - 2, testState.deckCount[0]));
    expectation(state.deckCount[0] - 2, testState.deckCount[0]);

    //Make sure the unused cards are discarded to the player's own pile, including used Adventurer card
    printf("\nTest 1c: Test for proper change in current player's discard pile (+1)\n");
    assert_true(compareInt(state.discardCount[0] + 1, testState.discardCount[0]));
    expectation(state.discardCount[0] + 1, testState.discardCount[0]);

    //Initialize game and copy the data to another gameState for testing
    initializeGame(2, k, 32, &state);
    memcpy(&testState, &state, sizeof(struct gameState));
    //Play the Adventurer card for first player using cardEffect() and remove 1 Adventurer from pile
    cardEffect(adventurer, 0, 0, 0, &testState, 0, 0);
    testState.supplyCount[adventurer]--;
    //Hardcode player's hand to test for adventurer accuracy
    testState.hand[0][0] = mine;
    testState.hand[0][1] = duchy;
    testState.hand[0][2] = adventurer;
    testState.hand[0][3] = province;
    testState.hand[0][4] = cutpurse;
    testState.deck[0][0] = mine;
    testState.deck[0][1] = duchy;
    testState.deck[0][2] = smithy;
    testState.deck[0][3] = province;
    testState.deck[0][4] = gardens;

    //Adventurer should reveal cards until player gains 2 treasure cards to their hand
    //Revealed cards that are not treasures should be placed in the discard pile
    printf("\nTest 2a: Play Adventurer with no Treasure Cards in Deck/Discard Piles (net -1 after discard)\n");
    assert_true(compareInt(state.handCount[0] - 1, testState.handCount[0]));
    expectation(state.handCount[0] - 1, testState.handCount[0]);

    //Make sure the cards are drawn from the player's own deck
    printf("\nTest 2b: Test for proper change in current player's deck count (-5)\n");
    assert_true(compareInt(state.deckCount[0] - 5, testState.deckCount[0]));
    expectation(state.deckCount[0] - 5, testState.deckCount[0]);

    //Make sure the unused cards are discarded to the player's own pile, including used Adventurer card
    printf("\nTest 2c: Test for proper change in current player's discard pile (+6)\n");
    assert_true(compareInt(state.discardCount[0] + 6, testState.discardCount[0]));
    expectation(state.discardCount[0] + 6, testState.discardCount[0]);

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
    //There should be 1 less Adventurer in card pile for testState
    printf("\nTest 7: Test for no changes in kingdom card piles\n");
    printf("** The Adventurer card should have 1 less card in the pile **\n");
    printf("Adventurer\n");
    assert_true(compareInt(state.supplyCount[adventurer] - 1, testState.supplyCount[adventurer]));
    expectation(state.supplyCount[adventurer] - 1, testState.supplyCount[adventurer]);
    printf("Gardens\n");
    assert_true(compareInt(state.supplyCount[gardens], testState.supplyCount[gardens]));
    expectation(state.supplyCount[gardens], testState.supplyCount[gardens]);
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


    printf("\n*** Unit Testing for adventurer_function() is Complete ***\n\n");
    return 0;
}