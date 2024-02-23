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
#include <string_view>
#include "version1.h" // file containing Version 1 code
#include "version2.h" // file containing Version 2 code

using namespace std; // I normally use this, but feel free to delete it
struct numParse 
{
int numVale;
std::string_view command;
};


    numParse me(string& command) {

        std::cout << " please enter the fallowing command of Create , destroy, or end ";
        std::getline(std::cin, command);
        const char* mander = command.c_str();
        const char* start = mander;
        int state = 0;
        bool has_number = false;
        bool initialized = false;
        int num_value;
        std::string_view a;
        while (*mander) {
            switch (state) {
            case 0:
            {
                if (isspace(*mander))
                {
                    state = 1;
                    a = std::string_view(start, (size_t)mander - (size_t)start);
                    initialized = true;
                }
                break;
            }
            case 1:
            {
                if (!isspace(*mander)) {
                    state = 2;
                    continue;
                }
            }
            break;
            case 2:
            {
                has_number = isdigit(*mander);
                num_value = atoi(mander);
                if (num_value >= 0 || num_value < 16)
                {
                    goto T_rex;
                }
            }
            break;
            }

            mander++;
        }
    T_rex:
        numParse er;
        if (!initialized) {
            er.command = start;
            return er;
        }
        er.command = a;
        er.numVale = num_value;
        return er;
    };

int main(int argc, char *argv[]) {
        // Main program goes here. The required steps have been copied into
// this file as comments. Feel free to add more comments to help
// you understand your code, or for any other reason.
// 1. Ask the user to enter commands of the form "create N", 
        std::vector<uint8_t> createVect;
        string commando;

        //   "destroy N", or "end", where N is an integer between 0 and 15.
    velociraptor:
        auto botanist = me(commando);
        std::string_view command = botanist.command;
        uint8_t num = (uint8_t)botanist.numVale;
        // failing test case is  p1DestroyNoChildV1
        if (command == "create")
        {
            createVect.push_back(num << 1);
            std::cout<<"**********DEBUG-DELETEME: Create process with parent "<<(int)num<<std::endl;
        }
        else if (command == "destroy")
        {
            std::cout<<"**********DEBUG-DELETEME: Destroy process with parent "<<(int)num<<std::endl;
            createVect.push_back((num << 1) | 1);
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
        std::cout<<"**********DEBUG-DELETEME: V1"<<std::endl;
        for (auto mobile : createVect) {
            if (mobile & 1)
            {
                v1.destroy(mobile >> 1);

            }
            else
            {
                v1.create(mobile >> 1);

            }
            std::cout<<"**********DEBUG-DELETEME: MARK START"<<std::endl;
        
            v1.showProcessInfo();
            std::cout<<"**********DEBUG-DELETEME: MARK END"<<std::endl;
        
        }
        std::cout<<"**********DEBUG-DELETEME: V2"<<std::endl;
        
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
            std::cout<<"**********DEBUG-DELETEME: MARK START"<<std::endl;
        
            v2.showProcessInfo();
            std::cout<<"**********DEBUG-DELETEME: MARK END"<<std::endl;
        
        }
std::cout<<"**********DEBUG-DELETEME: END"<<std::endl;
        
        // 7. Store the current system time in a variable
        auto time = std::chrono::high_resolution_clock::now();

        // ... then run the command sequence 200 times with Version 1.
        for (int i = 0; i < 200; i++)
        {
            Version1 v1_p2;
            for (auto mobile : createVect) {
                if (mobile & 1)
                {
                    v1_p2.destroy(mobile >> 1);

                }
                else
                {
                    v1_p2.create(mobile >> 1);

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
