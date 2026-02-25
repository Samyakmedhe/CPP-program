//////////////////////////////////////////////////////////////////////////
//
//  Project :           Customised Virtual File Systems
//  Description :       
//  Author :            Samyak Kailas Medhe
//  Date :              13/01/2026
//    
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//
//     Header File Inclusion
//
//////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

//////////////////////////////////////////////////////////////////////////
//
//
//     User Defined Macros
//
//
//////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILE 20

#define MAXINODE 5

#define READ 1 
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

//////////////////////////////////////////////////////////////////////////
//
//  user Define Structure 
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Description :       Holds the information to boot OS
//    
//////////////////////////////////////////////////////////////////////////
struct BootBlock
{
    char Information[100];
};


//////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock
//  Description :       Holds the information about File Systems 
//    
//////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};


//////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    Inode
//  Description :       Holds the information about File
//    
//////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int FileType;
    int ActualFileSize;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;


//////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable
//  Description :       Holds the information about open file 
//    
//////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;

};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

//////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA
//  Description :       Holds the information about process
//    
//////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName [20];
    PFILETABLE UFDT[MAXOPENFILE];

};


//////////////////////////////////////////////////////////////////////////
//
//  Global variable function of the project
//    
//////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;


PINODE head = NULL;



//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseUAREA
//  Description :       It is used to Initialise UAREA members
//  Author :            Samyak Kailas Medhe
//  Date :              13/01/2026
//////////////////////////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");

    int i = 0 ;
    for(i = 0 ; i < MAXFILESIZE ; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }

    printf("CVFS : UAREA gets initialize gets sucessfully\n");
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseSuperBlock
//  Description :       It is used to Initialise SuperBlock members
//  Author :            Samyak Kailas Medhe
//  Date :              13/01/2026
//    
//////////////////////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("CVFS : Super Block gets Initialise sucessfully\n");

}

//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateDILB
//  Description :       It is used to create linkedlist of iNode
//  Author :            Samyak Kailas Medhe
//  Date :              13/01/2026
//    
//////////////////////////////////////////////////////////////////////////

void CreateDILB()
{   
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1 ; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));
        
        strcpy(newn->FileName, "\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->FileType = 0;
        newn->ActualFileSize = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0 ;
        newn->Buffer = NULL;
        newn->next = 0;

        if(temp == NULL) // LL empty
        {
            head = newn;
            temp = head;
        }
        else // LL contins atleast 1 node 
        {
            temp->next = newn;
            temp = temp->next;
        }   
    }

    printf("CVFS : DILB created sucessfully\n");

    
}


//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     StartAuxillaryDataInitialisation
//  Description :       It is used to call all such function which are used to initialise auxillary Data
//  Author :            Samyak Kailas Medhe
//  Date :              13/01/2026
//    
//////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");
    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock();
    
    CreateDILB();
    
    InitialiseUAREA();

    printf("CVFS : Auxillary Data initialise sucessfully\n");

}

//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     DisplayHelp
//  Description :       It is used to Diplay the help page 
//  Author :            Samyak Kailas Medhe
//  Date :              14/01/2026
//    
//////////////////////////////////////////////////////////////////////////


void DisplayHelp()
{
    printf("-----------------------------------------------------------\n");
    printf("=================== CVFS Help Page ========================\n");
    printf("-----------------------------------------------------------\n\n");

    printf("man    : It is used to display manual page\n");
    printf("clear  : It is used to clear the Terminal\n");
    printf("creat  : It is used to create new file\n");
    printf("write  : It is used to write the data into the file\n");
    printf("read   : It is used to read the data from file\n");
    printf("stat   : It is used to Display statistical information\n");
    printf("unlink : It is used to Delete the File\n");
    printf("exit   : It is used to terminate CVFS\n");

    printf("\n===========================================================\n");
    
}
/////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ManPageDisplay
//  Description :       It is used to Diplay Man Page
//  Author :            Samyak Kailas Medhe
//  Date :              14/01/2026
//    
//////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name) == 0 )
    {
        printf("About : For each operand that names a file of a type other than directory ls display its name as well as any requested associated information For each operand that names a file of type directory ls display the names of files contained within that directory as well as any requested associated information\n");
        printf("usage : ls\n");
    }
    else if (strcmp("man",Name) == 0 )
    {
       printf("About : DESCRIPTION : The man utility finds and displays online manual documentation pages.  If mansect is provided, man restricts the search to the specific section of the manual.\n");
       printf("usage : man Command_name\n");
    }
    else if(strcmp("exit", Name) == 0)
    {
        printf("About : It is Used to terminate the shell\n");
        printf("usage : exit");
    }
    else
    {
        printf("No Manu");
    }
}
//////////////////////////////////////////////////////////////////////////
//
//      Entry Point Function of the project
//
//////////////////////////////////////////////////////////////////////////
int main()
{
    
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;


    StartAuxillaryDataInitialisation();
    printf("-----------------------------------------------------------\n");
    printf("=============== CVFS Started Sucessfully ==================\n");
    printf("-----------------------------------------------------------\n");
    

    // Inifinite Listening Shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");
        
        printf("\nCVFS : > ");
        fgets(str, sizeof(str), stdin);

        iCount = sscanf(str , "%s %s %s %s %s",Command[0], Command[1], Command[2], Command[3], Command[4]);
        
        fflush(stdin);
        
        if(iCount == 1)
        {
            if(strcmp("exit", Command[0]) ==  0 )
            {
                printf("Thankyou for using CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            else if(strcmp("ls", Command[0]) == 0 )
            {
                printf("Inside ls\n");
            }
            else if(strcmp("help", Command[0]) == 0 )
            {
                DisplayHelp();
            }
        }   // End of else if 1
        else if(iCount == 2)
        {
            if(strcmp("man", Command[0]) == 0 )
            {   
                ManPageDisplay(Command[1]);
            }
        }   // End of else if 2
        else if(iCount == 3)
        {

        }   // End of else if 3
        else if(iCount == 4)
        {

        }   // End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information\n");
        }// END of else
    
    }// End of While

    return 0 ;
} // End of Main