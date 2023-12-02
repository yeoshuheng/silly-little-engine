#include <ctime>

typedef long long ll;

class order {
    private:
        ll price;
        time_t time;
        ll id;
    public:
        order(ll price, ll id);
        ll getPrice();
        time_t getPlaceTime();
        ll getID();
};