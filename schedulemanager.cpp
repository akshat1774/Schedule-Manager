#include<iostream>
#include<iomanip>
#include<windows.h>
#include<fstream>
#include<ctime>
#include<stdio.h>
#include<dos.h>
#include<cstring>
#include<cstdlib>


using namespace std;
class schedule
{
    int date,month,year,day,date1,month1,year1;
    char s[200];



    public:
    void get_date();
    void calender();    //Displays calender and allows you to write edit or delete your schedule on a desired date
    void main_menu();    //to dispay the main menu
    void add();
    void write();        //to write schedule
    void display();    //to display schedule for a particular date
    void viewsc();    //to display entire schedule
    void edit();    //to edit the schedule
    int check(int,int,int);    //to check if schedule is already written or not
    void modify(int,int,int);    //to modify the schedule
    void delete_sch(int,int,int);    //to delete the schedule

};

void schedule::get_date()
{
    time_t now;

    struct tm nowlocal;

    now=time(NULL);
    nowlocal=*localtime(&now);
    date1=nowlocal.tm_mday;
    month1=nowlocal.tm_mon+1;
    year1=nowlocal.tm_year+1900;
    day=nowlocal.tm_wday;

}

void schedule::calender()        //Displays calender and allows you to write edit or delete your schedule on a desired date
{


    for(int x=month1;x<6+month1;x++)
    {


        if(x>12)
        {


            cout<<endl<<endl<<endl<<endl<<"\t\t\t\t     "<<year1+1<<endl<<endl;
            cout<<"\t\t\t\t       "<<x-12<<endl<<endl;
            cout<<"\t\t\t MON TUE WED THU FRI SAT SUN"<<endl;
        }
        else
        {
            cout<<endl<<endl<<"\t\t\t\t     "<<year1<<endl<<endl;
            cout<<"\t\t\t\t       "<<x<<endl<<endl;
            cout<<"\t\t\t MON TUE WED THU FRI SAT SUN"<<endl;

        }

        cout<<"\t\t\t";
        if(day>0 && day <7)
        {

            cout<<setw(4*day)<<date1;

        }

        else
            {

                cout<<setw(28)<<date1;

            }


        if(day==0)
            {
                cout<<endl<<endl;
                cout<<"\t\t\t";
                for(date1=date1;date1<31;)
                {
                    day++;
                    date1++;


                    cout<<setw(4)<<date1;


                    if(day>6)
                    {
                        day=0;

                        cout<<endl<<endl;
                        cout<<"\t\t\t";

                    }


                }
            }
        else
        {
            for(date1=date1;date1<31;)
            {
                day++;
            date1++;

            cout<<setw(4)<<date1;

            if(day>6)
                {
                    day=0;

                    cout<<endl<<endl;
                    cout<<"\t\t\t";
                }

            }


        }
        date1=0;
    }
}

void schedule::main_menu()
{
    system("COLOR F9");

    int choice;

    while(choice!=6)
    {

        cout<<endl<<endl;
        system("PAUSE");
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\t\t\t\t* MAIN MENU *";
        cout<<"\n\t\t\t\t*************";
        cout<<"\n\n\n\t\t\t1.View calender";
        cout<<"\n\t\t\t2.Write your schedule";
        cout<<"\n\t\t\t3.View schedule of a particular date";
        cout<<"\n\t\t\t4.View your schedule";
        cout<<"\n\t\t\t5.Edit schedule";
        cout<<"\n\t\t\t6.Exit";
        cout<<"\n\n\t\t\tEnter Your Choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                    get_date();
                    calender();
                    break;
            case 2: add();
                    break;
            case 3: display();
                    break;
            case 4: viewsc();
                    break;
            case 5: edit();
                    break;
            case 6: break;
            default:
                    {
                        cout<<"\n\n\t\t\tWrong choice!!!";
                        cout<<"\n\t\t\tPress any key to continue!!";

                    }
        }
    }



}

void schedule::add()
{
     system("cls");
    int d,m,y,flag=0;
    ofstream fout("myschedule.txt",ios::app);


    cout<<"\n Enter Schedule date";

    cout<<"\n\n Date: ";
    cin>>d;
    cout<<"\n\n Month: ";
    cin>>m;
    cout<<"\n\n Year: ";
    cin>>y;

    flag=check(d,m,y);

    if(flag)
        cout<<"\n You have already written your schedule";
    else
    {
        date=d;
        month=m;
        year=y;

        cout<<"You can start writing your schedule: \n";
        cout<< "(Note : Press ^Enter at the end of your schedule..)\n";

        for(int i=0;i<sizeof(s);i++)
        {
            cin.get(s[i]);
            if(i!=0 && s[i]==94)
            break;
        }

        fout.write((char*)this,sizeof(schedule)-200+sizeof(s));

    }



    fout.close();
}

void schedule::display()
{
     system("cls");
    ifstream fin("myschedule.txt",ios::in);
    int d,m,y,flag=0;
    cout<<"\n Enter date: ";
    cin>>d;
    cout<<"\n Enter month: ";
    cin>>m;
    cout<<"\n Enter year: ";
    cin>>y;

    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(schedule));
        if(date==d && month==m && year==y)
        {

            cout<<"\n\n Date: "<<date<<" "<<month<<" "<<year;
            cout<<"\n\n Schedule: \n";
            puts(s);

            flag=1;
            break;
        }
    }

    if(flag==0)
        cout<<"\n You have not written schedule for this date.";



    fin.close();
}

void schedule::viewsc()
{
     system("cls");

    ifstream fin("myschedule.txt");
    cout<<"\n\t\t\tYour schedule";


    while(fin.read((char*)this,sizeof(schedule)))
    {
        cout<<"\n\n Date : "<<date<<" "<<month<<" "<<year;
        cout<<"\n\nSchedule : \n"<<s;
    }





    fin.close();
}

void schedule::edit()
{
     system("cls");
    int choice,d,m,y;

    cout<<"\n EDIT MENU";
    cout<<"\n *********";
    cout<<"\n\n 1.Modify schedule";
    cout<<"\n 2.Delete schedule";

    cout<<"\n Enter your choice: ";
    cin>>choice;



    cout<<"\n Enter date: ";
    cin>>d;
    cout<<"\n Enter month: ";
    cin>>m;
    cout<<"\n Enter year: ";
    cin>>y;

    switch(choice)
    {
        case 1: modify(d,m,y);
                break;
        case 2: delete_sch(d,m,y);
                break;
        default: cout<<"\n Wrong choice selection from edit menu!!";
    }



}

int schedule::check(int d,int m,int y)
{
    int flag=0;
    ifstream fin("myschedule.txt");
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(schedule));
        if(date==d && month==m && year==y)
        {
            flag=1;
                break;
        }
    }

    fin.close();
    return(flag);
}

void schedule::modify(int d,int m,int y)
{
    system("cls");
    long pos,flag=0;
    fstream file("myschedule.txt",ios::in|ios::out|ios::app);

    while(!file.eof())
    {
        pos=file.tellg();
        file.read((char*)this,sizeof(schedule));
        if(date==d && month==m && year==y)
        {

            cout<<" You can start adding to your schedule: \n(Note : Press ^Enter at the end of your schedule..)\n";
            for(int i=0;i<sizeof(s);i++)
            {
                cin.get(s[i]);
                if(i!=0 && s[i]==94)
                break;
            }

            file.seekg(pos);
            file.write((char*)this,sizeof(schedule));
            cout<<"\n Your schedule has been modified !!";
            flag=1;
            break;
        }
    }

    if(flag==0)
        cout<<"\n You have not written any schedule on this date";

    file.close();
}

void schedule::delete_sch(int d,int m,int y)
{
    system("cls");
    int flag=0;
    char ch;
    ifstream fin("myschedule.txt",ios::in);
    ofstream fout("temp.txt",ios::out);

    while( fin.read((char*)this,sizeof(schedule)))
    {

        if(date==d && month==m && year==y)
        {
            cout<<"\n\n Date: "<<date<<" "<<month<<" "<<year;
            cout<<"\n\n Schedule: \n";
            puts(s);


            cout<<"\n\n Do you want to delete this schedule?(y/n): ";
            cin>>ch;

            if(ch=='n')
            fout.write((char*)this,sizeof(schedule));
            cout<<"\n Your schedule has been deleted !!";

            flag=1;
        }
        else
            fout.write((char*)this,sizeof(schedule));
    }

    fin.close();
    fout.close();

    if(flag==0)
        cout<<"\n You have not written any schedule on this date.";
    else
    {
        remove("myschedule.txt");
        rename("temp.txt","myschedule.txt");
    }
}

int main()
{
    schedule sch;

    cout<<"\n\t\t\t****************************";
    cout<<"\n\t\t\t*     SCHEDULE MANAGER     *";
    cout<<"\n\t\t\t****************************";


    sch.main_menu();
    return 0;
}
