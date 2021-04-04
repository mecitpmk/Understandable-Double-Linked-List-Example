#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



typedef struct Students
{
    char name[50];
    int finalExam;
    struct Students* next;
    struct Students* prev;
}Student;


Student *HEAD = NULL;
Student *currentlyStudent = NULL;


static bool isFirst = true;
static int LinkedListLength = 0;

Student *createStudent(char *name , int * finalExamination)
{

    Student *newStudent = (Student *) malloc(sizeof(Student));
    strcpy(newStudent->name , name);
    newStudent->finalExam = *finalExamination;
    newStudent->next = NULL;
    if (isFirst)
    {
        HEAD = newStudent;
        HEAD->prev = NULL; // no previous for head!
        currentlyStudent = newStudent;
        isFirst = false;
    }
    else
    {
        currentlyStudent->next = newStudent;  // 
        newStudent->prev = currentlyStudent;  // Purposes [Test]<->[Test2]<->[Test3]
        currentlyStudent = newStudent;
    }
    LinkedListLength++;
    return newStudent;

}

void InfoLinkedList()
{
   
    Student *myPointer = HEAD;
    printf("Length of Linked List is :%d \n",LinkedListLength);
    while (myPointer != NULL)
    {
        printf("Name is %s and Midterm is %d \n",myPointer->name , myPointer->finalExam);
        myPointer = myPointer->next;
    }
}


Student *findStudent(char *StudentName, bool isforRemoving)
{
    /*
        ->In this function check if the student exist.
            If the student exist, return the finded student struct adress.
            if its not return NULL.
        
        ->The parameeter isforRemoving is designed for RemoveStudent function.
            if this parameeter is true, returned value will be before the finded student
            adress. It make its easy to remove.

    */
    
    Student *headPointer = HEAD;
    Student *beforeHim = HEAD;

    while (headPointer != NULL)
    {
        if (strcmp(headPointer->name,StudentName) == 0)
        {
            printf("its founded.. %s \n",headPointer->name);
            if (!isforRemoving)
            {
                return headPointer;
            }
            else return beforeHim;
            
        }
        beforeHim = headPointer;
        headPointer = headPointer->next;
    }
    return NULL;
}

void RemoveStudent(char *StudentName)
{
    /*
        In this part, first check returned value from findStudent function
        if its not null it means that student has been founded However,
        returned value is not equal to removed student name:
            [BeforeRemoved]->[RemovedStudentStruct]->[AfterNextStudent]
            Returned value is BeforeRemoved Student Struct adress so,
            we can link to [BeforeRemoved]->[AfterNextStudent]
            and we can deallocate memory for RemovedStudent.

        Doubly linked list = [findedStudent]<->[willRemove]<->[AfterThat]
                After removing:  [findedStudent]<->[AfterThat]
    */
    Student *findedStudent = findStudent(StudentName,true);
    
    if (findedStudent) // findedStudent != NULL
    {
        Student *willRemove = findedStudent->next;
        findedStudent->next = willRemove->next; 
        willRemove->next->prev = findedStudent; 
        free(willRemove);
        LinkedListLength--;
        printf("Succesfully Removed! \n");
    }
    else printf("Student is not exist.!\n");
}

int main()
{
    
    /*
        ->Idea is create 3 Student , 
            Check LinkedList.
        ->Remove one of Student
            Check LinkedList Again.
    */

    char names[50] = "Hello word";
    int finalEx = 50;
    createStudent(names,&finalEx);
    
    char namesTwo[50] = "Hello wordSSS";
    int finalExTwo = 66;
    createStudent(namesTwo,&finalExTwo);
    

    char namesThird[50] = "Hello wordSSSXX";
    int finalExThird = 68;
    createStudent(namesThird,&finalExThird);
    InfoLinkedList();

    // [Hello Word]->["Hello wordSSS"]->["Hello wordSSSXX"]
    
    char namesX[50] = "Hello wordSSS";
    RemoveStudent(namesX);
    // [Hello Word]->["Hello wordSSSXX"]
    InfoLinkedList();
    
    printf("-------------------------------\n");

    // This lines testing for doubly linked list.
    Student *wordsXXX = findStudent(namesThird,false);
    printf("Student name is %s \n",wordsXXX->name);
    printf("Before its name is %s \n",wordsXXX->prev->name);


    return 0 ;
}