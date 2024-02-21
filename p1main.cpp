/* COMPSCI 424 Program 1
   Name:
   
   p1main.cpp: contains the main function for this program.

   This is a template. Feel free to edit any of these files, even
   these pre-written comments or my provided code. You can add any
   classes, methods, and data structures that you need to solve the
   problem and display your solution in the correct format.
*/

// You will probably need to add more #include directives.
// Remember: use <angle brackets> for standard C++ headers/libraries
// and "double quotes" for headers in the same directory as this file.
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "version1.h" // file containing Version 1 code
#include "version2.h" // file containing Version 2 code

using namespace std; // I normally use this, but feel free to delete it

int main(int argc, char *argv[]) {
   // Main program goes here. The required steps have been copied into
// this file as comments. Feel free to add more comments to help
// you understand your code, or for any other reason.
auto askNum = [&]()
{
    bool is_valid = false;
    while (is_valid != true)
    {
        std::cout << "please enter a number between 0 and 15: ";
    std::string num_str;
    std::getline(std::cin, num_str);
    int num = std::stoi(num_str);
    if (num >= 0 && num <= 15)
    {
        return num;

    }
    if (is_valid == false)
    {
    std::cout << "you did not enter a number between 0 and 15 please try again";
    }
     }
   return 0;
};
// 1. Ask the user to enter commands of the form "create N", 
std::vector<uint8_t> createVect;
//   "destroy N", or "end", where N is an integer between 0 and 15.
velociraptor:
std:string command;
std::cout << " please enter the fallowing command of Create , destroy, or end ";
std::getline(std::cin, command);
if ( command == "create")
{
    uint8_t num = (uint8_t)askNum();
    createVect.push_back(num << 1);
}
else if (command == "destroy")
{
    uint8_t num = (uint8_t)askNum();
    createVect.push_back((num <<1) | 1);
}
else if (command == "end")
{
    goto exit;
}
else {
    std::cout << " you messed up and didn't enter the asked values." << std::endl << "have an alright day";
    return -1;
}
goto velociraptor;
exit:
// 2. While the user has not typed "end", continue accepting
//    commands. Add each command to a list of actions to take while
//    you run the simulation. 
// 3. When the user types "end" (or optionally any word that is not
//    "create" or "destroy"), stop accepting commands and complete
//    the following steps.
//
// Hint: Steps 2 and 3 refer to the same loop. ;-)

// 4. Create an object of the Version 1 class and an object of the
//    Version 2 class.
Version1 v1;
Version2 v2;
// 5. Run the command sequence once with the Version 1 object, 
//    calling its showProcessTree method after each command to show
//    the changes in the tree after each command.
for (auto mobile : createVect) {
    if (mobile & 1)
    {
        v1.destroy(mobile>>1);
        
    }
    else
    {
        v1.create(mobile >> 1);
        
    }
    v1.showProcessInfo();
}
//v1.showProcessInfo();
// 6. Repeat step 5, but with the Version 2 object.
for (auto mobile : createVect) {
    if (mobile & 1)
    {
        v2.destroy(mobile >> 1);

    }
    else
    {
        v2.create(mobile >> 1);

    }
    v2.showProcessInfo();
}
      
// 7. Store the current system time in a variable
auto time = std::chrono::high_resolution_clock::now();

// ... then run the command sequence 200 times with Version 1.
for(int i =0; i<200;i++)
{ 
    Version1 v1_p2;
    for (auto mobile : createVect) {
        if (mobile & 1)
        {
            v1_p2.destroy(mobile >> 1);

        }
        else
        {
            v1_p2.create(mobile >>1);

        }
    }
}
// ... After this, store the new current system time in a second
//     variable. Subtract the start time from the end time to get
//     the Version 1 running time, then display the Version 1
//     running time.
auto bots = std::chrono::high_resolution_clock::now();
auto robots = bots - time;
std::cout << robots.count() << std::endl;


// 8. Repeat step 7, but with the Version 2 object.
auto time2 = std::chrono::high_resolution_clock::now();
for (int i = 0; i < 200; i++)
{
    Version2 v2_p2;
    for (auto mobile : createVect) {
        if (mobile & 1)
        {
            v2_p2.destroy(mobile >> 1);

        }
        else
        {
            v2_p2.create(mobile >> 1);
        };
    }
}
auto bots2 = std::chrono::high_resolution_clock::now();
auto robots2 = bots2 - time2;
std::cout << robots2.count() << std::endl;
// Don't forget to delete anything that you created with "new"!

cout << "Builds without errors and runs to completion.\n";

return 0; // tells the OS that the program terminated normally
}
