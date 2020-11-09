
#include "WorldState.h"
WorldState::WorldState(WorldState::HorizontalMonkey pos1, WorldState::VerticalMonkey pos2, WorldState::Box pos3, bool has):
        monkeyHorizontal(pos1), monkeyVertical(pos2), boxPos(pos3), hasBanana(has) {}


std::string WorldState::toString() const
{
    std::string res;
    res.append("Monkey is at ");
    switch (monkeyHorizontal) {
        case atDoor: res.append("[door] "); break;
        case atBox:  res.append("[box] "); break;
    }
    res.append("and on ");
    switch (monkeyVertical) {
        case onFloor: res.append("the [floor], "); break;
        case onBox:  res.append("the [box], "); break;
    }
    res.append("box is near ");
    switch (boxPos) {
        case nearWindow: res.append("[window], "); break;
        case underBanana:  res.append("[banana], "); break;
    }

    res.append(hasBanana ? "monkey [has] banana." : "monkey [hasn't] banana.");
    return res;
}
void WorldState::grab()
{
    funcStack.emplace_back(__func__);
    if (monkeyVertical == onBox && boxPos == underBanana) {
        hasBanana = true;
    }
}
void WorldState::climb()
{
    std::string func(__func__ );
    if (monkeyHorizontal == atBox){
        if (monkeyVertical == onFloor){
            func += "_up";
            monkeyVertical = onBox;
        } else {
            func += "_down";
            monkeyVertical = onFloor;
        }
    }
    funcStack.emplace_back(func);
}
void WorldState::walk(WorldState::HorizontalMonkey newPos)
{
    funcStack.emplace_back(__func__);
    if (monkeyVertical == onFloor){
        monkeyHorizontal = newPos;
    }
}
void WorldState::push(WorldState::Box to)
{
    funcStack.emplace_back(__func__);
    if (monkeyHorizontal == atBox && monkeyVertical == onFloor){
        boxPos = to;
    }
}
void WorldState::doProcess()
{
    // Recursion safe counter. Since program is very little, recursion shouldn't be deeper than 20-30 levels
    static int safeCounter = 0;
    if (safeCounter > 25) {
        success = false;
        return;
    }

    stateStack.push_back(toString());


    // Now we have to check world states, and take actions according to these states.
    // Firstly we check if we have a banana, to go out of recursion.
    if (hasBanana){
        success = true;
        return;
    }

    // Secondly, we check from the best states (e.g. can get the banana),
    // going down to least favourable states (e.g. need to make many moves to grab a banana).
    if (boxPos == underBanana){
        if (monkeyVertical == onBox){
            grab();
        } else if (monkeyHorizontal == atBox){
            climb(); //climb up
        } else{
            walk(atBox);
        }
    } else {
        if (monkeyHorizontal == atBox){
            if (monkeyVertical == onFloor){
                push(underBanana);
            } else {
                climb(); //climb down
            }
        } else {
            walk(atBox);
        }
    }
    safeCounter++;
    doProcess();
}
std::vector<std::string> WorldState::getPlan()
{
    return funcStack;
}
std::vector<std::string> WorldState::getStates()
{
    return stateStack;
}
bool WorldState::isSuccess() const
{
    return success;
}
