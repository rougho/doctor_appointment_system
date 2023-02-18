/*Rouhollah Ghobadinezhad 3107467
 *Walid Boucenna 3107821
 *Hana Salah 3107842
 *Doctor Appointment System
 *Advanced Programing
 *Prof. Amit Sen
 *09/02/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "signin.h"

#include <windows.h>
#define FILENAME "main.txt"
#define DPFILENAME "dp.txt"
#define MODE "a+"
#define YELLOW 14
#define GRAY 40
#define PURPLE 45
#define GREEN 50
#define RED 60
#define BLUE 65
#define DARKYELLOW 70
#define LIGHTBLUE 75
#define BLACK 80
#define NORMAL 7
#define STRSIZE 100

char line[1024];
struct dp_id{
    long int patient_id;
    long int doctor_id;
};
struct tracker{
    long int IDtracker;
    char USERtracker[STRSIZE];
};

typedef struct hour{
    int sec;
    int min;
    int hour;
}Hour;
typedef struct date{
    int day;
    int month;
    int year;
    Hour hour;
}Date;

typedef struct p_appointment{
    char details[100];
}P_app;

typedef struct account{
    char type;
    char username[50];
    char password[50];
}Account;

typedef struct address{
    char city[20];
    char street[20];
    int no;
    long int plz;

}address;

typedef struct cont{
    char email[50];
    char phone[50];
}Contact;

typedef struct info{
     char gender;
     char fname[20];
     char lname[20];
     int age;
 }Info;

struct data{
    char filename[50];
    Account acc;
    Info info;
    address addr;
    Contact contact;
    P_app pa;
    Date create_t;
    Date res_t;
    Date doc_available;
    Info Doctors_name;
    long int ID;
    long int booking_doc_id;

};

/*------------------------------------- Chane Text Color Function ---------------------------------------*/
//Source: https://www.codeincodeblock.com/2011/03/changing-text-color-in-codeblock.html
void SetColor(int ForgC)
{
    WORD wColor;
    //This handle is needed to get the current background attribute

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //csbi is used for wAttributes word

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //To mask out all but the background attribute, and to add the color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}
/*-------------------------------------------------------------------------------------------------------*/
//==================================== print struct =============================================//
void printStr2D(struct data *s,int rec,int color, int i,char type){
    if (s[i].acc.type == type){
        printf("[%d]\tID: %li\n\tRegistered at: %d.%d.%d\n\tAccount type: %c\n\tUsername: %s\n\tPassword: %s\n\tFirst Name: %s\n\tLast Name: %s\n\tAge: %d\n\tGender: %c\n\tAddress: %s.%d, %li %s\n\tPhone No.: %s\n\tEmail: %s",
               i,s[i].ID,s[i].create_t.day,s[i].create_t.month,s[i].create_t.year,s[i].acc.type,s[i].acc.username,s[i].acc.password,s[i].info.fname,s[i].info.lname,s[i].info.age,
               s[i].info.gender,s[i].addr.street,s[i].addr.no,s[i].addr.plz,s[i].addr.city,s[i].contact.phone,s[i].contact.email);
        SetColor(color);
        printf("\n--------------------------------------------------------------------\n");
        SetColor(NORMAL);
    }else{
        SetColor(RED);
        printf("Invalid input");
        SetColor(NORMAL);
    }

}
//========================== Read File and assign to struct ===========================//
// Sample:
//int i=0;
//struct data a[100];
//read_file(a,"main.txt","r",&i);
//printf("%d",i);
//printf("\n%s\n",a[2].acc.username);

void read_file(struct data *v,char file[], char mode[],int *record) {
    FILE *fptr;
    fptr = fopen(file, mode);
    if (fptr == NULL) {
        printf("such file or directory not existed!!");
    }
    int read = 0;
    int records = 0;
    do
    {
        read = fscanf(fptr,
                      "%li;%d;%d;%d;%c;%[^;];%[^;];%[^;];%[^;];%d;%c;%[^;];%d;%li;%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%d;%li\n",
                      &v[records].ID,
                      &v[records].create_t.day,
                      &v[records].create_t.month,
                      &v[records].create_t.year,
                      &v[records].acc.type,
                      v[records].acc.username,
                      v[records].acc.password,
                      v[records].info.fname,
                      v[records].info.lname,
                      &v[records].info.age,
                      &v[records].info.gender,
                      v[records].addr.street,
                      &v[records].addr.no,
                      &v[records].addr.plz,
                      v[records].addr.city,
                      v[records].contact.phone,
                      v[records].contact.email,
                      v[records].pa.details,
                      &v[records].res_t.day,
                      &v[records].res_t.month,
                      &v[records].res_t.year,
                      &v[records].res_t.hour.hour,
                      &v[records].res_t.hour.min,
                      &v[records].booking_doc_id
        );
        if (read == 24){
            records++;
        }
        if (read != 24 && !feof(fptr))
        {
            printf("File format incorrect.\n");
            exit(1);
        }
        if (ferror(fptr))
        {
            printf("Error reading file.\n");
            exit(1);
        }
    } while (!feof(fptr));
    *record = records;
    fclose(fptr);
}
void read_dp(struct dp_id *v,char file[], char mode[],int *record){
    FILE *fptr;
    fptr = fopen(file, mode);
    if (fptr == NULL) {
        printf("such file or directory not existed!!");
    }
    int read = 0;
    int records = 0;
    do
    {
        read = fscanf(fptr,
                      "%li;%li\n",
                      &v[records].patient_id,
                      &v[records].doctor_id
        );
        if (read == 2){
            records++;
        }
        if (read != 2 && !feof(fptr))
        {
            printf("File format incorrect.\n");
            exit(1);
        }
        if (ferror(fptr))
        {
            printf("Error reading file.\n");
            exit(1);
        }
    } while (!feof(fptr));
    *record = records;
    fclose(fptr);
}
void write_file(struct data *str_writer,int records ,char F[30],char M[10]){
    FILE *fptr;
    fptr = (fopen(F,M));
    if(fptr == NULL){
        printf("file error!!!");
        exit(1);
    }
    for (int i = 0; i < records; ++i) {
        fprintf(fptr,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",str_writer[i].ID,str_writer[i].create_t.day,str_writer[i].create_t.month,str_writer[i].create_t.year,str_writer[i].acc.type,
                str_writer[i].acc.username,str_writer[i].acc.password,str_writer[i].info.fname,str_writer[i].info.lname,str_writer[i].info.age,str_writer[i].info.gender,str_writer[i].addr.street,
                str_writer[i].addr.no,str_writer[i].addr.plz,str_writer[i].addr.city,str_writer[i].contact.phone,str_writer[i].contact.email,str_writer[i].pa.details,str_writer[i].res_t.day,
                str_writer[i].res_t.month,str_writer[i].res_t.year,str_writer[i].res_t.hour.hour,str_writer[i].res_t.hour.min,str_writer[i].booking_doc_id
        );
    }
    fclose(fptr);
}
//====================================================================================//

void admin();
void VDD();
void Patient_reg();
void Doctors_reg();
void signIn();
void signUpMenu();
void view_doc_profile(struct data d[],int records,int j,char fname[],char lname[],long int ID);
void doc_menu(struct data d[],int records,int j,char fname[],char lname[],long int ID);
void view_appointments(struct data d[],int records,long int ID);
void change_appointment(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]);
void cancel_appointment(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]);
void update_patient_profile(struct data d[],int records,int j,char fname[],char lname[],char user_filename[],char main_file[]);
void landingPage();
void get_appointment(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]);
void patients_menu(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]);
void SetColor(int ForgC);
void admin_view_all_doc(char type);

int main() {
    landingPage();
    return 0;
}

/*------------------------------------Read File----------------------------------------*/
// Try to write struct function to read a file and save it into struct and return the struct
/*------------------------------------Read File----------------------------------------
void read_file_to_struct(struct data *d_ptr,int *record){
    FILE *fptr;
    fptr = fopen(FILENAME, "r");
    if (fptr == NULL) {
        SetColor(12);
        printf("such file or directory not existed!!");
    } else {
        SetColor(2);
        printf("Log In:\n");
        SetColor(255);
    }


    int read = 0;
    do
    {
        read = fscanf(fptr,
                      "%d;%d;%d;%c;%[^;];%[^;];%[^;];%[^;];%d;%c;%[^;];%d;%li;%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%d\n",
                      &(d_ptr+*record)->create_t.day,
                      &(d_ptr+*record)->create_t.month,
                      &(d_ptr+*record)->create_t.year,
                      &(d_ptr+*record)->acc.type,
                      (d_ptr+*record)->acc.username,
                      (d_ptr+*record)->acc.password,
                      (d_ptr+*record)->info.fname,
                      (d_ptr+*record)->info.lname,
                      &(d_ptr+*record)->info.age,
                      &(d_ptr+*record)->info.gender,
                      (d_ptr+*record)->addr.street,
                      &(d_ptr+*record)->addr.no,
                      &(d_ptr+*record)->addr.plz,
                      (d_ptr+*record)->addr.city,
                      (d_ptr+*record)->contact.phone,
                      (d_ptr+*record)->contact.email,
                      (d_ptr+*record)->pa.details,
                      &(d_ptr+*record)->res_t.day,
                      &(d_ptr+*record)->res_t.month,
                      &(d_ptr+*record)->res_t.year,
                      &(d_ptr+*record)->res_t.hour.hour,
                      &(d_ptr+*record)->res_t.hour.min

        );

        if (read == 22){
            record++;
        }

        if (read != 22 && !feof(fptr))
        {
            printf("File format incorrect.\n");
            exit(1);

        }

        if (ferror(fptr))
        {
            printf("Error reading file.\n");
            exit(1);
        }

    } while (!feof(fptr));

    fclose(fptr);
}
------------------------------------------------------------------------*/
// End of Try to write struct function to read a file and save it into struct and return the struct
/*------------------------------------------------------------------------*/


//Not Completed
void admin(){
    int Doc_rec = 0;
    int Pat_rec = 0;
    int main_rec = 0;
    struct data Docters[STRSIZE];
    struct data Patients[STRSIZE];
    struct data main_struct[STRSIZE];
    read_file(main_struct,FILENAME,"r",&main_rec);

    printf("\n---------------------------");
    SetColor(RED);
    printf(" Administrator ");
    SetColor(NORMAL);
    printf("--------------------------\n");
    printf("-------------------------- 1.View Doctor Data ----------------------\n");
    printf("-------------------------- 2.View Patients Data --------------------\n");
    printf("-------------------------- 3.Search by name ------------------------\n");
    printf("-------------------------- 4.Exit ----------------------------------\n");
    printf("--------------------------------------------------------------------\n");
    int opt = 0;
    printf("Option:");
    scanf("%d",&opt);
    switch (opt) {
        case 1:
            VDD();
            break;
        case 2:
            admin_view_all_doc('P');
            break;
        case 3:
            printf("3");
        case 4:
            printf("Bye bye!\n");
            exit(1);
        default:
            printf("Invalid input!!!\n");
            exit(1);
    }


    exit(1);
}
//---------------
void admin_view_all_doc(char type){
    struct data Docters[STRSIZE];
    struct data P_struct[STRSIZE];
    int main_rec = 0;
    int Doc_rec = 0;
    read_file(Docters,FILENAME,"r",&Doc_rec);

    int c1 = 0;
    int id = 0;
    char fname[50];
    char lname[50];

    if (type == 'D'){
        SetColor(DARKYELLOW);
        printf("\n-------------------------- Doctors ---------------------------------\n");
        SetColor(NORMAL);
    }else if (type == 'P'){
        SetColor(DARKYELLOW);
        printf("\n-------------------------- Patients ---------------------------------\n");
        SetColor(NORMAL);
    }

    for (int i = 0; i < Doc_rec; ++i) {
        if (Docters[i].acc.type == type) {
            printStr2D(Docters, Doc_rec, DARKYELLOW,i,type);
        }
    }
    fflush(stdin);
        printf("1.Select by Number\t2.Select by Name\n");
        scanf("%d",&c1);
        if (c1 == 1){
            printf("Enter Number:");
            scanf("%d",&id);
            if (Docters[id].acc.type == type){
                printStr2D(Docters, Doc_rec, DARKYELLOW,id,type);
            }else{
                SetColor(RED);
                printf("\nInvalid input\n");
                SetColor(NORMAL);
                admin();
            }


        }else if (c1 == 2){
            fflush(stdin);
            printf("Enter First Name:");
            gets(fname);
            fflush(stdin);
            printf("Enter Last Name:");
            gets(lname);
            fflush(stdin);
            SetColor(DARKYELLOW);
            printf("\n--------------------------------------------------------------------\n");
            SetColor(NORMAL);
            for (int i = 0; i < Doc_rec; ++i) {
                if (strcmp(Docters[i].info.fname,fname) == 0 && strcmp(Docters[i].info.lname,lname) == 0 && Docters[i].acc.type == type){
                    printStr2D(Docters, Doc_rec, DARKYELLOW,i,type);
                    id = i;
                }
            }
        }
    char temp_user[50];
    strcpy(temp_user,Docters[id].acc.username);
    printf("\n\n%s\n\n",temp_user);
    int c2 = 0;
    int c3 = 0;
    printf("[1].Edit\t[2].");
    SetColor(RED);
    printf("Delete\n");
    SetColor(NORMAL);
    fflush(stdin);
    scanf("%d",&c2);
    if (c2 == 1){
        printf("----------------------------------------------------------------\n");
        printf("What do you like to Change?\n");
        printf("[1].ID\n[2].Username\n[3].Password\n[4].Name\n[5].Age\n[6].Address\n[7].Phone\n[8].Email\n");
        printf("----------------------------------------------------------------\n");
        printf("Option:");
        scanf("%d",&c3);
        fflush(stdin);
        if (c3 == 1){
            long int temp;
            printf("Enter new ID:");
            scanf("%li",&temp);
            for (int i = 0; i < Doc_rec; ++i) {
                if (Docters[i].ID == temp){
                    SetColor(RED);
                    printf("ID is token!\n");
                    SetColor(NORMAL);
                }
            }
                Docters[id].ID = temp;
                printf("ID updated!");
        }else if (c3 == 2){
            char Utemp[50];
                printf("Enter new username:");
                gets(Utemp);
                for (int i = 0; i < Doc_rec; ++i) {
                    if (strcmp(Docters[i].acc.username,Utemp) == 0){
                        SetColor(RED);
                        printf("Username is token!\n");
                        SetColor(NORMAL);
                        admin();
                    }
                }
            strcpy(Docters[id].acc.username,Utemp);
            SetColor(GREEN);
            printf("Username Updated!!\n\n");
            SetColor(NORMAL);
        }else if (c3 == 3){
            fflush(stdin);
            char Ptemp[50];
            printf("Enter new Password:");
            gets(Ptemp);
            strcpy(Docters[id].acc.password,Ptemp);
            SetColor(GREEN);
            printf("Password Updated!!\n\n");
            SetColor(NORMAL);
        }else if (c3 == 4){
            fflush(stdin);
            printf("Enter new First Name:");
            gets(Docters[id].info.fname);
            fflush(stdin);
            printf("Enter new Last Name:");
            gets(Docters[id].info.lname);
            SetColor(GREEN);
            printf("Name Updated!!\n\n");
            SetColor(NORMAL);
        }else if (c3 == 5){
            printf("Enter Age:");
            scanf("%d",&Docters[id].info.age);
            SetColor(GREEN);
            printf("Age Updated!!\n\n");
            SetColor(NORMAL);
        }else if (c3 == 6){
            fflush(stdin);
            printf("Address:\n");
            printf("\tStreet:");
            gets(Docters[id].addr.street);
            fflush(stdin);
            printf("\tHouse No.:");
            scanf("%d",&Docters[id].addr.no);
            fflush(stdin);
            printf("Post Code:");
            scanf("%li",&Docters[id].addr.plz);
            fflush(stdin);
            printf("City:");
            gets(Docters[id].addr.city);
            fflush(stdin);
            SetColor(GREEN);
            printf("Address Updated!!\n\n");
            SetColor(NORMAL);
        }else if (c3 == 7){
            printf("Phone No.:");
            gets(Docters[id].contact.phone);
            fflush(stdin);
            SetColor(GREEN);
            printf("Phone Number Updated!!\n\n");
            SetColor(NORMAL);
        }else if (c3 == 8){
            printf("Email Address:");
            gets(Docters[id].contact.email);
            fflush(stdin);
            SetColor(GREEN);
            printf("Email address Updated!!\n\n");
            SetColor(NORMAL);
        }
    }else if (c2 == 2){
        /*
        for (int i = id-1; i < Doc_rec-1; ++i) {
            Docters[id] = Docters[id+1];
        }
         */
        SetColor(RED);
        printf("Profile Deleted!!!\n");
        SetColor(NORMAL);
    }

    if (Docters[id].acc.type == 'P'){
        printf("\n\n%s\n\n",temp_user);

        char ftype[] = "P_";
        char user_filename[50];
        char username[50];
        char user_filename2[50];
        char username2[50];
        char format[] = ".txt";
        int P_rec =0;
        strcpy(username,temp_user);
        strcat(username,format);
        strcat(ftype,username);
        strcat(user_filename,ftype);
        read_file(P_struct,user_filename,"r",&P_rec);
        remove(user_filename);
        for (int i = 0; i < P_rec; ++i) {
            P_struct[i].ID = Docters[id].ID;
            strcpy(P_struct[i].acc.username,Docters[id].acc.username);
            strcpy(P_struct[i].acc.password,Docters[id].acc.password);
            strcpy(P_struct[i].info.fname,Docters[id].info.fname);
            strcpy(P_struct[i].info.lname,Docters[id].info.lname);
            P_struct[i].info.age = Docters[id].info.age;
            strcpy(P_struct[i].addr.street,Docters[id].addr.street);
            P_struct[i].addr.no = Docters[id].addr.no;
            P_struct[i].addr.plz = Docters[id].addr.plz;
            strcpy(P_struct[i].addr.city,Docters[id].addr.city);
            strcpy(P_struct[i].contact.phone,Docters[id].contact.phone);
            strcpy(P_struct[i].contact.email,Docters[id].contact.email);
        }

        strcpy(username2,Docters[id].acc.username);
        strcat(username2,format);
        strcat(ftype,username2);
        strcat(user_filename2,ftype);
        write_file(P_struct,P_rec,ftype,"w");
        printf("\n%d - %s\n",P_rec,P_struct[0].info.fname);
    }
        write_file(Docters,Doc_rec,FILENAME,"w");
        admin();

}

void VDD(){


    printf("-------------------------- View Doctors Data -----------------------\n");
    printf("-------------------------- 1.View All ------------------------------\n");
    printf("-------------------------- 2.Search by name ------------------------\n");
    printf("-------------------------- 3.Exit ----------------------------------\n");
    printf("--------------------------------------------------------------------\n");
    int opt = 0;

    printf("Option:");
    scanf("%d",&opt);

    switch (opt) {
        case 1:
            admin_view_all_doc('D');
            break;

    }











}

// Patient Registration Menu
void Patient_reg(){
    srand(time(0));
    struct data *reg_p,reg_patients;
    reg_p = &reg_patients;
    struct data d[STRSIZE];
    int record = 0;
    read_file(d,FILENAME,"r",&record);
    reg_p->acc.type = 'P';
    char user[50];
    //
    fflush(stdin);
    char buff[100];
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    strftime (buff, 100, "%d-%m-%Y %H:%M:%S", (const struct tm *) &time);
    reg_p->create_t.year = (now_t.tm_year )+1900;
    reg_p->create_t.month = (now_t.tm_mon)+1;
    reg_p->create_t.day = now_t.tm_mday;
    //
    printf("\nEnter a Username:");
    fgets(line, sizeof(line),stdin);
    sscanf(line,"%s",user);
    //
    for (int i = 0; i < record; ++i) {
        if (strcmp(d[i].acc.username,user) == 0){
            SetColor(150);
            printf("you already have an account or this username is taken!\n");
            SetColor(255);
            landingPage();
        }
    }
    //
    printf("Enter a Password:");
    gets(reg_p->acc.password);
    fflush(stdin);
    printf("------- Information's -------\n");
    printf("First Name:");
    gets(reg_p->info.fname);
    printf("Last Name:");
    gets(reg_p->info.lname);
    printf("Age:");
    scanf("%d",&reg_p->info.age);
    fflush(stdin);
    printf("Gender(M/F):");
    scanf("%c",&reg_p->info.gender);
    fflush(stdin);
    printf("--------- Addrerss ----------\n");
    printf("Street:");
    gets(reg_p->addr.street);
    printf("House Number:");
    fflush(stdin);
    scanf("%d",&reg_p->addr.no);
    printf("Post Code:");
    scanf("%li",&reg_p->addr.plz);
    printf("City:");
    fflush(stdin);
    gets(reg_p->addr.city);
    printf("--------- Contact ----------\n");
    printf("Phone:");
    gets(reg_p->contact.phone);
    fflush(stdin);
    printf("Email:");
    gets(reg_p->contact.email);
    fflush(stdin);
    strcpy(reg_p->pa.details,"Empty");
    reg_p->ID = rand();
    reg_p->booking_doc_id = 0;
    reg_p->res_t.day = 0;
    reg_p->res_t.month = 0;
    reg_p->res_t.year = 0;
    reg_p->res_t.hour.hour = 0;
    reg_p->res_t.hour.min = 0;
    char t[] = "P_";
    char uf[50];
    char us[50];
    char form[] = ".txt";

    FILE *fptr;
    fptr = (fopen(FILENAME,"a"));
    if(fptr == NULL){
        printf("file error!!!");
        exit(1);
    }
    fprintf(fptr,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",reg_p->ID,reg_p->create_t.day,reg_p->create_t.month,reg_p->create_t.year,reg_p->acc.type,
            user,reg_p->acc.password,reg_p->info.fname,reg_p->info.lname,reg_p->info.age,reg_p->info.gender,reg_p->addr.street,
            reg_p->addr.no,reg_p->addr.plz,reg_p->addr.city,reg_p->contact.phone,reg_p->contact.email,reg_p->pa.details,reg_p->res_t.day,
            reg_p->res_t.month,reg_p->res_t.year,reg_p->res_t.hour.hour,reg_p->res_t.hour.min,reg_p->booking_doc_id
    );

    printf("Thank You for Registration dear %s\n\n",reg_p->info.fname);

    fclose(fptr);
    landingPage();

}

//  Doctors Registration Menu
void Doctors_reg(){
    srand(time(0));
    char user[50];
    struct data *reg_d,reg_Doctors;
    reg_d = &reg_Doctors;
    int record = 0;
    struct data d[STRSIZE];
    read_file(d,FILENAME,"a+",&record);


    reg_d->acc.type = 'D';
    //
    //
    char buff[100];
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    strftime (buff, 100, "%d-%m-%Y %H:%M:%S", (const struct tm *) &time);
    reg_d->create_t.year = (now_t.tm_year )+1900;
    reg_d->create_t.month = (now_t.tm_mon)+1;
    reg_d->create_t.day = now_t.tm_mday;
    //
    //
    FILE *fptr;
    fptr = (fopen(FILENAME,"a+"));
    if(fptr == NULL){
        printf("file error!!!");
        exit(1);
    }


    fflush(stdin);
    printf("\nEnter a Username:");
    fgets(line, sizeof(line),stdin);
    sscanf(line,"%s",user);
    //
    for (int i = 0; i < record; ++i) {
        if (strcmp(d[i].acc.username,user) == 0){
            SetColor(150);
            printf("you already have an account or this username is taken!\n");
            SetColor(255);
            landingPage();
        }
    }
    //
    printf("Enter a Password:");
    gets(reg_d->acc.password);
    fflush(stdin);
    printf("------- Information's -------\n");

    printf("First Name:");
    gets(reg_d->info.fname);

    printf("Last Name:");
    gets(reg_d->info.lname);
    fflush(stdin);
    printf("Age:");
    scanf("%d",&reg_d->info.age);
    fflush(stdin);
    printf("Gender(M/F):");
    scanf("%c",&reg_d->info.gender);
    fflush(stdin);
    printf("--------- Addrerss ----------\n");
    printf("Street:");
    gets(reg_d->addr.street);
    fflush(stdin);
    printf("House Number:");
    scanf("%d",&reg_d->addr.no);
    fflush(stdin);
    printf("Post Code(Numberic Only):");
    scanf("%li",&reg_d->addr.plz);
    fflush(stdin);
    printf("City:");
    gets(reg_d->addr.city);
    fflush(stdin);
    printf("--------- Contact ----------\n");
    printf("Phone:");
    gets(reg_d->contact.phone);
    printf("Email:");
    gets(reg_d->contact.email);
    strcpy(reg_d->pa.details,"Doctors");
    reg_d->ID = rand();
    reg_d->booking_doc_id = 0;
    reg_d->res_t.day = 0;
    reg_d->res_t.month = 0;
    reg_d->res_t.year = 0;
    reg_d->res_t.hour.hour = 0;
    reg_d->res_t.hour.min = 0;

    fprintf(fptr,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",reg_d->ID,reg_d->create_t.day,reg_d->create_t.month,reg_d->create_t.year,reg_d->acc.type,
            user,reg_d->acc.password,reg_d->info.fname,reg_d->info.lname,reg_d->info.age,reg_d->info.gender,reg_d->addr.street,
            reg_d->addr.no,reg_d->addr.plz,reg_d->addr.city,reg_d->contact.phone,reg_d->contact.email,reg_d->pa.details,reg_d->res_t.day,
            reg_d->res_t.month,reg_d->res_t.year,reg_d->res_t.hour.hour,reg_d->res_t.hour.min,reg_d->booking_doc_id
    );


    printf("Thank You for Registration Dr. %s %s\n",reg_d->info.fname,reg_d->info.lname);
    printf("Your ID is: %li\n",reg_d->ID);
    fclose(fptr);
    Sleep(5000);
    landingPage();
}

//  Sign Up Menu
void signUpMenu(){

    int opt,*opt_ptr;
    opt_ptr = &opt;
    printf("--------------------------------------------------------\n");
    printf("------------------------ Sign Up -----------------------\n");
    printf("---------------------- 1.As Doctor ---------------------\n");
    printf("-----------------------2.As Patient --------------------\n");
    printf("--------------------------------------------------------\n");
    printf("enter your option:");
    scanf("%d",&opt);

    switch(opt) {
        case 1:
            Doctors_reg();
            break;
        case 2:
            Patient_reg();
            break;
        default:
            printf("something went wrong!");
    }

}

void view_doc_profile(struct data d[],int records,int j,char fname[],char lname[],long int ID){
    struct data D[STRSIZE];
    int rec = 0;
    read_file(D,FILENAME,"r",&rec);
    int opt_mod = 0;
    int opt = 0;
    fflush(stdin);
    SetColor(NORMAL);
    printf("[1]. Change\n");
    printf("[2].");
    SetColor(RED);
    printf(" Delete Profile\n");
    SetColor(NORMAL);
    printf("Please Choose an Option:");
    scanf("%d",&opt);
    fflush(stdin);
    if(opt == 1){
        SetColor(DARKYELLOW);
        printf("--------------------- Your Information --------------------\n");
        printf("-----------------------------------------------------------\n");
        SetColor(NORMAL);
        SetColor(GRAY);
        printf("[X].\tID: %li\n",D[j].ID);
        printf("[X].\tFirst Name: %s\n",D[j].info.fname);
        printf("[X].\tLast Name: %s\n",D[j].info.lname);
        printf("[X].\tGender: %c\n",D[j].info.gender);
        SetColor(NORMAL);
        printf("[1].\tAddress: %s.%d, %li %s\n",D[j].addr.street,D[j].addr.no,D[j].addr.plz,D[j].addr.city);
        printf("[2].\tTel: %s\n",D[j].contact.phone);
        printf("[3].\tEmail: %s\n",D[j].contact.email);
        printf("[4].\tPassword: *********\n");
        SetColor(DARKYELLOW);
        printf("-----------------------------------------------------------\n");
        SetColor(NORMAL);
        printf("What do you like to edit?");
        scanf("%d",&opt_mod);

        if (opt_mod == 1){
            fflush(stdin);
            printf("Address:\n");
            printf("\tStreet:");
            gets(D[j].addr.street);
            fflush(stdin);
            printf("\t\tHouse Number:");
            scanf("%d",&D[j].addr.no);
            printf("\t\tPost Code:");
            scanf("%li",&D[j].addr.plz);
            fflush(stdin);
            printf("\t  City:");
            gets(D[j].addr.city);
            fflush(stdin);
        }else if (opt_mod == 2){
            getchar();
            printf("\tTel:");
            gets(D[j].contact.phone);
    }else if (opt_mod == 3){
            fflush(stdin);
            printf("\tEmail:");
            gets(D[j].contact.email);
    }else if (opt_mod == 4){
            char pass[50];
            fflush(stdin);
            printf("Enter your current password:");
            gets(pass);
            if (strcmp(pass,D[j].acc.password) == 0){
                printf("enter your new password:");
                gets(D[j].acc.password);
            }else{
                SetColor(RED);
                printf("\nWrong password!!\n");
                SetColor(NORMAL);
                view_doc_profile(d,records,j,fname,lname,ID);
            }
        }else{
        printf("Wrong input!");
    }//opt 1 end
    }
    if (opt == 2){
        char yes;
        fflush(stdin);
        printf("Are you sure? [Y/y]\n");
        scanf("%c",&yes);
        if (yes == 'y' || yes == 'Y'){
            for (int i = j; i < rec; ++i) {
                D[j] = D[j+1];
            }
            rec-=1;
        }
        printf("Your Profile has been deleted!\nGood Bye!\n\n");
        landingPage();
    }

    switch (opt_mod) {
        case 1:
            SetColor(GREEN);
            printf("Address Updated!\n");
            SetColor(NORMAL);
            break;
        case 2:
            SetColor(GREEN);
            printf("Telephone number Updated!\n");
            SetColor(NORMAL);
            break;
        case 3:
            SetColor(GREEN);
            printf("Email Address Updated!\n");
            SetColor(NORMAL);
            break;
        case 4:
            SetColor(GREEN);
            printf("Password successfully changed!\n");
            SetColor(NORMAL);
            break;
        default:
            printf("Something Went Wrong!!\n");
            exit(1);
    }
    write_file(D,rec,FILENAME,"w");
    exit(1);
}

void doc_menu(struct data d[],int records,int j,char fname[],char lname[],long int ID){
    int opt;
    printf("--------------------------------------------------------\n");
    printf("--------------------- Doctors Menu ---------------------\n");
    printf("--------------------- 1.View Patients-------------------\n");
    printf("----------------------2.View/Edit Your Profile ---------\n");
    printf("----------------------3.Exit ---------------------------\n");
    printf("--------------------------------------------------------\n");
    printf("enter your option:");
    scanf("%d",&opt);
    switch (opt) {
        case 1:
            view_appointments(d,records,ID);
            break;
        case 2:
            view_doc_profile(d,records,j,fname,lname,ID);
            break;
        case 3:
            printf("Good Bye!\n\n");
            exit(1);
            break;
        default:
            printf("something went wrong!");
            exit(0);
            break;
    }

}

void view_appointments(struct data d[],int records,long int ID){
    char ftype[] = "P_";
    char user_filename[50];
    char username[50];
    char format[] = ".txt";
    struct data p[100];
    char fname[50];
    char lname[50];
    int temp_ID;
    struct dp_id dpID[STRSIZE];
    int counter = 0;


    //
    read_dp(dpID,DPFILENAME,"r",&counter);
    //
    //
    struct tracker Ptracker[STRSIZE];
    int b = 0;
    for (int i = 0; i < records; ++i) {
        if (dpID[i].doctor_id == ID){
            Ptracker[b].IDtracker = dpID[i].patient_id;
            ++b;
        }
    }
    //
    int k = 0;
    for (int i = 0; i < records; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (Ptracker[j].IDtracker == d[i].ID){
                strcpy(Ptracker[k].USERtracker,d[i].acc.username);
                ++k;
            }
        }
    }
    //

    //for (int i = 0; i <= b ; ++i) {
    //    printf("%s\n",Ptracker[i].USERtracker);
    //}
    /*
    char **pUser;
    pUser = (char**) calloc(STRSIZE, sizeof(char*));

    static int x = 0;
    int z = 0;
    for (int i = 0; i < records; ++i) {
        if (d[i].ID == pIDtracker[x]){
            //pUser[x] = (char *) calloc(50,sizeof(char));
            //strcpy(pUser[x],d[i].acc.username);
            //++x;
            SetColor(RED);
            printf("\nsay hello\n");
            SetColor(NORMAL);
            ++x;
        }
    }
    */
    //printf("\n x:%d \n",x);


    //for (int i = 0; i < x; ++i) {
    //        printf("patient ids: %s\n",pUser[i]);
    //}
    printf("------------------------------");
    SetColor(YELLOW);
    printf(" Patients list ");
    SetColor(NORMAL);
    printf("------------------------------\n");
    int m = 0;
    for (int i = 0; i < records; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (Ptracker[j].IDtracker == d[i].ID){
                if (d[i].acc.type == 'P'){
                    char g[] = "Unknown";
                    if (d[i].info.gender == 'M' || d[i].info.gender == 'm'){
                        strcpy(g,"Male");
                    }else if(d[i].info.gender == 'F' || d[i].info.gender == 'f'){
                        strcpy(g,"Female");
                    }
                        SetColor(LIGHTBLUE);
                        printf("[%d].\t",i+1);
                        SetColor(NORMAL);
                        printf("ID: %li\n\tPatient Since: %d.%d.%d\n\tFirst Name: %s\n\tLast Name: %s\n\tGender: %s\n\tAge: %d\n\tAddress: %s.%d, %li,%s\n\tTelephone: %s\n\tEmail: %s\n",d[i].ID,
                               d[i].create_t.day,d[i].create_t.month,d[i].create_t.year,d[i].info.fname,d[i].info.lname,
                               g,d[i].info.age,d[i].addr.street,d[i].addr.no,d[i].addr.plz,d[i].addr.city,d[i].contact.phone,d[i].contact.email);
                        printf("-------------------------------------------------------------------\n");
                }
            }
        }
    }



    fflush(stdin);
    printf("To select a patient please enter they first name last name and ID:\nFirst Name:");
    gets(fname);
    printf("Last name:");
    gets(lname);
    printf("ID:");
    scanf("%d",&temp_ID);
    int selectedPatient;
    for (int i = 0; i < records; ++i) {
        if (strcmp(d[i].info.fname, fname) == 0 && strcmp(d[i].info.lname, lname) == 0 && d[i].ID == temp_ID && d[i].acc.type == 'P') {
            strcpy(username, d[i].acc.username);
            selectedPatient = i;
            break;
        }
    }
    strcat(username,format);
    strcat(ftype,username);
    strcat(user_filename,ftype);
    //printf("\n%s\n",user_filename);
    read_file(p,user_filename,"r",&records);
    SetColor(YELLOW);
    printf("%s %s from %s is selected!\n",p[0].info.fname,p[0].info.lname,p[0].addr.city);
    SetColor(NORMAL);

    printf("Your patient Information and appointments:\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < records; ++i) {
        if (strcmp(p[i].info.fname,fname) == 0 && strcmp(p[i].info.lname,lname) == 0 && p[i].acc.type == 'P' && p[i].booking_doc_id == ID){
            printf("[%d]:\tSymptoms: %s\n\tAppointment: "
                   "%d.%d.%d - %d:%d\n--------------------------------------------------------\n",
                   i+1,p[i].pa.details,p[i].res_t.day,p[i].res_t.month,p[i].res_t.year,p[i].res_t.hour.hour,p[i].res_t.hour.min);
        }
    }

    exit(1);
}

void change_appointment(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]){
    struct data p_mod[100];
    int n = 0;
    read_file(p_mod,user_filename,"r",&n);
    /*
    FILE *fptr;
    fptr = fopen(user_filename, "r");

    if (fptr == NULL) {
        SetColor(RED);
        printf("You Never Booked an appointment!!");
    }
    int read = 0;

    int n = 0;

    do
    {
        read = fscanf(fptr,
                      "%d;%d;%d;%c;%[^;];%[^;];%[^;];%[^;];%d;%c;%[^;];%d;%li;%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%d\n",
                      &p_mod[n].create_t.day,
                      &p_mod[n].create_t.month,
                      &p_mod[n].create_t.year,
                      &p_mod[n].acc.type,
                      p_mod[n].acc.username,
                      p_mod[n].acc.password,
                      p_mod[n].info.fname,
                      p_mod[n].info.lname,
                      &p_mod[n].info.age,
                      &p_mod[n].info.gender,
                      p_mod[n].addr.street,
                      &p_mod[n].addr.no,
                      &p_mod[n].addr.plz,
                      p_mod[n].addr.city,
                      p_mod[n].contact.phone,
                      p_mod[n].contact.email,
                      p_mod[n].pa.details,
                      &p_mod[n].res_t.day,
                      &p_mod[n].res_t.month,
                      &p_mod[n].res_t.year,
                      &p_mod[n].res_t.hour.hour,
                      &p_mod[n].res_t.hour.min

        );

        if (read == 22){
            n++;
        }

        if (read != 22 && !feof(fptr))
        {
            printf("File format incorrect.\n");
            exit(1);

        }

        if (ferror(fptr))
        {
            printf("Error reading file.\n");
            exit(1);
        }

    } while (!feof(fptr));
    fclose(fptr);
     */
    SetColor(GREEN);
    printf("Dear %s %s, appointments you've booked are:\n",p_mod[0].info.fname,p_mod[0].info.lname);
    SetColor(NORMAL);
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < records; ++i) {
        for (int t = 0; t < n; ++t) {
            if (d[i].ID == p_mod[t].booking_doc_id && d[i].acc.type == 'D'){
                printf("[%d]:\tPatient Since:%d.%d.%d\n\tSymptoms: %s\n\tDoctor: %s %s\n\tAddress: %s.%d, %li %s\n\tAppointment: "
                        ,t+1,p_mod[t].create_t.day,p_mod[t].create_t.month,p_mod[t].create_t.year,p_mod[t].pa.details,d[i].info.fname,d[i].info.lname,
                        d[i].addr.street,d[i].addr.no,d[i].addr.plz,d[i].addr.city);
                SetColor(LIGHTBLUE);
                printf("%d.%d.%d - %d:%d",
                       p_mod[t].res_t.day,p_mod[t].res_t.month,p_mod[t].res_t.year,p_mod[t].res_t.hour.hour,p_mod[t].res_t.hour.min);
                SetColor(NORMAL);
                printf("\n--------------------------------------------------------\n");
            }

        }
    }
    int f=0;
    int k=0;
    printf("Which one do you like to change?\n");
    scanf("%d",&f);
    f-=1;
    printf("what would you like to change?\n[1]. Date\n[2]. Time\n[3]. Symptoms\n");
    scanf("%d",&k);
    fflush(stdin);
    if(k == 1){
        printf("what day would you like to book an appointment? [dd.mm.yyyy]:");
        scanf("%d.%d.%d",&p_mod[f].res_t.day,&p_mod[f].res_t.month,&p_mod[f].res_t.year);
    }else if(k == 2){
        printf("what time would you like to book an appointment? [hh:mm] 00-24 :");
        scanf("%d:%d",&p_mod[f].res_t.hour.hour,&p_mod[f].res_t.hour.min);
    }else if(k == 3){
        fflush(stdin);
        printf("Please describe your symptoms:");
        gets(p_mod[f].pa.details);
    }else{
        printf("Input invalid!");
    }

    FILE *wfptr;
    wfptr = fopen(user_filename, "w");
    if (wfptr == NULL) {
        SetColor(12);
        printf("file err!!");
    }

    for (int i = 0; i < n; ++i) {
            fprintf(wfptr,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",p_mod[i].ID,p_mod[i].create_t.day,p_mod[i].create_t.month,p_mod[i].create_t.year,p_mod[i].acc.type,
                    p_mod[i].acc.username,p_mod[i].acc.password,p_mod[i].info.fname,p_mod[i].info.lname,p_mod[i].info.age,p_mod[i].info.gender,p_mod[i].addr.street,
                    p_mod[i].addr.no,p_mod[i].addr.plz,p_mod[i].addr.city,p_mod[i].contact.phone,p_mod[i].contact.email,p_mod[i].pa.details,p_mod[i].res_t.day,p_mod[i].res_t.month,p_mod[i].res_t.year,
                    p_mod[i].res_t.hour.hour,p_mod[i].res_t.hour.min,p_mod[i].booking_doc_id);
    }
    fclose(wfptr);
    SetColor(GREEN);
    printf("Your appointment successfully updated!\n");
    SetColor(NORMAL);
    fflush(stdin);
    char q;
    printf("Main Menu:[M/m]\tQuit:[Q/q]\n");
    scanf("%c",&q);
    if (q == 'M' || q == 'm'){
        patients_menu(d,records,j,d[j].info.fname,d[j].info.lname,user_filename);
    }else{
        printf("\nGood Bye...\n");
        exit(1);
    }



}

void cancel_appointment(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]){
    struct data p_canc[100];
    int n = 0;
    read_file(p_canc,user_filename,"r",&n);
    /*
    FILE *cancfptr;
    cancfptr = fopen(user_filename, "r");

    if (cancfptr == NULL) {
        SetColor(RED);
        printf("You Never Booked an appointment!!");
    }
    int read = 0;

    int n = 0;

    do
    {
        read = fscanf(cancfptr,
                      "%d;%d;%d;%c;%[^;];%[^;];%[^;];%[^;];%d;%c;%[^;];%d;%li;%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%d\n",
                      &p_canc[n].create_t.day,
                      &p_canc[n].create_t.month,
                      &p_canc[n].create_t.year,
                      &p_canc[n].acc.type,
                      p_canc[n].acc.username,
                      p_canc[n].acc.password,
                      p_canc[n].info.fname,
                      p_canc[n].info.lname,
                      &p_canc[n].info.age,
                      &p_canc[n].info.gender,
                      p_canc[n].addr.street,
                      &p_canc[n].addr.no,
                      &p_canc[n].addr.plz,
                      p_canc[n].addr.city,
                      p_canc[n].contact.phone,
                      p_canc[n].contact.email,
                      p_canc[n].pa.details,
                      &p_canc[n].res_t.day,
                      &p_canc[n].res_t.month,
                      &p_canc[n].res_t.year,
                      &p_canc[n].res_t.hour.hour,
                      &p_canc[n].res_t.hour.min

        );

        if (read == 22){
            n++;
        }

        if (read != 22 && !feof(cancfptr))
        {
            printf("File format incorrect.\n");
            exit(1);

        }

        if (ferror(cancfptr))
        {
            printf("Error reading file.\n");
            exit(1);
        }

    } while (!feof(cancfptr));
    fclose(cancfptr);
     */
    SetColor(GREEN);
    printf("Dear %s %s, appointments you've booked are:\n",p_canc[0].info.fname,p_canc[0].info.lname);
    SetColor(NORMAL);
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n; ++i) {
        printf("[%d]:\tPatient Since:%d.%d.%d\n\tSymptoms: %s\n\tAppointment: "
                ,i+1,p_canc[i].create_t.day,p_canc[i].create_t.month,p_canc[i].create_t.year,p_canc[i].pa.details);
        SetColor(LIGHTBLUE);
        printf("%d.%d.%d - %d:%d",
               p_canc[i].res_t.day,p_canc[i].res_t.month,p_canc[i].res_t.year,p_canc[i].res_t.hour.hour,p_canc[i].res_t.hour.min);
        SetColor(NORMAL);
        printf("\n--------------------------------------------------------\n");
    }
    int f=0;
    char yes;
    printf("Which one do you like to Cancel?\n");
    scanf("%d",&f);
    f-=1;
    fflush(stdin);
    printf("Are you sure? [Y/y]\n");
    scanf("%c",&yes);

    if (yes == 'y' || yes == 'Y'){
        for (int i = f; i < records; ++i) {
            p_canc[f] = p_canc[f+1];
        }
        n-=1;
    }
    write_file(p_canc,n,user_filename,"w");
    /*
    FILE *wfptr;
    wfptr = fopen(user_filename, "w");
    if (wfptr == NULL) {
        SetColor(12);
        printf("file err!!");
    }

    for (int i = 0; i < n; ++i) {
        fprintf(wfptr,"%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d\n",p_canc[i].create_t.day,p_canc[i].create_t.month,p_canc[i].create_t.year,p_canc[i].acc.type,
                p_canc[i].acc.username,p_canc[i].acc.password,p_canc[i].info.fname,p_canc[i].info.lname,p_canc[i].info.age,p_canc[i].info.gender,p_canc[i].addr.street,
                p_canc[i].addr.no,p_canc[i].addr.plz,p_canc[i].addr.city,p_canc[i].contact.phone,p_canc[i].contact.email,p_canc[i].pa.details,p_canc[i].res_t.day,p_canc[i].res_t.month,p_canc[i].res_t.year,p_canc[i].res_t.hour.hour,p_canc[i].res_t.hour.min);
    }
    fclose(wfptr);
    */
    SetColor(GREEN);
    printf("Your appointment successfully updated!\n");
    SetColor(NORMAL);

    char q;
    fflush(stdin);
    printf("Main Menu:[M/m]\tQuit:[Q/q]\n");
    scanf("%c",&q);
    while(q != 'q' || q != 'Q' || q != 'm' || q != 'M'){
        if (q == 'q' || q == 'Q'){
            printf("Thank you for choosing us.\nGood Bye\n");
            exit(1);
        }else if(q == 'm' || q == 'M'){
            patients_menu(p_canc,records,j,fname,lname,user_filename);
        }
    }



}

void update_patient_profile(struct data d[],int records,int j,char fname[],char lname[],char user_filename[],char main_file[]){
    struct data p_main[STRSIZE];
    struct data p_pers[STRSIZE];
    int rec_main= 0;
    int rec_pers= 0;
    read_file(p_main,main_file,"r",&rec_main);
    read_file(p_pers,user_filename,"a+",&rec_pers);
    int opt = 0;
    int opt_out = 0;
    printf("[1]. Change\n");
    printf("[2].");
    SetColor(RED);
    printf(" Delete Profile\n");
    SetColor(NORMAL);
    printf("Enter your option:");
    scanf("%d",&opt_out);
    fflush(stdin);
    if (opt_out == 1){
        SetColor(DARKYELLOW);
        printf("--------------------- Your Information --------------------\n");
        printf("-----------------------------------------------------------\n");
        SetColor(NORMAL);
        SetColor(GRAY);
        printf("[X].\tID: %li\n",d[j].ID);
        printf("[X].\tFirst Name: %s\n",d[j].info.fname);
        printf("[X].\tLast Name: %s\n",d[j].info.lname);
        printf("[X].\tGender: %c\n",d[j].info.gender);
        SetColor(NORMAL);
        printf("[1].\tAddress: %s.%d, %li %s\n",d[j].addr.street,d[j].addr.no,d[j].addr.plz,d[j].addr.city);
        printf("[2].\tTel: %s\n",d[j].contact.phone);
        printf("[3].\tEmail: %s\n",d[j].contact.email);
        printf("[4].\tPassword: *********\n");
        SetColor(DARKYELLOW);
        printf("-----------------------------------------------------------\n");
        SetColor(NORMAL);
        printf("What do you want to change:");
        scanf("%d",&opt);
        // Address Change
        if (opt == 1){
            fflush(stdin);
            printf("Address:\n");
            printf("\tStreet:");
            gets(d[j].addr.street);
            printf("\tHouse Number:");
            scanf("%d",&d[j].addr.no);
            printf("\tPost Code:");
            scanf("%li",&d[j].addr.plz);
            fflush(stdin);
            printf("\tCity:");
            gets(d[j].addr.city);
            for (int i = 0; i < rec_pers; ++i) {
                strcpy(p_pers[i].addr.street,d[j].addr.street);
                p_pers[i].addr.no = d[j].addr.no;
                p_pers[i].addr.plz = d[j].addr.plz;
                strcpy(p_pers[i].addr.city,d[j].addr.city);
            }
        }else if (opt == 2){
            fflush(stdin);
            printf("Tel:");
            gets(d[j].contact.phone);
            for (int i = 0; i < rec_pers; ++i) {
                strcpy(p_pers[i].contact.phone,d[j].contact.phone);
            }
        }else if (opt == 3){
            fflush(stdin);
            printf("Email address:");
            gets(d[j].contact.email);
            for (int i = 0; i < rec_pers; ++i) {
                strcpy(p_pers[i].contact.email,d[j].contact.email);
            }
        }else if (opt == 4){
            fflush(stdin);
            char pass[50];
            printf("Enter your current password:");
            gets(pass);
            if (strcmp(pass,d[j].acc.password) == 0){
                fflush(stdin);
                printf("enter your new password:");
                gets(d[j].acc.password);
            }else{
                SetColor(RED);
                printf("\nWrong password!!\n");
                SetColor(NORMAL);
                update_patient_profile(d,records,j,fname,lname,user_filename,FILENAME);
            }
        }
    }else if(opt_out == 2){
        fflush(stdin);
        char yes;
        printf("Are you sure? [Y/y]\n");
        scanf("%c",&yes);

        if (yes == 'y' || yes == 'Y'){
            for (int i = j; i < records; ++i) {
                d[i] = d[i+1];
            }
            records-=1;
            write_file(d,records,FILENAME,"w");
            remove(user_filename);
            SetColor(RED);
            printf("Profile Deleted!!\n\n");
            SetColor(NORMAL);
            landingPage();
        }
    }else if (opt_out != 1 || opt_out != 2){
        SetColor(RED);
        printf("Wrong input!\n");
        SetColor(NORMAL);
        update_patient_profile(d,records,j,fname,lname,user_filename,FILENAME);
    }

    //write_file(p_pers,rec_pers,user_filename,"w");
    //write_file(d,records,FILENAME,"w");

    FILE *fptr,*fmain;
    fptr = fopen(user_filename, "w");
    fmain = fopen(FILENAME, "w");
    if (fptr == NULL || fmain == NULL) {
        SetColor(RED);
        printf("such file or directory not existed!!");
    }

    for (int i = 0; i < records; ++i) {
        fprintf(fmain,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",d[i].ID,d[i].create_t.day,d[i].create_t.month,d[i].create_t.year,d[i].acc.type,
                d[i].acc.username,d[i].acc.password,d[i].info.fname,d[i].info.lname,d[i].info.age,d[i].info.gender,d[i].addr.street,
                d[i].addr.no,d[i].addr.plz,d[i].addr.city,d[i].contact.phone,d[i].contact.email,d[i].pa.details,d[i].res_t.day,d[i].res_t.month,d[i].res_t.year,d[i].res_t.hour.hour,
                d[i].res_t.hour.min,d[i].booking_doc_id);
    }
    for (int i = 0; i < rec_pers; ++i) {
        fprintf(fptr,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",p_pers[i].ID,p_pers[i].create_t.day,p_pers[i].create_t.month,p_pers[i].create_t.year,p_pers[i].acc.type,
                p_pers[i].acc.username,p_pers[i].acc.password,p_pers[i].info.fname,p_pers[i].info.lname,p_pers[i].info.age,p_pers[i].info.gender,p_pers[i].addr.street,
                p_pers[i].addr.no,p_pers[i].addr.plz,p_pers[i].addr.city,p_pers[i].contact.phone,p_pers[i].contact.email,p_pers[i].pa.details,p_pers[i].res_t.day,p_pers[i].res_t.month,p_pers[i].res_t.year,
                p_pers[i].res_t.hour.hour,p_pers[i].res_t.hour.min,p_pers[i].booking_doc_id);
    }

    fclose(fptr);
    fclose(fmain);


        switch (opt) {
            case 1:
                SetColor(GREEN);
                printf("Address Updated!\n");
                SetColor(NORMAL);
                break;
            case 2:
                SetColor(GREEN);
                printf("Phone number Updated!\n");
                SetColor(NORMAL);
                break;
            case 3:
                SetColor(GREEN);
                printf("Email address Updated!\n");
                SetColor(NORMAL);
                break;
            case 4:
                SetColor(GREEN);
                printf("Password successfully changed!\n");
                SetColor(NORMAL);
                break;
            default:
                printf("Something Went Wrong!!\n");
                exit(1);


    }
    patients_menu(d,records,j,d[j].info.fname,d[j].info.lname,user_filename);
}

void patients_menu(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]){
    int opt;
    printf("-----------------------------------------------------------\n");
    printf("--------------------- Patients Menu -----------------------\n");
    printf("--------------------- 1.Update profile --------------------\n");
    printf("--------------------- 2.Get an Appointment ----------------\n");
    printf("--------------------- 3.Change an Appointment -------------\n");
    printf("--------------------- 4.Cancel an Appointment -------------\n");
    printf("--------------------- 5.Exit ------------------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("enter your option:");
    scanf("%d",&opt);
    switch (opt) {
        case 1:
            update_patient_profile(d,records,j,fname,lname,user_filename,FILENAME);
            break;
        case 2:
            get_appointment(d,records,j,fname,lname,user_filename);
            break;
        case 3:
            change_appointment(d,records,j,fname,lname,user_filename);
            break;
        case 4:
            cancel_appointment(d,records,j,fname,lname,user_filename);
            exit(1);
        case 5:
            printf("Hope to see you again, good bye\n\n");
            exit(1);
        default:
            printf("something went wrong!");
            exit(0);
    }
}

void get_appointment(struct data d[],int records,int j,char fname[],char lname[],char user_filename[]){

    //read file

    struct data doctors_info[STRSIZE];
    int s = 0;
    read_file(doctors_info,FILENAME,"r",&s);
    FILE *dp_otr;
    dp_otr = fopen("dp.txt","a+");
    struct data rfile[STRSIZE];
    int num = 0;
    write_file(rfile,num,user_filename,"a+");
    read_file(rfile,user_filename,"r",&num);

    //
    //assign current time
    char buff[100];
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    strftime (buff, 100, "%d-%m-%Y %H:%M:%S", (const struct tm *) &time);
    d[j].create_t.year = (now_t.tm_year )+1900;
    d[j].create_t.month = (now_t.tm_mon)+1;
    d[j].create_t.day = now_t.tm_mday;
    //
    int dd;
    int mm;
    int yyyy;
    int min;
    int hh;
    SetColor(PURPLE);
    printf("--------------------------- Doctors List ---------------------------\n");
    SetColor(NORMAL);
    for (int i = 0; i < records; ++i) {
        if (doctors_info[i].acc.type == 'D'){
            printf(" [%d]\tID: %li\n\tName: %s\n\tLast Name: %s\n\tGender: %c\n\tAddress:%s.%d,%li %s\n\tTel: %s\n",i+1,
                        doctors_info[i].ID,doctors_info[i].info.fname,doctors_info[i].info.lname,doctors_info[i].info.gender,
                        doctors_info[i].addr.street,doctors_info[i].addr.no,doctors_info[i].addr.plz,doctors_info[i].addr.city,doctors_info[i].contact.phone);
            SetColor(BLUE);
            printf("--------------------------------------------------------------------\n");
            SetColor(NORMAL);
        }
    }
    int x = 0;
    printf("Please choose a doctor:\n");
    scanf("%d",&x);
    x-=1;
    d[j].booking_doc_id = doctors_info[x].ID;
    printf("what day would you like to book an appointment? [dd.mm.yyyy]:");
    scanf("%d.%d.%d",&dd,&mm,&yyyy);
    printf("what time would you like to book an appointment? [hh:mm] 00-24 :");
    scanf("%d:%d",&hh,&min);
    fflush(stdin);
    printf("Please describe your symptoms:");
    gets(d[j].pa.details);
    d[j].res_t.day = dd;
    d[j].res_t.month = mm;
    d[j].res_t.year = yyyy;
    d[j].res_t.hour.min = min;
    d[j].res_t.hour.hour = hh;


    printf("\ndoc id: %li \nyour id: %li\n",d[j].booking_doc_id,d[j].ID);
    /*fprintf(fptr,"%d;%d;%d;%s;%s;%d:%c;%s;%d;%d;%d;%d;%d\n",
                d[j].create_t.day,d[j].create_t.month,d[j].create_t.year,
                d[j].info.fname,d[j].info.lname,d[j].info.age,d[j].info.gender,
                d[j].contact.phone,d[j].res_t.day,d[j].res_t.month,d[j].res_t.year,
            d[j].res_t.hour.hour,d[j].res_t.hour.min);*/
    FILE *fptr,*fmain;
    fptr = fopen(user_filename, "a");
    fmain = fopen(FILENAME, "w");
    if (fptr == NULL || fmain == NULL) {
        SetColor(12);
        printf("such file or directory not existed!!");
    }

    for (int i = 0; i < records; ++i) {
        if (strcmp(d[i].acc.username,d[j].acc.username) == 0){
            fprintf(fptr,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",d[i].ID,d[i].create_t.day,d[i].create_t.month,d[i].create_t.year,d[i].acc.type,
                    d[i].acc.username,d[i].acc.password,d[i].info.fname,d[i].info.lname,d[i].info.age,d[i].info.gender,d[i].addr.street,
                    d[i].addr.no,d[i].addr.plz,d[i].addr.city,d[i].contact.phone,d[i].contact.email,d[i].pa.details,d[i].res_t.day,d[i].res_t.month,d[i].res_t.year,d[i].res_t.hour.hour,d[i].res_t.hour.min,d[i].booking_doc_id);
        }
    }
    for (int i = 0; i < records; ++i) {
            fprintf(fmain,"%li;%d;%d;%d;%c;%s;%s;%s;%s;%d;%c;%s;%d;%li;%s;%s;%s;%s;%d;%d;%d;%d;%d;%li\n",d[i].ID,d[i].create_t.day,d[i].create_t.month,d[i].create_t.year,d[i].acc.type,
                    d[i].acc.username,d[i].acc.password,d[i].info.fname,d[i].info.lname,d[i].info.age,d[i].info.gender,d[i].addr.street,
                    d[i].addr.no,d[i].addr.plz,d[i].addr.city,d[i].contact.phone,d[i].contact.email,d[i].pa.details,d[i].res_t.day,d[i].res_t.month,d[i].res_t.year,d[i].res_t.hour.hour,d[i].res_t.hour.min,d[i].booking_doc_id);
    }
    // patient ID / Doctor ID
    fprintf(dp_otr,"%li;%li\n",d[j].ID,d[x].ID);
    fclose(dp_otr);
    fclose(fptr);
    fclose(fmain);
    printf("\ndoc id: %li \nyour id: %li\n",d[j].booking_doc_id,d[j].ID);
    printf("---------------------------------------------------\n");
    printf("Dear %s, You Appointment has been set successfuly.\n",d[j].info.lname);
    SetColor(DARKYELLOW);
    printf("You Appointment details is:\n");
    SetColor(NORMAL);
    SetColor(GREEN);
    printf("\tDate: %d.%d.%d\n\tTime:%d:%d\n\tDoctor: %s %s\n\tAddress: %s.%d,%li %s\n\tTel: %s",d[j].res_t.day,d[j].res_t.month,d[j].res_t.year,d[j].res_t.hour.hour,
                                                                                                d[j].res_t.hour.min,doctors_info[x].info.fname,doctors_info[x].info.lname,
                                                                                                doctors_info[x].addr.street,doctors_info[x].addr.no,doctors_info[x].addr.plz,doctors_info[x].addr.city,doctors_info[x].contact.phone);
    SetColor(NORMAL);
    char c;
    printf("\nMain Menu [M/m]\tQuit [Q/q]\n");
    scanf("%c",&c);

    if (c == 'M' || c == 'm'){
        patients_menu(d,records,j,d[j].info.fname,d[j].info.lname,user_filename);
    }else{
        printf("Good bye!\n\n");
        exit(0);
    }
}

void signIn(){
    char ftype[] = "P_";
    char user_filename[50];
    char format[] = ".txt";

    int records = 0;
    struct data d[STRSIZE];
    read_file(d,FILENAME,"r",&records);

    /*
    printf("\n%d records read.\n\n", records);
    for (int i = 0; i < records; ++i) {
        printf("Type:%c - Name: %s\n",d[i].acc.type,d[i].acc.username);

    }
    */


    char user[50];
    char pass[50];
    printf("Username:");
    scanf("%s",user);
    printf("Password:");
    scanf("%s",pass);
    for (int i = 0; i < records; ++i) {
        if (strcmp(d[i].acc.username,user)==0 && strcmp(d[i].acc.password,pass) == 0 && d[i].acc.type == 'D'){
                printf("\nHello Dr. %s\n",d[i].info.lname);
                doc_menu(d,records,i,d[i].info.fname,d[i].info.lname,d[i].ID);

        }else if(strcmp(d[i].acc.username,user)==0 && strcmp(d[i].acc.password,pass) == 0 && d[i].acc.type == 'P'){
            if (d[i].info.gender == 'M'){

                printf("\nHello Mr. %s\n",d[i].info.lname);
            }else if (d[i].info.gender == 'F'){
                printf("\nHello Ms. %s\n",d[i].info.lname);
            }
            strcat(user_filename,ftype);
            strcat(user_filename,d[i].acc.username);
            strcat(user_filename,format);
            patients_menu(d,records,i,d[i].info.fname,d[i].info.lname,user_filename);
        }else if(strcmp(d[i].acc.username,user)==0 && strcmp(d[i].acc.password,pass) == 0 && d[i].acc.type == 'A'){
            admin();
        }
    }

    SetColor(RED);
    printf("Username or Password is wrong, please try again\n");
    SetColor(NORMAL);
    landingPage();

}

void landingPage(){
    int opt;
    printf("--------------------------------------------------------\n");
    printf("--------------- Doctor Appointment System --------------\n");
    printf("---------------------- 1.Sign Up -----------------------\n");
    printf("-----------------------2.Sign In -----------------------\n");
    printf("--------------------------------------------------------\n");
    printf("enter your option:");
    scanf("%d",&opt);

    switch(opt) {

        case 1:
            signUpMenu();
            break;
        case 2:
            signIn();
            break;
        default:
            SetColor(RED);
            printf("Invalid Input! please try again\n");
            SetColor(NORMAL);
            landingPage();
    }


}


