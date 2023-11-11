
#include <vector>

struct SubscriptionPeriod
{
    SubscriptionPeriod(const long long start, const long long initCost):
    StartingDay{start},
    EndingDay{start},
    InitCost{initCost},
    TotalCost{1+initCost}
    {
    }

    bool IsCombined(const long long newEndDay)
    {
        const auto newCost = newEndDay - StartingDay + 1 + InitCost;
        const auto alternativeCost = TotalCost + (1 + InitCost);
        if(newCost <= alternativeCost)
        {
            EndingDay = newEndDay;
            TotalCost = newCost;
            return true;
        }
        return false;
    }
    long long StartingDay;
    long long EndingDay;
    long long InitCost;
    long long TotalCost;
};

long long GetTotalCost(const long long initCost, const std::vector<long long>& days)
{
    if(days.empty())
    {
        return 0ULL;
    }
    auto itr = days.begin();
    std::vector<SubscriptionPeriod> periods{SubscriptionPeriod{*itr, initCost}};
    while(++itr != days.end())
    {
        if(!periods.back().IsCombined(*itr))
        {
            periods.emplace_back(*itr, initCost);
        }
    }
    long long retVal{0ULL};
    for(const auto& period : periods)
    {
        retVal += period.TotalCost;
    }
    return retVal;
}