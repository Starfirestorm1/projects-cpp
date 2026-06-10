#include <iostream>
#include <assert.h>
#include <bitset>
#include <list>
#include <map>
#include <exception>
class Entity {
    public: 
        int ID;
};
class Component {
    public:
        Component(){};
        int ID;
};
class System {
    public:
        int ID;
    virtual void run(std::list<int>*){};

};
// template <typename T> class Manager {
//     public:
//     T show (T some_var){
//         std::cout << some_var << std::endl;
//         return 0;
//     }
// };
class Signature {
    public:
        std::map<std::string, std::bitset<5>> mComponentSignatures;
        std::map<int, std::bitset<5>> mEntitySignatures;
        std::map<int, std::bitset<5>> mSystemSignatures;
        template<typename T>
        void RegisterComponent(char* value){
            std::string nameOfTypeFull = typeid(T).name();
            std::string name = nameOfTypeFull.substr(1, nameOfTypeFull.length());
            mComponentSignatures.insert({name, std::bitset<5>(value)});

        }
        void RegisterEntity(Entity* e){
            mEntitySignatures.insert({e->ID, std::bitset<5>("00000")});
            
        }
        void RegisterSystem(System* s, char* value){
            mSystemSignatures.insert({s->ID, std::bitset<5>(value)});
            std::cout << s->ID << " " << std::bitset<5>(value) << std::endl;
        }
        void ShowEntitySignature(Entity* e){
            std::cout << " 'ShowEntitySignature': entity ID = " << e->ID << ", signature: " << mEntitySignatures.at(e->ID) << std::endl;
        }


};
class EntityManager {
        Signature* signature;
        const int maxEntityes = 10;

        std::map<int, Entity*> mEntityes;
        int countEntitys=0;
        int aEntityes[10]; 
        std::map<int, int> mEntityIdToIndex;
        void FillEntityIds (){
            for(int i=0; i < maxEntityes; i++){
                aEntityes[i]=i;
            }
        } 
        int GetNextFreeIndex(){
            assert(countEntitys != maxEntityes && "Limit of Entityes reached");
            return aEntityes[countEntitys];
        }
   public:

        EntityManager(Signature* s, std::map<int, int>& m) : signature(s), mEntityIdToIndex(m){
            FillEntityIds();
        }
        void ShowEntityIds(){
           for(int i =0; i<maxEntityes; i++ ){
               std::cout << aEntityes[i] << std::endl;
          }
        }
        void CreateEntity(){
            Entity* e = new Entity();
            e->ID = GetNextFreeIndex();
            mEntityIdToIndex.insert({e->ID, countEntitys});
            countEntitys++;
            mEntityes.insert({e->ID, e});
            RegisterEntity(e);

        }
        void DeleteEntity(Entity* e){
            int ID = e->ID;
            int index = mEntityIdToIndex.at(e->ID);
            int value = aEntityes[index];
            int lastIndex = aEntityes[countEntitys-1];
            int lastValue = aEntityes[lastIndex];
            aEntityes[index] = lastValue;
            aEntityes[lastIndex] = value;
            countEntitys--;
            mEntityes.erase({e->ID});
        }
        void RegisterEntity(Entity* e){
            signature->RegisterEntity(e);
        }
        Entity* GetEntity(int id){
            return mEntityes.at(id);
        }
        Entity* GetEntityLast(){
            auto it = mEntityes.end();
            it--;
            return it->second;
        }
}; 
class Transform : public Component {
    //bitset mask 
    //00001
    public:
    Transform():Component(){
        ID = 1;
    }
};
class Move : public Component {
    //bitset mask 
    //00010
    public:
    Move(){
        ID = 2;
    }
};
class Collide : public Component {
    //bitset mask
    //00100
    public:
        Collide(){
            ID = 3;
    }
};
class Render : public Component {
    //bitset mask
    //01000
    public: 
        Render(){
            ID = 4;
        }
};
class IArrayComponents {
    public:
        
    IArrayComponents(){

    };
    void virtual hello(){};
    void show(){
        std::cout << "base IArrayComponents" << std::endl;
    }
};
template<typename T>
class ArrayComponents : public IArrayComponents {
    public:
        std::list<int> lComponents;
    ArrayComponents(){};
    // void add(T t, Entity* e){
    //     const char* name = typeid(T).name();
    //     mNameComponent.at(name).push_back(e);
    // }
    void show() {
        std::cout<< "Derived show: " << typeid(T).name()<<std::endl;
    }

};
class ComponentManager {
    
    public:
        int entityesCount = 0;
        Signature* signature;
        std::map<int, std::list<int>> mEntityIdComponentIds;
        std::map<std::string, IArrayComponents*> mNameComponentId;

        ComponentManager(Signature* s): signature(s){
        }
        template<typename T>
        void addComponent(Entity* e, Component* c){
            // std::cout << "Component type is: " << typeid(c).name() << std::endl;
            // if(mEntityIdComponentIds.find(e->ID) == mEntityIdComponentIds.end()){
            //     mEntityIdComponentIds.insert({e->ID, std::list<int>()});
            // }
            // signature->mEntitySignatures.at(e->ID) = signature->mEntitySignatures.at(e->ID) | signature->mComponentSignatures.at(c->ID);
            // mEntityIdComponentIds.at(e->ID).push_back(c->ID);
        }
        template<typename T> 
        void RegisterComponent(char* value){
            signature->RegisterComponent<T>(value);
            std::string name = typeid(T).name();
            std::string editedName = name.substr(1, name.length());
            mNameComponentId.insert({editedName, new ArrayComponents<T>()});
        }
        void show(){
            std::cout << " Template insert: ";
            for(auto v:mNameComponentId){
                std::string name = v.first;
                std::cout << "v.first = " << v.first << std::endl;
                
                if(v.first == "Transform") {

                    ArrayComponents<Transform>* ac = dynamic_cast<ArrayComponents<Transform>*>(v.second);
                    ac->show();
                }
                else if(v.first == "Move") {

                    ArrayComponents<Move>* ac = dynamic_cast<ArrayComponents<Move>*>(v.second);
                    ac->show();
                }
                else if(v.first == "Render") {

                    ArrayComponents<Render>* ac = dynamic_cast<ArrayComponents<Render>*>(v.second);
                    ac->show();
                }
                else if(v.first == "Collide") {

                    ArrayComponents<Collide>* ac = dynamic_cast<ArrayComponents<Collide>*>(v.second);
                    ac->show();
                }
            }
        }
};
class ArrayOfComponents {
    public:
        ArrayOfComponents(){

        }
};
class Moving : public System {
    //bitset mask
    //00011
    public:
        Moving(){
            ID = 1;
        };
    void run(std::list<int>* l){
        std::cout << "Moving run" << std::endl;
    } 
};
class Rendering: public System {
    //bitset mask
    //01000
    public:
        Rendering(){
            ID = 4;
        };
    void run(std::list<int>* l){
        std::cout << "Rendering run" << std::endl;
    };
};
class SystemManager {
    public:
        std::map<int, System> mIndexSystems;
        Signature* signature;
        std::map<int, std::list<int>> mSystemsEntityes;
        std::map<int, System*> mSystems;
    SystemManager(Signature* s): signature(s){

    }
    void RegisterSystem(System* s, char* value){
        std::cout << " System id: " << s->ID << std::endl;
        signature->RegisterSystem(s, value);
        mSystemsEntityes.insert({s->ID, std::list<int>()});
        mSystems.insert({s->ID, s});
    }
    void addEntity(System* s, Entity* e){
        // std::cout << " system signature: " << signature->mSystemSignatures.at(s->ID) << ", entity signature: " << signature->mEntitySignatures.at(e->ID) << ", system id: " << s->ID << std::endl;
        std::bitset<5> a = signature->mSystemSignatures.at(s->ID);
        std::bitset<5> b = signature->mEntitySignatures.at(e->ID);
        // std::cout << a << " " << b << " " << (a & b) << std::endl;
        std::cout << " adding entity with id : " << e->ID << " to system with id: " << s->ID << std::endl;
        if((signature->mSystemSignatures.at(s->ID) & signature->mEntitySignatures.at(e->ID)) == signature->mSystemSignatures.at(s->ID)){
            mSystemsEntityes.at(s->ID).push_back(e->ID);
            std::cout << "entity added" << std::endl;
        }
    }
    void ShowSystemsEntityes(){
        std::map<int, std::list<int>>::iterator it;
         
        for(it = mSystemsEntityes.begin(); it != mSystemsEntityes.end(); it++){
        std::string result = " ";
            for(auto v:mSystemsEntityes.at(it->first)){
                result+=std::to_string(v) + " ";
            }
            std::cout << " system id: " << (it->first) << " , entityes id: " << result << std::endl;
        }

    }
    void runAll(){
        std::map<int, std::list<int>>::iterator it;
        for(it= mSystemsEntityes.begin(); it !=mSystemsEntityes.end(); it++){
            std::cout << "running all: " << it->first << std::endl;
            mSystems.at(it->first)->run(&mSystemsEntityes.at(it->first));
        }
    }



};
int main(){
    Signature signature;
    ComponentManager* cm = new ComponentManager(&signature);
    Transform* tr = new Transform();
    Move* mv = new Move();
    Collide* cl = new Collide();
    Render* rn = new Render();
    cm->RegisterComponent<Transform>((char*)"00001");
    cm->RegisterComponent<Move>((char*)"00010");
    cm->RegisterComponent<Collide>((char*)"00100");
    cm->RegisterComponent<Render>((char*)"01000");
    
    std::map<int, int> mEntityIdToIndex;
    EntityManager* em = new EntityManager(&signature, mEntityIdToIndex);
    em->CreateEntity();
    em->CreateEntity();
    em->CreateEntity();

    Entity* e1 = em->GetEntity(0);
    Entity* e2 = em->GetEntity(1);
    Entity* e3 = em->GetEntity(2);
    
    cm->addComponent<Move>(e1, mv);
    cm->addComponent<Render>(e1, rn);
    cm->addComponent<Transform>(e2, tr);
    cm->addComponent<Move>(e2, mv);
    cm->addComponent<Render>(e2, rn);
    cm->addComponent<Render>(e3, rn);

    Moving* movingSystem = new Moving();
    Rendering* renderingSystem = new Rendering();
    SystemManager* sm = new SystemManager(&signature);

    sm->RegisterSystem(movingSystem, (char*)"00010");
    sm->RegisterSystem(renderingSystem, (char*)"01000");

    sm->addEntity(movingSystem, e1);
    sm->addEntity(movingSystem, e2);
    sm->addEntity(movingSystem, e3);
    sm->addEntity(renderingSystem, e1);
    sm->addEntity(renderingSystem, e2);
    sm->addEntity(renderingSystem, e3);
    // sm->ShowSystemsEntityes();
    sm->runAll();
    cm->show();

    return 0;
}
