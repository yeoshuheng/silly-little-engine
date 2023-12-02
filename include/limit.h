typedef long long ll;

class limit {
    class limitNode {
        order *ord;
        limitNode *nxt;
        limitNode *prv;
        limitNode(order *o);
        limitNode();
        void removeOrder();
    };
    private:
        ll price;
        ll size;
        std::map<ll, limitNode*> idMp;
        limitNode *head;
        limitNode *tail;
    public:
        limit(ll price);
        void insertOrder(order *o);
        order retrieveOrder();
        void removeOrder(ll id);
        ll getSize();
        ll getPrice();
};