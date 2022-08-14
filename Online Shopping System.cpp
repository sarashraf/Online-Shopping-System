// Sara Ashraf Ali 20200215
// Menna t Allah Mohamed 20201178
#include <iostream>

using namespace std;

// this code provides an online shopping system for the user
class Item
{
// private member variables of class item
private:
    static int ID;
    string name;
    double quantity,price;

public:
    // public member functions of class item

    // default constructor
    Item(){};

    // parametrized constructor which takes name, quantity and the price of the item as parameters
    Item(string n,double q,double p)
    {
        ID++; // increasing the static integer id variable every time an object is created
        name=n;
        quantity=q;
        price=p;
    }
    // copy constructor
    Item(const Item & obj)
    {
        name=obj.name;
        quantity=obj.quantity;
        price=obj.price;
    }

    // setters
    void setID(int);
    void setName(string);
    void setQuantity(double);
    void setPrice(double );

    //getters
    int getID();
    string getName();
    double getQantity();
    double getprice();

    // operators functions
    bool operator==(Item &obj)
    {
        if(name==obj.name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    double operator+=(Item &obj)
    {
        quantity+=obj.quantity;
        return quantity;
    }
    double operator-=(double q )
    {
        if(quantity>=q)
        {
            quantity-=q;
            return quantity;
        }
        else
        {
            cout<<"invalid quantity";
        }
    }
    // operator function which takes an object as a cin
   friend istream& operator>>(istream & is,Item &obj)
    {
        is>>obj.name;
        is>>obj.quantity;
        is>>obj.price;
    }
    // operator function which prints an object as a cout
    friend ostream& operator<<(ostream& os ,Item &obj)
    {
        os<<"Name: "<<obj.name<<endl;
        os<<"Quantity: "<<obj.quantity<<endl;
        os<<"Price:  "<<obj.price<<endl;
        return os;
    }
};

class Seller
{
// private member variables of class seller
private:
    string name,email;
    Item *items;
    int maxItems;


public:
    // public member variables and functions of class seller
    // initializing id
    int id=0;

    // making class item as a friend of class seller
    friend class Item;

    // parameterized constructor
    Seller(string n,string e,int siz)
    {
        name=n;
        email=e;
        maxItems=siz;
        items=new Item[maxItems];
    }
    friend ostream& operator <<(ostream & os,Seller & per)
    {
        os<<"Name: "<<per.name<<endl;
        os<<"E_Mail: "<<per.email<<endl;
        return os;
    }
    // add an item function which takes object as a parameter
    bool Add_An_Item(Item &obj )
    {
        for(int i=0;i<id;i++)
        {
            // adding a quantity in case this item exists
            if(items[i]==obj)
            {
                items[i]+=obj;
                return true;
            }
        }
        // adding the new item in case there is enough space
        if(id!=maxItems)
        {
            items[id]=obj;
            id++;
            return true;
        }
        else
        {
            cout<<"Sorry there is no enough space"<<endl;
            return false;
        }
    }
    // sell an item function which takes the item's name and item's quantity as parameters
    bool Sell_An_Item(string n,double q)
    {
        for(int i=0;i<id;i++)
        {
            if(n==items[i].getName())
            {
                //  decreasing the item's quantity,If the quantity is less than or equal to the item’s quantity
                if(q<=items[i].getQantity())
                {
                    items[i]-=q;
                    return true;
                }
                else
                {
                    cout<<"There is only "<<items[i].getQantity()<<" left for this item"<<endl;
                    return false;
                }

            }
        }
        cout<<"The Item is Not Found"<<endl;
        return false;
    }
    // print items function which prints all the item information for the seller
    void print_Items()
    {
        for(int i=0;i<id;i++)
        {
            cout<<items[i]<<endl;
        }
    }
    // this function detects the item by using it's id
    Item find_by_id(int index)
    {
        Item temp("Not Found",-2,-2);
        for(int i=0;i<id;i++)
        {
            if(index-1==i)
            {
                cout<<items[i]<<endl;;
                return items[i];
            }
        }
        cout<<"Not Found"<<endl;
        return temp;
    }
    //Destructor
    ~Seller()
    {
        delete[]items;
    }

};
//initialize static variable
int Item::ID=0;

void Item::setID(int id)
{
    ID=id;
}
void Item::setName(string n)
{
    name=n;
}
void Item::setQuantity(double q)
{
    quantity=q;
}
void Item::setPrice(double p)
{
    price=p;
}
int Item::getID()
{
    return ID;
}
string Item::getName()
{
    return name;
}
double Item::getQantity()
{
    return quantity;
}
double Item::getprice()
{
    return price;
}


int main()
{
    string name,email;
    int siz;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your Email: ";
    cin>>email;
    cout<<"Enter the capacity: ";
    cin>>siz;

    Seller s1(name,email,siz);     // passing arguments for class seller
    int num;
    while(num!=6)
    {
        // displaying menu to the user
        cout<<endl;
        cout<<"1. Print My Info"<<endl;
        cout<<"2. Add An Item"<<endl;
        cout<<"3. Sell An Item"<<endl;
        cout<<"4. Print Items"<<endl;
        cout<<"5. Find an Item by ID"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<endl;
        cout<<"choose a number from the given menu: ";
        cin>>num;
        if(num==1)
        {
            cout<<s1<<endl;
        }
        else if(num==2)
        {
            string n;
            double q,p;
            cout<<"Enter the name of the item: ";
            cin>>n;
            cout<<"Enter the quantity of the item: ";
            cin>>q;
            cout<<"Enter the price: ";
            cin>>p;
            Item i(n,q,p);    // passing arguments to class Item
            if(s1.Add_An_Item(i))
            {
                cout<<"Your item has been added successfully"<<endl;
            }
            else{
                cout<<"Sorry! There is no enough space for adding this item"<<endl;
            }
        }
        else if (num==3)
        {
            string itemname;
            double quantity;
            cout<<"Enter the item name: ";
            cin>>itemname;
            cout<<"enter the quantity of the item: ";
            cin>>quantity;
            if (s1.Sell_An_Item(itemname,quantity))
            {
                cout<<"the quantity has been sold"<<endl;
            }
        }
        else if(num==4)
        {
            s1.print_Items();
        }
        else if(num==5)
        {
            int id;
            cout<<"Enter the ID: ";
            cin>>id;
            s1.find_by_id(id);
        }
    }


    return 0;
}
