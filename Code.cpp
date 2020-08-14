/*
        HOTEL MANAGEMENT SYSTEM
        
        DEVELOPED BY          
        M.ASWIN KISHORE           
        ANSAF NIYAZ               

        IDE:CODE BLOCKS 17.12
        COMPILER:GNU GCC
*/

#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
#include<iomanip>
#include<stdlib.h>

using namespace std;

void  file_check();                              //TO CREATE DATA FILE OR IMPORT DATA FILE IF PRESENT
void  modify_file();                             //TO MODIFY THE DATA OF DATA FILE
void  initialize_room(double,double,double);     //TO INITIALIZE THE ROOMS AS ROOM NO. 100-109 WITH RESPECTIVE CATEGORIES:STANDARD,SUPERIOR AND DELUXE

void  room_enquiry();                            //TO ENQUIRE THE STATUS OF ROOMS
void  room_booking();                            //TO BOOK ROOMS
void  customer_details();                        //SHOWS CUSTOMER DETAILS BY ROOM NO OR CUSTOMER NAME
void  billing();                                 //BILLING
void  modify_room_price();                       //TO MODIFY ROOM PRICES
void  admin_panel();                             //TO CALL ADMIN PANEL

char* display_time();                            //RETURNS CURRENT SYSTEM TIME
void  delay(int);                                //TO CREATE DELAY IN OUTPUT
int   date_calc(int,int,int,int,int,int);        //RETURNS THE NUMBER OF DAYS BETWEEN ENTRY DATE & EXIT DATE
int   check_date(int,int,int);                   //TO CHECK IF THE DATE ENTERED IS CORRECT.RETURNS 0 OF DATE IS INCORRECT
int   check_phone(char phone[]);                 //TO CHECK IF PHONE NUMBER ENTERED IS CORRECT
void  check_password(bool);                      //TO CHECK PASSWORD AT ADMIN PANEL OR AT THE STARTING OF PROGRAM

fstream f,ft;

class room {
               public:

                    char status[20];
                    char category[30];
                    int bookdays;

                    struct date{
                                int d,y,m;
                               };
                    date entrydate,exitdate;

                    char name[40];
                    char occupation[40];
                    char phone[12];
                    int  no_of_people;
                    int  roomno;

                    double price;

                    void input()
                    {
                        cout<<"\n\n";
                        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
                        cout<<"\t\t\t\t| #################### FILL THE FORM ################### |\n";
                        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
                        cout<<"\n";
                        cout<<setw(74)<<display_time()<<"\n";
                        cout<<"\t\t\t\t---------------------------------------------------------\n";
                        cout<<"\n\t\t\t\t NAME:";cin.sync();;
                        cin.getline(name,40);
                        cout<<"\n\t\t\t\t OCCUPATION:";cin.sync();
                        cin.getline(occupation,40);
                        cout<<"\n\t\t\t\t PHONE:";cin.sync();
                        cin.getline(phone,12);
                        while(check_phone(phone)==0)
                        {
                            system("color 0C");
                            cout<<"\n\t\t\t\t INCORRECT PHONE NUMBER";
                            cout<<"\n\t\t\t\t RE-ENTER PHONE:";cin.sync();
                            cin.getline(phone,12);
                        }
                        system("color 0B");

                        cout<<"\n\t\t\t\t NUMBER OF PEOPLE:";
                        cin>>no_of_people;

                        cout<<"\n\t\t\t\t ENTRY DATE [DD  MM  YYYY]:";
                        cin>>entrydate.d>>entrydate.m>>entrydate.y;
                        cin.sync();
                        while((check_date(entrydate.d,entrydate.m,entrydate.y)==0))
                              {
                                  system("color 0C");
                                  cout<<"\n\t\t\t\t INCORRECT DATE";
                                  cout<<"\n\t\t\t\t RE-ENTER ENTRY DATE [DD  MM  YYYY]:";
                                  cin>>entrydate.d>>entrydate.m>>entrydate.y;
                              }
                        system("color 0B");

                        cout<<"\n\t\t\t\t EXIT DATE  [DD  MM  YYYY]:";
                        cin>>exitdate.d>>exitdate.m>>exitdate.y;
                        cin.sync();
                        bookdays=date_calc(entrydate.d,entrydate.m,entrydate.y,exitdate.d,exitdate.m,exitdate.y);
                        while((check_date(exitdate.d,exitdate.m,exitdate.y)==0)||(bookdays<=0))
                              {
                                  system("color 0C");
                                  cout<<"\n\t\t\t\t INCORRECT DATE";
                                  cout<<"\n\t\t\t\t RE-ENTER EXIT DATE [DD  MM  YYYY]:";
                                  cin>>exitdate.d>>exitdate.m>>exitdate.y;
                                  bookdays=date_calc(entrydate.d,entrydate.m,entrydate.y,exitdate.d,exitdate.m,exitdate.y);
                              }
                        system("color 0B");

                        cout<<"\n\t\t\t\t---------------------------------------------------------\n";
                        system("color 0A");
                        cout<<"\n\t\t\t\t ROOM "<<roomno<<" HAS BEEN BOOKED BY "<<name<<" FOR "<<bookdays<<" DAY(S)";

                    }

                    void output()
                    {
                        cout<<"\n\t\t\t\t---------------------------------------------------------\n";
                        cout<<"\n\t\t\t\t NAME:"<<name;
                        cout<<"\n\t\t\t\t OCCUPATION:"<<occupation;
                        cout<<"\n\t\t\t\t PHONE:"<<phone;
                        cout<<"\n\t\t\t\t NUMBER OF PEOPLE:"<<no_of_people<<"\n";
                        cout<<"\n\t\t\t\t ROOM NO:"<<roomno;
                        cout<<"\n\t\t\t\t CATEGORY:"<<category;
                        cout<<"\n\t\t\t\t ENTRY DATE [DD  MM  YYYY]:"<<entrydate.d<<"/"<<entrydate.m<<"/"<<entrydate.y;
                        cout<<"\n\t\t\t\t EXIT DATE  [DD  MM  YYYY]:"<<exitdate.d<<"/"<<exitdate.m<<"/"<<exitdate.y;
                        cout<<"\n\t\t\t\t BOOKED FOR:"<<bookdays<<" DAY(S)\n";
                        cout<<"\n\t\t\t\t---------------------------------------------------------\n";

                    }

                    void bill()
                    {
                        float cash_recieved,total_cash;
                        total_cash=(price*bookdays*no_of_people);

                        BILL:
                        system("cls");
                        cout<<"\n\n";
                        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
                        cout<<"\t\t\t\t| ------------------------ BILL ------------------------ |\n";
                        cout<<"\t\t\t\t| ------------------------------------------------------ |\n\n";
                        cout<<"\t\t\t\t  ######################################################  ";
                        cout<<"\n\t\t\t\t  BILLING DATE:"<<display_time();
                        cout<<"\n\t\t\t\t  NAME:"<<name;
                        cout<<"\n\t\t\t\t  PHONE:"<<phone;
                        cout<<"\n\t\t\t\t  ROOM NO:"<<roomno;
                        cout<<"\n\t\t\t\t  CATEGORY:"<<category;
                        cout<<"\n\t\t\t\t  ENTRY DATE [DD  MM  YYYY]:"<<entrydate.d<<"/"<<entrydate.m<<"/"<<entrydate.y;
                        cout<<"\n\t\t\t\t  EXIT DATE  [DD  MM  YYYY]:"<<exitdate.d<<"/"<<exitdate.m<<"/"<<exitdate.y<<"\n";
                        cout<<"\t\t\t\t  ------------------------------------------------------  \n";
                        cout<<"\t\t\t\t  ROOM PRICE | NO OF DAYS | NO OF PEOPLE | TOTAL  \n";
                        cout<<setw(40)<<price<<setw(12)<<bookdays<<setw(14)<<no_of_people<<setw(12)<<"RS:"<<total_cash<<"\n";
                        cout<<"\t\t\t\t  ------------------------------------------------------  \n";
                        cout<<"\t\t\t\t  ######################################################  \n\n";
                        cout<<"\t\t\t\t  ------------------------------------------------------  \n";
                        cout<<"\t\t\t\t  ENTER CASH RECIEVED:";
                        cin>>cash_recieved;
                        cout<<"\n";
                        if(cash_recieved<total_cash)
                            goto BILL;
                        cout<<"\t\t\t\t  REMAINING BALANCE:"<<cash_recieved-total_cash<<"\n";
                        cout<<"\t\t\t\t  ------------------------------------------------------  \n";
                        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";

                        //RESET ROOM TO AVAILABLE
                        entrydate.y=exitdate.y=0;
                    }

            }obj[10],temp;


int main()
{
    int c=0;
    system("color 3E");
    system("MODE CON: COLS=119 LINES=31");
    cout<<"\n\n\n\n\n\n";
    cout<<"\t\t\t\t| =================================================== |\n";
    cout<<"\t\t\t\t| =================================================== |\n";
    cout<<"\t\t\t\t| ############  HOTEL MANAGEMENT SYSYEM  ############ |\n";
    cout<<"\t\t\t\t| =================================================== |\n";
    cout<<"\t\t\t\t| =================================================== |\n";
    cout<<"\n\n\n";
    cout<<"\t\t\t\t======================================================= \n";
    cout<<"\t\t\t\t~~~~~~~~~~~~ DEVELOPED BY ASWIN AND ANSAF ~~~~~~~~~~~~~ \n";
    cout<<"\t\t\t\t======================================================= \n";
    delay(2);
    system("cls");

    check_password(false);   //PASSWORD CHECK AT BEGINNING OF PROGRAM
    file_check();

    while(c!=6)
    {
    system("MODE CON: COLS=119 LINES=31");
    system("cls");
    system("color 0E");
    cout<<"\n\n";
    cout<<"\t\t\t\t  ---------------------------------------------------- \n";
    cout<<"\t\t\t\t | ################################################## |\n";
    cout<<"\t\t\t\t | ########### WELCOME TO HOTEL ESPERENZA ########### |\n";
    cout<<"\t\t\t\t | ################################################## |\n";
    cout<<"\t\t\t\t ---------------------------------------------------- \n\n\n";
    cout<<"\t\t\t\t\t        "<<display_time()<<"\n\n";
    cout<<"\t\t\t\t  ---------------------------------------------------- \n";
    cout<<"\t\t\t\t |                                                    |\n";
    cout<<"\t\t\t\t |                 1.ROOM EQUIRY                      |\n";
    cout<<"\t\t\t\t |                 2.ROOM BOOKING                     |\n";
    cout<<"\t\t\t\t |                 3.CUSTOMER DETAILS                 |\n";
    cout<<"\t\t\t\t |                 4.CHECK OUT & BILLING              |\n";
    cout<<"\t\t\t\t |                 5.ADMIN PANEL                      |\n";
    cout<<"\t\t\t\t |                 6.EXIT                             |\n";
    cout<<"\t\t\t\t |                                                    |\n";
    cout<<"\t\t\t\t  ---------------------------------------------------- \n";
    cout<<"\n\t\t\t\t                   ENTER CHOICE:";
    cin.sync();
    cin>>c;
        if(c==1)
            room_enquiry();
        else if(c==2)
            room_booking();
        else if(c==3)
            customer_details();
        else if(c==4)
            billing();
        else if(c==5)
            admin_panel();
        else if(c==6)
            return 0;
        else
            cin.clear();
    }
    return 0;
}


//FILE HANDLING FUNCTIONS

void initialize_room(double x=300,double y=500,double z=900)
{
  for(int i=0;i<10;i++)
  {
      obj[i].roomno=i+100;
      if(i<=3)
         {
              strcpy(obj[i].category,"STANDARD");
              obj[i].price=x;
         }
      else if(i>=4&&i<=7)
          {
              strcpy(obj[i].category,"SUPERIOR");
              obj[i].price=y;
          }
      else if(i>=8)
          {
              strcpy(obj[i].category," DELUXE ");
              obj[i].price=z;
          }
      strcpy(obj[i].status,"N/A");
      obj[i].entrydate.y=0;
      obj[i].exitdate.y=0;
  }
}

void file_check()
{
    f.open("data.dat",ios::in|ios::out|ios::binary|ios::ate);
    if(!f.is_open())
    {
        f.open("data.dat",ios::in|ios::out|ios::binary|ios::trunc);
        initialize_room();
        f.sync();
        f.seekg(0);
        for(int i=0;i<10;i++)
        {
            f.write((char*)&obj[i],sizeof(room));
        }

    }
    else
    {
        f.sync();
        f.seekg(0);
        for(int i=0;i<10;i++)
         {
             f.read((char*)&temp,sizeof(room));
             obj[i]=temp;
         }
    }
}

void modify_file()
{
        f.close();
        ft.open("data.dat",ios::out|ios::binary|ios::trunc);
        if(!ft)
        {
            cout<<"data FILE NOT OPENING!!";
            system("pause");
        }
        ft.sync();
        ft.seekg(0);
        for(int i=0;i<10;i++)
        {
           temp=obj[i];
           ft.write((char*)&temp,sizeof(room));
        }
        ft.close();
        file_check();

}

void modify_room_price()
{
        double price_std,price_sup,price_del;
        system("cls");
        system("color 4E");
        cout<<"\n\n";
        cout<<"\t\t\t\t     -------------------------------------------- \n";
        cout<<"\t\t\t\t     ############### ROOM PRICES ################ \n";
        cout<<"\t\t\t\t     -------------------------------------------- \n";
        cout<<"\t\t\t\t     $$$$ CAUTION: ROOM DATA WILL BE CLEARED $$$$ \n";
        cout<<"\t\t\t\t     -------------------------------------------- \n\n\n";
        cout<<"\t\t\t\t     ----------------  CURRENT  ----------------- \n";
        cout<<"\t\t\t\t     STANDARD:"<<obj[0].price<<"\n";
        cout<<"\t\t\t\t     SUPERIOR:"<<obj[5].price<<"\n";
        cout<<"\t\t\t\t     DELUXE  :"<<obj[9].price<<"\n";
        cout<<"\t\t\t\t     -------------------------------------------- \n\n\n";
        cout<<"\t\t\t\t     -------------- ENTER NEW PRICES ------------ \n";
        cout<<"\t\t\t\t     STANDARD:";cin>>price_std; cout<<"\n";
        cout<<"\t\t\t\t     SUPERIOR:";cin>>price_sup; cout<<"\n";
        cout<<"\t\t\t\t     DELUXE  :";cin>>price_del; cout<<"\n";
        cout<<"\t\t\t\t     -------------------------------------------- \n";
        initialize_room(price_std,price_sup,price_del);
        modify_file();
        cout<<"\n\n\t\t\t\t\t    ";
        system("pause");
}


//MENU FUNCTIONS

void room_enquiry()
{
    system("cls");
    system("color 0D");
    cout<<"\n\n";
    cout<<"   #################################################### ROOMS ##################################################\n\n";
    cout<<setw(71)<<display_time()<<"\n";
    cout<<"   -------------------------------------------------------------------------------------------------------------\n";
    cout<<"   ROOM NO."<<setw(11)<<"TYPE"<<setw(22)<<"STATUS"<<setw(24)<<"BOOKED FOR"<<setw(23)<<"ENTRY - DATE"<<setw(21)<<"EXIT - DATE \n";
    cout<<"   -------------------------------------------------------------------------------------------------------------\n";
    for(int i=0;i<10;i++)
    {
    cout<<"   "<<obj[i].roomno<<setw(18)<<obj[i].category;
        if((obj[i].entrydate.y)==0)
          cout<<setw(22)<<"AVAILABLE"<<setw(18)<<"N/A"<<setw(22)<<"N/A"<<setw(22)<<"N/A"<<"\n";
        else
        {
            cout<<setw(20)<<"BOOKED"<<setw(18)<<obj[i].bookdays<<" DAY(S)";
           cout<<setw(15)<<obj[i].entrydate.d<<"/"<<obj[i].entrydate.m<<"/"<<obj[i].entrydate.y;
           cout<<setw(13)<<obj[i].exitdate.d<<"/"<<obj[i].exitdate.m<<"/"<<obj[i].exitdate.y<<"\n";
        }
    }
    cout<<"   -------------------------------------------------------------------------------------------------------------\n\n";
    cout<<setw(79)<<"PRICES OF ROOMS PER HEAD PER DAY FOR:-\n\n";
    cout<<setw(60)<<"STANDARD:"<<obj[0].price<<"\n";
    cout<<setw(60)<<"SUPERIOR:"<<obj[5].price<<"\n";
    cout<<setw(60)<<"DELUXE  :"<<obj[9].price<<"\n";
    cout<<"\n\t\t\t\t\t";
    system("pause");
}

void customer_details()
{
        char search_customer[40];
        int found,c,rmno;

        DETAILS:
        system("cls");
        system("color 0f");
        found=0;
        cout<<"\n\n";
        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
        cout<<"\t\t\t\t| ################### CUSTOMER DETAILS ################# |\n";
        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
        cout<<"\n";
        cout<<setw(74)<<display_time()<<"\n\n";
        cout<<setw(66)<<"SEARCH BY :-\n\n";
        cout<<setw(63)<<"1.ROOM NO \n";
        cout<<setw(70)<<"2.CUSTOMER NAME \n\n";
        cout<<setw(65)<<"ENTER CHOICE:";cin.sync();

        cin>>c;
        if(c==1)
        {
            cout<<"\n"<<setw(66)<<"ENTER ROOM NO:";cin.sync();
            cin>>rmno;
        }
        else if(c==2)
        {
            cout<<"\n"<<setw(72)<<"ENTER CUSTOMER NAME:";cin.sync();
            cin.getline(search_customer,40);
        }
        else
            goto DETAILS;

        system("cls");
        cout<<"\n\n";
        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
        cout<<"\t\t\t\t| ################### CUSTOMER DETAILS ################# |\n";
        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
        cout<<"\n";
        cout<<setw(74)<<display_time();
        for(int i=0;i<10;i++)
        {
            if((!strcmpi(obj[i].name,search_customer)||(obj[i].roomno==rmno))&&obj[i].entrydate.y!=0)
            {
                obj[i].output();
                found=1;
            }
        }
        if(found==0)
           {
             system("color 0C");
             cout<<"\n"<<setw(73)<<"CUSTOMER/ROOM NOT FOUND!";
           }
        cout<<"\n\n\t\t\t\t\t      ";
        system("pause");


}

void room_booking()
{
    long int rmno,c;
    BOOKING:
    system("cls");
    system("color 0B");
    cout<<"\n\n";
    cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
    cout<<"\t\t\t\t| ####################### BOOKING ###################### |\n";
    cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
    cout<<"\n";
    cout<<setw(73)<<display_time()<<"\n";
    cout<<setw(71)<<"ROOMS AVAILABLE:-\n\n";
    for(int i=0;i<10;i++)
    {
        if(obj[i].entrydate.y==0)
        {
            cout<<setw(56);
            cout<<obj[i].roomno<<"   "<<obj[i].category<<"\n";
        }
    }
    cout<<"\n";
    cout<<setw(67)<<"ENTER ROOM NO:";
    cin>>rmno;
    for(int i=0;i<10;i++)
    {

           if((obj[i].roomno==rmno)&&(obj[i].entrydate.y!=0))
                {
                   system("color 0C");
                   cout<<"\n"<<setw(75)<<"THIS ROOM IS BOOKED ALREADY";
                   cout<<"\n\n"<<setw(85)<<"PRESS 1 TO RE-ENTER OR 0 TO RETURN TO MAIN MENU:";
                   cin>>c;
                   if(c==1)
                        goto BOOKING;
                   else if(c==0)
                        break;

                }
            else if((obj[i].roomno==rmno)&&(obj[i].entrydate.y==0))
                {

                    system("cls");
                    obj[i].input();
                    modify_file();
                    cout<<"\n\n\t\t\t\t ";
                    system("pause");

                }
             else if(rmno>109||rmno<100)
             {
                   system("color 0C");
                   cout<<"\n\n"<<setw(64)<<"INVALID";
                   cout<<"\n\n"<<setw(85)<<"PRESS 1 TO RE-ENTER OR 0 TO RETURN TO MAIN MENU:";
                   cin>>c;
                   if(c==1)
                        goto BOOKING;
                   else if(c==0)
                        break;
             }
    }
}

void billing()
{
        system("cls");
        system("color 0A");
        char search_customer[40],c;
        int found=0,rmno;
        cout<<"\n\n";
        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
        cout<<"\t\t\t\t| ################## CHECK OUT & BILLING ############### |\n";
        cout<<"\t\t\t\t| ------------------------------------------------------ |\n";
        cout<<"\n\n";
        cout<<setw(67)<<"ENTER ROOM NO:";cin.sync();
        cin>>rmno;
        for(int i=0;i<10;i++)
        {
            if(((rmno==obj[i].roomno))&&(obj[i].entrydate.y!=0))
            {
                found=1;
                cout<<"\n"<<setw(67)<<"CUSTOMER NAME:"<<obj[i].name;

                TRYAGAIN:
                cout<<"\n\n"<<setw(84)<<"PRESS 1 TO CONTINUE OR 0 TO RETURN TO MAIN MENU:";
                cin.sync();
                cin>>c;
                cin.clear();
                if(c=='1')
                {
                  obj[i].bill();
                  modify_file();
                }
                else if(c=='0')
                    break;
                 else
                    goto TRYAGAIN;
            }
        }
        if(found==0)
           {
             system("color 0C");
             cout<<"\n"<<setw(71)<<"CUSTOMER NOT FOUND!";
           }
        if(c!='0')
        {
            cout<<"\n\n\t\t\t\t\t\t";
            system("pause");
        }

}

void admin_panel()
{
        int c;
        system("cls");
        system("color 4E");
        check_password(true);       //PASSWORD CHECK BY ADMIN PANEL
        while(c!=4)
        {
            system("cls");
            system("color 4E");
            cout<<"\n\n";
            cout<<"\t\t\t\t     -------------------------------------------- \n";
            cout<<"\t\t\t\t     ############### ADMIN PANEL ################ \n";
            cout<<"\t\t\t\t     -------------------------------------------- \n";
            cout<<"\t\t\t\t                   1.ROOM DATA RESET              \n";
            cout<<"\t\t\t\t                   2.CHANGE ROOM PRICE            \n";
            cout<<"\t\t\t\t                   3.CHANGE PASSWORD              \n";
            cout<<"\t\t\t\t                   4.RETURN TO MAIN MENU          \n";
            cout<<"\t\t\t\t     -------------------------------------------- \n\n";
            cout<<"\t\t\t\t                   ENTER:";
            cin>>c;
            if(c==1)
                {
                    f.close();
                    remove("data.dat");
                    file_check();
                    system("cls");
                    cout<<"\n\n\n\n\n";
                    cout<<"\n\t\t\t\t\t        DATA RESET SUCCESSFULLY";
                    cout<<"\n\n\t\t\t\t\t     ";
                    system("pause");
                }
            else if(c==2)
                modify_room_price();
            else if(c==3)
                {
                    remove("password.dat");
                    check_password(true);
                }
            else if(c==4)
                break;
            else
                cin.clear();
        }

}


//TIME & DATE FUNCTIONS

char* display_time()
{
    time_t t= time(0);
    char*temp=ctime(&t);
    return temp;
}

void delay(int seconds)
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

int date_calc(int d1,int m1,int y1,int d2,int m2,int y2)
{
    int entry_date,exit_date;

    if (m1 < 3)
        y1--, m1 += 12;
    entry_date=365*y1 + y1/4 - y1/100 + y1/400 + (153*m1 - 457)/5 + d1 - 306;

    if (m2 < 3)
        y2--, m2+=12;
    exit_date=365*y2 + y2/4 - y2/100 + y2/400 + (153*m2 - 457)/5 + d2 - 306;

    return 1+exit_date-entry_date;

}

int check_phone(char phone[])
{
    for(int i=0;i<9;i++)
    {
        if(phone[i]=='\0'||!isdigit(phone[i]))
            return 0;
    }
    for(int i=0;i<10;i++)
    {
        if(phone[i]=='\0'||!isdigit(phone[i]))
            return 0;
    }
    if((phone[10]=='\0'&&phone[0]!='0')||(phone[0]=='0' && phone[11]=='\0'))
        return 1;
    return 0;
}

int check_date(int d,int m,int y)
{
    if((m==1||m==3||m==5||m==7||m==8||m==10||m==12)&&(d>31||d<1))
        return 0;
    else if((m==4||m==6||m==9||m==11)&&(d>30||d<1))
        return 0;
    else if(m==2)
    {
      if(d>29||d<1)
            return 0;
      else if((((y % 4 == 0)&&(y % 100 != 0))||(y% 400 == 0))&&(d>28||d<1))    //LEAP YEAR CHECK
            return 0;
    }
    else if(m>12||m<1)
        return 0;
    return 1;
}

void check_password(bool admin_call)
{
    char password[40];
    char ch_password[40];
    int i;
    char key[9] = {'M','A','K','A','N','S','K','E','Y'};      //KEY FOR ENCRYTION
    ft.open("password.dat",ios::in|ios::out|ios::binary|ios::ate);
    f.open("data.dat",ios::in|ios::out|ios::binary|ios::ate);
    cout<<"\n\n\n\n\n\n";

    //NO DATA FOR PASSWORD AND ROOMS
    if((!ft.is_open()&&!f.is_open())||(!ft.is_open()&&(admin_call)))
    {
        ft.open("password.dat",ios::in|ios::out|ios::binary|ios::trunc);
        ft.sync();
        ft.seekg(0);
        do{
            if(admin_call)
            {
                system("color 4E");
                system("cls");
                cout<<"\n\n";
                cout<<"\t\t\t\t     -------------------------------------------- \n";
                cout<<"\t\t\t\t     ############### ADMIN PANEL ################ \n";
                cout<<"\t\t\t\t     -------------------------------------------- \n\n";
                cout<<"\t\t\t\t            ENTER NEW PASSWORD:";
            }
            else
            {
                system("color 3E");
                cout<<"\n\n\n\t\t\t\t\t\t ENTER NEW PASSWORD:";
            }
            cin.sync();
            cin.getline(password,40);
          }
          while(password[0]=='\0');

        //XOR ENCRYPTION
        for(int i=0;password[i]!='\0';i++)
        {
            password[i]=(password[i])^key[i%(sizeof(key)/sizeof(char))];
        }
        ft<<password;

    }

    //CHECKING DATA FOR PASSWORD AND ROOMS
    else
    {
        ft.sync();
        ft.seekg(0);
        if(!(ft.getline(password,40))) //PASSWORD FILE EMPTY
        {
            if(f.is_open()) //SECURING DATA FILE BY DELETING IT
            {
                f.close();
                remove("data.dat");
                system("color 0C");
                cout<<"\n\n\n\n\n\n\t\t\t\t\tPASSWORD DATA NOT FOUND.DATA FILE DELETED";
                cout<<"\n\n\t\t\t\t\t\t";
                system("pause");
                system("cls");
                check_password(admin_call);
            }
            else           //DELTETING PASSWORD FILE
            {
                system("color 0C");
                cout<<"\n\n\n\n\n\n\t\t\t\t PASSWORD DATA NOT FOUND.EMPTY PASSWORD DATA FILE DELETED";
                ft.close();
                remove("password.dat");
                cout<<"\n\n\t\t\t\t\t\t";
                system("pause");
                system("cls");
                check_password(admin_call);
            }
        }

        else //PASSWORD FOUND
        {
            //XOR DECRYPTION
            for(i=0;password[i]!='\0';i++)
            {
              password[i]=(password[i])^key[i%(sizeof(key)/sizeof(char))];
            }

             i=1;
             if(!admin_call) //NOT CALLED BY ADMIN PANEL
              {
                  while(strcmp(ch_password,password)) //CHECKING IF PASSWORD ENTERED IS CORRECT
                {
                  if(i==1)
                    {
                        cout<<"\n\t\t\t\t\t\t  ENTER PASSWORD:";
                        ++i;
                    }
                  else
                    cout<<"\n\t\t\t\t\t\t  RE-ENTER PASSWORD:";
                  cin.sync();
                  cin.getline(ch_password,40);
                }
              }
             else
                {
                     system("color 4E");
                     while(strcmp(ch_password,password)) //CHECKING IF PASSWORD ENTERED IS CORRECT
                     {
                      if(i==1)
                        {
                            cout<<"\n\n";
                            cout<<"\t\t\t\t     -------------------------------------------- \n";
                            cout<<"\t\t\t\t     ############### ADMIN PANEL ################ \n";
                            cout<<"\t\t\t\t     -------------------------------------------- \n\n";
                            cout<<"\t\t\t\t              ENTER PASSWORD:";
                            ++i;
                        }
                      else
                            cout<<"\t\t\t\t              RE-ENTER PASSWORD:";
                      cin.sync();
                      cin.getline(ch_password,40);
                     }

                }
        }

    }
    f.close();
    ft.close();
    system("cls");
}
