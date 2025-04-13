/*Abdullah Sonija 24k-0013*/
#include <iostream>
#include <string>
using namespace std;

class Ghost 
{
    protected:
    string aName;
    int scareLevel;
    public:
    Ghost(string name, int level) : aName(name), scareLevel(level) {}
    virtual ~Ghost() {}
    virtual void haunt();
    int getScareLevel() 
    {
        return scareLevel;
    }
    virtual Ghost* clone() const = 0;
    friend ostream& operator<<(ostream& out,Ghost& g) 
    {
        out<<"Ghost: "<<g.aName<<", Scare Level: "<<g.scareLevel;
        return out;
    }
    Ghost* operator+(const Ghost& other) const 
    {
        Ghost* upgraded = this->clone();
        upgraded->scareLevel += other.scareLevel;
        upgraded->aName += " & " + other.aName;
        return upgraded;
    }
};
class Poltergeist : virtual public Ghost 
{
    public:
    Poltergeist(string name, int level) : Ghost(name, level) {}
    void haunt() override 
    {
        cout << aName << " is moving objects around\n";
    }
    Ghost* clone() const override 
        { return new Poltergeist(*this); }
    };
class Banshee : virtual public Ghost 
{
    public:
    Banshee(string name, int level) : Ghost(name, level) {}
    void haunt() override
    {
        cout << aName << " screams loudly!\n";
    }
    Ghost* clone() const override 
        { return new Banshee(*this); }
};
class ShadowGhost : virtual public Ghost 
{
    public:
    ShadowGhost(string name, int level) : Ghost(name, level) {}
    void haunt()  override 
    {
        cout << aName << " whispers from the dark\n";
    }
    Ghost* clone() const override
        { return new ShadowGhost(*this); }
};
class ShadowPoltergeist : public ShadowGhost, public Poltergeist 
{
    public:
    ShadowPoltergeist(string name, int level) :
                Ghost(name, level), ShadowGhost(name, level), Poltergeist(name, level) {}
    void haunt() override 
    {
        ShadowGhost::haunt();
        Poltergeist::haunt();
    }
    Ghost* clone() const override 
        { return new ShadowPoltergeist(*this); }
};
class Visitor 
{
    string name;
    int bravery; 
    public:
    Visitor(string n, int b) : name(n), bravery(b) {}
    string getReaction(int scareLevel) const 
    {
        if (scareLevel < bravery - 2)
            return name + "Cowardly";
        else if (scareLevel > bravery + 2)
            return name + "Average";
        else
            return name + "Fearless";
    }
};
class HauntedHouse 
{
    string name;
    Ghost** ghosts;
    int ghostCount;
    public:
    HauntedHouse(string n, int count) : name(n), ghostCount(count) 
    {
        ghosts = new Ghost*[ghostCount];
    }
    ~HauntedHouse() 
    {
        for (int i = 0; i < ghostCount; i++)
            delete ghosts[i];
        delete[] ghosts;
    }
    void setGhost(int index, Ghost* g) 
    {
        if (index >= 0 && index < ghostCount)
        {    
            ghosts[index] = g;
        }
    }
    friend void visit(Visitor visitors[], int vCount, const HauntedHouse& house);
};
void visit(Visitor visitors[], int vCount, const HauntedHouse& house) {
    cout << "\n>> Visitors enter " << house.name << "\n";
    for (int v = 0; v < vCount; v++) {
        for (int g = 0; g < house.ghostCount; g++) {
            house.ghosts[g]->haunt();
            cout << visitors[v].getReaction(house.ghosts[g]->getScareLevel()) << "\n";
        }
        cout << "\n";
    }
}
int main() {
    Visitor group[3] = 
    {
        Visitor("Ali", 2),
        Visitor("Asad", 6),    
        Visitor("Abdullah", 9)    
    };
    HauntedHouse house1("ABC", 3);
    house1.setGhost(0, new Poltergeist("Tom", 3));
    house1.setGhost(1, new Banshee("Sarah", 7));
    house1.setGhost(2, new ShadowGhost("Rabia", 5));
    HauntedHouse house2("Void Estate", 2);
    house2.setGhost(0, new ShadowPoltergeist("Jerry", 8));
    Ghost* twin1 = new ShadowGhost("GhostA", 4);
    Ghost* twin2 = new ShadowGhost("GhostB", 4);
    Ghost* fused = *twin1 + *twin2;
    house2.setGhost(1, fused);
    delete twin1;
    delete twin2;
    visit(group, 3, house1);
    visit(group, 3, house2);
    return 0;
}
        
    