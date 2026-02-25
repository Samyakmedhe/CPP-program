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
//     User Defined Macros
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
//     User Defined Macros for error handling
//
//////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALLREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILE_OPEN -8

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


//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ManPageDisplay
//  Description :       It is used to Diplay the Man PAge
//  Author :            Samyak Kailas Medhe
//  Date :              14/01/2026
//    
//////////////////////////////////////////////////////////////////////////


void ManPageDisplay(char Name[])
{
    if(strcmp("ls", Name) == 0 )
    {
        printf("NAME = ls – list directory contents\nDESCRIPTION :\n    For each operand that names a file of a type other than directory, ls displays its name aswell as any requested, associated information.  For each operand that names a file of type directory, ls displays the names of files contained within that directory, as well as any requested, associated information.If no operands are given, the contents of the current directory are displayed.  If more than one operand is given, non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexicographical order.\n");
    }   
    else if(strcmp("man", Name) == 0 )
    {
        printf("NAME = man,  manual documentation pages\nDESCRIPTION :\n    The man utility finds and displays online manual documentation pages.  If mansect is provided, man restricts the search to the specific section of the manual.\n");
    }
    else if(strcmp("exit", Name) == 0 )
    {
        printf("Name = exit\nDESCRIPTION :\n   It is used to terminate the shell\n");
    }
    else if(strcmp("clear", Name) == 0)
    {
        printf("Name = clear\nDESCRIPTION :\n  It is used to clear the shell\n");
    }
    else
    {
        printf("No manual entry for %s\n", Name);
    }
}

//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     IsFileExist
//  Description :       It is used to check wheather file is already exist or not
//  Input     :         It accepts file name 
//  Output  :           It returns the True or False
//  Author :            Samyak Kailas Medhe
//  Date :              16/01/2026
//    
//////////////////////////////////////////////////////////////////////////


bool IsFileExist(
                    char * name // File Name
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name , temp->FileName) == 0 ) && (temp->FileType == REGULARFILE))
        {   
            bFlag = true;
            break;
        }
        temp = temp->next;
    }

    return bFlag;
}
//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateFile
//  Description :       It is used to Create new Regular file
//  Input     :         It accepts file name and permissions
//  Output  :           It returns the file descriptor
//  Author :            Samyak Kailas Medhe
//  Date :              16/01/2026
//    
//////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,         // Name of new file 
                    int permission      // Permission for that file
                )
{
    PINODE temp = head;
    int i = 0 ;

    printf("Total number of iNode remaining : %d\n",superobj.FreeInodes);
    
    // if name is Missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }
    // if permission value is wrong
    // permission -> 1 -> READ
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if the iNode are full 
    if(superobj.FreeInodes == 0 )
    {
        return ERR_NO_INODES;
    }

    // If file is already is present
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALLREADY_EXIST;
    }

    // Search empty inode 
    while(temp != NULL)
    {
        if(temp->FileType == 0 )
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("There is no iNode\n");
        return ERR_NO_INODES;
    }
    
    // search for empty UFDT entry
    // Note : 0 , 1 , 2 are reserved
    for(i = 3; i < MAXOPENFILE ; i++)
    {
        if(uareaobj.UFDT[i] == NULL)
        {
            break;
        }

    }

    // UFDT is full 
    if(i == MAXOPENFILE)
    {
        return ERR_MAX_FILE_OPEN;
    }

    // allocate memory for file table 
    
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise file table 

    uareaobj.UFDT[i]->ReadOffset = 0 ;
    uareaobj.UFDT[i]->WriteOffset = 0;
    uareaobj.UFDT[i]->Mode = permission;

    // Connect file table with inode

    uareaobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of iNode;
    strcmp(uareaobj.UFDT[i]->ptrinode->FileName , name);
    uareaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
    uareaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
    uareaobj.UFDT[i]->ptrinode->Permission = permission;
    
    // allocate memory for file data
    uareaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

    superobj.FreeInodes--;

    return i; // File Descriptor

}

//////////////////////////////////////////////////////////////////////////
//
//  Function Name :     LsFile
//  Description :       It is used to list of File
//  Input     :         Nothing
//  Output  :           Nothing
//  Author :            Samyak Kailas Medhe
//  Date :              16/01/2026
//    
//////////////////////////////////////////////////////////////////////////

// ls -l 
void LsFile()
{
    PINODE temp = head;

    printf("-----------------------------------------------------------\n");
    printf("================= CVFS Files Information ==================\n");
    printf("-----------------------------------------------------------\n");

    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%d\t%s\t%d\t",temp->InodeNumber, temp->FileName, temp->ActualFileSize);
        }
        temp = temp ->next;
    }   

    printf("===========================================================\n");
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
    int iRet = 0;


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
            //CVFS : > exit
            if(strcmp("exit", Command[0]) ==  0 )
            {
                printf("Thankyou for using CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            // CVFS : > ls
            else if(strcmp("ls", Command[0]) == 0 )
            {
                LsFile();
            }
            // CVFS : > help
            else if(strcmp("help", Command[0]) == 0 )
            {
                DisplayHelp();
            }
            // CVFS : > clear
            else if(strcmp("clear", Command[0]) == 0 )
            {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
        }   // End of else if 1
        else if(iCount == 2)
        {
            // CVFS : > man __
            if(strcmp("man", Command[0]) == 0 )
            {
                ManPageDisplay(Command[1]);   
            }
        }   // End of else if 2
        else if(iCount == 3)
        {   
            // CVFS : > create File_Name.c 3
            if(strcmp("creat", Command[0]) == 0 )
            {
                iRet = CreateFile(Command[1],atoi(Command[2])); 

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROR : Unable to create the file as because Invalid Parameter");
                    printf("Please refer man page\n");
                }  

                if(iRet == ERR_NO_INODES)
                {
                    printf("ERROR : Unable to create file as there are no inode\n");
                }
                if(iRet == ERR_FILE_ALLREADY_EXIST)
                {
                    printf("ERROR : unable to create because file is already present\n");
                }
                if(iRet == ERR_MAX_FILE_OPEN)
                {
                    printf("ERROR : unable to create file\n");
                    printf("Max opened files limit reached\n");
                }
                printf("File Gets Successfully created with FD %d\n",iRet);

            
            }
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