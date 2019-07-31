#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<string.h>

class customer
{
 int ID;
 char name[20];
 char city;
 char status[20];
 public:
 void getdata();
 void showdata();
 void show_tabular();
 int getid();
};

void customer::getdata()
{int st;
 cout<<endl<<"Enter ID ";
 cin>>ID;
 cout<<endl<<"Enter Name ";
 gets(name);
 cout<<endl<<"Enter City ";
 cin>>city;
 cout<<endl<<"Choose status "<<endl<<"1) Processing"<<endl<<"2) Packaging"<<endl<<"3) Dispatched"<<endl<<"4) Delivered";
 cin>>st;
  switch (st)
 {
  case 1:  strcpy(status,"Processing");
	   break;
  case 2:  strcpy(status,"Packaging");
	   break;
  case 3:  strcpy(status,"Dispatched");
	   break;
  case 4:  strcpy(status,"Delivered");
	   break;
  default: cout<<"Enter Proper choice";
 };
}

void customer::showdata()
{
 cout<<endl<<"ID "<<ID<<endl<<"Name "<<name<<endl<<"City "<<city<<endl<<"Status "<<status<<endl;
}

void customer::show_tabular()
{
}

int customer::getid()
{
 return ID;
}

void intro()
{
 cout<<"\n\n\n\t\t            Online Shopping ";
 cout<<"\n\n\t\t            Project ";
 cout<<"\n\n\n\t    Made By : DEEPAK DAHIYA";
 cout<<"\n\t    School  : BAL BHARATI PUBLIC SCHOOL";
 getch();
}

void myreco();
void entry_menu();

int main()
{
 clrscr();
 intro();
 int ch;
 do
 {
  clrscr();
  cout<<"\n\n\n\t Main Menu";
  cout<<"\n\n\t 1)Result Menu";
  cout<<"\n\n\t 2)Entry/Edit Menu";
  cout<<"\n\n\t 3)Exit";
  cout<<"\n\n\t Choose Option";
  cin>>ch;
  clrscr();
  switch(ch)
  {
   case 1 : myreco();
	    break;
   case 2 : entry_menu();
	    break;
   case 3 :
	    break;
   default:cout<<"\a";
  }
 }while(ch!=3);
 return 0;
}

void write_customer()
{
 customer cs;
 ofstream fout("customer.dat",ios::binary||ios::app);
 cs.getdata();
 fout.write((char*)&cs,sizeof(customer));
 fout.close();
 cout<<"\n\nCustomer's Record Has Been Created";
 cin.ignore();
 getch();
}

void display_all()
{
 customer cs;
 ifstream fin("customer.dat",ios::binary);
 if(!fin)
 {
  cout<<"File not found! Press any key to continue";
  getch();
  return;
 }
 cout<<"\n\n\n\t\t DISPLAY ALL RECORD \n\n";
 while(fin.read((char*)&cs,sizeof(customer)))
 {
  cs.showdata();
  cout<<"\n\n=====================================\n";
 }
 fin.close();
 getch();
}

void display_sp(int n)
{
 customer cs;
 ifstream fin("customer.dat",ios::binary);
 if(!fin)
 {
  cout<<"File not found! Press any key to continue";
  getch();
  return;
 }
 int flag=0;
 while(fin.read((char*)&cs,sizeof(customer)))
 {
  if(cs.getid()==n)
  {
   cs.showdata();
   flag=1;
  }
 }
 fin.close();
 if(flag=0)
 cout<<"\n\n Record does not exist";
 getch();
}

void modify_customer(int n)
{
 int found=0;
 customer cs;
 fstream file;
 file.open("customer.dat",ios::binary|ios::in|ios::out);
 if(!file)
 {
  cout<<"File not found! Press any key to continue";
  getch();
  return;
 }
 while(file.read((char*)&cs,sizeof(customer))&&found==0)
 {
  if(cs.getid()==n)
  {
   cs.showdata();
   cout<<"\n\nEnter New Details\n";
   cs.getdata();
   int pos=(-1)*sizeof(cs);
   file.seekp(pos,ios::cur);
   file.write((char*)&cs,sizeof(customer));
   cout<<"\n\n\t Updated";
   found=1;
  }
 }
 file.close();
 if(found==0)
 cout<<"\n\n Not Found";
 getch();
}


void delete_customer(int n)
{
 customer cs;
 ifstream fin("customer.dat",ios::binary);
 if(!fin)
 {
  cout<<"File not found! Press any key to continue";
  getch();
  return;
 }
 ofstream fout("temp.dat",ios::out);
 fin.seekg(0,ios::beg);
 while(fin.read((char*)&cs,sizeof(customer)))
 {
  if(cs.getid()!=n)
  {
    fout.write((char*)&cs,sizeof(customer));
  }
 }
 fout.close();
 fin.close();
 remove("customer.dat");
 rename("temp.dat","customer.dat");
 cout<<"\n\nDeletion Complete!";
 getch();
}

void allrecords()
{
 customer cs;
 ifstream fin("customer.dat",ios::binary);
 if(!fin)
 {
  cout<<"File not found! Press any key to continue";
  getch();
  return;
 }
 cout<<"\n\n\t All Customers \n\n";
 cout<<"==========================================================\n";
 cout<<"ID       Name       City        Status                    \n";
 cout<<"==========================================================\n";
 while(fin.read((char*)&cs,sizeof(customer)))
 {
  cs.show_tabular();
 }
 getch();
 fin.close();
}

void myreco()
{
 int ch;
 int ID;
 cout<<"\n\n\n\tRecord Menu";
 cout<<"\n\n\n\t1) All Records";
 cout<<"\n\n\n\t2) One Record";
 cout<<"\n\n\n\t3) Main Menu";
 cout<<"\n\n\n\tEnter choice";
 cin>>ch;
 clrscr();
 switch(ch)
 {
  case 1 :allrecords();
	  break;
  case 2 :cout<<"\n\n\tEnter ID : ";
	  cin>>ID;
	  display_sp(ID);
	  break;
  case 3 :break;
  default:cout<<"\a";
 }
}

void entry_menu()
{
 int ch;
 int num;
 clrscr();
 cout<<"\n\n\n\tEntry Menu";
 cout<<"\n\n\t1) Create customer's record";
 cout<<"\n\n\t2) Display all customers' records";
 cout<<"\n\n\t3) Search";
 cout<<"\n\n\t4) Modify";
 cout<<"\n\n\t5) Delete";
 cout<<"\n\n\t6) Main Menu";
 cout<<"\n\n\t Enter Choice";
 cin>>ch;
 clrscr();
 switch(ch)
 {
  case 1:write_customer();
	 break;
  case 2:display_all();
	 break;
  case 3:cout<<"\n\n\tEnter ID ";cin>>num;
	 display_sp(num); break;
  case 4:cout<<"\n\n\tEnter ID ";cin>>num;
	 modify_customer(num); break;
  case 5:cout<<"\n\n\tEnter ID ";cin>>num;
	 delete_customer(num); break;
  case 6:
	 break;
  default:cout<<"\a"; entry_menu();
 }
}













