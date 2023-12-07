#include <iostream>
#include <queue>
#include <random>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
using namespace std;
using namespace chrono;

typedef pair<string, int> psi;

// Classes to handle the parcel processes
class ParcelNode
{
    string name;
    int parcel_num;
    int weight; 
    string dest; //destination address

    public:
    ParcelNode *next;
    ParcelNode *prev;
    ParcelNode()
    {
        parcel_num = -1;
        weight = 0;
        dest = "NULL";
        next = NULL;
        prev = NULL;
    }

    ParcelNode(int n, int w, string nm, string d)
    {
        parcel_num = n;
        weight = w;
        name = nm;
        dest = d;
        next = NULL;
        prev = NULL;
    }

    void setParcelnum(int n)
    {
        parcel_num=n;
    }

    void setaddress_dest(string n)
    {
        dest=n;
    }

    void setname(string n)
    {
        name=n;
    }

    int getnum()
    {
        return parcel_num;
    }

    int getweight()
    {
        return weight;
    }

    string getname()
    {
        return name;
    }

    string getdest()
    {
        return dest;
    }
};

class Parcels
{
    public:
    ParcelNode *head,*tail;

    Parcels()
    {
        head = tail = NULL;
    }

    void Insert(int n, int w, string name, string addD)
    {
        ParcelNode* newParcel = new ParcelNode(n, w, name, addD); //creating a new parcel
        if(head == NULL)
        {
            head = newParcel;
            tail = newParcel;
        }
        else
        {
            newParcel->prev = tail;
            tail->next = newParcel;
            tail=newParcel;
        }
    }

    void Show()
    {
        if (head == NULL)
        {
            cout << "There is no parcel in the queue!" << endl;
            return;
        }

        ParcelNode *temp=head;
        cout << "This is the list of our pending parcels:-" << endl << endl;
        while(temp!=NULL)
        {
            cout << "Parcel Name: "<<temp->getname()<<" " << endl;
            cout << "Parcel Weight: "<<temp->getweight() << "kg"<< endl;
            cout << "Parcel Number: "<<temp->getnum()<<" " << endl;
            cout << "Delivery Address: "<<temp->getdest() << endl;
            cout << "-------------------------------------------" << endl;
            cout << endl;
            temp = temp->next;
        }
    }

    bool checknum(int id)
    {
        ParcelNode *cur = head;

        while(cur != NULL)
        {
            if (cur->getnum() == id)
            {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void Delete(int num) //parcel number will be the best choice as it will be unique
    {
        ParcelNode *current = head;

        while(current!=NULL)
        {
            if(current->getnum() == num)
            {
                if(current == head)
                {
                    head = current->next;

                    if(head != NULL)
                    {
                        head->prev=NULL;
                    }
                }
                else if(current == tail)
                {
                    tail = current->prev;
                    tail->next=NULL;
                }
                else
                {
                    current->prev->next=current->next;
                    current->next->prev=current->prev;
                }

                delete current;
                return;
            }
            
            current = current->next;
        }
    }

    bool isEmpty()
    {
        if (head == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void ReadOrders(string filename)
    {
        ifstream file(filename,ios::in);

        if (!file.is_open())
        {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        int parcelNum, weight;
        string name, dest;

        while (file >> parcelNum >> weight >> name >> dest)
        {
            Insert(parcelNum, weight, name, dest);
        }

        file.close();
    }
};

// Classes to handle the riders processes
class Rider_Node
{
    int Id; //for identification
    string name;
    bool isFree;

    public:
    Rider_Node* next;
    Rider_Node* prev;

    Rider_Node()
    {
        next = prev = NULL;
    }

    Rider_Node(int id, string name)
    {
        this->Id = id;
        this->name = name;
        isFree = true;
        next = prev = NULL;
    }

    void set_ID(int id)
    {
        Id = id;
    }

    void set_name(string n)
    {
        name = n;
    }

    void set()
    {
        isFree = false;
    }

    void reset()
    {
        isFree = true;
    }

    bool get_Status()
    {
        return isFree;
    }

    int getID()
    {
        return Id;
    }

    string getname()
    {
        return name;
    }
};

class Riders
{
    public:
    Rider_Node* head;
    Rider_Node* tail;

    Riders()
    {
        head = tail = NULL;
    }

    void Insert(int n, string name)
    {
        Rider_Node* newRider = new Rider_Node(n,name); //creating a new rider
        if(head == NULL)
        {
            head = newRider;
            tail = newRider;
        }
        else
        {
            newRider->prev = tail;
            tail->next = newRider;
            tail=newRider;
        }
    }

    void ShowRiders()
    {
        Rider_Node* temp = head;
        cout << "This is the list of our riders:-" << endl << endl;
        while(temp!=NULL)
        {
            cout << "Rider Name: " << temp->getname() << endl;
            cout << "Rider ID: " << temp->getID() << endl;
            cout << "Delivery status: ";
            if (temp->get_Status() == true)
            {
                cout << "Free" << endl;
            }
            else{
                cout << "Busy" << endl;
            }
            cout << "-------------------------------------------" << endl;
            cout << endl;
            temp = temp->next;
        }
    }

    void ShowfreeRiders()
    {
        Rider_Node* temp = head;
        cout << "This is the list of our free riders:-" << endl << endl;
        while(temp!=NULL)
        {
            if (temp->get_Status() == true)
            {
                cout << "Rider Name: " << temp->getname() << endl;      
                cout << "Rider ID: " << temp->getID() << endl;
                cout << endl;
            }
            temp = temp->next;
        }
    }

    bool sendRider(int x)
    {
        Rider_Node* temp = head;
        while (temp != NULL)
        {
            if (temp->get_Status() == true && temp->getID() == x)
            {
                temp->set();
                return true;
            }
            temp = temp->next;
        }
        cout << "There is no rider with this id..." << endl;
        return false;
    }

    void ReadRiders(const char* filename)
    {
        ifstream infile(filename,ios::in);

        if(!infile)
        {
            cerr<<"Error opening file."<<endl;
            return;
        }

        string line;

        while(getline(infile,line))
        {
            istringstream iss(line);

            int n;
            string x;

            if (iss >> n >> ws && getline(iss, x)) 
            {
                // Trim leading and trailing whitespaces from the name
                x.erase(0, x.find_first_not_of(" \t"));
                x.erase(x.find_last_not_of(" \t") + 1);

                Insert(n, x);
            }

        }

        infile.close();
    }
};

// Classes to save time of delivered parcels
class TimeNode
{
public:
	int parcelID;
    string name;
    int distance;
    int estimatedTime;
    TimeNode* left;
    TimeNode* right;

    TimeNode() : parcelID(0), name(""), distance(0), estimatedTime(0), left(NULL), right(NULL) {}
    TimeNode(int id, string n, int d) : parcelID(id), name(n), distance(d), estimatedTime(0), left(NULL), right(NULL) {}
};

class Time
{
    public:
    TimeNode* root;
    Time() : root(NULL) {}

    TimeNode* insertRecursive(TimeNode* node, int id, string name, int distance)
    {
        TimeNode *t = NULL;
        if (node == NULL)
        {
            t = new TimeNode(id,name,distance);
            t->left = t->right= NULL;
            t->estimatedTime = calculateEstimatedTime(t->distance);
            return t;
        }
        if (distance <= node->distance)
        {
            node->left = insertRecursive(node->left, id, name, distance);
        }
        else
        {
            node->right = insertRecursive(node->right, id, name, distance);
        }
        return node;
    }
    
    void insert(int id, string name, int distance)
    {
        root = insertRecursive(root, id, name, distance);
    }

    TimeNode* deleteNodeRecursive(TimeNode* node, string name)
    {
        if (node == NULL)
        {
            return node;
        }

        if (name < node->name)
        {
            node->left = deleteNodeRecursive(node->left, name);
        }
        else if (name > node->name)
        {
            node->right = deleteNodeRecursive(node->right, name);
        }
        else
        {
            // Node with only one child or no child
            if (node->left == NULL)
            {
                TimeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL)
            {
                TimeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children, get the inorder successor (smallest
            // in the right subtree)
            TimeNode* temp = InSucc(node->right);

            // Copy the inorder successor's content to this node
            node->name = temp->name;
            node->distance = temp->distance;
            node->estimatedTime = temp->estimatedTime;

            // Delete the inorder successor
            node->right = deleteNodeRecursive(node->right, temp->name);
        }
        return node;
    }

    TimeNode* InSucc(TimeNode* node)
    {
        TimeNode* current = node;

        // Find the leftmost leaf
        while (current->left != NULL)
        {
            current = current->left;
        }

        return current;
    }

    void inorderTraversalRecursive(TimeNode* node)
    {
        if (node != NULL)
        {
            inorderTraversalRecursive(node->left);
            cout << "Parcel ID: " << node->parcelID << endl;
			cout << "Parcel delivered to " << node->name << endl;
			cout << "Parcel delivered in " << node->estimatedTime << " minutes." << endl;
            cout << "-------------------------------------------" << endl;
			cout << endl;
            inorderTraversalRecursive(node->right);
        }
    }

    int calculateEstimatedTime(int distance)
    {
        const int speed = 10;  // Speed in km/h, you can adjust this value
        if (distance == 0)
        {
            return 0;
        }
        else
        {
            int timeInMinutes = (distance * 60) / speed;
            return timeInMinutes;
        }
    }
};

// Classes to save all orders in a linkedlist and text file
class node
{
public:
    int id;
    string status;
    node* next;

    node(int n, string st)
    {
        id = n;
        status = st;
        next = NULL;
    }
};

class AllOrders 
{ 
    public: node* head;
    AllOrders()
    {
        head = NULL;
    }

    void Insert(int id, string st)
    {
        node* n = new node(id, st);
        node* temp = head;

        if (head == NULL)
        {
            head = n;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = n;
        }

        // Append the node to the appropriate file based on the status
        if (st == "Delivered")
        {
            writeToFile("Delivered.txt", n);
        }
        else if (st == "Cancelled")
        {
            writeToFile("Cancelled.txt", n);
        }
    }
    
    void Insertfromfile(int id, string st)
    {
        node* n = new node(id, st);
        node* temp = head;

        if (head == NULL)
        {
            head = n;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
    }

    void display()
    {
        node* temp = head;
        cout << "List of our All-time parcels:-" << endl << endl;
        while (temp != NULL)
        {
            cout << "Parcel ID = " << temp->id << endl;
            cout << "Status    = " << temp->status << endl;
            cout << "-------------------------------------------" << endl;
            temp = temp->next;
        }
        cout << endl;
    }

    void Delete(int val)
    {
        if (head->id == val)
        {
            node* Ndelete = head;
            head = head->next;
            delete Ndelete;
            return;
        }

        node* cur = head->next;
        node* prev = head;

        while (cur != NULL)
        {
            if (cur->id == val)
            {
                prev->next = cur->next;
                delete cur;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }

    // writeToFile function to append the file with a given node
    void writeToFile(char* filename, node* n)
    {
        ofstream file(filename, ios::app);

        if (!file.is_open())
        {
            cerr << "Error: Unable to open file for writing." << endl;
            return;
        }

        file << n->id << " " << n->status << endl;

        file.close();
    }

    void readFromFile(char* filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Error: Unable to open file for reading." << endl;
            return;
        }

        int id;
        string status;

        while (file >> id >> status)
        {
            Insertfromfile(id, status);
        }

        file.close();
    }
};

// Classes to handle the location and delivery processes
class Location
{
    string name;
    float longitude;
    float latitude;

public:
    Location(float lon, float lat, string n)
    {
        longitude = lon;
        latitude = lat;
        name = n;
    }

    Location()
    {
        longitude = 0.0f;
        latitude = 0.0f;
        name = "NULL";
    }

    float getLongitude()
    {
        return longitude;
    }

    float getLatitude()
    {
        return latitude;
    }

    string getName()
    {
        return name;
    }
};

class Graph
{
    vector<Location> locations;
    int num;
    vector<vector<int>> DistanceMatrix;

public:
    Graph(int n)
    {
        num = n;
        locations.resize(num);
        DistanceMatrix.resize(num, vector<int>(num, INT_MAX));
    }

    void addLocation(int index, Location l_name)
    {
        locations[index] = l_name; // Assign directly at the specified index
    }

    string getLocation(int index)
    {
        return locations[index].getName();
    }

    void showLocations()
    {
        cout << "These are the locations where we deliver our parcels:-" << endl << endl;

        for (int i=0; i <= locations.size()-1; i++)
        {
            cout << i << "- " << locations[i].getName() << endl;
        }
    }

    void link_location(int src, int dest, int cost)
    {
        DistanceMatrix[src][dest] = cost;
        DistanceMatrix[dest][src] = cost;
    }

    int get_size()
    {
        return num;
    }

    void primsMST(Parcels* parcel, Time* time, AllOrders* all)
    {
        priority_queue<psi, vector<psi>, greater<psi>> pq;

        // Find the index of "CourierStation" in the locations vector
        int startIndex = -1;
        for (int i = 0; i < num; i++)
        {
            if (locations[i].getName() == "CourierStation")
            {
                startIndex = i;
                break;
            }
        }

        if (startIndex == -1)
        {
            cerr << "Start location not found in the graph." << endl;
            return;
        }

        int src = startIndex;

        vector<int> key(num, INT_MAX);
        vector<bool> inMST(num, false);

        pq.push(make_pair(locations[src].getName(), 0));
        key[src] = 0;

        while (!pq.empty())
        {
            string uName = pq.top().first;
            int u = -1;

            for (int i = 0; i < locations.size(); i++)
            {
                if (locations[i].getName() == uName)
                {
                    u = i;
                    break;
                }
            }

            pq.pop();

            inMST[u] = true;

            for (int v = 0; v < num; v++)
            {
                if (!inMST[v] && DistanceMatrix[u][v] != INT_MAX && DistanceMatrix[u][v] < key[v])
                {
                    key[v] = DistanceMatrix[u][v];
                    pq.push(make_pair(locations[v].getName(), key[v]));
                }
            }
        }

        int totaldis = 0, tp = 0;
        cout << "Delivering the parcels to the locations:" << endl << endl;
        for (int i = 1; i < num; i++)
        {
        	string name = locations[i].getName();
        	if (tp < 5 && parcel->isEmpty() == false)
            {
                totaldis += key[i];
                if (checkparcel(parcel, name) == true)
                {
                    cout << "The rider is now at " << name << " to deliver the parcels." << endl << endl;
                    tp += deliverparcels(parcel, time, all, name, totaldis);
                }
            }
	    }
        cout << endl << "Total distance covered by the rider is " << totaldis << "km." << endl;
    }
    
    bool checkparcel(Parcels* parcel, string name)
    {
        ParcelNode *temp = parcel->head;
        int i=0;
    	while(temp != NULL)
        {
            if (temp->getdest() == name)
            {
                i++;
            }
            temp = temp->next;
        }
        if (i==0)
            return false;
        else    
            return true;    
	}
	
	int deliverparcels(Parcels* parcel, Time* time, AllOrders* all, string name, int dist)
    {
    	ParcelNode *temp = parcel->head;
        int i=0;
    	while(temp != NULL)
        {
            if (temp->getdest() == name)
            {
                time->insert(temp->getnum(), name, dist);
                all->Insert(temp->getnum(), "Delivered");
                cout << "The parcel of id " << temp->getnum() << " is successfully delivered." << endl;
                parcel->Delete(temp->getnum());
                i++;
            }
            temp = temp->next;
        }
        cout << "-----------------------------------------------------------------------------" << endl << endl;
        return i;
	}

    void ReadLocations(string filename)
    {
        ifstream infile(filename, ios::in);
        if (!infile)
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        int i = 0;

        while (getline(infile, line))
        {
            istringstream iss(line);

            float longitude, latitude;
            string name;

            if (iss >> longitude >> ws && iss.ignore(1,',') && iss >> latitude >> ws && getline(iss, name))
            {
                if (!name.empty() && name[0] == ',') 
                {
                    name = name.substr(1);
                }
                Location newLocation(longitude, latitude, name);
                addLocation(i++, newLocation);
            }
        }

        infile.close();
    }

    void LinkAll()
    {
        int N = get_size();
        int k=1;
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                int k = 1 + rand() % 100;
                link_location(i, j, k);
            }
        }
    }
};

//CLass that deals with login and buying of our service
class Customer
{
    int age;
    string name;
    string email;
    string password;
    float balance;

    public:
    Customer()
    {
        age=-1;
        name = "Jhon Doe";
        email="NULL";
        password="NULL";
        balance=-1.0f;
    }

    Customer(int x,string n,string mail,string pass,float bal)
    {
        name = n;
        age = x;
        email = mail;
        password = pass;
        balance = bal;
    }

    Customer(string n,int x)
    {
        name = n;
        age = x;
    }

    void setmail(string m)
    {
        email = m;
    }

    void setpassword(string p)
    {
        password = p;
    }

    void set_balance(float n)
    {
        balance = n;
    }

    float get_balance()
    {
        return balance;
    }

    void sign_up()
    {
        ofstream outfile("Customers.txt",ios::app);

        if(!outfile.is_open())
        {
            cerr<<"Error opening file"<<endl;
            return;
        }

        outfile << email << " " << password << " " << balance << endl;
        outfile<<endl;

        cout<<"Welcome To ZSA Courier"<<endl;

        outfile.close();

    }

    bool login()
    {
        string mail,pas;
        cout<<"Enter your mail : ";
        cin>>mail;
        cout<<"Enter your password : ";
        cin>>pas;
        ifstream infile("Customers.txt",ios::in);
        if(!infile.is_open())
        {
            cerr<<"Error, File not found.\n";
            return false;
        }

        string filemail,filepass;

        bool flag = false;

        while(infile >> filemail >> filepass >> balance)
        {
            if(mail == filemail && pas == filepass)
            {
                flag = true;
                break;
            }
        }

        infile.close();

        return flag;

    }

    bool Buy_Service()
    {
        cout<<"Our charges : 50$ per order\n";
        int ch;
        cout<<"Do you want to buy our service?\n 1.Yes 0.No";
        cin>>ch;

        while(ch < 0 || ch > 1)
        {
            cout<<"Please follow the instructions carefully!\n Input again";
            cin>>ch;
        }

        if(ch == 1)
        {
            if(balance >= 50.0)
            {
                set_balance(get_balance() - 50.0);
                cout<<"Thank You for chosing ZSA Courier. You can place your order\n";
                return true;
            }
            else
            {
                cout<<"Not enough Balance\n";
                return false;
            }
        }
        else
        {
            cout<<"You have declined the service. Please buy the service to place your order\n";
            return false;
        }
    }
};


void Interactive()
{
    srand(static_cast<int>(time(nullptr)));
    Parcels orders;
    Riders list;
    Time time;
    AllOrders deliver;
    AllOrders cancel;
	Graph graph(6);

    // Reading all our past orders from text file
    deliver.readFromFile("Delivered.txt");
    cancel.readFromFile("Cancelled.txt");

    // Creating two predefined riders
    list.Insert(11, "Ammar Qasmi");
    list.Insert(22, "Maaz Khan");
    
    // Adding locations to the graph
    graph.addLocation(0, Location(24.8607, 67.0011, "CourierStation"));
    graph.addLocation(1, Location(24.8918, 67.0341, "Clifton"));
    graph.addLocation(2, Location(24.9123, 67.0525, "Saddar"));
    graph.addLocation(3, Location(24.9500, 67.0374, "DHA"));
    graph.addLocation(4, Location(24.9772, 67.0508, "Gulshan-e-Iqbal"));
    graph.addLocation(5, Location(25.0107, 67.0711, "Karachi University"));

    // Linking all locations with different costs
    graph.link_location(0, 1, 5); 
    graph.link_location(0, 2, 8);
    graph.link_location(0, 3, 6); 
    graph.link_location(0, 4, 3);
    graph.link_location(0, 5, 7); 

    graph.link_location(1, 2, 2);
    graph.link_location(1, 3, 9);
    graph.link_location(1, 4, 4);
    graph.link_location(1, 5, 1);

    graph.link_location(2, 3, 7); 
    graph.link_location(2, 4, 5); 
    graph.link_location(2, 5, 2);

    graph.link_location(3, 4, 8);
    graph.link_location(3, 5, 6); 

    graph.link_location(4, 5, 3);
    
    // Now the main menu

    while (true) 
    {
        std::cout << "-------------------------- ZSA courier service --------------------------" << std::endl << std::endl;
        std::cout << "1. I am an Admin" << std::endl;
        std::cout << "2. I am a costumer" << std::endl;
        std::cout << "0. Exit\n" << std::endl;

        char zero;
        std::cout << "Enter your choice: ";
        std::cin >> zero;

        if (zero == '1') 
        {
            std::string un, pw;
            std::cout << "Enter your username: ";
            std::cin >> un;
            std::cout << "Enter the password: ";
            std::cin >> pw;

            if (un == "DSAproject" && pw == "courier") 
            {
                bool fall = true;
                while (fall == true) 
                {
                    std::cout << std::endl << "What do you want to do?" << std::endl << std::endl;
                    std::cout << "1. Show all pending parcels" << std::endl;
                    std::cout << "2. Deliver parcels" << std::endl;
                    std::cout << "3. Show all riders" << std::endl;
                    std::cout << "4. Add another rider" << std::endl;
                    std::cout << "5. Show all locations" << std::endl;
                    std::cout << "6. Show delivery time of all delivered parcels" << std::endl;
                    std::cout << "7. Show delivered parcels history" << std::endl;
                    std::cout << "8. Show cancelled parcels history" << std::endl;
                    std::cout << "0. Go back!\n" << std::endl;

                    char first;
                    std::cout << "Enter your choice: ";
                    std::cin >> first;
                    std::cout << std::endl;

                    if (first == '1') 
                    {
                        orders.Show();
                        system("pause");
                    } 
                    else if (first == '2') 
                    {
                        list.ShowfreeRiders();
                        int id;
                        std::cout << std::endl << "Enter the rider id: ";
                        std::cin >> id;
                        while (std::cin.fail() || id < 0 || list.sendRider(id) != true) 
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << std::endl << "Invalid id, input again: ";
                            std::cin >> id;
                        }
                        graph.primsMST(&orders, &time, &deliver);
                        std::cout << std::endl;
                        system("pause");
                    }
                     else if (first == '3') 
                    {
                        list.ShowRiders();
                        system("pause");
                    } 
                    else if (first == '4') 
                    {
                        // Adding rider
                        std::string name;
                        int id;
                        std::cout << "Enter the name of the rider: ";
                        std::cin >> name;
                        std::cout << "Enter the id of the rider: ";
                        std::cin >> id;
                        list.Insert(id, name);
                        std::cout << name << " is successfully added to our rider's database." << std::endl;
                        std::cout << std::endl;
                        system("pause");
                    }
                    else if (first == '5') 
                    {
                        graph.showLocations();
                        std::cout << std::endl;
                        system("pause");
                    }
                    else if (first == '6') 
                    {
                        // Time taken for parcel delivery
                        time.inorderTraversalRecursive(time.root);
                        std::cout << std::endl;
                        system("pause");
                    }
                    else if (first == '7') 
                    {
                        deliver.display();
                        std::cout << std::endl;
                        system("pause");
                    }
                    else if (first == '8') 
                    {
                        cancel.display();
                        std::cout << std::endl;
                        system("pause");
                    }
                    else if (first == '0') 
                    {
                        std::cout << "Going back....\n";
                        fall = false;
                        system("CLS");
                    } 
                    else 
                    {
                        std::cout << "Invalid choice. Please enter a valid option.\n" << std::endl;
                    }
                }
            }
            else 
            {
                std::cout << std::endl << "Invalid username or password! You are not an admin." << std::endl;
                system("pause");
                system("CLS");
            }
        }
        else if (zero == '2') 
        {
            std::string name;
            int age;
            float balance;
            std::cout << "Enter your name\n";
            fflush(stdin);
            std::getline(std::cin, name);
            std::cout<<"Enter your age\n";
            std::cin >> age;
            std::cout<<"Enter your bank balance\n";
            cin >> balance;
            while (std::cin.fail() || age < 0) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please input again: ";
                std::cin >> age;
            }
            Customer c(name, age);
            c.set_balance(balance);
            bool fall = true;
            while (fall == true) 
            {
                int opt;
                std::cout << "Please Login if you already have an account or Sign Up if you don't\n 1.Login 2.Sign Up\n";
                std::cin >> opt;
                while (std::cin.fail() || opt < 1 || opt > 2) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input, input again: ";
                    std::cin >> opt;
                }

                if (opt == 1) 
                {
                    bool isthere = c.login();
                    if (!isthere) 
                    {
                        std::cout << "You do not have an account, please sign up\n";
                        std::string mail, pass;
                        std::cout << "Enter your mail : ";
                        std::cin >> mail;
                        std::cout << "Enter your password : ";
                        std::cin >> pass;
                        c.setmail(mail);
                        c.setpassword(pass);
                        c.sign_up();
                    }
                }
                else if (opt == 2) 
                {
                    std::cout << "You do not have an account, please sign up\n";
                    std::string mail, pass;
                    std::cout << "Enter your mail : ";
                    std::cin >> mail;
                    std::cout << "Enter your password : ";
                    std::cin >> pass;
                    c.setmail(mail);
                    c.setpassword(pass);
                    c.sign_up();
                }

                bool isbought = c.Buy_Service();

                while(isbought == false)
                {
                    cout<<"Please Buy to proceed\n";
                    isbought = c.Buy_Service();
                }

                std::cout << std::endl << "What do you want to do?" << std::endl << std::endl;
                std::cout << "1. Place an order!" << std::endl;
                std::cout << "2. Cancel your order!" << std::endl;
                std::cout << "0. Go back!\n" << std::endl;

                char second;
                std::cout << "Enter your choice: ";
                std::cin >> second;
                std::cout << std::endl;

                if (second == '1') 
                {
                    int num, weight, ch;
                    std::string name, dest;
                    std::cout << "Enter your name: ";
                    std::cin >> name;
                    std::cout << "Enter your parcel's weight: ";
                    std::cin >> weight;
                    while (std::cin.fail() || weight < 0) 
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input, input again: ";
                        std::cin >> weight;
                    }
                    num = rand() % 900 + 100;
                    std::cout << std::endl;

                    graph.showLocations();

                    while (true) 
                    {
                        std::cout << "Choose the location for your delivery address: ";
                        std::cin >> ch;

                        if (std::cin.fail() || ch < 0 || ch > 5) 
                        {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Please enter a valid input (an integer)." << std::endl;
                        }
                        else 
                        {
                            break;
                        }
                    }
                    dest = graph.getLocation(ch);

                    orders.Insert(num, weight, name, dest);
                    std::cout << std::endl << "Your order has been placed!" << std::endl;
                    std::cout << "Your order id is " << num << std::endl << std::endl;
                    system("pause");
                }
                else if (second == '2') 
                {
                    int ide;
                    std::cout << "Enter the id of your parcel: ";
                    std::cin >> ide;
                    if (orders.checknum(ide) == true) 
                    {
                        cancel.Insert(ide, "Cancelled");
                        orders.Delete(ide);
                        std::cout << "Your order has been cancelled." << std::endl;
                    }
                    else 
                    {
                        std::cout << "This id is invalid!" << std::endl;
                    }

                    std::cout << std::endl;
                    system("pause");
                }
                else if (second == '0') 
                {
                    std::cout << "Going back....\n";
                    fall = false;
                    system("CLS");
                } 
                else 
                {
                    std::cout << "Invalid choice. Please enter a valid option.\n" << std::endl;
                }
            }
        }
        else if (zero == '0') 
        {
            std::cout << "Exiting program....\n";
            return;
        } 
        else 
        {
            std::cout << "Invalid choice. Please enter a valid option.\n" << std::endl;
        }
    }

    return;
}
int main()
{
    Interactive();
    return 0;
}