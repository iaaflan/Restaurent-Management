///********************** RESTURANT MANAGEMENT SYSTEM **********************///
///*************************  C LANGUAGE PROJECT  **************************///

///********                      CREATED BY                     ************///
///******** NAME: IFAZ AHMED AFLAN & A.B.M FAHIM SHAHRIAR REED  ************///
///******** STUDENT ID(s): 154405 & 154410                      ************///
///******** INSTITUITION: ISLAMIC UNIVERSITY OF TECHNOLOGY      ************///
///_________________________________________________________________________///


///******** PROJECT START TIME : 2 JULY,2016                    ************///
///******** PROJECT END TIME   : 3 OCTOBER,2016                 ************///
///******** FINALIZING DATE    : 8 NOVEMBER,2016                ************///
///_________________________________________________________________________///


///********                     HEADER FILES                    ************///

#include<windows.h>
#include<stdio.h>
#include<conio.h>                   /// TO USE delay(),getch(),gotoxy()
#include<stdlib.h>
#include<string.h>                  /// TO USE strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   /// TO USE toupper(), tolower(),etc
#include<dos.h>                     /// TO _dos_getdate
#include<time.h>                    /// USED FOR TIME FUNCTIONs


///********                  DEFINITION SECTIONS                 ************///

#define RETURNTIME 15


///********                  FUNCTION PROTOTYPES                 ************///

void Return_Mainmenu(void);
void Return_Customermenu(void);
void Admin_Menu(void);
void mainmenu001(void);
void cusmenu(void);
void addfoods(void);
void deletefoods(void);
void orderfood(void);
void viewfoods(void);
void cusviewfoods(void);
void cusfeedback(void);
void adfeedback(void);
void closeapplication(void);
int getdata();
int checkid(int);
int t(void);
void Password();
void change_password(void);
void loaderanim();

///********                  USING COORDINATION                  ************///
COORD coord = {0, 0}; /// SET COORDINATE TO 0,0
COORD max_res,cursor_size;
void gotoxy (int x, int y)
{
    coord.X = x; /// GETTING THE VALUE OF X FROM OTHER FUNCTIONS
    coord.Y = y; /// GETTING THE VALUE OF Y FROM OTHER FUNCTIONS
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

///********                  GLOBAL FILES                       ************///
FILE *fp,*ft,*fs,*fc,*fa,*fb;

///********                  GLOBAL VARIABLES                   ************///

int s;
char findbook;
char password[10]= {"aflanreed"};
float prc[30];
float totalbill=0;
struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;

///********                  MAIN FUNCTION                      ************///

int main()

{
    system("COLOR 3F");
    mainmenu001();
    getch();
    return 0;

}

///********                  2-07-2016                           ************///
///********           CODED BY FAHIM SHAHRIAR REED               ************///
///********           MODIFIED BY IFAZ AHMED AFLAN               ************///
///********                  ADMIN MENU                          ************///


void Admin_Menu()
{

    loaderanim(); /// SHOWING LOADING SCREEN
    system("cls");
    /// SHOWING ADMIN OPTIONS
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADMINISTRATOR MENU");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Add Foods   ");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Delete Foods");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. View Menu");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 4. Go to main menu");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 5. View feedbacks");
    gotoxy(20,15);
    printf("\xDB\xDB\xDB\xDB\xB2 6. Change Password");
    gotoxy(20,17);
    printf("\xDB\xDB\xDB\xDB\xB2 7. Close Application");
    gotoxy(20,19);
    printf("------------------------------------------");
    gotoxy(20,23);
    t();
    gotoxy(20,25);
    printf("Enter your choice:");
    switch(getch())
    {
    case '1':
        addfoods(); /// ADMIN CAN ADD FOODS
        break;
    case '2':
        deletefoods(); /// ADMIN CAN DELETE FOOD
        break;
    case '3':
        viewfoods(); /// ADMIN CAN VIEW FOOD
        break;
    case '4':
    {
        mainmenu001(); /// RETURNS TO MAIN MENU
        break;
    }
    case '5':
    {
        adfeedback(); /// SEE FEEDBACK
        break;
    }
    case '6':
    {
        change_password(); /// CHANGE PASSWORD
        break;
    }
    case '7':
    {
        system("cls");
        gotoxy(16,3);
        printf("Thank you for using the Program");
        gotoxy(10,7);
        printf("Exiting in 3 second...........");
        //flushall();
        delay(3000); /// DELAY BEFORE CLOSING APPLICATION
        exit(0); /// EXITING THE CONSOLE
    }
    default:
    {
        gotoxy(20,27);
        printf("\a\xDB\xDB\xDB\xDB\xB2 WRONG ENTRY! PLEASE RE-ENTER THE CORRECT OPTION \xB2\xDB\xDB\xDB\xDB"); /// \a TO ALERT (MAKE A SOUND)
        gotoxy(20,28);
        getch();
        if(kbhit())
            system("cls");
        Admin_Menu();
    }

    }
}

///********                  2-07-2016                           ************///
///********    CODED BY IFAZ AHMED AFLAN & FAHIM SHAHRIAR REED   ************///
///********           MODIFIED BY FAHIM SHAHRIAR REED            ************///
///********                ADMIN FUNCTIONS                       ************///

void addfoods(void)    /// FUNCTION THAT ADD FOODS FROM FILE
{
    loaderanim();
    system("cls");
    int i;
    gotoxy(20,5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADD FOOD");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    system("cls");
    fp=fopen("menu.txt","r+");
    if(getdata()==1)
    {
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        gotoxy(21,14);
        printf("The record is stored successfully");
        gotoxy(21,15);
        printf("More records to store ?(Y/N):");
        if(getch()=='n')
            Admin_Menu();
        else
            system("cls");
        addfoods();
    }
}

void deletefoods()    /// FUNCTION THAT DELETES FOODS FROM FILE
{
    loaderanim();
    system("cls");
    int d;
    char another='y';
    while(another=='y')
    {
        system("cls");
        gotoxy(10,5);
        printf("Enter the Food ID to  delete:");
        scanf("%d",&d);
        fp=fopen("menu.txt","a+");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.id==d)
            {

                gotoxy(10,7);
                printf("The food is available");
                gotoxy(10,8);
                printf("Food name is %s",a.name);
                findbook='t';
            }
        }
        if(findbook!='t')
        {
            gotoxy(10,10);
            printf("No record is found modify the search");
            if(getch())
                Admin_Menu();
        }
        if(findbook=='t' )
        {
            gotoxy(10,9);
            printf("Do you want to delete it?(Y/N):");
            if(getch()=='y')
            {
                ft=fopen("temp.txt","a+");
                rewind(fp);
                while(fread(&a,sizeof(a),1,fp)==1)
                {
                    if(a.id!=d)
                    {
                        fseek(ft,0,SEEK_CUR);
                        fwrite(&a,sizeof(a),1,ft);
                    }
                }
                fclose(ft);
                fclose(fp);
                remove("menu.txt");
                rename("temp.txt","menu.txt");
                fp=fopen("menu.txt","a+");
                if(findbook=='t')
                {
                    gotoxy(10,10);
                    printf("The food is successfully deleted");
                    gotoxy(10,11);
                    printf("Delete another food?(Y/N)");
                }
            }
            else
                Admin_Menu();
            fflush(stdin);
            another=getch();
        }
    }
    gotoxy(10,15);
    Admin_Menu();
}
void viewfoods(void)  /// show the list of foods present in the menu, used by customer too
{
    loaderanim();
    int i=0,j;
    system("cls");
    gotoxy(2,1);
    printf("\t FOOD LIST ");
    gotoxy(2,2);
    printf(" ID    FOOD NAME     PRICE ");
    j=4;
    fp=fopen("menu.txt","r+");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        gotoxy(3,j);
        printf("%d",a.id);
        gotoxy(9,j);
        printf("%s",a.name);
        gotoxy(23,j);
        printf("%.2f",a.Price);
        printf("\n\n");
        j++;

    }
    gotoxy(3,25);
    fclose(fp);
    gotoxy(35,25);
    Return_Mainmenu();
}
void Return_Mainmenu(void)
{
    {
        printf(" Press ENTER to return to main menu");
    }
a:
    if(getch()==13) /// 13 is ASCII VALUE OF ENTER
        Admin_Menu();
    else
        goto a;
}
int getdata()
{
    int t;
    gotoxy(20,3);
    printf("Enter the Information Below");
    gotoxy(20,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xB2");
    gotoxy(46,5);
    printf("\xB2");
    gotoxy(20,6);
    printf("\xB2");
    gotoxy(46,6);
    printf("\xB2");
    gotoxy(20,7);
    printf("\xB2");
    gotoxy(46,7);
    printf("\xB2");
    gotoxy(20,8);
    printf("\xB2");
    gotoxy(46,8);
    printf("\xB2");
    gotoxy(20,9);
    printf("\xB2");
    gotoxy(46,9);
    printf("\xB2");
    gotoxy(20,10);
    printf("\xB2");
    gotoxy(46,10);
    printf("\xB2");
    gotoxy(20,11);
    printf("\xB2");
    gotoxy(46,11);
    printf("\xB2");
    gotoxy(20,12);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(21,6);
    printf(" FOOD ID:");
    gotoxy(30,6);
    scanf("%d",&t);
    if(checkid(t) == 0)
    {
        gotoxy(21,13);
        printf("\aThe Food id already exists\a");
        getch();
        Admin_Menu();
        return 0;
    }
    a.id=t;
    gotoxy(21,7);
    printf(" Food Name:");
    gotoxy(33,7);
    scanf("%s",a.name);
    gotoxy(21,8);
    printf(" Price:");
    gotoxy(28,8);
    scanf("%f",&a.Price);
    return 1;
}
int t(void) /// SHOWS DATE AND TIME
{

    time_t t;
    time(&t);
    printf("Date and time: %s\n",ctime(&t));

    return 0 ;
}


void loaderanim()
{
    int loader;
    system("cls");
    gotoxy(20,10);
    printf("LOADING......");
    printf("\n\n");
    gotoxy(22,11);
    for(loader=1; loader<20; loader++)
    {
        delay(100);
        printf("%c",219);
    }
}
int checkid(int t)  /// SEARCHES FOR FOOD
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
        if(a.id==t)
            return 0;  /// RETURNS 0 IF FOOD EXISTS
    return 1; /// RETURN 1 IF NOT
}
void mainmenu001(void)
{

    system("cls");
    int i;
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. CUSTOMER   ");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 2. ADMINISTRATOR");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 3. CLOSE APPLICATION");
    gotoxy(20,15);
    printf("------------------------------------------");
    gotoxy(20,17);
    t();
    gotoxy(20,18);
    printf("Enter your choice: ");
    switch(getch())
    {
    case '1':
        cusmenu();
        break;
    case '2':
        Password();
        Admin_Menu();
        break;
    case '3':
    {
        system("cls");
        gotoxy(16,3);
        printf("Thanks for using the Program.");
        gotoxy(10,7);
        printf("Exiting in 3 second.........");
        //flushall();
        delay(3000);
        exit(0);
    }
    default:
    {
        gotoxy(20,20);
        printf("\a\xDB\xDB\xDB\xDB\xB2 WRONG ENTRY! PLEASE RE-ENTER THE CORRECT OPTION \xB2\xDB\xDB\xDB\xDB");
        if(getch())
            mainmenu001();
    }
    }
}
void cusmenu(void)
{

    loaderanim();
    system("cls");
    int i;
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 CUSTOMER MENU");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. ORDER FOOD  ");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. FEEDBACK ");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. RETURN TO MENU");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 4. CLOSE APPLICAION");
    gotoxy(20,15);
    printf("------------------------------------------");
    gotoxy(20,20);
    t();
    gotoxy(20,22);
    printf("Enter your choice:");
    switch(getch())
    {
    case '1':
        orderfood();
        break;
    case '2':
        cusfeedback();
        break;
    case '3':
        mainmenu001();
        break;
    case '4':
    {
        system("cls");
        gotoxy(16,3);
        printf("Thanks for using the Program..");
        gotoxy(10,7);
        printf("Exiting in 5 second...........>");
        //flushall();
        delay(5000);
        exit(0);
    }
    default:
    {
        gotoxy(20,22);
        printf("\a\xDB\xDB\xDB\xDB\xB2 Wrong Entry!!Please re-enter correct option \xB2\xDB\xDB\xDB\xDB");
        if(getch())
            cusmenu();
    }

    }
}
void cusviewfoods(void)
{
    loaderanim();
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("\t FOOD LIST");
    gotoxy(2,2);
    printf(" ID    FOOD NAME     PRICE ");
    j=4;
    fp=fopen("menu.txt","r+");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        gotoxy(3,j);
        printf("%d",a.id);
        gotoxy(9,j);
        printf("%s",a.name);
        gotoxy(23,j);
        printf("%.2f",a.Price);
        printf("\n\n");
        j++;
    }
    gotoxy(3,25);
    fclose(fp);
}
void cusreturnfunc(void)
{
    {
        printf(" Press ENTER to return to customer menu");
    }
a:
    if(getch()==13)
        cusmenu();
    else
        goto a;
}
void orderfood(void)
{
    gotoxy(20,9);
    int fid,amount,num,i=0;

    cusviewfoods();
    printf("Enter the food id you want to buy : \n\n\t\t");
    scanf("%d",&fid);
    printf("\n\n Enter quantity: \n\n\t\t");
    scanf("%d",&amount);

    fp=fopen("menu.txt","a+");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        prc[a.id]=a.Price;
    }
    fclose(fp);


    totalbill=totalbill+(prc[fid]*amount);
    printf("\n\nDo you want to buy another food item?(Y/N):\n\n");
    if(getch()=='y')
    {
        orderfood();
    }
    else
    {
        loaderanim();
        system("cls");
        printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        printf(" \n\n \xB2\xB2\xB2 your total bill is : %f",totalbill);
        printf(" \n\n \xB2\xB2\xB2 Thank you, visit again\n\n");
        printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    }

}

///********                  7-07-2016                           ************///
///********             CODED BY IFAZ AHMED AFLAN                ************///
///********                   PASSWORD                           ************///

void Password(void)
{

    system("cls");
    char d[25]="Password Protected";
    char pass[10],given[10];
    int i=0,j;
    gotoxy(10,4);
    for(j=0; j<20; j++)
    {
        delay(50);
        printf("\xDB");
    }
    printf(" ");
    for(j=0; j<20; j++)
    {
        delay(50);
        printf("%c",d[j]);
    }
    for(j=0; j<20; j++)
    {
        delay(50);
        printf("\xDB");
    }
    gotoxy(10,10);
    gotoxy(15,7);
    printf("\xDB\xDB\xDB\xDB\xDB Enter Password: ");
    gotoxy(15,9);
    printf("\xDB\xDB\xDB\xDB\xB2 ");
    scanf("%s",given);
    fb=fopen("password.txt","r");
    fscanf(fb,"%s",&pass);
    fclose(fb);




    if(strcmp(pass,given)==0)
    {

        gotoxy(15,9);
        printf("\xDB\xDB PASSWORD MATCHES");
        gotoxy(15,11);
        printf("\xDB\xDB PRESS ANY KEY TO CONTINUE.....");
        getch();
        Admin_Menu();
    }
    else
    {
        gotoxy(15,13);
        printf("\a\xDB\xDB INCORRECT PASSWORD. PRESS ANY KEY...");
        getch();
        Password();
    }
}
void cusfeedback(void)
{
    loaderanim();
    system("cls");
    printf("Your Feedback(MAX 1000 LETTER): \n");
    char str[1000];
    gets(str);
    FILE *fc;
    fc = fopen("cusfeed.txt","a");
    fprintf(fc,"%s\n\n",str);
    fclose(fc);
    fprintf(fc,"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2",str);
    printf("Thank you for your feedback");
    cusmenu();
}
void adfeedback(void)
{
    loaderanim();
    system("cls");
    char str[100],ch;
    FILE *fc;
    fc = fopen("cusfeed.txt","r");

    while(!feof(fc))
    {
        fgets(str,80,fc);
        printf("%s\n",str);
    }
    fclose(fc);
    printf("\n\n PRESS ANY KEY TO RETURN.");
    getch();
    Admin_Menu();

}
void change_password(void)
{
    loaderanim();
    system("cls");
    FILE *fb1;
    fb1=fopen("password.txt","r");
    char old_pass[100];
    char ch;
    int j=0;
    char str[100],new_pass1[100],new_pass2[100];
    fscanf(fb1,"%s",&old_pass);
    fclose(fb1);

    printf("Enter The Current Password\n");
    scanf("%s",&str);

    if(strcmp(str,old_pass)!=0)
    {
        printf("%s",old_pass);
        printf("WRONG PASSWORD\n");
        delay(50);
        Admin_Menu();
    }
    printf("Enter a New Password\n");
    scanf("%s",&new_pass1);
    printf("Re-enter The New Password\n");
    scanf("%s",&new_pass2);
    if(strcmp(new_pass1,new_pass2)!=0)
    {
        printf("Passwords don't match\n");
        delay(3000);
        Admin_Menu();
    }
    else
    {
        fb1=fopen("password.txt","w");
        fprintf(fb1,"%s",new_pass1);
        fclose(fb1);
        printf("password changed successfully !");
        delay(3000);
        Admin_Menu();
    }

}
