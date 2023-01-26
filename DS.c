#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX 100000

FILE *fp, *fp1, *fptr;

struct Laptop
{
    char brand[15];
    char model[25];
    int price;
    int processor;
    char series[25];
    int ram;
    int storage;
    float screenSize;
    float weight;
} st[MAX];
void verify_admin();
void main_res();
void getPreferences();
void res(int);
void deleteLaptop();
void modifyLaptop();
void addLaptop();
void admin();
void main_res();
void userRes();
void welcome();
void addLaptop();
void modifyLaptop();
void deleteLaptop();
void display();
void welcome();
void admin();
void main_res();
int totalLaptops = 0;

void oldData()
{
    int i = 0;
    fp = fopen("laptops.txt", "r");
    fp1 = fopen("olddata.txt", "a");
    while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", st[i].brand, st[i].model, &st[i].price, &st[i].processor, st[i].series, &st[i].ram, &st[i].storage, &st[i].screenSize, &st[i].weight) != EOF)
    {
        fprintf(fp1, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
        i++;
    }
    fclose(fp1);
    fclose(fp);
}

void sortLaptops()
{
    // Read laptops from laptops.txt file into memory
    struct Laptop laptops[1000];
    fp = fopen("laptops.txt", "r");
    if (fp == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else
    {
        int i = 0;
        char tempBrand[15], tempModel[25], tempSeries[25];
        int price, processor, ram, storage;
        float screenSize, weight;
        while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", &tempBrand, &tempModel, &price, &processor, &tempSeries, &ram, &storage, &screenSize, &weight) != EOF)
        {
            strcpy(laptops[i].brand, tempBrand);
            strcpy(laptops[i].model, tempModel);
            laptops[i].price = price;
            laptops[i].processor = processor;
            strcpy(laptops[i].series, tempSeries);
            laptops[i].ram = ram;
            laptops[i].storage = storage;
            laptops[i].screenSize = screenSize;
            laptops[i].weight = weight;
            i++;
        }
        fclose(fp);
        totalLaptops = i;

        // Sort laptops array by price using bubble sort
        int j;
        struct Laptop temp;
        for (i = 0; i < totalLaptops - 1; i++)
        {
            for (j = 0; j < totalLaptops - i - 1; j++)
            {
                if (laptops[j].price > laptops[j + 1].price)
                {
                    temp = laptops[j];
                    laptops[j] = laptops[j + 1];
                    laptops[j + 1] = temp;
                }
            }
        }

        // Write sorted laptops back to laptops.txt file
        fptr = fopen("laptops.txt", "w");
        if (fptr == NULL)
        {
            printf("\n\t\tFile opening error");
            exit(0);
        }
        else
        {
            for (i = 0; i < totalLaptops; i++)
            {
                fprintf(fptr, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", laptops[i].brand, laptops[i].model, laptops[i].price, laptops[i].processor, laptops[i].series, laptops[i].ram, laptops[i].storage, laptops[i].screenSize, laptops[i].weight);
            }
            fclose(fptr);
            printf("Laptops sorted successfully by budget!\n");
        }
    }
}

void getPreferences()
{
   
    system("cls");
    int choice;
    printf("\n----------------------------------------------------------------------------\n");
    printf("                     Welcome to Laptop Recommendation Portal");
    printf("\n----------------------------------------------------------------------------\n");
    int budget, processor, ram, storage;
    int maxPrice, minPrice;
    int laptopsFound = 0;
    printf("Enter your budget: ");
    scanf("%d", &budget);
    printf("Enter processor (in GHz): ");
    scanf("%s", &processor);
    printf("Enter RAM (in GB): ");
    scanf("%d", &ram);
    printf("Enter storage (in GB): ");
    scanf("%d", &storage);

    // Read laptops from laptops.txt file and check for matches with user preferences
    fp = fopen("laptops.txt", "r");
    if (fp == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else
    {
        char brand[15], model[25], ser[25];
        int price, proc, r, stor;
        float screen, wt;
        while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", &brand, &model, &price, &proc, &ser, &r, &stor, &screen, &wt) != EOF)
        {
            if (proc >= processor && r >= ram && stor >= storage && price <= budget)
            {
                printf("\nLaptop found: %s %s", brand, model);
                printf("\nPrice: %d", price);
                printf("\nProcessor: %d GHz", proc);
                printf("\nRAM: %d GB", r);
                printf("\nStorage: %d GB", stor);
                printf("\nScreen Size: %d inches", screen);
                printf("\nWeight: %d lbs\n", wt);
                laptopsFound++;
            }
        }
        fclose(fp);

        // If no matches found, suggest 5 laptops near to budget
        if (laptopsFound == 0)
        {
            printf("\nSorry, we couldn't find a perfect match for your preferences.\n");
            printf("Here are laptops near to your budget:\n");
            printf("----------------------------------------------------------------------------");
            minPrice = budget - 1000;
            maxPrice = budget + 1000;

            fp = fopen("laptops.txt", "r");
            if (fp == NULL)
            {
                printf("\n\t\tFile opening error");
                exit(0);
            }
            else
            {
                int laptopsSuggested = 0;
                while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", &brand, &model, &price, &proc, &ser, &r, &stor, &screen, &wt) != EOF)
                {
                    if (price >= minPrice && price <= maxPrice && laptopsSuggested < 5)
                    {
                        printf("\n%s %s\nPrice: %d", brand, model, price);
                        laptopsSuggested++;
                    }
                }
                fclose(fp);
                if (laptopsSuggested == 0)
                {
                    printf("\nSorry, we couldn't find any laptops near to your budget. Please try again with a different budget.\n");
                }
            }
        }
    }
    userRes();
}

void userRes()
{
    char add;
    printf("\n----------------------------------------------------------------------------\n");
    printf("\n\tWant to Search Another Laptop \n");
    printf("Enter(y/n) :\t");
    scanf(" %c", &add);
    printf("\n----------------------------------------------------------------------------\n");
    if (add == 'y')
        getPreferences();
    else if (add == 'n')
    {
        main_res();
    }
}

void welcome()
{
    system("cls");
    int choice;
    printf("\n----------------------------------------------------------------------------\n");
    printf("                     Welcome to Laptop Recommendation Portal");
    printf("\n----------------------------------------------------------------------------\n");
    printf("\n\tSelect Mode as follows: \n\t\t1.Admin\n\t\t2.Customer\n\t\t3.Exit");
    printf("\n----------------------------------------------------------------------------\n");
    printf("\t\tEnter (1/2) :\t");
    scanf("%d", &choice);
    printf("----------------------------------------------------------------------------\n");
    printf("\n");
    if (choice == 1)
    {
        verify_admin();
        admin();
    }
    else if (choice == 2)
        getPreferences();
    else if (choice == 3)
    {
        printf("\t    *********Laptop Recommendation Portal Terminated*********\n\n");
    }
    else
    {
        printf("Select valid choice");
        welcome();
    }
}

void main_res()
{
    char Main_res;
    printf("\tWant to Go to Main Portal-->\n \t\tEnter(y/n) : ");
    scanf(" %c", &Main_res);
    printf("----------------------------------------------------------------------------\n\n");
    if (Main_res == 'y')
        welcome();
    else if (Main_res == 'n')
        printf("\t    *********Laptop Recommendation Portal Terminated*********\n\n\n");
}

void res(int num)
{
    char Admin_res, Main_res;
    if (num == 0)
    {
        printf("Want to Go to Admin Mode :\n\tEnter(y/n) :\t");
        scanf(" %c", &Admin_res);
        if (Admin_res == 'y')
            admin();
        else if (Admin_res == 'n')
            main_res();
    }
}

void addLaptop()
{
    char Admin_res, Main_res, add;
    int add_num;
    float screenSize, weight;
    // Append new laptop information to laptops.txt file
    fp = fopen("laptops.txt", "a");
    if (fp == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else
    {
        printf("\n----------------------------------------------------------------------------\n");
        printf("\tNo. of Laptops do you want to add : ");
        scanf("%d", &add_num);
        printf("----------------------------------------------------------------------------\n");
        for (int i = 0; i < add_num; i++)
        {
            printf("Enter brand: ");
            scanf("%s", st[i].brand);
            printf("Enter model: ");
            scanf("%s", st[i].model);
            printf("Enter price: ");
            scanf("%d", &st[i].price);
            printf("Processor:\n\t1.Intel I3 or Ryzen 3\n\t2.Intel I5 or Ryzen 5\n\t3.IntelI7 or Ryzen 7\n\t\tEnter(1/2/3) :\t");
            scanf("%d", &st[i].processor);
            printf("Enter Specific Series: ");
            scanf("%s", st[i].series);
            printf("Enter RAM (in GB): ");
            scanf("%d", &st[i].ram);
            printf("Enter storage (in GB): ");
            scanf("%d", &st[i].storage);
            printf("Enter screen size (in inches): ");
            scanf("%f", &st[i].screenSize);
            printf("Enter weight (in KG): ");
            scanf("%f", &st[i].weight);
            printf("\n----------------------------------------------------------------------------\n");

            fprintf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
        }
    }
    fclose(fp);
    printf("\nLaptop added successfully!\n");
    oldData();
    sortLaptops();
    printf("----------------------------------------------------------------------------\n");
    printf("\tWant to Add More Entries of Laptop");
    printf("\n----------------------------------------------------------------------------\n");
    printf("\tEnter(y/n) :\t");
    scanf(" %c", &add);
    printf("\n----------------------------------------------------------------------------\n");
    if (add == 'y')
        addLaptop();
    else if (add == 'n')
        res(0);
}

void modifyLaptop()
{
    oldData();
    fp = fopen("laptops.txt", "r");
    fp1 = fopen("tempModify.txt", "w"); // temprary file
    if (fp == NULL && fp1 == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else
    {
        int i = 0;
        int flag = 0;
        char brand[15], model[25], series[25], add;
        int price, processor, ram, storage;
        float screenSize, weight;
        printf("Enter brand of laptop to modify: ");
        scanf("%s", brand);
        printf("Enter model of laptop to modify: ");
        scanf("%s", model);

        // Read laptops from laptops.txt file into memory
        while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", st[i].brand, st[i].model, &st[i].price, &st[i].processor, st[i].series, &st[i].ram, &st[i].storage, &st[i].screenSize, &st[i].weight) != EOF)
        {
            if (strcmp(st[i].brand, brand) == 0 && strcmp(st[i].model, model) == 0)
            {
                printf("Enter new price: ");
                scanf("%d", &price);
                printf("Processor:\n\t1.Intel I3 or Ryzen 3\n\t2.Intel I5 or Ryzen 5\n\t3.IntelI7 or Ryzen 7\n\t\tEnter(1/2/3) :\t");
                scanf("%d", &processor);
                printf("Enter Specific Series of Processor:");
                scanf("%s", &series);
                printf("Enter new RAM (in GB): ");
                scanf("%d", &ram);
                printf("Enter new storage (in GB): ");
                scanf("%d", &storage);
                printf("Enter new screen size (in inches): ");
                scanf("%f", &screenSize);
                printf("Enter new weight (in lbs): ");
                scanf("%f", &weight);

                // writing in temporary file
                fprintf(fp1, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, price, processor, series, ram, storage, screenSize, weight);
                printf("Laptop modified successfully!\n");
                flag = 1;
            }
            else
                fprintf(fp1, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
            i++;
        }
        if (flag == 0)
        {
            printf("Details not Matched !\n\tNot Found\n");
        }
        fclose(fp);
        fclose(fp1);

        // Write laptops back to laptops.txt file
        fp = fopen("laptops.txt", "w");
        fp1 = fopen("tempModify.txt", "r");
        if (fp == NULL && fp1 == NULL)
        {
            printf("\n\t\tFile opening error");
            exit(0);
        }
        else
        {
            i = 0;
            while (fscanf(fp1, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", st[i].brand, st[i].model, &st[i].price, &st[i].processor, st[i].series, &st[i].ram, &st[i].storage, &st[i].screenSize, &st[i].weight) != EOF)
            {
                fprintf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
                i++;
            }
        }
        fclose(fp);
        fclose(fp1);
        sortLaptops();
        printf("\n----------------------------------------------------------------------------\n");
        printf("\n\tWant to Modify More Entries of Laptop \n");
        printf("Enter(y/n) :\t");
        scanf(" %c", &add);
        printf("\n----------------------------------------------------------------------------\n");
        if (add == 'y')
            modifyLaptop();
        else if (add == 'n')
            res(0);
    }
}

void deleteLaptop()
{
    char add;
    fp = fopen("laptops.txt", "r");
    fp1 = fopen("tempDelete.txt", "w"); // temprary file
    if (fp == NULL && fp1 == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else
    {
        int i = 0;
        int flag = 0;
        char brand[15], model[25], series[25];
        int price, processor, ram, storage;
        float screenSize, weight;
        printf("Enter brand of laptop to modify: ");
        scanf("%s", brand);
        printf("Enter model of laptop to modify: ");
        scanf("%s", model);

        // Read laptops from laptops.txt file into memory
        while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", st[i].brand, st[i].model, &st[i].price, &st[i].processor, st[i].series, &st[i].ram, &st[i].storage, &st[i].screenSize, &st[i].weight) != EOF)
        {
            if (strcmp(st[i].brand, brand) == 0 && strcmp(st[i].model, model) == 0)
            {
                printf("Laptop Found & Deleted Successfully");
                flag = 1;
            }
            else
                fprintf(fp1, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
            i++;
        }
        if (flag == 0)
        {
            printf("Details not Matched !\n      Not Found");
        }
        fclose(fp);
        fclose(fp1);
        // Write laptops back to laptops.txt file
        fp = fopen("laptops.txt", "w");
        fp1 = fopen("tempDelete.txt", "r");
        if (fp == NULL && fp1 == NULL)
        {
            printf("\n\t\tFile opening error");
            exit(0);
        }
        else
        {
            i = 0;
            while (fscanf(fp1, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", st[i].brand, st[i].model, &st[i].price, &st[i].processor, st[i].series, &st[i].ram, &st[i].storage, &st[i].screenSize, &st[i].weight) != EOF)
            {
                fprintf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
                i++;
            }
        }
        fclose(fp);
        fclose(fp1);
        sortLaptops();
    }
    printf("\n----------------------------------------------------------------------------\n");
    printf("\n\tWant to Delete More Entries of Laptop \n");
    printf("Enter(y/n) :\t");
    scanf(" %c", &add);
    printf("\n----------------------------------------------------------------------------\n");
    if (add == 'y')
        deleteLaptop();
    else if (add == 'n')
        res(0);
}

void display()
{
    int i;
    fp = fopen("laptops.txt", "r");
    if (fp == NULL)
    {
        printf("\n\t\tFile opening error");
        exit(0);
    }
    else
    {
        i = 0;
        printf("\n\tBrand\tModel\tPrice\tProcessor Series\tRam\tStorage\tScreen   \tWeight");
        printf("\n-----------------------------------------------------------------------------------------------------\n");
        while (fscanf(fp, "%s\t%s\t%d\t%d\t%s\t%d\t%d\t%f\t%f", st[i].brand, st[i].model, &st[i].price, &st[i].processor, st[i].series, &st[i].ram, &st[i].storage, &st[i].screenSize, &st[i].weight) != EOF)
        {
            printf("\t%s\t%s\t%d\t%d        %s    \t%d\t%d\t%f\t%f\n", st[i].brand, st[i].model, st[i].price, st[i].processor, st[i].series, st[i].ram, st[i].storage, st[i].screenSize, st[i].weight);
            i++;
        }
        fclose(fp);
    }
    printf("\n");
}

void admin()
{
    int choice, num;
    // Admin mode
    system("cls");
    printf("\n----------------------------------------------------------------------------\n");
    printf("                        Entered in Admin Mode");
    printf("\n----------------------------------------------------------------------------\n");
    printf("\n\tSelect an option: \n\t1. Add a laptop\n\t2. Modify a laptop\n\t3. Delete a laptop\n\t4. Display a laptop\n\t5. Main Menu\n");
    printf("----------------------------------------------------------------------------\n");
    printf("\tEnter (1/2/3/4/5) :\t");
    scanf("%d", &choice);
    printf("----------------------------------------------------------------------------\n");
    if (choice == 1)
    {
        addLaptop();
    }
    else if (choice == 2)
    {
        modifyLaptop();
    }
    else if (choice == 3)
    {
        deleteLaptop();
    }
    else if (choice == 4)
    {
        num = 0;
        display();
        res(num);
    }
    else if (choice == 5)
    {
        main_res();
    }
    else
    {
        printf("Invalid choice\n");
        admin();
    }
}

void verify_admin()
{
    char ch;
    char Admin_name[20], Admin_pass[20], saved_name[20] = "Nikhil", saved_pass[20] = "NK123@";
name:
    printf("Enter Username : \t");
    scanf("%s", Admin_name);

    fptr = fopen("Admin.txt", "r");
    // {
    //     fprintf(fptr,"%s\t%s",saved_name,saved_pass);
    // }
    // fclose(fptr);

    fscanf(fptr, "%s\t%s", saved_name, saved_pass);
    if (strcmp(Admin_name, saved_name) != 0)
    {
        printf("\n\tIncorrect Username\n \tPlease Try Again\n\n");
        goto name;
    }
    else
    {
    start:
        printf("Enter Password : \t");
        int i = 0;
        while (1)
        {
            ch = getch();
            if (ch == 13) // Ascii valur of Enter
            {
                Admin_pass[i] = '\0';
                break;
            }
            else if (ch == 8) // AsCII value of Backspace
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if (ch == 9 || ch == 32) // ASCII value of tab and space
            {
                continue;
            }
            else
            {
                Admin_pass[i++] = ch;
                printf("*");
            }
        }
        int l = strcmp(Admin_pass, saved_pass);
        if (l == 0)
        {
            printf("\n#### LOGIN SUCCESSFULL ####\n");
        }
        else
        {
            printf("\n\n\tINCORRECT PASSWORD\n\n");
            goto start;
        }
    }
}

int main()
{
    welcome();
    
}
