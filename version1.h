/* COMPSCI 424 Program 1
   Name:

   version1.h: contains the code to implement the process creation
   hierarchy for Version 1, which uses linked lists.

   This is a template. Feel free to edit any of these files, even
   these pre-written comments or my provided code. You can add any
   classes, methods, and data structures that you need to solve the
   problem and display your solution in the correct format.

   C++ style note:
   This .h file is set up to include both declarations and code. It's
   considered good practice for .h files to contain only declarations
   and for most or all non-declaration code to be in .cpp files (which
   #include the relevant .h file(s)). However, if you're not used to
   compiling and linking multiple .cpp (or .cc or .C) files at once,
   putting both declarations and code in the .h files is easier.

   If you prefer to separate your declarations and code, feel free to
   do that. GitHub Classroom is set up to compile all .cpp, .cc, and
   .C files that are in your repository.
*/

#ifndef VERSION1_H
#define VERSION1_H

// You may need to add more #include directives.
// Remember: use <angle brackets> for standard C++ headers/libraries
// and "double quotes" for headers in the same directory as this file.
#include <iostream>
#include<list>
using namespace std; // I normally use this, but feel free to delete it

struct PCB {
    bool is_initialized = false;
    PCB* parent = nullptr;
    list<PCB*> children;
};


class Version1 {
private: // it's good OOP practice to make data members private
    PCB array[16];

public:  // all methods are normally public
    Version1() {
        /* Default constructor. Use this to allocate (if needed) and
        initialize the PCB array, create the PCB for process 0, and do
        any other initialization that is needed.
        */
        array[0].is_initialized = true;
    }

    ~Version1() {
        /* Destructor. If you allocated anything with "new" during
        the lifetime of this object, and you haven't yet "delete"d
        it, "delete" it (using the "delete" keyword) here.
        */
    }

    int convertToPid(PCB* ptr) {
        if (!ptr) {
            return -1;
        }
        int ret = (((size_t)ptr) - ((size_t)array)) / sizeof(PCB);
        return ret;
    }

    /* Creates a new child process of process with ID parentPid.
    */
    int create(int parentPid) {
        // If parentPid is not in the process hierarchy, do nothing; 
        // your code may return an error code or message in this case,
        // but it should not halt.

        if (array[parentPid].is_initialized == false)
        {
            return -1;
        }
        for (int i = 0; i < 16; i++)
        {
            if (array[i].is_initialized == false)
            {
                array[i].parent = &array[parentPid];
                array[i].parent->children.push_back(&array[i]);
                array[i].is_initialized = true;
                return i;
            }
        }
        // Assuming you've found the PCB for parentPid in the PCB array:
        // 1. Allocate and initialize a free PCB object from the array
        //    of PCB objects

        // 2. Insert the newly allocated PCB object into parentPid's
        //    list of children

        // You can decide what the return value(s), if any, should be.
        return -1; // often means "success" or "terminated normally"
    }

    /* Recursively destroys the process with ID parentPid and all of
       its descendant processes (child, grandchild, etc.).
    */
    int destroy(int targetPid) {
        // If targetPid is not in the process hierarchy, do nothing; 
        // your code may return an error code or message in this case,
        // but it should not halt

        if (array[targetPid].is_initialized == false)
        {
            return -1;
        }
        for (PCB* i : array[targetPid].children) {
            int pid = convertToPid(i);
            destroy(pid);
            i->is_initialized = false;
            i->children.clear();
            i->parent = nullptr;
        }
        if(array[targetPid].parent != nullptr) {

        array[targetPid].parent->children.remove(&array[targetPid]);

    }
        array[targetPid].is_initialized = false;
        array[targetPid].children.clear();
        array[targetPid].parent = nullptr;
        // Assuming you've found the PCB for targetPid in the PCB array:
        // 1. Recursively destroy all descendants of targetPid, if it
        //    has any, and mark their PCBs as "free" in the PCB array 
        //    (i.e., deallocate them)

        // 2. Remove targetPid from its parent's list of children

        // 3. Deallocate targetPid's PCB and mark its PCB array entry
        //    as "free"

        // You can decide what the return value(s), if any, should be.
        return 0; // often means "success" or "terminated normally"
    }

    /* Traverse the process creation hierarchy graph, printing
       information about each process as you go. See Canvas for the
       *required* output format.

       You can directly use "cout" or "printf" statements to send
       the required output to stdout, or you can change the return
       type of this function to return the text to the main program
       for printing. It's your choice.
    */
    void showProcessInfo() {
        //  Process 0: parent is -1 and children are 1 2
        for (int i = 0; i < 16; i++) {
            if (!array[i].is_initialized) {
                continue;
            }
            std::cout << "Process " << i << ": parent is " << convertToPid(array[i].parent);
            if (array[i].children.empty())
            {
                std::cout << " and has no children";
            }
            else {
                std::cout << " and children are ";
                for (std::list<PCB*>::iterator j = array[i].children.begin(); j != array[i].children.end();)
                {
                    int numb = convertToPid(*j);
                    std::cout << numb;
                    j++;
                    if (j != array[i].children.end()) {
                        std::cout << ' ';
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    /* If you need or want more functions, feel free to add them. */

};
#endif