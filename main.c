//==============================================
// Name:           Khang Nguyen
// Student Number: 122582208
// Email:          knguyen101@myseneca.ca
// Section:        NCC
// Date:           August 11th, 2021
//==============================================
// Final Assessment: Question 1
//==============================================

#include<stdio.h>
#include<string.h>

#define MAX_ACTIVITY_NAME_LEN 16
#define MAX_NAME_LEN 20
#define NUM_ACTIVITY_NAMES 3

// ***STRUCTS*** //

struct Date
{   
    int year;
    int month;
    int day;
};

struct activity
{
    int activityType;
    struct Date date;
    double distance;
};


struct Participant
{
    int numActivities;
    char name[MAX_NAME_LEN];
    struct activity activities[20];
};

void displayHeader(void)
{
    printf("Read 4 Participants\n");
}

// ***Functions w/ Defintions*** //

int findParticipant(struct Participant participants[],int count,char name[])
{
    for(int i = 0; i < count; i++)
    {
        if( !strcmp( participants[i].name,name) )
        {
            return i;
        }
    }


    return -1;
}

int findString(const char activNames[][MAX_ACTIVITY_NAME_LEN + 1],int n , char activity[])
{
    for(int i = 0; i < n; i++)
    {
        if( !strcmp( activNames[i] ,activity) )
        {
            return i;
        }
    }
}

int zeller(const struct Date* date)

{
     int month = date->month;

     int year = date->year;

     if (date->month < 3)

     {

            year--;

            month += 12;

     }

     int yr = year % 100;

     int century = year / 100;

     int result = date->day;

     result += 13 * (month + 1) / 5;

     result += yr;

     result += yr / 4;

     result += century / 4;

     result -= 2 * century;

     result = result % 7;

     return result;

}

int readActivityFile(FILE* fp, struct Participant participants[],const char activNames[][MAX_ACTIVITY_NAME_LEN + 1])
{

     int count = 0, ch, addPosn, actPosn;

     char activity[MAX_ACTIVITY_NAME_LEN];

     char name[MAX_NAME_LEN + 1];

     int year=0, month=0, day=0;

     double dist=0.0;

 
     while (!feof(fp))

     {  

            fscanf(fp, "%[^~]s%*c", name);

            ch = fgetc(fp);

            fscanf(fp, "%[^~]s%*c", activity);

            ch = fgetc(fp);

            fscanf(fp, "%d", &year);

            ch = fgetc(fp);

            fscanf(fp, "%d", &month);

            ch = fgetc(fp);

            fscanf(fp, "%d", &day);

            ch = fgetc(fp);

            fscanf(fp, "%lf", &dist);


            ch = fgetc(fp);

            addPosn = findParticipant(participants, count, name);

            if (addPosn < 0)

            {

                  addPosn = count;

                  count++;

                  participants[addPosn].numActivities = 0;

                  strcpy(participants[addPosn].name, name);

            }

 

            actPosn = participants[addPosn].numActivities;

            participants[addPosn].activities[actPosn].activityType = findString(activNames, NUM_ACTIVITY_NAMES, activity);

            participants[addPosn].activities[actPosn].date.year = year;

            participants[addPosn].activities[actPosn].date.month = month;

            participants[addPosn].activities[actPosn].date.day = day;

            participants[addPosn].activities[actPosn].distance = dist;

            participants[addPosn].numActivities++;

 
            ch = fgetc(fp);

            if (!feof(fp)) ungetc(ch, fp);

     }

     return count;

}

// ***MAIN*** // 
int main()
{
    FILE *fp; // File pointer is declared and is opened in read mode
    fp = fopen("inputfile.txt", "r"); 
    if ( fp == NULL )
    {
        printf( "file failed to open." ) ;
    }

    const int maxParticipants = 100;
    struct Participant participants[maxParticipants];
    const char activNames[3][MAX_ACTIVITY_NAME_LEN+1]={"run","swim","bike"};
    int j = readActivityFile(fp, participants , activNames );
    char *day[7]={"Sat","Sun","Mon","Tue","Wed","Thu","Fri"};
    char *month[12]={"Jan","Feb","Mar","Api","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    fclose(fp); // closes the file

    displayHeader(); // header display
    int def = 1;
    int flag = 0;

    while (1)
    {

    int choice;

    if(def)
    {
        printf("\nSelect one of the following options:\n");

        printf("0 - Exit\n");

        printf("1 - list all participants and events\n");

        printf("2 - list total run distances\n");

        printf("3 - list total swim distances\n");

        printf("4 - list total bike distances\n");

        printf("5 - list best run distances\n");

        printf("6 - list best swim distances\n");

        printf("7 - list best bike distances\n");

    }

    scanf("%d",&choice);

    def=1;

    switch (choice)
    {
    case 0:
        flag=1;
        printf("Goodbye");
        break;
    case 1:

        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("%s\n----------------------------------------------\n",participants[i].name);
        

            for(int a=0;a<na;a++)
            {   

                printf("%s ",activNames[participants[i].activities[a].activityType]);

                int dy = zeller(&participants[i].activities[a].date);

                printf("%s ",day[dy]);

                printf("%s ",month[participants[i].activities[a].date.month]);

                printf("%d ",participants[i].activities[a].date.year%100);

                printf("%.1f\n",participants[i].activities[a].distance);

            }

        }
        break;
    case 2:
        printf("\n        *** TOTAL RUNS ***\n");

        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("            %s ",participants[i].name);
        double sum=0;
            for(int a=0;a<na;a++)
            {   
                if(participants[i].activities[a].activityType==0)
                    sum+=participants[i].activities[a].distance;
            }

        printf("  %.1f\n",sum);
        }

        break;
    case 3:
        printf("\n        *** TOTAL SWIMS ***\n");

        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("            %s ",participants[i].name);
        double sum=0;
            for(int a=0;a<na;a++)
            {   
                if(participants[i].activities[a].activityType==1)
                    sum+=participants[i].activities[a].distance;
            }

        printf("  %.1f\n",sum);
        }

        break;
    case 4:
        printf("\n        *** TOTAL BIKE ***\n");
        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("            %s ",participants[i].name);
        double sum=0;
            for(int a = 0; a < na; a++)
            {   
                if(participants[i].activities[a].activityType==2)
                    sum+=participants[i].activities[a].distance;
            }

        printf("  %.1f\n",sum);
        }

        break;
    case 5:
        printf("\n        *** TOP RUNS ***\n");
        
        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("            %s ",participants[i].name);
        double max=0;
            for(int a = 0; a < na; a++)
            {   
                if(participants[i].activities[a].activityType==0)
                    if(max<participants[i].activities[a].distance)
                    {
                        max=participants[i].activities[a].distance;
                    }
            }

        printf("  %.1f\n",max);
        }

        break;
    case 6:
        printf("\n        *** TOP SWIM ***\n");
       
        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("            %s ",participants[i].name);
        double max=0;
            for(int a=0;a<na;a++)
            {   
                if(participants[i].activities[a].activityType==1)
                    if(max<participants[i].activities[a].distance)
                    {
                        max=participants[i].activities[a].distance;
                    }
            }

        printf("  %.1f\n",max);
        }

        break;
    case 7:
        printf("\n        *** TOP BIKE ***\n");
     
        for(int i = 0; i < j; i++)
        {
        
        int na=participants[i].numActivities;
        printf("            %s ",participants[i].name);
        double max=0;
            for(int a = 0; a < na; a++)
            {   
                if(participants[i].activities[a].activityType==2)
                    if(max<participants[i].activities[a].distance)
                    {
                        max=participants[i].activities[a].distance;
                    }
            }

        printf("  %.1f\n",max);
        }

        break;
    default:
        printf("\nEnter a number between 0 to 7: ");
        def=0;
        break;
    }

    if(flag) break; 

    }
    
    return 0;
}

