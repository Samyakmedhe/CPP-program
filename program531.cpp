//////////////////////////////////////////////////////////////////////////
//
//
//     Header File Inclusion
//
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
//      Entry Point Function of the project
//
//////////////////////////////////////////////////////////////////////////
int main()
{

    return 0 ;
}