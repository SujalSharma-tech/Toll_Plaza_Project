#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct AllData
{
    char name[30];
    char NoPlate[15];
    char time[35];
    char RegDate[25];
    int toll;
    char VehType[20];
    char retInc;
    int ss, sr;
} Data;
int value = 0;
int read = 0;
Data MyData[10];

Data Records[20];
Data FareDetails[5];
int TotalRec;
void CallVehRecords()
{

    FILE *fileptr;
    int recnum = 0;
    int recread = 0;

    fileptr = fopen("Records.txt", "r");
    do
    {
        recread = fscanf(fileptr, "%30[^,],%16[^,],%25[^,],%20[^,],%c,%d[^\n]", Records[recnum].name, Records[recnum].NoPlate, Records[recnum].RegDate, Records[recnum].VehType, &Records[recnum].retInc, &Records[recnum].toll);

        if (recread == 6)
        {
            recnum++;
        }
    } while (!feof(fileptr));
    fclose(fileptr);

    TotalRec = recnum;
}

void CallFareDetails()
{
    FILE *fileptr;
    fileptr = fopen("FAREDETAILSNEW.txt", "r");
    int fareread = 0;
    int farere = 0;
    do
    {
        fareread = fscanf(fileptr, "%d,%d", &FareDetails[farere].ss, &FareDetails[farere].sr);
        if (fareread == 2)
        {
            farere++;
        }
    } while (!feof(fileptr));
    fclose(fileptr);
    printf("%d %d\n", FareDetails[1].ss, FareDetails[1].sr);
}
void Updatefare()
{
    FILE *fileptr;
    FILE *fileptr2;
    int opt;
    fileptr = fopen("FAREDETAILSNEW.txt", "a+");

    printf("\n===============================================================================================================\n");
    printf("Which Fare you want to update?\n");
    printf("1. Small vehicles\n");
    printf("2. Medium vehicles\n");
    printf("3. Large vehicles\n");
    printf("===============================================================================================================\n");
    printf("-->Enter a Choice: ");
    scanf("%d", &opt);

    int fareread = 0;
    int farerec = 0;
    do
    {
        fareread = fscanf(fileptr, "%d,%d", &FareDetails[farerec].ss, &FareDetails[farerec].sr);
        if (fareread == 2)
        {
            farerec++;
        }
    } while (!feof(fileptr));
    fclose(fileptr);

    fileptr2 = fopen("Faretemp.txt", "w");

    if (opt == 1)
    {
        for (int i = 0; i <= 2; i++)
        {
            if (i == 0)
            {
                printf("Enter Fare details for single side: ");
                scanf("%d", &MyData[0].ss);
                printf("Enter Fare details for return included: ");
                scanf("%d", &MyData[0].sr);

                fprintf(fileptr2, "%d,%d\n", MyData[0].ss, MyData[0].sr);
            }
            else
            {
                fprintf(fileptr2, "%d,%d\n", FareDetails[i].ss, FareDetails[i].sr);
            }
        }
    }
    if (opt == 2)
    {
        for (int i = 0; i <= 2; i++)
        {
            if (i == 1)
            {
                printf("Enter Fare details for single side: ");
                scanf("%d", &MyData[0].ss);
                printf("Enter Fare details for return included: ");
                scanf("%d", &MyData[0].sr);

                fprintf(fileptr2, "%d,%d\n", MyData[0].ss, MyData[0].sr);
            }
            else
            {
                fprintf(fileptr2, "%d,%d\n", FareDetails[i].ss, FareDetails[i].sr);
            }
        }
    }
    if (opt == 3)
    {

        for (int i = 0; i <= 2; i++)
        {
            if (i == 2)
            {
                printf("Enter Fare details for single side: ");
                scanf("%d", &MyData[0].ss);
                printf("Enter Fare details for return included: ");
                scanf("%d", &MyData[0].sr);

                fprintf(fileptr2, "%d,%d\n", MyData[0].ss, MyData[0].sr);
            }
            else
            {
                fprintf(fileptr2, "%d,%d\n", FareDetails[i].ss, FareDetails[i].sr);
            }
        }
    }

    fclose(fileptr2);
    fileptr = fopen("Faretemp.txt", "r");
    fileptr2 = fopen("FAREDETAILSNEW.txt", "w");
    fareread = 0;
    farerec = 0;
    do
    {
        fareread = fscanf(fileptr, "%d,%d\n", &FareDetails[farerec].ss, &FareDetails[farerec].sr);

        if (fareread == 2)
        {
            farerec++;
        }
    } while (!feof(fileptr));

    fclose(fileptr);

    for (int i = 0; i < 3; i++)
    {
        fprintf(fileptr2, "%d,%d\n", FareDetails[i].ss, FareDetails[i].sr);
    }

    fclose(fileptr2);

    printf("===============================================================================================================\n");

    printf("%-45s%s", "", "FARE UPDATED SUCCESSFULLY\n");
    printf("===============================================================================================================\n");

    fareread = 2;
    farerec = 0;
}
void Add()
{
    FILE *fileptr;

    fileptr = fopen("Records.txt", "a");

    printf("Enter Name of User: ");
    scanf(" %[^\n]s", MyData[0].name);
    printf("Enter Vehicle Number of User: ");
    scanf(" %[^\n]s", MyData[0].NoPlate);
    printf("Enter Registration date of vehicle (DD/MM/YYYY): ");
    scanf(" %[^\n]s", MyData[0].RegDate);
    while (1)
    {
        printf("Enter Type of Vehicle (Light,Medium,Heavy):");
        scanf(" %[^\n]s", MyData[0].VehType);
        printf("Is return included (y/n):");
        scanf(" %c", &MyData[0].retInc);

        if (!strcmp("Light", MyData[0].VehType) || !strcmp("light", MyData[0].VehType))
        {
            if (MyData[0].retInc == 'n')
            {
                printf("Vehicle is light and one side");
                MyData[0].toll = FareDetails[0].ss;
            }
            else
            {
                printf("Vehicle is light and return side");
                MyData[0].toll = FareDetails[0].sr;
            }
            break;
        }
        if (!strcmp("Medium", MyData[0].VehType) || !strcmp("medium", MyData[0].VehType))
        {
            if (MyData[0].retInc == 'n')
            {
                printf("Vehicle is medium and one side");
                MyData[0].toll = FareDetails[1].ss;
            }
            else
            {
                printf("Vehicle is medium and return side");
                MyData[0].toll = FareDetails[1].sr;
            }
            break;
        }
        if (!strcmp("Heavy", MyData[0].VehType) || !strcmp("heavy", MyData[0].VehType))
        {
            if (MyData[0].retInc == 'n')
            {
                printf("Vehicle is heavy and one side");
                MyData[0].toll = FareDetails[2].ss;
            }
            else
            {
                printf("Vehicle is heavy and return side");
                MyData[0].toll = FareDetails[2].sr;
            }
            break;
        }
        else
        {

            printf("**********INVALID INPUT**********\n");
            continue;
        }
    }

    fprintf(fileptr, "%s,%s,%s,%s,%c,%d", MyData[0].name, MyData[0].NoPlate, MyData[0].RegDate, MyData[0].VehType, MyData[0].retInc, MyData[0].toll);

    fclose(fileptr);
    printf("===============================================================================================================\n");

    printf("%-45s%s", "", "RECORD ADDED SUCCESSFULLY\n");
    printf("===============================================================================================================\n");
}
void Update()
{
    FILE *fileptr;
    FILE *fileptr2;

    fileptr = fopen("Records.txt", "r");
    fileptr2 = fopen("temp.txt", "w");

    char srch[10];
    printf("Enter Number plate to search: ");
    scanf("%s", srch);
    int flag = 0;
    for (int i = 0; i < value; i++)
    {
        if (!strcmp(srch, Records[i].NoPlate))
        {
            flag = 1;

            printf("Enter Updated Name of User: ");
            scanf(" %[^\n]s", MyData[0].name);
            printf("Enter Updated Vehicle Number of User: ");
            scanf(" %[^\n]s", MyData[0].NoPlate);
            printf("Enter Updated Registration date of vehicle (DD/MM/YYYY): ");
            scanf(" %[^\n]s", MyData[0].RegDate);
            printf("Enter Updated Type of Vehicle (Light,Medium,Heavy):");
            scanf(" %[^\n]s", MyData[0].VehType);
            printf("Is return included (y/n):");
            scanf(" %c", &MyData[0].retInc);
            if (!strcmp("Light", MyData[0].VehType) || !strcmp("light", MyData[0].VehType))
            {
                if (MyData[0].retInc == 'n')
                {
                    MyData[0].toll = FareDetails[0].ss;
                }
                else
                {
                    MyData[0].toll = FareDetails[0].sr;
                }
            }
            if (!strcmp("Medium", MyData[0].VehType) || !strcmp("medium", MyData[0].VehType))
            {
                if (MyData[0].retInc == 'n')
                {
                    MyData[0].toll = FareDetails[1].ss;
                }
                else
                {
                    MyData[0].toll = FareDetails[1].sr;
                }
            }
            if (!strcmp("Heavy", MyData[0].VehType) || !strcmp("heavy", MyData[0].VehType))
            {
                if (MyData[0].retInc == 'n')
                {
                    MyData[0].toll = FareDetails[2].ss;
                }
                else
                {
                    MyData[0].toll = FareDetails[2].sr;
                }
            }

            fprintf(fileptr2, "%s,%s,%s,%s,%c,%d", MyData[0].name, MyData[0].NoPlate, MyData[0].RegDate, MyData[0].VehType, MyData[0].retInc, MyData[0].toll);
        }
        else
        {
            fprintf(fileptr2, "%s,%s,%s,%s,%c,%d", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, Records[i].retInc, Records[i].toll);
        }
    }
    fclose(fileptr);
    fclose(fileptr2);

    if (flag == 0)
    {
        printf("===============================================================================================================\n");

        printf("%-50s%s", "", "NOT FOUND\n");
        printf("===============================================================================================================\n");
    }
    else
    {

        fileptr2 = fopen("temp.txt", "r");
        fileptr = fopen("Records.txt", "w");
        int i = 0;
        do
        {

            read = fscanf(fileptr2, "%30[^,],%16[^,],%25[^,],%20[^,],%c,%d[^\n]", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, &Records[i].retInc, &Records[i].toll);

            i++;

        } while (i < value);
        fclose(fileptr2);

        for (int i = 0; i < value; i++)
        {
            fprintf(fileptr, "%s,%s,%s,%s,%c,%d", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, Records[i].retInc, Records[i].toll);
        }

        fclose(fileptr);

        printf("===============================================================================================================\n");

        printf("%-45s%s", "", "UPDATED SUCCESSFULLY\n");
        printf("===============================================================================================================\n");
    }

    printf("%d %d\n", FareDetails[1].ss, FareDetails[1].sr);
}
void Delete()
{
    FILE *fileptr;
    FILE *fileptr2;

    fileptr = fopen("Records.txt", "r");
    fileptr2 = fopen("temp.txt", "w");

    char srch[10];
    printf("Enter Number plate to search: ");
    scanf("%s", srch);
    int flag = 0;
    for (int i = 0; i < value; i++)
    {
        if (!strcmp(srch, Records[i].NoPlate))
        {

            flag = 1;
        }
        else
        {

            fprintf(fileptr2, "%s,%s,%s,%s,%c,%d", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, Records[i].retInc, Records[i].toll);
        }
    }
    fclose(fileptr2);
    fclose(fileptr);

    if (flag == 0)
    {
        printf("===============================================================================================================\n");

        printf("%-50s%s", "", "Not Found\n");
        printf("===============================================================================================================\n");
    }
    else
    {

        fileptr2 = fopen("temp.txt", "r");
        fileptr = fopen("Records.txt", "w");
        int i = 0;
        do
        {

            read = fscanf(fileptr2, "%30[^,],%16[^,],%25[^,],%20[^,],%c,%d[^\n]", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, &Records[i].retInc, &Records[i].toll);

            i++;

        } while (!feof(fileptr2));
        fclose(fileptr2);

        for (int i = 0; i < value - 1; i++)
        {
            fprintf(fileptr, "%s,%s,%s,%s,%c,%d", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, Records[i].retInc, Records[i].toll);
        }

        fclose(fileptr);

        printf("===============================================================================================================\n");

        printf("%-45s%s", "", "DELETED SUCCESSFULLY\n");
        printf("===============================================================================================================\n");

        fclose(fopen("temp.txt", "w"));
    }
}
void Search()
{

    FILE *fileptr;

    fileptr = fopen("Records.txt", "r");

    int vall = 0;
    int readd = 0;

    do
    {
        readd = fscanf(fileptr, "%30[^,],%16[^,],%25[^,],%20[^,],%c,%d[^\n]", Records[vall].name, Records[vall].NoPlate, Records[vall].RegDate, Records[vall].VehType, &Records[vall].retInc, &Records[vall].toll);
        if (readd == 6)
        {
            vall++;
        }

    } while (!feof(fileptr));

    fclose(fileptr);

    char srch[10];
    printf("Enter Plate to search: ");
    scanf("%s", srch);
    int flag = 0;

    for (int i = 0; i < value; i++)
    {

        if (!strcmp(srch, Records[i].NoPlate))
        {
            printf("===============================================================================================================\n");
            printf("%-18s%-18s%-20s%-18s%-14s%s", "Name", "Number Plate", "Registration", "Vehicle Type", "Return", "Toll\n");
            printf("===============================================================================================================\n");

            printf("%-18s%-18s%-20s%-18s%-14c%d\n", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, Records[i].retInc, Records[i].toll);

            printf("===============================================================================================================\n");
            flag = 1;
        }
    }

    if (flag != 1)
    {
        printf("==============================================================================================================\n");

        printf("%-35s%s", "", "NOT FOUND\n");
        printf("==============================================================================================================\n");
    }
}
int count = 0;
void Display()
{

    FILE *fileptr;
    value = 0;
    fileptr = fopen("Records.txt", "r");

    do
    {

        read = fscanf(fileptr, "%30[^,],%16[^,],%25[^,],%20[^,],%c,%d[^\n]", Records[value].name, Records[value].NoPlate, Records[value].RegDate, Records[value].VehType, &Records[value].retInc, &Records[value].toll);
        if (read == 6)
        {

            value++;
        }

    } while (!feof(fileptr));
    fclose(fileptr);

    printf("===============================================================================================================\n");
    printf("%-18s%-18s%-20s%-18s%-14s%s", "Name", "Number Plate", "Registration", "Vehicle Type", "Return", "Toll\n");
    printf("===============================================================================================================\n");

    for (int i = 0; i < value; i++)
    {
        printf("%-18s%-18s%-20s%-18s%-14c%d\n", Records[i].name, Records[i].NoPlate, Records[i].RegDate, Records[i].VehType, Records[i].retInc, Records[i].toll);
    }
    printf("===============================================================================================================\n");
}
void clnAll()
{
    fclose(fopen("temp.txt", "w"));
    fclose(fopen("Records.txt", "w"));
    printf("===============================================================================================================\n");

    printf("%-45s%s", "", "CLEANED SUCCESSFULLY\n");
    printf("===============================================================================================================\n");
}
void DISFARE()
{

    printf("\n%-10s%s", "", "Here are the fare details: \n");
    printf("==============================================\n");
    printf("%-18s%-15s%-20s\n", "Vehicle Type", "Fare(Single)", "Fare(Return)");
    printf("==============================================\n");

    printf("%-18s%-15d%-20d\n", "Light", FareDetails[0].ss, FareDetails[0].sr);
    printf("%-18s%-15d%-20d\n", "Medium", FareDetails[1].ss, FareDetails[1].sr);
    printf("%-18s%-15d%-20d\n", "Heavy", FareDetails[2].ss, FareDetails[2].sr);
    printf("==============================================\n\n");
}

void Tottoll()
{
    int toll = 0;

    for (int i = 0; i < TotalRec; i++)
    {
        toll += Records[i].toll;
    }
    printf("\n%-10s%s", "", "Here are the Toll details: \n");
    printf("==============================================\n");
    printf("Total Toll Collected: %d\n", toll);
    printf("==============================================\n\n");
}
int main()
{

    int act;
    printf("===============================================================================================================\n");

    printf("%-35s%s", "", "Welcome to Toll Management System\n");
    printf("===============================================================================================================\n");

    do
    {
        CallFareDetails();
        CallVehRecords();

        printf("What action you want to perform?\n");
        printf("1. Add a Vehicle record\n");
        printf("2. update a record\n");
        printf("3. delete a record\n");
        printf("4. search record\n");
        printf("5. Fetch all records\n");
        printf("6. Clean All records\n");
        printf("7. Display Fare Details \n");
        printf("8. Edit Fare Details \n");
        printf("9. Total Toll Collected\n");
        printf("10. Exit\n");
        printf("--->Enter Action: ");
        scanf("%d", &act);
        getc(stdin);
        if (act == 10)
        {
            printf("===============================================================================================================\n");

            printf("%-45s%s", "", "THANK YOU FOR USING\n");
            printf("===============================================================================================================\n");

            break;
        }

        switch (act)
        {
        case 1:
            Add();
            break;
        case 2:
            Update();
            break;
        case 3:
            Delete();
            break;
        case 4:
            Search();
            break;
        case 5:
            Display();
            break;
        case 6:
            clnAll();
            break;
        case 7:
            DISFARE();
            break;
        case 8:
            Updatefare();
            break;
        case 9:
            Tottoll();
        }

    } while (act != 10);

    return 0;
}
