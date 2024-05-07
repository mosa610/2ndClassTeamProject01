#pragma once

class status
{
protected:
    int cost;
    static int current_cost;
public:
    void addCurrentCost(int cost_) { current_cost += cost_; }
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