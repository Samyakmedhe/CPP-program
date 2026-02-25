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
//      Entry Point Function of the project
//
//////////////////////////////////////////////////////////////////////////
int main()
{
    
    char str[80] = {'\0'};
    char Command[4][20];
    int iCount = 0;


    StartAuxillaryDataInitialisation();
    printf("-----------------------------------------------------------\n");
    printf("=============== CVFS Started Sucessfully ==================\n");
    printf("-----------------------------------------------------------\n");
    
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");
        
        printf("\n CVFS : > ");
        fgets(str, sizeof(str), stdin);

        
    }

    return 0 ;
}