#include <iostream>
#include <assert.h>
#include <bitset>
#include <list>
#include <map>
class Entity {
    public: 
        int ID;
};
class Component {
    public:
        Component();
        int ID;
};
class System {
    public:
        int ID;
    virtual void run(std::list<int>*);

};
