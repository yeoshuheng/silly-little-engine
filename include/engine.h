#include <limit.h>
#include <order.h>
#include <map>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef long long ll;
typedef priority_queue<limit*, vector<limit*>, maxHCompare> maxh;
typedef priority_queue<limit*, vector<limit*>, minHCompare> minh;

class engine {
    private:
        map<ll, limit*> idToBuyPrice;
        map<ll, limit*> idToSellPrice;
        map<ll, ll> sellVolume;
        map<ll, ll> buyVolume;
        maxh buyOrders;
        minh sellOrders;
        ll id;

        void Execute();
        void buildOutput(vector<ll> orders);

    public:
        engine();
        void Buy(ll price, ll quantity);
        void Sell(ll price, ll quanity);
        void removeOrder(ll id);
        void getVolume();
        void getBestPrice();
};