#include <iostream>
#include <vector>
#include "WorldState.h"
/*
 *  actions: (1) grab banana
 *           (2) climb box (down or up)
 *           (3) push box
 *           (4) walk around
 *
 *  goal:
 *      get banana
 *
 */

void testCases(){
    std::vector<WorldState> states = {
            WorldState(WorldState::atDoor, WorldState::onFloor, WorldState::nearWindow, false),
            WorldState(WorldState::atBox, WorldState::onFloor, WorldState::nearWindow, false),
            WorldState(WorldState::atBox, WorldState::onBox, WorldState::nearWindow, false),
            WorldState(WorldState::atBox, WorldState::onFloor, WorldState::underBanana, false),
            WorldState(WorldState::atBox, WorldState::onBox, WorldState::underBanana, true),
            WorldState(WorldState::atBox, WorldState::onBox, WorldState::underBanana, false),
            WorldState(WorldState::atDoor, WorldState::onFloor, WorldState::underBanana, false)
    };

    std::vector<std::vector<std::string>> expectedPlans = {
            {"walk","push","climb","grab"},
            {"push","climb","grab"},
            {"climb","push","climb","grab"},
            {"climb","grab"},
            {},
            {"grab"},
            {"walk","climb","grab"}
    };

    for(int i = 0; i < states.size(); i++){
        states[i].doProcess();
        bool plansMatch = states[i].getPlan() == expectedPlans[i];
        printf("Test case %i: %s, plans match: %s\n", i + 1, states[i].isSuccess() ? "success" : "fail", plansMatch ? "true" : "false");
    }
}


int main() {

    if (1) {
        WorldState state(WorldState::atBox, WorldState::onFloor, WorldState::underBanana, false);
        state.doProcess();
        std::cout << "Calculated plan is: " << std::endl;
        const auto &plan = state.getPlan();
        for (int i = 0; i < plan.size(); i++){
            printf("\t%i. %s\n", i + 1, plan[i].c_str());
        }

        std::cout << "and, states stack is: " << std::endl;
        const auto &states = state.getStates();
        for (int i = 0; i < states.size(); i++){
            printf("\t%i. %s\n", i + 1, states[i].c_str());
        }
    }

    testCases();

    return 0;
}
