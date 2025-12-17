#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
 
void listContacts(AddressBook *addressBook,int sortCriteria ) {
    // Sort contacts based on the chosen criteria
  printf(YELLOW"---------------------------------------------------------------------------\n");
  printf("%-8s %-20s %-20s %-30s\n","Slno.","Name","Contact","Email");  // prompt for Column headings
  printf("---------------------------------------------------------------------------\n");
    for(int j=0;j<addressBook->contactCount;j++) // Loop through all contacts
    { printf("%-8d %-20s %-20s %-30s\n",j+1,addressBook->contacts[j].name,addressBook->contacts[j].phone,addressBook->contacts[j].email); }   // Print contact details 
    printf("---------------------------------------------------------------------------\n"RESET);
}

void initialize(AddressBook *addressBook) {
     loadContactsFromFile(addressBook);
  }

  int arr[50];int m=0;int notfound=0;  // Global variables for search,edit and delete operations

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
  }
  
void createContact(AddressBook *addressBook) //function for creating a contact
{
    /* Define the logic to create a Contacts */
  char nname[50];
  loop1:           //goto loop          
  printf("Enter Name: ");   //prompt for entering name
  getchar();     // Clear input buffer since using selective scanf
  scanf("%[^\n]",nname);  // Read full name with spaces
  int res=namevalidate(nname); //passing to validate function for validating name
  if(res==0){goto loop1; }              // Retry if invalid
  strcpy(addressBook->contacts[addressBook->contactCount].name,nname);  // Store name in Addressbook
      
  char nphone[10];
  loop2:
  printf("Enter Phone: ");getchar(); //enter phone
  scanf("%[^\n]",nphone); // Read phone number and clear buffer if space contains
  res =phonevalidate(nphone,addressBook); // Validate phone number
  if(res==0){ goto loop2; }   // Retry if invalid
  
  char nemail[50];
  loop3:
  printf("Enter Email: "); //enter email
  scanf("%s",nemail); //while(getchar()!='\n');// Read email and clear buffer if space contains
  res =emailvalidate(nemail,addressBook);  // Validate email
  if(res==0){goto loop3;}  // Retry if invalid
  
  strcpy(addressBook->contacts[addressBook->contactCount].phone,nphone); // Save phone in addressbook
  strcpy(addressBook->contacts[addressBook->contactCount].email,nemail); // Save Email in addressbook
  printf(GREEN"Contact Added Successfully ✔\n"RESET);
  addressBook->contactCount++; //saveContactsToFile(addressBook);  // Increase total count
}
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
  up:       // Label for menu repeat
    int n;m=0;notfound=0; //intialize variable to '0'
    printf("\nSearch by using\n"); //prompt message to choose option
    printf("1.Name\n");printf("2.Phone\n"); printf("3.Email\n");
    printf("4.Exit\nChoose option: ");
    scanf("%d",&n);while(getchar()!='\n');//clear buffer if we entered invalid datatype or exceeded format
    switch(n) //switch case for selecting particular option based on user choice
    {
        case 1:
        { loopn:
          printf("Enter name: "); //enter name for searching
          char na[50];
          //getchar(); //clear buffer since using selective scanf
          scanf("%[^\n]",na);getchar();
          int res=namevalidate(na);       // Validate name
          if(res==0)
          { goto loopn;}  //if invalid re-enter name
          
          int flag=0;printf("\n");
          for (int i=0;i<addressBook->contactCount;i++)       // Loop through all contacts
          {
            if(strcasestr(addressBook->contacts[i].name,na)!=NULL)   // Search by Name and get into loop if matches
            {
                flag++;
                printf(WHITE"%-8d %-20s %-20s %-30s\n"RESET,m+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                arr[m++]=i; // Store matched index in global array
            }
          }
          if(flag==0)
          {printf(RED"Person Not Found.\n"RESET);notfound=1;}   // If not found
          break;
        }
        case 2:
        {
          printf("Enter phone: ");
          char p[20];
          //getchar();
          scanf("%s",p);while(getchar()!='\n');
          int flag=0;printf("\n");
          for (int i=0;i<addressBook->contactCount;i++)
          {
            if(strcmp(addressBook->contacts[i].phone,p)==0)    // Search by phone and get into loop if matches
            {
                flag=1;
                printf(WHITE"%-8d %-20s %-20s %-30s\n"RESET,m+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                arr[m++]=i; //storing matched index in array declared in global scope
            }
          }
          if(flag==0)
          {printf(RED"Person Not Found.\n"RESET);notfound=1; } //prompt if not found
          break;
        }
        case 3:
        {
          printf("Enter email: ");
          char e[50];
          //getchar();
          scanf("%s",e);while(getchar()!='\n');
          int flag=0;printf("\n");
          for (int i=0;i<addressBook->contactCount;i++)
          {
            if(strcmp(addressBook->contacts[i].email,e)==0)      // Search by Email and get into loop if matches
            {
                flag=1;
                printf(WHITE"%-8d %-20s %-20s %-30s\n"RESET,m+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                arr[m++]=i; //storing matched index
            }
          }
          if(flag==0)
          {  printf(RED"Person Not Found.\n"RESET);notfound=1;}
          break;
        }
        case 4:{notfound=1; return;}      // Exit search
        default:{ printf(RED"Wrong Option!\n"RESET);
          goto up;break; }      // Repeat menu//return;
    } //
}

void editContact(AddressBook *addressBook)
{
  searchContact(addressBook);          // Search first  
  int num,j=0,i=arr[0];    //intialize variable for selecting contact for editing 
   if(m>=2){  //m is index position of globally declared array
    printf("Enter Slno.: ");
    scanf("%d",&num);
    while (getchar() != '\n'); //clear buffer if are entering invalid format
    for(j=0;j<m;j++)
    {
        if(num==j+1)  // Check selected index
        {i=arr[j];  // Store actual index
          break;}
    }
    if(j==m)
    { printf(RED"wrong input"RESET);
    return; } }
    if(notfound!=1){
    printf("what needs to be modified ?\n");printf("1.Name\n");printf("2.Phone\n");printf("3.Email\n");printf("4.Exit\n");
    int op;
    printf("Enter option: "); //choose option for editing
    scanf("%d",&op);//getchar();
    switch(op) //switch case
      {
        case 1:
        {
        loopc1:
        char newname[20];
        printf("Enter new name: ");getchar();  //new name for modification
        scanf("%[^\n]",newname);
        int res=namevalidate(newname);  //validate
        if(res==0){goto loopc1;}
        strcpy(addressBook->contacts[i].name,newname);      // Update name
        printf(GREEN"Updated successfully ✔\n"RESET);break;
        }
        case 2:
        {
        loopc2:
        char newphone[20];
        printf("Enter new phone : "); //new phone for modification
        scanf("%s",newphone);while(getchar()!='\n');
        int res=phonevalidate(newphone,addressBook); //validate
        if(res==0){goto loopc2;}
        strcpy(addressBook->contacts[i].phone,newphone);        // Update Phone
        printf(GREEN"Updated successfully ✔\n"RESET);break;
        }
        case 3:
        {
        loopc3:
        char newemail[20];
        printf("Enter new email: ");
        scanf("%s",newemail);while(getchar()!='\n');
        int res =emailvalidate(newemail,addressBook);
        if(res==0){goto loopc3;}
        strcpy(addressBook->contacts[i].email,newemail);          // Update Email
        printf(GREEN"Updated successfully ✔\n"RESET);break;
        }
        case 4:{return;}
        default:printf(RED"Wrong Option"RESET);
      }
      return;}
 }   
 
void deleteContact(AddressBook *addressBook)
{
    searchContact(addressBook);       // using search before delete
    int num,j=0,i=arr[0]; //variable for selecting contact to delete, intializze 'i' with 1st element in array(if ony 1 ement is found after searching)
    if(m>=2){
      printf("Enter Slno.: "); //choose which contact to delete
      scanf("%d",&num);
      while(getchar()!='\n'); //clear buffer
      for(j=0;j<m;j++)
      {
          if(num==j+1)  // Check entered index
          {i=arr[j];  // Map to actual record
            break;}
      }
      if(j==m)
      { printf(RED"Wrong Input!"RESET);
      return; }
    }
    char c;
    if(notfound!=1){
    printf(RED"Do you want to delete(Y/N): "RESET);//getchar();
    scanf("%c",&c); 
    if(c=='Y' || c=='y'){   // Confirm delete
    for(int k=i;k<addressBook->contactCount;k++)
      { addressBook->contacts[k]=addressBook->contacts[k+1];}       // Shift remaining contacts
    addressBook->contactCount--;printf(GREEN"Deleted succesfully ✔\n"RESET);}    // Decrease count
    else if(c=='N'||c=='n'){printf(RED"Operation Terminated!\n"RESET); //condition to terminate delete operation
      return;}
    else{printf(RED"Wrong Input!\n"RESET);return;}}
    notfound=0; //update variable so no issue when called again.
}

int namevalidate(char nname[])      // Function to validate name
{
   if(nname[0]==32 || nname[0]=='\n'){printf(RED"Please enter a valid name!\n"RESET);return 0;}
   for (int i = 0; nname[i] != '\0'; i++){
        if (!isalpha(nname[i]) && nname[i] != ' ') //check for only alphabets and spaces
        { printf(RED"Please enter a valid name!\n"RESET);
            return 0; } // Invalid character 
    }return 1; // Valid name
}

int phonevalidate(char nphone[],AddressBook *addressBook)     // Function to validate Phone
{
  int flag=0; //int set=0;
  for(int i=0;i<addressBook->contactCount;i++)
  {
    if(strcmp(addressBook->contacts[i].phone,nphone)==0){printf(RED"Entered number already exists in Addresbook!\n"RESET);return 0;} // strcmp(str1,str2)==0 (if present) // Check for duplicates
  }
  for(int i=0;i<10;i++) // Check if all digits
  { 
    if(nphone[i]<=57 && nphone[i]>=48){ flag++; }
  }
  if(nphone[0]=='0' || flag!=10  || strlen(nphone)!=10) //check if number starts with "0" or length not equal "10"
  {
    printf(RED"Enter valid number!\n"RESET); return 0;
  } 
}

int emailvalidate(char nemail[],AddressBook *addressBook)       // Function to validate Email
{
  int flag=0,len=0,flag2=0,flag3=0,len2=0,flag4=0;
  for(int i=0;i<addressBook->contactCount;i++)
  {
    if(strcmp(addressBook->contacts[i].email,nemail)==0){printf(RED"Entered mail ID already exists in Addresbook!\n"RESET);return 0;} // strcmp(str1,str2)==0 (if present)   // Check for duplicates
  }
  if(strchr(nemail,'@')!=NULL && (strlen(nemail) >= 4 && strcmp(&nemail[strlen(nemail) - 4], ".com") == 0) && (nemail[0]>='a' && nemail[0]<='z'))  //check for "@",".com" and test email start with digit
  {flag2=1;}//else{goto loop3;}
  while(nemail[len]!='@') //finding length till '@' for validating alphabets and numbers only contained before '@'.
  {
    len++;
  }
  for(int i=0;nemail[i]!='@';i++)  //check for digits and small alphabet contained between start and @
  {
    if((nemail[i]>=97 && nemail[i]<=122) || (nemail[i]>=48 && nemail[i]<=57))
    {flag++;}
  }
  for(int i=len+1;i<strlen(nemail);i++){if(nemail[i]=='.'){flag4++;}}  //flag4=1 only one '.' is present after @.
  for(int i=len+1;nemail[i]!='.';i++)
  { //if(nemail[i+1]=='.'){flag2=0;}
    len2++;
    if((nemail[i]>=97 && nemail[i]<=122)) //check for only alphabets after '@' and '.com'
    { flag3++;}
  }
  if(flag!=len || flag2==0 || flag3!=len2 || len2==0 || flag4!=1)   //invalid condition
  {printf(RED"Invalid\n"RESET);return 0; } 
} 
