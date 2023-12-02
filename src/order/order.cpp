#include "order.h"
#include <ctime>

typedef long long ll;

class order {
    private:
        ll price;
        time_t time;
        ll id;
    public:
        order (ll p, ll i) {
            this->id = i;
            this->price = p;
            this->time = std::time(0);
        }
        ll getPrice() {
            return this->price;
        };
        time_t getPlaceTime() {
            return this->time;
        };
        ll getID() {return this->id;}
};