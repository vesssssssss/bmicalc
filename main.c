#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct BMIHistory
{
char name[20];
float height;
float weight;
float bmi;

struct BMIHistory* next;
};

float inputUserHeight();
float inputUserWeight();
void calculateBMI(struct BMIHistory **head);
void showStatistics();
void displayHistory(struct BMIHistory **head);
void delete(struct BMIHistory **head, char name[]);
void purple();
void printMenu();
void printHeart();

FILE *fp;
int main()
{
struct BMIHistory *head=NULL;
int option;
char name [20], name1[20];
float height, weight;
do {
        printMenu();
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                calculateBMI(&head);
                break;
            case 2:
                showStatistics();
                break;
            case 3:
                displayHistory(&head);
                break;
            case 4:
                printf("Enter the name corresponding to the calculation you want to delete: ");
                scanf("%s", name);
                delete(&head, name);
                break;
            case 5:
                printf("Thank you for using S&V BMI Calculator!\n");
                printHeart();
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        printf("\n");
    } 
    while (option != 5);
    return 0;
}
 
void purple()
{
printf("\033[0;35m");
}

void printMenu()
{
    printf("\n");
    purple();
    printf("*************************************\n");
    printf("* Welcome to S&V BMI Calculator!    *\n");
    printf("* This program calculates your BMI  *\n");
    printf("* based on your height and weight.  *\n");
    printf("* BMI is a measure of body fat      *\n");
    printf("* based on your weight and height   *\n");
    printf("* ratio. It provides an indication  *\n");
    printf("* of whether you are underweight,   *\n");
    printf("* normal weight, overweight, or     *\n");
    printf("* obese.                            *\n");
    printf("*************************************\n");
    printf("* MENU                              *\n");
    printf("*                                   *\n");
    printf("* 1. Calculate your BMI             *\n");
    printf("* 2. Find BMI range and get advice  *\n");
    printf("* 3. Display history                *\n");
    printf("* 4. Delete in history              *\n");
    printf("* 5. Exit                           *\n");
    printf("*************************************\n");
    printf("\n");
}

void printHeart() {
    printf("\n");
    printf("   ***    ***                   \n");
    printf("  *****  *****                  \n");
    printf(" **************                 \n");
    printf("****************                 \n");
    printf(" **************                  \n");
    printf("   **********             \n");
    printf("     ******               \n");
    printf("       **    \n");
}


float inputUserHeight()
{
float height;
int h_number;
printf("Please choose the desired unit:\n\
1. Inches(in)\n\
2. Centimeters (cm): \n ");
scanf("%d", &h_number);
if (h_number==1)
{
printf("Please enter your height: ");
scanf("%f", &height);
if(height<=0)
{
printf("Invalid input!");
}
height=height*2.54;
}
else if (h_number==2)
{
printf("Please enter your height: ");
scanf("%f", &height);
if(height<=0)
{
printf("Invalid input!");
}
}
return height;
}
 

float inputUserWeight()
{
float weight;
int w_number;
printf("Please choose the desired unit:\n\
1. Pounds(lb)\n\
2. Kilograms (kg): \n ");
scanf("%d", &w_number);
if (w_number==1)
{
printf("Please enter your weight: ");
scanf("%f", &weight);
if(weight<=0)
{
printf("Invalid input!");
}
weight=weight/2.205;
}
else if (w_number==2)
{
printf("Please enter your weight: ");
scanf("%f", &weight);
if(weight<=0)
{
printf("Invalid input!");
}
}
return weight;
}

void calculateBMI(struct BMIHistory **head)
{
char name1[15];
printf("Please enter your name: ");
scanf("%s",name1);
float height=inputUserHeight();
float weight=inputUserWeight();
float BMI=weight/((height/100)*(height/100));
printf("Your BMI is: %f", BMI);
struct BMIHistory* newNode = (struct BMIHistory*)malloc(sizeof(struct BMIHistory));
newNode->height = height;
newNode->weight = weight;
newNode->bmi = BMI;
strcpy(newNode->name,name1);
newNode->next = NULL;
if (*head == NULL) {
*head = newNode;
} else {
struct BMIHistory* curr = *head;
while (curr->next != NULL) {
curr = curr->next;
}
curr->next = newNode;
}
fp = fopen("bmi_history.txt", "a");
if (fp == NULL) {
printf("Cannot open file!\n");
return;
}
fprintf(fp,"%s %.2f %.2f %.2f\n", newNode->name, newNode->height, newNode->weight, newNode->bmi);
fclose(fp);
}

void showStatistics()
{
printf("Enter your bmi to see the category you fall into: \n");
float bmi;
scanf("%f", &bmi);
printf("If you want advice based on your result press 1 if not press 0: \n");
int option;
scanf("%d", &option);
if (bmi < 18.5) {
printf("Category: Underweight\n");
if (option) {
printf("Based on your BMI, you are underweight. It's important to focus on gaining weight in a healthy way. Consider the following advice:\n\
- 1. Consult a nutritionist or dietitian to create a balanced meal plan that could help you gain weight.\n\
- 2. Include nutrient-rich foods in your diet such as lean proteins, whole grains, fruits, and vegetables.\n\
- 3. Regularly engage in strength training exercises to build muscle mass.\n\
- 4. Prioritize adequate sleep and manage stress levels for overall well-being.");
}
} else if (bmi >= 18.5 && bmi < 25.0) {
printf("Category: Normal weight\n\n");
if (option) {
printf("Congratulations! Your BMI falls within the normal weight range. To maintain your current weight and overall health, consider the following advice:\n\
- 1. Maintain a balanced diet with a variety of nutrient-rich foods.\n\
- 2. Engage in regular physical activity to support cardiovascular fitness and muscle strength.\n\
- 3. Prioritize mental well-being through stress management techniques and self-care activities.\n\
- 4. Monitor your weight periodically and make adjustments to your lifestyle if necessary.");
}
} else if (bmi >= 25.0 && bmi < 30.0) {
printf("Category: Overweight\n\n");
if (option) {
printf("It appears that you are in the overweight category based on your BMI. It's important to focus on maintaining a healthy weight to reduce the risk of various health conditions. Consider the following advice:\n\
- 1. Consult a healthcare professional or registered dietitian to create a personalized weight management plan.\n\
- 2. Incorporate more fruits, vegetables, whole grains, and lean proteins into your diet.\n\
- 3. Engage in regular aerobic exercise and strength training to support weight loss and overall fitness.\n\
- 4. Practice portion control and mindful eating to manage calorie intake.\n\
- 5. Seek support from a healthcare professional, support groups, or weight loss programs if needed.");
}
} else {
printf("Category: Obese\n\n");
if (option) {
printf("Based on your BMI, it appears you are in the obese category. Obesity can have significant health implications, and it's important to address weight management for overall well-being. Consider the following advice:\n\
- 1. Consult a healthcare professional or registered dietitian to develop a comprehensive weight loss plan.\n\
- 2. Emphasize a balanced diet with portion control and a focus on whole, unprocessed foods.\n\
- 3. Engage in regular physical activity to support weight loss and improve overall fitness.\n\
- 4. Seek social support and consnameer joining weight management programs or support groups.\n\
- 5. Monitor progress regularly and celebrate small achievements along the way.");
}
}
}
 
void displayHistory(struct BMIHistory **head)
{
printf("If you want to display all history press 1.\n\
If you want to recall a calculation press 2\n");
int option;
scanf("%d", &option);
if (option==1)
{
char c;
fp=fopen("bmi_history.txt", "r");
if(fp == NULL) {
printf("Cannot open file!");
}
else {
c = fgetc(fp);
while (c != EOF) {
printf ("%c", c);
c = fgetc(fp);
}
fclose(fp);
}
}
else if (option==2)
{
char name[20];
printf("Enter name: ");
scanf("%s", name);
struct BMIHistory *curr=NULL, *prev=NULL,* newNode=NULL;
fp = fopen("bmi_history.txt", "r");
if (fp == NULL) {
printf("Cannot open file!\n");
return;
}
while(!feof(fp)){
newNode = (struct BMIHistory*)malloc(sizeof(struct BMIHistory));
fscanf(fp,"%s %f %f %f", (newNode->name), &(newNode->height), &(newNode->weight), &(newNode->bmi));
//printf("%s %.2f %.2f %.2f", (newNode->name), (newNode->height), (newNode->weight), (newNode->bmi));
if(strcmp(newNode->name, name)==0)
    {
    printf("%s %.2f %.2f %.2f", (newNode->name), (newNode->height), (newNode->weight), (newNode->bmi));
    }
    newNode->next=NULL;
    if (*head == NULL) {
    *head = newNode;
    curr = newNode;
    }
    else {
    curr->next = newNode;
    curr = newNode;
    }
    newNode=curr->next;
}
curr = *head;
    struct BMIHistory *temp;

    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}
fclose(fp);
}
 
void delete(struct BMIHistory **head, char name[]) {
    struct BMIHistory *curr = *head;
    struct BMIHistory *prev = NULL;
    struct BMIHistory *temp = NULL;
    int found = 0;
 
    fp = fopen("bmi_history.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        return;
    }
 
    while (!feof(fp)) {
        temp = (struct BMIHistory*)malloc(sizeof(struct BMIHistory));
        fscanf(fp, "%s %f %f %f", temp->name, &(temp->height), &(temp->weight), &(temp->bmi));
        temp->next = NULL;
 
        if (*head == NULL) {
            *head = temp;
            curr = temp;
        } else {
            curr->next = temp;
            curr = temp;
        }
    }
 
    fclose(fp);
 
    curr = *head;
 
    if (curr == NULL) {
        printf("The list is empty.\n");
        return;
    }
 
    if (strcmp(curr->name, name) == 0) {
        *head = curr->next;
        free(curr);
        printf("History with name %s has been canceled.\n", name);
        found = 1;
    } else {
        while (curr != NULL && strcmp(curr->name, name) != 0) {
            prev = curr;
            curr = curr->next;
        }
 
        if (curr != NULL) {
            prev->next = curr->next;
            free(curr);
            printf("History with name %s has been canceled.\n", name);
            found = 1;
            //return;

        }
    }
 
    if (!found) {
        printf("History with name %s not found.\n", name);
        return;
    }
 
    fp = fopen("bmi_history.txt", "w");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        return;
    }
 
    curr = *head;
    while (curr != NULL) {
        fprintf(fp, "%s %.2f %.2f %.2f\n", curr->name, curr->height, curr->weight, curr->bmi);
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
 
    fclose(fp);
}