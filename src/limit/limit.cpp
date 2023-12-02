#include <limit.h>
#include <order.h>
#include <map>

typedef long long ll;

class limit {

    class limitNode {
            public:
                order *ord;
                limitNode *nxt = nullptr;
                limitNode *prv = nullptr;
                limitNode(order *o) {
                    this->ord = o;
                }
                limitNode() {
                    this->ord = NULL;
                }
                void removeOrder() {
                    limitNode *next = nxt; 
                    limitNode *prev = prv;
                    prev->nxt = next;
                    next->prv = prev;
                }
        };

    std::map<ll, limitNode*> idMp;
    limitNode *head;
    limitNode *tail; 
    ll size;
    ll price;
    public:
        limit(ll p) {
            price = p;
            size = 0;
            head = new limitNode();
            tail = new limitNode();
            head->nxt = tail;
            tail->prv = head;
        }
        void insertOrder(order *o) {
            limitNode *tmp = tail->prv;
            limitNode *curr = new limitNode(o);
            tmp->nxt = curr;
            curr->nxt = tail;
            tail->prv = curr;
            size++;
            idMp[o->getID()] = curr;
        }
        order retrieveOrder() {
            limitNode *ret = head->nxt;
            limitNode *tmp = ret->nxt;
            ret->prv = nullptr;
            ret->nxt = nullptr;
            tmp->prv = head;
            head->nxt = tmp;
            idMp.erase(ret->ord->getID());
            size--;
            return *(ret->ord);
        }
        
        void removeOrder(ll id) {
            auto itr = idMp.find(id);
            if (itr == idMp.end()) {
                return;
            }
            limitNode *rm = itr->second;
            size--;
            rm->removeOrder();
            idMp.erase(id);
        }
        ll getSize() {return this->size;}
        ll getPrice() {return this->price;}
};