#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>


using namespace std;

string selector(int n){
    if(n == 1)return "st";
    else if(n == 2)return "nd";
    else if(n == 3)return "rd";
    else return "th";
}

int main()
{
    char choice,another;
    FILE *fp, *ft;

    struct student
    {
        /** Roll no = 1209001 **/
        int roll_no;
        /** Name be like Ekramul Islam **/
        /** First name + Last Name     **/
        char first_name[50], last_name[50];
        /** Course name = ECE-1109  **/
        char course_name[100];
        /** Session = 2012-13 **/
        char session[20];
        /** Year = 1st + 1st semister **/
        int year, semister;
    };

    struct student s;
    char xfirst_name[50],xlast_name[50],xcourse_name[100];
    long int recsize;

    fp = fopen("database.txt","rb+");

    if(fp == NULL)
    {
        fp = fopen("database.txt","wb+");

        if(fp == NULL)
        {
            puts("Cannot open file.");
            return 0;
        }
    }

    recsize = sizeof(s);

    while(1)
    {
        system("cls");

        cout << "\n\t\t====== STUDENT INFORMATION SYSTEM ======\n\n\n\n" ;
        cout << "\n\t\t\t 1. Add    Records" ;
        cout << "\n\t\t\t 2. List   Records" ;
        cout << "\n\t\t\t 3. Modify Records" ;
        cout << "\n\t\t\t 4. Delete Records" ;
        cout << "\n\t\t\t 5. Exit   Program" ;
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice :=> ";


        fflush(stdin);

        choice = getche();
        switch(choice)
        {
        case '1' :
            fseek(fp,0,SEEK_END);
            another ='Y';
            while(another == 'Y' || another == 'y')
            {
                system("cls");
                cout << "Enter the Roll Number : ";
                cin >> s.roll_no;
                cout << "Enter the First Name  : ";
                cin >> s.first_name;
                cout << "Enter the Last Name   : ";
                cin >> s.last_name;
                cout << "Enter the Course      : ";
                cin >> s.course_name;
                cout << "Enter the session     : ";
                cin >> s.session;
                cout << "Enter the year        : ";
                cin >> s.year;
                cout << "Enter the semister    : ";
                cin >> s.semister;
                fwrite(&s,recsize,1,fp);
                cout << "\n Add Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }
            break;

        case '2':
            system("cls");
            rewind(fp);
            cout << "\n=== View the Records in the Database ===" ;
            cout << "\n" ;
            while(fread(&s,recsize,1,fp) == 1)
            {
                cout << "========================================" ;
                cout << "\n\n" ;
                cout << "Name        : " << s.first_name << setw(6) << s.last_name;cout << "\n\n" ;
                cout << "Roll        : " << s.roll_no     ; cout << "\n\n" ;
                cout << "Course Name : " << s.course_name ; cout << "\n\n" ;
                cout << "Session     : " << s.session     ; cout << "\n\n" ;
                cout << "Year        : " << s.year << selector(s.year)       ; cout << "\n\n" ;
                cout << "Semister    : " << s.semister <<  selector(s.semister)     ; cout << "\n\n" ;
                cout << "========================================" ;
            }
            cout << "\n\n";
            system("pause");
            break;

        case '3':
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the student : ";
                cin >> xlast_name;

                rewind(fp);
                while (fread(&s,recsize,1,fp) == 1)
                {
                    if (strcmp(s.last_name,xlast_name) == 0)
                    {
                        cout << "Enter new the Firt Name : ";
                        cin >> s.first_name;
                        cout << "Enter new the Last Name : ";
                        cin >> s.last_name;
                        cout << "Enter new the Course    : ";
                        cin >> s.course_name;
                        cout << "Enter new the Session   : ";
                        cin >> s.session;
                        cout << "Enter new the Year      : ";
                        cin >> s.year;
                        cout << "Enter new the Semister  : ";
                        cin >> s.semister;
                        fseek(fp, - recsize, SEEK_CUR);
                        fwrite(&s,recsize,1,fp);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }
            break;

        case '4':
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the student to delete : ";
                cin >> xlast_name;

                ft = fopen("temp.dat", "wb");

                rewind(fp);
                while (fread (&s, recsize,1,fp) == 1)

                    if (strcmp(s.last_name,xlast_name) != 0)
                    {
                        fwrite(&s,recsize,1,ft);
                    }
                fclose(fp);
                fclose(ft);
                remove("database.txt");
                rename("temp.dat","database.txt");

                fp=fopen("database.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }

            break;
        case '5':
            fclose(fp);
            cout << "\n\n";
            cout << "\t\t     THANK YOU FOR USING THIS SOFTWARE";
            cout << "\n\n";
            exit(0);
        }
    }
}
