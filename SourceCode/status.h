#pragma once

class status
{
protected:
    int cost;
    static int current_cost;
public:
    void addCurrentCost(int cost_) { current_cost += cost_; }
    int getCost() { return current_cost; }
};

enum Attribute
{
    stone,
    wood,
};

enum Weather
{
    nornal,
    rain,
    thunder,
};