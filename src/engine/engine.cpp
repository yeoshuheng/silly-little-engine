#include <engine.h>
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

class maxHCompare {
    public:
        bool operator() (limit* o1, limit* o2) {
            if (o1->getPrice() > o2->getPrice()) {return true;}
            return false;
        }
};

class minHCompare {
    public:
        bool operator() (limit* o1, limit* o2) {
            if (o1->getPrice() < o2->getPrice()) {return true;}
            return false;
        }
};

class engine {

    private:
        map<ll, limit*> idToBuyPrice;
        map<ll, limit*> idToSellPrice;
        map<ll, ll> sellVolume;
        map<ll, ll> buyVolume;
        maxh buyOrders;
        minh sellOrders;
        ll id;

        void Execute() {
            cout << "EXECUTING ORDERS:" << endl;
            while (!buyOrders.empty() && !sellOrders.empty()) {
                if (buyOrders.top()->getSize() == 0) {buyOrders.pop(); continue;}
                if (sellOrders.top()->getSize() == 0) {sellOrders.pop(); continue;}
                if (sellOrders.top()->getPrice() > buyOrders.top()->getPrice()) {break;}
                order bestBid = buyOrders.top()->retrieveOrder();
                order bestAsk = sellOrders.top()->retrieveOrder();
                cout << "BID: " << bestBid.getID() << endl;
                cout << "ASK: " << bestAsk.getID() << endl;
                cout << "EXECUTED @ " << bestBid.getPrice() << endl;
                sellVolume[bestAsk.getPrice()]--; buyVolume[bestBid.getPrice()]--;
                idToBuyPrice.erase(bestBid.getID()); idToSellPrice.erase(bestAsk.getID());
            }
        }
        void buildOutput(vector<ll> orders) {
            stringstream ss;
            for (auto it = orders.begin(); it != orders.end(); it++) {ss << *it; ss << " ";}
            cout << ss.str() << endl;
        }
    public:
        engine() {id = 0;}
        void Buy(ll price, ll quantity) {
            string rt = quantity + " @ " + price;
            buyVolume[price] += quantity;
            cout << "BIDDING: " << rt << endl;
            auto itr = idToBuyPrice.find(price);
            if (itr == idToBuyPrice.end()) {
                idToBuyPrice[price] = new limit(price);
                buyOrders.emplace(idToBuyPrice[price]);
            }
            vector<ll> orderIDs;
            while (quantity-- > 0) {
                order* buyorder = new order(price, this->id);
                orderIDs.push_back(this->id); id++;
                idToBuyPrice[price]->insertOrder(buyorder);
            }
            cout << "YOUR ORDERS: " << endl;
            buildOutput(orderIDs);
            Execute();
        }
        void Sell(ll price, ll quantity) {
            string rt = quantity + " @ " + price;
            sellVolume[price] += quantity;
            cout << "ASKING: " + rt << endl;
            auto itr = idToSellPrice.find(price);
            if (itr == idToSellPrice.end()) {
                idToSellPrice[price] = new limit(price);
                sellOrders.emplace(idToBuyPrice[price]);
            }
            vector<ll> orderIDs;
            while (quantity-- > 0) {
                order* sellorder = new order(price, this->id);
                orderIDs.push_back(this->id); id++;
                idToSellPrice[price]->insertOrder(sellorder);
            }
            cout << "YOUR ORDERS: " << endl;
            buildOutput(orderIDs);
            Execute();
        }
        void removeOrder(ll id) {
            if (idToSellPrice.find(id) != idToSellPrice.cend()) {
                ll price = idToSellPrice.find(id)->second->getPrice();
                sellVolume[price]--;
                idToSellPrice[id]->removeOrder(id);
                idToSellPrice.erase(id);
            }
            if (idToBuyPrice.find(id) != idToBuyPrice.cend()) {
                ll price = idToBuyPrice.find(id)->second->getPrice();
                buyVolume[price]--;
                idToBuyPrice[id]->removeOrder(id);
                idToBuyPrice.erase(id);
            }
        }
        void getVolume() {
            cout << "BUY VOLUME: " << endl;
            for(map<ll, ll>::iterator iter = buyVolume.begin(); iter != buyVolume.end(); ++iter) {
                if (iter->second == 0) {continue;}
                cout << iter->first << ": " << iter->second << endl;
            }
            cout << "SELL VOLUME: " << endl;
            for(map<ll, ll>::iterator iter = buyVolume.begin(); iter != buyVolume.end(); ++iter) {
                if (iter->second == 0) {continue;}
                cout << iter->first << ": " << iter->second << endl;
            }
        }
        void getBestPrice() {
            string bestBuy = "EMPTY", bestSell = "EMPTY";
            while (!buyOrders.empty()) {
                if (buyOrders.top()->getSize() == 0) {buyOrders.pop(); continue;}
                bestBuy = buyOrders.top()->getPrice();
            }
            while (!sellOrders.empty()) {
                if (sellOrders.top()->getSize() == 0) {sellOrders.pop(); continue;}
                bestSell = sellOrders.top()->getPrice();
            }
            cout << "Best Bid: " << bestBuy << " Best Ask: " << bestSell << endl;
        }
};