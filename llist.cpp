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
//  FILE:		llist.cpp      
//
//  DESCRIPTION:	This file contains the method definitions of 
//			the "llist" linked-list [Project 2] 
//
//****************************************************************/

#include <iostream>
using namespace std;
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#ifndef LLIST
  #include "llist.h"
#endif


#ifndef RECORD
  #include "record.h"
#endif 

/*****************************************************************/
// GLOBAL VARIABLES */
extern int debugmode;
/*****************************************************************/



/*****************************************************************
//
//  Function name:		llist::readfile()  
//
//  DESCRIPTION:		Reding from a file and fill in the list
//
//  Parameters:			no input parameter
//				
//  Return values:		int: the number of valid records added to the linked-list
//
//****************************************************************/

	  int llist::readfile()
	  {
	    
	    ifstream inputfile; 
	     
	    char keyword[100];
	    char line[1000];
	    char newline[1];
	    int numrecords = 0;
	    
	    char uname[25];
	    char uaddress[80];
	    char address[1000];
	    int  uyearofbirth;
	    int  count = 0;
	    char utelephone[15];
	    
	    newline[0] = '\n';

	    
	    
	    inputfile.open(filename);  

	    if (!inputfile)
	    {
	      inputfile.clear();  
	      return 0;  //  No. of input contacts = 0
	    }
	      
	      
	      
	      while(! inputfile.eof() )
	      {
                    inputfile >> keyword;
		    
	            if (!strcmp(keyword, "Name:"))
		    {
		      inputfile.getline(line, 1000 );
		      
		      for (int i=strlen(line)-2; line[i]==' '; i--)
		            line[i]='\0';
		      
		      if (strlen(line) > 25) 
			    line[25]='\0';

		      strncpy(uname,line+1,25);
		      count++;
		       
		    }
		    
		    address[0]='\0';
 		    if (!strcmp(keyword, "Address:"))
		    {   
		        inputfile.getline(line, 1000 );
			strcat(address,line+1);

			inputfile >> keyword;

		        while (strcmp(keyword," ") && strcmp(keyword,"YearofBirth:") && strcmp(keyword,"Telephone:") )
			{ 

			  int length = strlen(address);
			  address[length] = '\n';
			  address[length+1] = '\0';
			  strcat(address,keyword);
			  inputfile.getline(line, 1000 );
			  strcat(address,line);
			  
			  inputfile >> keyword;
			  
			}

			for (int i=strlen(address)-2; address[i]==' '; i--)
		           address[i]='\0';
		       
			if (strlen(address) > 79) 
			    address[79]='\0';

			strncpy(uaddress, address, 80);
			count++;


		    }
		    
	            if (!strcmp(keyword, "YearofBirth:"))
		    {
		      inputfile.getline(line, 1000 );
		      uyearofbirth = atof(line+1);
		      count++;
		    } 
		    
		    
		    if (!strcmp(keyword, "Telephone:"))
		    {
		      
		      inputfile.getline(line, 1000 );
		      
		      for (int i=strlen(line)-2; line[i]==' '; i--)
		       line[i]='\0';
		      
		      if (strlen(line) > 15) 
			    line[15]='\0';
		      strncpy(utelephone, line+1, 15);
		      count++;
		    }
   
 		if (count/4 == 1) 
		{
		addRecord(uname, uaddress, uyearofbirth, utelephone);
		numrecords++;
		count=0;
		}
    
               
	      }
	      

	    inputfile.close();
	    return numrecords;
	    
	  }
	  
/*****************************************************************
//
//  Function name:		llist::writefile 
//
//  DESCRIPTION:		writing the linked-list into a file
//
//  Parameters:			no input parameter
//				
//  Return values:		int: the number of valid records written to the file
//
//****************************************************************/

	  int llist::writefile()
	  {
	    
	    int  counter = 0;
	    ofstream outputfile;
	    record *current = start;
	    
	    outputfile.open(filename, std::ios::binary);  

	    if (!outputfile)
	    { 
	      
	      outputfile.clear();  
	      return 0;  //  No. of contacts = 0
	    }
	    
	    outputfile << "****************************\n" ;
	    outputfile << "The list of all contacts\n";
	    outputfile << "****************************\n\n" ;
	    
	    
	    while (current != NULL)
	    {
	      counter++;
	      
	      outputfile << "Contact No.: " << counter << endl;
	      outputfile << "Name: " << current->name << "\n";
	      
	      
	      outputfile << "Address: " << current->address << "\n";
	      outputfile << "YearofBirth: " << current->yearofbirth << "\n";
	      outputfile << "Telephone: " << current->telno << "\n\n";
	      outputfile << "****************************\n" ;
	      current = current->next;
	    }
	    
	    outputfile << "Number of contacts: " << counter << endl;
	    outputfile << "****************************\n" ;
	    
	    outputfile.close();
	    return counter;
	    
	  }
	  
/*****************************************************************
//
//  Function name:		llist::reverse
//
//  DESCRIPTION:		reversing the input linked-list
//
//  Parameters:			record *oldlist: the header of the linked-list to be reversed
//				
//  Return values:		record*: the header of the reversed linked-list
//
//****************************************************************/
	  
	  
          record *  llist::reverse(record *oldlist)
	  {

/** implementing the method using a loop */
// 	    record *end = oldlist;
// 	    record *pre = NULL;
// 	    record *tmp = NULL;
// 	   
// 	     while (end != NULL)
// 	     {
// 	       
// 	       tmp = end->next;
// 	       end->next = pre;
// 	       pre = end;
// 	       end = tmp;
// 	    
// 	    
// 	    
// 	     }
// 	     
// 	     return pre;
/** the end of looping method */
	    
/** recursive method */
	    if (oldlist == NULL) return NULL;
	    else if (oldlist->next == NULL) return oldlist;
	    else 
	    {
	      
	     record *head = reverse(oldlist->next);
	     oldlist->next->next = oldlist;
	     oldlist->next = NULL;
	     
	     return head;
	     
	    }
          
	  }

/*****************************************************************
//
//  Function name:		llist::cleanup
//
//  DESCRIPTION:		Deleting all the allocated memory to hold the record 
//				of the current linked-list
//
//  Parameters:			no input parameter
//				
//  Return values:		no output
//
//****************************************************************/
          
          void llist::cleanup()
	  {
	    
	   record *current = start; 
	   record *next = NULL;
	    
	   while (current != NULL)
	   {
	     
	     next = current->next;
	     delete current;
	     current = next;
	     
	   }
	    
	  }
 

/*****************************************************************
//
//  Function name:		llist::llist( )  and llist::~llist( )
//
//  DESCRIPTION:		Constructor and Destructor of the linked-list
//
//  Parameters:			Constructor1: no input
//				Constructor2: input and output filename
//				Destructor: no input
//				
//  Return values:		no output
//
//****************************************************************/ 
 
 
 
         /** NULL constructor
	  * @param no-input parameter
	  */
	

          llist::llist( )
	  {
	    start = NULL;
	    std::strcpy(filename, "Database.txt");
	  }
	  
	  /** constructor: reading from a file 
	   *   @param filename
	   */
  
          llist::llist(char filename[])
	  {
	    
	    start = NULL;
	    std::strcpy(this->filename, filename);
	    
	    readfile();
	    
	  }
	  
	  
	  /** Destructor
	   *  @param no-input parameter
	   * */
          llist::~llist( )
	  {
	    
	    writefile();
	    cleanup();
	    
	  }

/*****************************************************************
//
//  Function name:		llist::addRecord
//
//  DESCRIPTION:		addind a new record to the linked-list
//
//  Parameters:			name: char[25] - one line supported only
//				address: char[80] - multiple line supported
//				birth: int
//				tel: char[15] - one line supported only
//				
//  Return values:		int: number of available records after adding the new record
//
//****************************************************************/

         int llist::addRecord(char name[], char address[], int birth, char tel [])
	 {
	   
	   int counter = 1;
	     
	   if (debugmode)
	   {
	    
	     cout << "\n****************************" << endl;
	     cout << "*** D E B U G   M O D E ****" << endl ;
	     cout << "****************************" << endl;
	     cout << "Function name: addRecord" << endl;
	     cout << "Name: " << name << "\n";
	     cout << "Address: " << address << "\n";
	     cout << "YearofBirth: " << birth << endl;
	     cout << "Telephone: " << tel << endl;
	     cout << "****************************" << endl << endl;
	     
	   }
	   
	   record *current = start;
	   
	   
	   record *newrecord = new record;
	   
	   strcpy(newrecord->name, name);
	   strcpy(newrecord->address, address);
	   newrecord->yearofbirth =  birth;
	   strcpy(newrecord->telno, tel);	   
	   newrecord->next = NULL;
	   
	   if (start == NULL)
	     start = newrecord;
	   else 
	   {
	     while (current->next != NULL)
	     {
	       current = current->next;
	       counter++;
	     }
	    current->next = newrecord;
	    counter++;
	   }
	   
	   return counter;
	 }
	 
/*****************************************************************
//
//  Function name:		llist::printRecord
//
//  DESCRIPTION:		finding and printing a record (or records) of the linked-list
//				based on the "name" as the key
//
//  Parameters:			uname: char[25] - one line supported only
//				
//  Return values:		int: number of printed records
//
//****************************************************************/
	 
         int llist::printRecord(char uname[ ])
	 {
	   int counter = 0, count = 0;
	   record *current = start;
	   
	     
	   if (debugmode)
	   {
	    
	     cout << "\n****************************" << endl;
	     cout << "*** D E B U G   M O D E ****" << endl ;
	     cout << "****************************" << endl;
	     cout << "Function name: printRecord" << endl;
	     cout << "Name: " << uname << "\n";
	     cout << "****************************" << endl << endl;
	     
	   }
	   
	   while (current != NULL)
	   {
	     
	     if(!strcmp(current->name, uname))
	     {
	        cout << "\n****************************" << "\n";
		cout << "#: " << count + 1 << "\n";
		cout << "Name: " << current->name << "\n";
		cout << "Address: " << current->address << "\n";
		cout << "YearfBirth: " << current->yearofbirth << "\n";
		cout << "Telephone: " << current->telno << "\n";
		cout << "****************************" << "\n";
		counter++;
	     }
	   count++;
	   current = current->next;
	   }
	   
	   if (counter == 0)
	   {
	     cout << "\n ****************************" << "\n";
	     cout << " No contact was found. \n" ; 
	     cout << " ****************************" << "\n\n";
	   }
	   else
	   {
	     cout << "\n\n ****************************" << "\n";
	     cout << " # of found contacts: " << counter <<  "\n" ; 
	     cout << " ****************************" << "\n\n";
	   }
	     
	 
	   
	 return counter; 
	 
	 }

/*****************************************************************
//
//  Function name:		llist::modifyRecord
//
//  DESCRIPTION:		modifying a record (or records) 
//				based on the "name" as the key
//
//  Parameters:			name: char[25] - one line supported only
//				address: char[80] - multiple line supported
//				tel: char[15] - one line supported only
//				
//  Return values:		int: number of modified records
//
//****************************************************************/

         int llist::modifyRecord(char name[], char address[], char tel [])
	 {

	   int counter = 0;
	   record *current = start;
	   
	   
	     
	   if (debugmode)
	   {
	    
	     cout << "\n****************************" << endl;
	     cout << "*** D E B U G   M O D E ****" << endl ;
	     cout << "****************************" << endl;
	     cout << "Function name: modifyRecord" << endl;
	     cout << "Name: " << name << "\n";
	     cout << "Address: " << address << "\n";
	     cout << "Telephone: " << tel << endl;
	     cout << "****************************" << endl << endl;
	     
	   }
	   
	   
	   while (current != NULL)
	   {
	     
	     if(!strcmp(current->name, name))
	     {
	        
		strcpy(current->name, name) ;
		strcpy(current->address, address) ;
		strcpy(current->telno, tel) ;
		
		counter++;
	     }
	   current = current->next;
	   }
 
	 return counter;

	 }
         
/*****************************************************************
//
//  Function name:		llist::printAll
//
//  DESCRIPTION:		printing all the available records in the linked-list
//
//  Parameters:			no input parameter
//				
//  Return values:		no output parameter
//
//****************************************************************/        
         
         void llist::printAll()
	 {
	   
	   int counter = 0;
	   record *current = start;
	   
	   	   
	     
	   if (debugmode)
	   {
	    
	     cout << "\n****************************" << endl;
	     cout << "*** D E B U G   M O D E ****" << endl ;
	     cout << "****************************" << endl;
	     cout << "Function name: printAll" << endl;
	     cout << "****************************" << endl << endl;
	     
	   }
	   
	   while (current != NULL)
	   {
	     

	        cout << "\n****************************" << "\n";
		cout << "#: " << counter+1 << "\n";
		cout << "Name: " << current->name << "\n";
		cout << "Address: " << current->address << "\n";
		cout << "YearfBirth: " << current->yearofbirth << "\n";
		cout << "Telephone: " << current->telno << "\n";
		cout << "****************************" << "\n";
		
		counter++;

	   current = current->next;
	   }
	   
	   if (counter == 0)
	   {
	     cout << "\n ****************************" << "\n";
	     cout << " This database is empty. \n" ; 
	     cout << " ****************************" << "\n\n";
	   }
	   else
	   {
	     cout << "\n ****************************" << "\n";
	     cout << " # of available contacts: " << counter <<  "\n" ; 
	     cout << " ****************************" << "\n\n";
	   }
	     

	 }

/*****************************************************************
//
//  Function name:		llist::deleteRecord
//
//  DESCRIPTION:		finding and removing a record (or records) of the linked-list
//				based on the "name" as the key
//
//  Parameters:			uname: char[25] - one line supported only
//				
//  Return values:		int: number of the removed records
//
//****************************************************************/
 
         int llist::deleteRecord(char uname[])
	 {
	   
	   int counter = 0;
	   record *end = start;
	   record *pre = NULL;
	   record *tmp = NULL;
	   
	   
	   	   
	     
	   if (debugmode)
	   {
	    
	     cout << "\n****************************" << endl;
	     cout << "*** D E B U G   M O D E ****" << endl ;
	     cout << "****************************" << endl;
	     cout << "Function name: deleteRecord" << endl;
	     cout << "Name: " << uname << "\n";
	     cout << "****************************" << endl << endl;
	     
	   }
	   
	   
	   while (end != NULL)
	   {
	     
	     if(!strcmp(end->name, uname))
	     { 
	       
	       if (start == end)
	       {
		 start = start->next;
		 
	       }
	       else
	       {
		 pre->next = end->next;
		 
	       }
	       
	       tmp = end->next;
	       delete end;
	       end = tmp;
	       counter++ ;
	       
	     }
	     else
	     {
	       pre = end;
	       end = end->next;
	     }
	   }
	   

	 return counter; 
	   
	 }
         
/*****************************************************************
//
//  Function name:		llist::reverse
//
//  DESCRIPTION:		reversing the linked-list
//
//  Parameters:			no input parameter
//				
//  Return values:		no output parameter
//
//****************************************************************/

         void llist::reverse()
	 {
	   
	   if (debugmode)
	   {
	    
	     cout << "\n****************************" << endl;
	     cout << "*** D E B U G   M O D E ****" << endl ;
	     cout << "****************************" << endl;
	     cout << "Function name: reverse" << endl;
	     cout << "****************************" << endl << endl;
	     
	   }
	     
	   start = reverse(start);
	   
	 }


/*****************************************************************
//
//  Function name:		operator<<
//
//  DESCRIPTION:		Overloaded "<<" operator which prints the entire linked-list using "printAll" method
//
//  Parameters:			ostream &output: The ostream opbject which receives the printed stuffs
//				llist &mylist: The linked-list to be printed
//
//  Return values:		no output parameter
//
//****************************************************************/

ostream & operator<<(ostream &out, llist &mylist)
{
  
  mylist.printAll();
  
  return out;
} 

/** END */

