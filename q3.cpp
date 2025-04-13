/*Abdullah sonija 24k-0013*/
#include <iostream>
#include <string>
using namespace std;

class RamzanBoxVehicle 
{
    protected:
    string vehicleID;
    double speed;      
    double capacity;   
    double efficiency;
    static int totalDeliveries;
    public:
    RamzanBoxVehicle(string id, double spd, double cap, double eff)
            : vehicleID(id), speed(spd), capacity(cap), efficiency(eff) 
            {
                totalDeliveries++;
            }
    virtual void move(string destination) 
    {
        cout << "Vehicle " << vehicleID << " is moving towards " << destination << "." << endl;
    }
    virtual void command(string action, int packageID) 
    {
        cout << "Vehicle " << vehicleID << " executing command: " << action << " for package " << packageID << endl;
    }
    virtual void command(string action, int packageID, string urgencyLevel) 
    {
        cout << "Vehicle " << vehicleID << " executing urgent command: " << action << " for package " << packageID
             << " with urgency: " << urgencyLevel << endl;
    }
    static int getTotalDeliveries() { return totalDeliveries; }
    friend bool operator==(const RamzanBoxVehicle &v1, const RamzanBoxVehicle &v2);
    virtual ~RamzanBoxVehicle() {}
};
int RamzanBoxVehicle::totalDeliveries = 0;
bool operator==(const RamzanBoxVehicle &v1, const RamzanBoxVehicle &v2)
{
    return (v1.speed == v2.speed) && (v1.capacity == v2.capacity) && (v1.efficiency == v2.efficiency);
}
class RamzanDrone : public RamzanBoxVehicle 
{
public:
    RamzanDrone(string id) : RamzanBoxVehicle(id, 300, 5, 0.9) {} 
    void move(string destination) override 
    {
        cout << "RamzanDrone " << vehicleID << " is flying to " << destination << "." << endl;
    }
    void command(string action, int packageID, string urgencyLevel) override 
    {
        if (urgencyLevel == "urgent") 
        {
            cout << "Ramzan Drone " << vehicleID << " activating HIGH-SPEED mode for iftar package " << packageID << endl;
        } else 
        {
            RamzanBoxVehicle::command(action, packageID, urgencyLevel);
        }
    }
};
class RamzanTimeShip : public RamzanBoxVehicle 
{
public:
    RamzanTimeShip(string id) : RamzanBoxVehicle(id, 150, 50, 0.8) {} // Speed: 150 km/h, Capacity: 50 kg

    void move(string destination) override 
    {
        cout << "RamzanTimeShip " << vehicleID << " is calculating time for " << destination << "." << endl;
    }

    void command(string action, int packageID, string urgencyLevel) override {
        if (urgencyLevel == "urgent") 
        {
            cout << "RamzanTimeShip " << vehicleID << " is calculating minimun time for " << packageID << " urgent delivery." << endl;
        } else 
        {
            RamzanBoxVehicle::command(action, packageID, urgencyLevel);
        }
    }
};
class RamzanHyperPod : public RamzanBoxVehicle
{
public:
    RamzanHyperPod(string id) : RamzanBoxVehicle(id, 600, 100, 0.95) {}
    void move(string destination) override
    {
        cout << "RamzanHyperPod " << vehicleID << " is transporting bulk food supplies via underground tunnel to " << destination << "." << endl;
    }
};
void resolveConflict(RamzanBoxVehicle &v1, RamzanBoxVehicle &v2) {
    if (v1 == v2) {
        cout << "Both vehicles are equally efficient." << endl;
    } else {
        cout << "One vehicle is more efficient." << endl;
    }
}
int main() {
    RamzanBoxVehicle* vehicles[3];
    vehicles[0] = new RamzanDrone("Samsung-786");
    vehicles[1] = new RamzanTimeShip("Apple-1400");
    vehicles[2] = new RamzanHyperPod("HP-9000");
    vehicles[0]->move("Landhi");
    vehicles[1]->move("PECHS");
    vehicles[2]->move("DHA");
    vehicles[0]->command("Deliver", 101, "Urgent");
    vehicles[1]->command("Deliver", 102, "Urgent");
    vehicles[2]->command("Deliver", 103);
    cout << "Total Deliveries So Far: " << RamzanBoxVehicle::getTotalDeliveries() << endl;
    resolveConflict(*vehicles[0], *vehicles[1]);
    for (int i = 0; i < 3; i++) {
        delete vehicles[i]; 
    }
    return 0;
}
