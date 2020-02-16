/*****************************************************************
//
//  NAME:		Ehsan Kourkchi
//
//  HOMEWORK:		Project 2
//
//  CLASS:		ICS 212
//
//  INSTRUCTOR:		Ravi Narayan
//
//  DATE:		November 28, 2013           
//
//  FILE:		database2.cpp        
//
//  DESCRIPTION:	This file contains the user-interface and functions 
//			to handle a database [Project 2] 
//
//****************************************************************/
// To compile the program:
// $ make all
// $ ./database2
// or
// $ ./database2 debug
//****************************************************************/

#include <iostream>
using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>



#ifndef RECORD
#include "record.h"
#endif 


#ifndef LLIST
#include "llist.h"
#endif 



/*****************************************************************/
// GLOBAL VARIABLES */

 int debugmode = 0;

/****************************************************************/
// Function declarations
int main_menu();
int addData(llist &list);
int modifyData(llist &list);
int removeData(llist &list);
int printData(llist &list);
int reverseList(llist &list);
int getdata(char name[], char address[], int &yearofbirth, char telno[]);
int getdata_modify(char name[], char address[], char telno[]);
int arguments(int argc, char *argv[]);
/****************************************************************/





/**
 * User interface for this Database
 * 
 * @param argc number of arguments
 * @param argv the array holding the arguments
 * 
 * @use llist object to hold data
 * 
 */

int main(int argc, char *argv[]) 
{
  
  int check, menu;
  int exit_program=0;
  
  
llist mylist("Database.txt");  
  
 
if (arguments(argc, argv) == 1)  // wrong arguments
  return 1;


do {
  
menu = main_menu();
switch (menu)
{
   case 1: // add
     addData(mylist);
     break;
   case 5:  // print all
     cout << mylist;
     break;
   case 2: // modify
     modifyData(mylist);
     break;
   case 4: // print / find
     printData(mylist);
     break;
   case 3:  // remove
     check = removeData(mylist);
     break;
  case 6:  // exit
    exit_program=1;
    break;
  case 7:  // reverse list
    reverseList(mylist);
    break;
}
 

} while(exit_program == 0) ;
  
  
  
  cout << endl << endl << " The database is available in \"Database.txt\"  ..." << endl ;
  cout << " Goodbye ...." << endl << endl;
  return 0;
  
}




/*****************************************************************
//
//  Function name:		main_menu  
//
//  DESCRIPTION:		a function to produce the main menu of the program 
//				asking user to enter the proper menu option
//
//  Parameters:			No input
//				
//  Return values:		int: the menu number that entered by user
//
//****************************************************************/

int main_menu()
{
 
 char entry[20];
 int menu = 1;

 do {
  

   cout << endl << " **********************" << endl ;
   cout << " * by: Ehsan Kourkchi *" << endl ;
   cout << " * Copyright (C) 2013 *" << endl ;
   cout << " **********************" << endl ;
   
   cout << endl << " ****** M E N U ******" << endl ;

   cout << "\n A) Add a contact" << endl ;
   cout << " M) Modify a contact" << endl ;   
   cout << " D) Delete a contact" << endl ; 
   cout << " F) Find a contact" << endl ;
   cout << " P) Print all contacts" << endl ;
   cout << " R) Reverse the list" << endl ;
   cout << " Q) Quit" << endl  << endl ;
   cout << " ***********************" << endl ;

   
    if (menu == 0) 
      cout << " Wrong entry ..." << endl << " Please enter your choice again: ";
    else
      cout << " Enter your choice: ";
   
   
   cin.getline(entry, 20);
   
   if (!strcmp(entry,"A") || !strcmp(entry,"a")) menu = 1;
   else if (!strcmp(entry,"M") || !strcmp(entry,"m")) menu = 2;
   else if (!strcmp(entry,"D") || !strcmp(entry,"d")) menu = 3;
   else if (!strcmp(entry,"F") || !strcmp(entry,"f")) menu = 4;
   else if (!strcmp(entry,"P") || !strcmp(entry,"p")) menu = 5;
   else if (!strcmp(entry,"Q") || !strcmp(entry,"q")) menu = 6;
   else if (!strcmp(entry,"R") || !strcmp(entry,"r")) menu = 7;
   else menu = 0;

  
   } while(!menu);
   
return menu;  
}

/*****************************************************************
//
//  Function name:		addData  
//
//  DESCRIPTION:		a function which gets data from the user
//				and add it to the loaded database
//
//  Parameters:			The linked-list containing all the database
//				
//  Return values:		int: the number of records in the list after adding the new data
//
//****************************************************************/

int addData(llist &list)
{
 
   char name[25];
   char address[80];
   int  yearofbirth, no;
   char telno[15];
 
 cout << "\n ****************************"   << endl ;
 cout << " Adding a new contact ...." << endl;
 cout << " ****************************" << endl << endl;
 getdata(name, address, yearofbirth, telno); 
 
 if(no = list.addRecord(name, address, yearofbirth, telno))
 {
   
    cout << "\n ****************************"   << endl ;
    cout << " Added successfully ...." << endl;
    cout << " # of available contacts: " << no <<  "" << endl  ; 
    cout << " ****************************" << endl << endl;
 }
 
 
 return no;
 
}


/*****************************************************************
//
//  Function name:		modifyData  
//
//  DESCRIPTION:		a function which modify a record (or records)
//				using the "name" as the key
//
//  Parameters:			The linked-list containing all the database
//				
//  Return values:		int: the number of records in the list which were modifies
//
//****************************************************************/

int modifyData(llist &list)
{
 
   char name[25];
   char address[80];
   char telno[15];
   int no;
 
 cout << "\n ****************************"   << endl ;
 cout << " Modifying a contact ...." << endl;
 cout << " ****************************" << endl << endl;
 getdata_modify(name, address, telno); 
 
 if(no = list.modifyRecord(name, address, telno))
 {
      cout << "\n ****************************"   << endl ;
      cout << " # of the modified contacts: " << no <<  "" << endl  ; 
      cout << " ****************************"   << endl << endl ;
 }
 else
 {
     cout << "\n ****************************"   << endl ;
     cout << " This name is not available in database. " << endl  ; 
     cout << " No contact was modified. " << endl  ; 
     cout << " ****************************"   << endl << endl ;
 }
 
 
 
 return no;
 
}

/*****************************************************************
//
//  Function name:		removeData  
//
//  DESCRIPTION:		a function to removed a record (or records)
//				based on the "name" as the key
//
//  Parameters:			The linked-list containing all the database
//				
//  Return values:		int: the number of deleted records
//
//****************************************************************/

int removeData(llist &list)
{
  
  char name[25];
  char str[1000];
  int  p =  0, no;
  
   cout << "\n ****************************"   << endl ;
   cout << " Removing a contact ...." << endl;
   cout << " ****************************" << endl << endl;
  
   p=1;
   while(p>0)
   {
   
   if (p==2) cout << " Please try again ... Enter the name: "  ;
     else cout << " Enter the name: "  ;
   cin.getline(str, 1000);
   
   for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
   
   if (strlen(str) > 24) 
       str[24]='\0';

   strncpy(name, str, 25);
   
   if(str[0] == '\0') p=2;
      else p=0;
     
  }
  
  
  
  if(no = list.deleteRecord(name))
    {
      cout << "\n ****************************"   << endl ;
      cout << " # of the removed contacts: " << no <<  "" << endl  ; 
      cout << " ****************************"   << endl << endl ;
    }
  else
    {
     cout << "\n ****************************"   << endl ;
     cout << " This name is not available in database. " << endl  ; 
     cout << " No contact was removed. " << endl  ; 
     cout << " ****************************"   << endl << endl ;
    }
    
    return no;
}


/*****************************************************************
//
//  Function name:		printData  
//
//  DESCRIPTION:		a function to find and print a record (or records)
//				based on the "name" as the key
//
//  Parameters:			The linked-list containing all the database
//				
//  Return values:		int: the number of printed records
//
//****************************************************************/

int printData(llist &list)
{
  
  char name[25];
  char str[1000];
  int  p =  0, no;
  
   cout << "\n ****************************"   << endl ;
   cout << " Finding a contact ...." << endl;
   cout << " ****************************" << endl << endl;
  
   p=1;
   while(p>0)
   {
   
   if (p==2) cout << " Please try again ... Enter the name: "  ;
     else cout << " Enter the name: "  ;
   cin.getline(str, 1000);
   
   for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
   
   if (strlen(str) > 24) 
       str[24]='\0';

   strncpy(name, str, 25);
   
   if(str[0] == '\0') p=2;
      else p=0;
     
  }
  
  return list.printRecord(name);

}

/*****************************************************************
//
//  Function name:		reverseList  
//
//  DESCRIPTION:		a function to reverse the order of the records in the lined-list
//
//  Parameters:			The linked-list containing all the database
//				
//  Return values:		int: always returns 1
//
//****************************************************************/

int reverseList(llist &list)
{
  
  list.reverse();
  
      cout << "\n ****************************"   << endl ;
      cout << " The list is reversed successfully. " <<  "" << endl  ; 
      cout << " ****************************"   << endl << endl ;
  
  return 1;    
}



/*****************************************************************
//
//  Function name:		getdata  
//
//  DESCRIPTION:		a function to get the data from the user interactively
//				for adding to the database
//
//  Parameters:			name: char[25] - one line supported only
//				address: char[80] - multiple line supported
//				yearofbirth: int
//				telno: char[15] - one line supported only

//				
//  Return values:		int: always returns 1
//
//****************************************************************/

int getdata(char name[], char address[], int &yearofbirth, char telno[])
{
 
   char str[1000], adr[1000];
   int  year;
   int  p =  0;
   int length; 
   
   // Getting the name
   p=1;
   while(p>0)
   {
   
   if (p==2) cout << " Please try again ... Enter the name: "  ;
     else cout << " Enter the name: "  ;
   cin.getline(str, 1000);
   
   for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
   
   if (strlen(str) > 24) 
       str[24]='\0';

   strncpy(name, str, 25);
   
   if(str[0] == '\0') p=2;
      else p=0;
     
  }

   // Getting the address
   cout << " Enter the address: " << endl ;
   cout << " Press the <Enter> key two times when you are done." << endl ;
   
   adr[0]='\0';
   p=0;
   while(p<1)
   {
     
     cout << "# " ;
     cin.getline(str, 1000);
     
     for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
     
     if (str[0] == '\0') p++;
     
     strcat(adr,str);
     
     length = strlen(adr);
     adr[length] = '\n';
     adr[length+1] = '\0';
     
   }
   
   adr[length-1] = '\0';
   if (strlen(adr) > 79) 
     adr[79]='\0';
   
   strncpy(address, adr, 79);
   adr[0]='\0';
   
   
   // Getting the year of birth
   cout << " Enter the year of birth: " ;
   cin.getline(str, 1000);
   yearofbirth = atoi(str);
   
   // Getting the telephone number
   cout << " Enter the telephone number: "  ;
   cin.getline(str, 1000);
   
   for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
   
   if (strlen(str) > 14) 
       str[14]='\0';

   strncpy(telno, str, 14);
     
  
 return 1;
 
}


/*****************************************************************
//
//  Function name:		getdata_modify  
//
//  DESCRIPTION:		a function to get the data from the user interactively
//				for modifying a record (or records) in the database
//
//  Parameters:			name: char[25] - one line supported only
//				address: char[80] - multiple line supported
//				telno: char[15] - one line supported only

//				
//  Return values:		int: always returns 1
//
//****************************************************************/

int getdata_modify(char name[], char address[], char telno[])
{
 
   char str[1000], adr[1000];
   int  p =  0;
   int length; 
   
   
   // Getting the name
   p=1;
   while(p>0)
   {
   
   if (p==2) cout << " Please try again ... Enter the name: "  ;
     else cout << " Enter the name: "  ;
   cin.getline(str, 1000);
   
   for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
   
   if (strlen(str) > 24) 
       str[24]='\0';

   strncpy(name, str, 25);
   
   if(str[0] == '\0') p=2;
      else p=0;
     
  }
  
   // Getting the address
   cout << " Enter the address: " << endl ;
   cout << " Press the <Enter> key two times when you are done." << endl ;
   
   adr[0]='\0';
   p=0;
   while(p<1)
   {
     
     cout << "# " ;
     cin.getline(str, 1000);
     
     for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
     
     if (str[0] == '\0') p++;
     
     strcat(adr,str);
     
     length = strlen(adr);
     adr[length] = '\n';
     adr[length+1] = '\0';
     
   }
   
   adr[length-1] = '\0';
   if (strlen(adr) > 79) 
     adr[79]='\0';
   
   strncpy(address, adr, 79);
   adr[0]='\0';

   // Getting the telephone number
   cout << " Enter the telephone number: "  ;
   cin.getline(str, 1000);
   
   for (int i=strlen(str)-2; str[i]==' '; i--)
       str[i]='\0';
   
   if (strlen(str) > 14) 
       str[14]='\0';

   strncpy(telno, str, 14);

  
 return 1;
 
}


/*****************************************************************
//
//  Function name:		arguments  
//
//  DESCRIPTION:		a function to handle the permitted arguments of the program 
//				in a command line run
//
//  Parameters:			int argc: the number of arguments
//				char *argv[]: the pointer to the array of strings which hold all arguments
//
//  Return values:		int: = 1 if user runs the program with the proper arguments
//				     = 0 if the user is not running the program properly
//
//****************************************************************/

int  arguments(int argc, char *argv[])
{
  int exit_program = 0;
   if (argc == 1) 
 {
   debugmode = 0;
 }
 else if (argc == 2) 
 {
	if (!strcmp(argv[1] , "--help") || !strcmp(argv[1] , "-h")) 
	{
	  cout <<  "\n\n Usage: database [OPTION] " ;
	  cout <<  "\n If no option is used,\n the program will be run in the normal mode." ;
	  cout <<  "\n\n *** OPTIONS *** " ;

	  cout <<  "\n\n -d, debug" ;
	  cout <<  "\n   In this mode, the name of all functions" ;
	  cout <<  "\n   and the passed parameters will be displayed." ;
	  
	  cout <<  "\n\n -v, --version" ;
	  cout <<  "\n   output version information and exit" ;
	  

	  cout <<  "\n\n -h, --help" ;
	  cout <<  "\n   display this help and exit" << endl  ;

          cout <<  "\n\n   Copyright (C) 2013" ;
	  cout <<  "\n     Ehsan Kourkchi" ;
	  cout <<  endl << endl  ;

	  
	  exit_program = 1;
	} 
	else if (!strcmp(argv[1] , "debug") || !strcmp(argv[1] , "-d")) 
	{
	  debugmode = 1;
	}
	else if (!strcmp(argv[1] , "-v") || !strcmp(argv[1] , "--version"))
	{
	 cout <<  "\n   Database2" ;
 	 cout <<  "\n   version: (ICS212)" ;
	 cout <<  "\n   language: (C++)" ;
	 cout <<  "\n   Copyright (C) 2013" ;	  
	 cout <<  "\n   by: Ehsan Kourkchi" << endl << endl  ;  
	 exit_program = 1;
	}
	else
	{
	  cout <<  "\n Bad opperands\n Try '--help' flag for more information." << endl << endl  ;
	  exit_program = 1;
	}
  
 }
 else {
   cout <<  "\n Bad operands.\n Try '--help' flag for more information." << endl << endl  ;
   exit_program = 1;
 }

 return exit_program;
}

/** END */
