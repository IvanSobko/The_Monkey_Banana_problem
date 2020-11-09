
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
    funcStack.emplace_back(__func__);
    if (monkeyHorizontal == atBox){
        if (monkeyVertical == onFloor){
            monkeyVertical = onBox;
        } else {
            monkeyVertical = onFloor;
        }

    }
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
    static int safeCounter = 0;
    if (safeCounter > 50) {
        success = false;
        return;
    }

    stateStack.push_back(toString());

    if (hasBanana){
        success = true;
        return;
    }

    if (boxPos == underBanana){
        if (monkeyVertical == onBox){
            //grab
            grab();
        } else if (monkeyHorizontal == atBox){
            climb();
        } else{
            //walk
            walk(atBox);
        }
    } else {
        //walk or push
        if (monkeyHorizontal == atBox){
            if (monkeyVertical == onFloor){
                push(underBanana);
            } else {
                climb();
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
