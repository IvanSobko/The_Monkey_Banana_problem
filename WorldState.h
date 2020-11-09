#ifndef MONKEY_AND_BANANA_PROBLEM_WORLDSTATE_H
#define MONKEY_AND_BANANA_PROBLEM_WORLDSTATE_H

#include <iostream>
#include <vector>

class WorldState
{
public:
    enum HorizontalMonkey{
        atDoor,
        atBox
    };

    enum VerticalMonkey{
        onFloor,
        onBox
    };

    enum Box{
        nearWindow,
        underBanana
    };


    WorldState(HorizontalMonkey horizontalMonkey, VerticalMonkey verticalMonkey, Box boxPos, bool has);

    std::string toString() const;
    void doProcess();
    std::vector<std::string> getPlan();
    std::vector<std::string> getStates();
    bool isSuccess() const;

private:
    void grab();
    void climb();
    void walk(HorizontalMonkey newPos);
    void push(Box to);

    HorizontalMonkey monkeyHorizontal;
    VerticalMonkey monkeyVertical;
    Box boxPos;
    bool hasBanana = false;

    bool success = false;
    std::vector<std::string> funcStack;
    std::vector<std::string> stateStack;
};


#endif//MONKEY_AND_BANANA_PROBLEM_WORLDSTATE_H
