// taskManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector> //this is important to allow for a dynamic array-like structure.
#include <string> //this is important to use "getline" function

using namespace std; 

class Task {
public:
    string name;
    string status; //pending or finished
    string description; 
};

class TaskHolder {
 public: 
     vector <Task> holder;

};

string userSaid() {
    cout << "\nEnter response...\n\n";
    string said;
    //cin >> said;  This will stop the string at the first space.
    getline(cin, said); //This will allow for spaces in the string
    return said;
}

void createTask(TaskHolder& holder) { 
//important note that the "&" references the object that is passed into it and will make modifications.  
//Without the "&" in "TaskHolder&", the object passed will be different from the one passed in and there will be no visible modification because the original object was "destroyed".
    Task newTask;
    cout << "\n\nWhat is the name of the new task?\n";
    

    newTask.name = userSaid();
    /*
    Testing lines
    cout << "the task name is..." << newTask.name << endl;
    */
    cout << "\nWhat is the decription of the task?\n";
    
    newTask.description = userSaid();
    newTask.status = "Pending";

    //cout << "\nOverview of newly added task\nTask name: "<< newTask.name << " \nTask Status: " << newTask.status << " \nTask Description" << newTask.description << endl;
    
    
    
    holder.holder.push_back(newTask);
    cout << "\nOverview of newly added task in the vector";
    cout << "\nTask name : " << holder.holder[0].name << " \nTask Status : " << holder.holder[0].status << " \nTask Description\nThere are now a total of..'" << holder.holder.size()<<"' task(s)" << endl;

    //cout << holder.holder.size()<< endl; test line
    
    

}

//This shows both pending and completed vectors
void displayHolders(TaskHolder pending, TaskHolder done) {
    cout << "\n--------------Pending List---------------" << endl;
    if (pending.holder.size() == 0) {
        cout << "\n\n--- Pending List Empty ---\n\n";
    }
    else {

        for (int i = 0; i < pending.holder.size(); i++) {
            cout << "\n" << i + 1 << ". " << pending.holder[i].name << endl << "Decription: " << pending.holder[i].description << endl << "Status: " << pending.holder[i].status << "\n\n";
        }
    }



    cout << "\n---------------Completed List-------------" << endl;
    if (done.holder.size() == 0) {
        cout << "\n\n--- Completed List Empty ----\n\n";
    }
    else {

        for (int i = 0; i < done.holder.size(); i++) {
            cout << "\n" << i + 1 << ". " << done.holder[i].name << endl << "Decription: " << done.holder[i].description << endl << "Status: " << done.holder[i].status << "\n\n";
        }
    }
} // end of displayHolders function

void removeTask(int number, TaskHolder& pending, TaskHolder& done) {
    pending.holder[number - 1].status = "Completed"; // change status of task to completed

    done.holder.push_back(pending.holder[number - 1]); // adds the task from the pending vector to the completed vector

    cout << "The task.... '" << pending.holder[number - 1].name << " ' was added to the completed list" << endl;

    pending.holder.erase(pending.holder.begin() + (number - 1)); // removes the task from the pending vector

    //displayHolders(pending, done);
    

    

   

}// End of removeTask function


void choices(TaskHolder& pending, TaskHolder& done, bool exit) {
    while (exit != true) {
        cout << "\n\n-------------------Main Menu--------------------\n\n";
        displayHolders(pending, done);

        cout <<"Enter in the numeric option from the menu \n\n1.Create a task\n2.Complete a task\n3.Exit program\n\n";
        
        
        string choice = userSaid();
        
        if (choice == "1") {
            cout << "You have chosen...create task\n\n";
            createTask(pending);
            cout << "\n\n********* RETURNING TO MAIN MENU***************\n\n";
            choices(pending, done, exit);
        }
        else if (choice == "2") {
            cout << "You have chosen...remove task\n\n";
            if (pending.holder.size() > 0) {
                displayHolders(pending, done);
                cout << "Which task do you want to remove?  Enter the numeric value of the option.\n\n";
                string pick = userSaid();
                removeTask(stoi(pick), pending, done);

            }
            else {
                cout << "*******************WARNING!!!*****************\nThere are no tasks to complete!\n";

            }
            
            cout << "\n\n********* RETURNING TO MAIN MENU***************\n\n";
            choices(pending, done, false);
        }
        else if (choice == "3") {
            cout << "\n\nYou have chosen...Exit Program\n\nThank you!  Come again!!!\n\nEnd of Program\n\n";
            exit = true;
            


        }
        else {
            cout << "\n\nINVALID ENTRY, PLEASE TRY AGAIN\n\n";
            choices(pending, done, false);
        }
    }
    
}


int main()
{
    bool exit = false;
    TaskHolder pending;
    TaskHolder completed; 

    cout << "Hello Welcome to the Task Manager 1.0 written in C++!\n\n";

    choices(pending, completed, exit);
   

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

