/*Abdullah Sonija 24k-0013*/
#include<iostream>
#include<string>
using namespace std;

class BusStop
{
	protected:
	string location;
	int personIDs[100];
	int personCount;
	public:
	BusStop(string loc): location(loc),personCount(0){}
	string getLocation()const{return location;}
	void addPerson(int id){if(personCount<100)personIDs[personCount++]=id;}
};
class Person
{
	protected:
	int id;
	string name;
	bool hasPaid;
	BusStop *assignedStop;
	public:
	Person(int i,string n):id(i),name(n),hasPaid(false),assignedStop(nullptr){}
	virtual void payFees()=0;
	void registerTransport(BusStop *stop);
	bool isPaid()const{return hasPaid;}
	string getName()const{return name;}
};
void Person::registerTransport(BusStop *stop)
{
	assignedStop=stop;
	stop->addPerson(id);
}
class Student:public Person
{
	public:
	Student(int id,string name):Person(id,name){}
	void payFees(){hasPaid=true;cout<<name<<" paid semester fees.\n";}
};
class Teacher:public Person
{
	public:
	Teacher(int id,string name):Person(id,name){}
	void payFees(){hasPaid=true;cout<<name<<" paid monthly fees.\n";}
};
class Staff:public Person
{
	public:
	Staff(int id,string name):Person(id,name){}
	void payFees(){hasPaid=true;cout<<name<<" paid monthly staff fees.\n";}
};
class Route
{
	protected:
	int routeID;
	BusStop *stops[10];
	int stopCount;
	public:
	Route(int id):routeID(id),stopCount(0){}
	void addStop(BusStop *stop){if(stopCount<10)stops[stopCount++]=stop;}
	int getRouteID()const{return routeID;}
	bool operator==(const Route &r)const{return routeID==r.routeID;}
};
class Bus
{
	protected:
	int busID;
	Route *assignedRoute;
	public:
	Bus(int id,Route *route):busID(id),assignedRoute(route){}
	int getBusID()const{return busID;}
};
class TransportSystem
{
	Person *people[100];
	int personCount;
	Bus *buses[10];
	int busCount;
	Route *routes[10];
	int routeCount;
	public:
	TransportSystem():personCount(0),busCount(0),routeCount(0){}
	void addStudent(int id,string name){if(personCount<100)people[personCount++]=new Student(id,name);}
	void addTeacher(int id,string name){if(personCount<100)people[personCount++]=new Teacher(id,name);}
	void addStaff(int id,string name){if(personCount<100)people[personCount++]=new Staff(id,name);}
	void addRoute(int id){if(routeCount<10)routes[routeCount++]=new Route(id);}
	void addBus(int id,Route *route){if(busCount<10)buses[busCount++]=new Bus(id,route);}
	~TransportSystem()
	{
		for(int i=0;i<personCount;i++)delete people[i];
		for(int i=0;i<busCount;i++)delete buses[i];
		for(int i=0;i<routeCount;i++)delete routes[i];
	}
};
int main()
{
	TransportSystem system;
	system.addStudent(1,"Ali");
	system.addTeacher(2,"Sir Usman");
	system.addStaff(3,"Ahmed");
	BusStop *stop1=new BusStop("Gulshan");
	BusStop *stop2=new BusStop("Clifton");
	Route *routeA=new Route(101);
	Route *routeB=new Route(102);
	routeA->addStop(stop1);
	routeB->addStop(stop2);
	cout<<"Are Route A and B same? ";
	if(*routeA==*routeB)
		{cout<<"Yes\n";}
		else {cout<<"No\n";}
	system.addRoute(101);
	system.addBus(10,routeA);
	Person *p1=new Student(4,"Zainab");
	Person *p2=new Teacher(5,"Miss Sara");
	Person *p3=new Staff(6,"Kamran");
	p1->registerTransport(stop1);
	p2->registerTransport(stop2);
	p3->registerTransport(stop1);
	p1->payFees();
	p2->payFees();
	p3->payFees();
	delete p1;
	delete p2;
	delete p3;
	delete stop1;
	delete stop2;
	delete routeA;
	delete routeB;
	cout<<"\nTransport System Demo Completed Successfully!"<<endl;
	return 0;
}
