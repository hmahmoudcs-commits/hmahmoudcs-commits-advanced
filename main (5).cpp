
#include <iostream>
#include <iomanip>
#include <vector>



class Member {
    private:
        int id;
        int months;
        std::string plan;
        std::string timing;
        bool isVirtual;
    public:
    
    Member(int i, int m, std::string p, std::string t, bool v): id(i), months(m), plan(p), timing(t), isVirtual(v){}
    
    int getMonths(){    return months;  }
    std::string getPlan(){  return plan;    }
    std::string getTiming(){  return timing;  }
    bool getIsVirtual(){    return isVirtual;   }
    
    std::string display()
    {
        return "\nMember ID#: " + std::to_string(id);
    }
    
};//////////////////////////////

class Fee{ 
    friend std::ostream& operator<<(std::ostream& o, Fee f);
    private:
        std::string label;
        double fee;
    public:
    
    Fee(std::string l, double f): label(l), fee(f){}

    std::string getLabel(){   return label;   }
    double getFee(){    return fee; }
    
    double operator-(float d){  return this->fee*d;}
    double operator+(float d){  return this->fee*d;}
    
    Fee operator*(int months)
    {
        Fee base("",0);
        double f = fee*months;
        base = Fee("Base Membership",f);
        return base;
    }

};
std::ostream& operator<<(std::ostream& o, Fee f)
{
    o<<f.getLabel()<<"       $   "<<f.getFee();
    return o;
}
/////////////////////////////////


class MembershipInvoice{
    private:
        Member oneMember;
        std::vector<Fee> allFees;
        double totalFees;
        int invoiceId;
        static long int newInvoiceId;
    public:
    
    MembershipInvoice(int i, int m, std::string p, std::string t, bool v): oneMember(i,m,p,t,v)
    {
        totalFees = 0;
        invoiceId = newInvoiceId;
        newInvoiceId++;
    }
    
    Fee feePerMonth(std::string thePlan)
    {
        Fee oneFee("",0);
        if(thePlan == "basic")
        return oneFee=Fee("Basic per month",60.0);
        else if(thePlan == "standard")
        return oneFee=Fee("Standard per month",95.0);
        else if(thePlan == "premium")
        return oneFee=Fee("Premium per month",140.0);
        else if(thePlan == "elite")
        return oneFee=Fee("Elite per month",220.0);
        else
        return Fee("Invalid plan", 0);
    }
    
    void compute()
    {
        
        Fee aFee("",0);
        
        aFee = feePerMonth(oneMember.getPlan());
        allFees.push_back(aFee);
        
        Fee base("",0);
        base  = aFee * oneMember.getMonths();  /// #1
        
        allFees.push_back(base);
        
        if(oneMember.getTiming() == "early")
        {
          double discount;
          discount =  base - .07;
          Fee aDiscount("Early Registration discount", -discount );
          allFees.push_back(aDiscount);
        }
        else if(oneMember.getTiming() == "late")
        {
          double surcharge =  base + .10;
          Fee aSurcharge("Late signup charge", surcharge );
          allFees.push_back(aSurcharge);
          
        }

    
    for( Fee x : allFees)
    totalFees+=x.getFee();
    
    if( oneMember.getIsVirtual() == true)
    {
    double oDiscount;
    oDiscount =  base - .12;
    Fee onlineDiscount("Online Registration discount", -oDiscount );
    allFees.push_back(onlineDiscount);
    totalFees-=oDiscount;
    
    }
    
    
        
    }
    
    void display()
    {
        oneMember.display();
        std::cout<<"\n"<<invoiceId<<"\n";
        for(Fee x : allFees)
        {
            std::cout<<x<<"\n";
        }
        
        (totalFees > 5000.0) ? std::cout<<"\nPlease contact the Billing Office.\n" : 
		   							 std::cout<<"\n\nYour Membership bill is:          $  "<< totalFees << "\n";
    }
    
    
    
};
long int MembershipInvoice::newInvoiceId = 700100;










void inputData(int& theMonths, int& theirId);
bool inputVirtual();
int main()
{
    int theMonths, theirId = 0;
    bool online;
    std::string planType, thierTiming;
    inputData(theMonths,theirId);
    std::cout<<"\nEnter your plan type: ( Basic, Standard, Premium, Elite )";
    std::cin.ignore(1000,'\n');
    getline(std::cin,planType);
    std::cout<<"\nSignup timing: ( early, ontime, late ) ";
    getline(std::cin, thierTiming);
    
    online = inputVirtual();
    
    MembershipInvoice invoice1(theirId, theMonths, planType, thierTiming, online);

    invoice1.compute();
    invoice1.display();

    return 0;
}
    


void inputData(int& theMonths,  int& theirId)
{
    std::cout<<" Enter member ID: ";
    std::cin>>theirId;
    
    while(std::cin.fail()|| theirId < 10000)
    {
    if(std::cin.fail())
    {
      std::cout<<"Your ID must be numeric\n";
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<" Enter member ID: ";
      std::cin>>theirId;
    }
    else if(theirId < 10000)
    {
      std::cout<<"Your ID must be at least 5 digits \n";
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<" Enter member ID: ";
      std::cin>>theirId;
    }
    }
    std::cout<<"Total Membership Months ( 1 - 24 ):";
    std::cin>>theMonths;
    
    while(std::cin.fail()|| theMonths < 1 || theMonths > 24)
    {
    if(std::cin.fail())
    {
      std::cout<<"Your ID must be numeric\n";
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Total Membership Months ( 1 - 24 ):";
      std::cin>>theMonths;
    }
    else if(theMonths < 1 || theMonths > 24)
    {
      std::cout<<"Your months must be between 1 and 24, \n";
      std::cin.clear();
      std::cin.ignore(1000,'\n');
      std::cout<<"Total Membership Months ( 1 - 24 ):";
      std::cin>>theMonths;
    }
        
    }
}

bool inputVirtual()
{
    std::cout << std::fixed << std::setprecision(2);
    std::string choice;
    std::cout<<"Virtual-only Membership? (yes/no):";
    getline(std::cin, choice);
    
    if(choice =="yes")
    return true;
    else
    return false;
}


