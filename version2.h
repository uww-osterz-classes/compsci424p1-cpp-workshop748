/* COMPSCI 424 Program 1
   Name:

   version2.h: contains the code to implement the process creation
   hierarchy for Version 2, which does not use linked lists.

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

#ifndef VERSION2_H
#define VERSION2_H

// You may need to add more #include directives.
// Remember: use <angle brackets> for standard C++ headers/libraries
// and "double quotes" for headers in the same directory as this file.
#include <iostream>

using namespace std; // I normally use this, but feel free to delete it

struct PCBV2
{
    int parent = -1;
    int firstChild = -1;
    // YungerSibling
    int next = -1;
    // OlderSibling
    int prev = -1;
    bool is_initialized=false;
};
class Version2 {
private: // it's good OOP practice to make data members private
  PCBV2 array[16];

public:  // all methods are normally public
    Version2() {
        /* Default constructor. Use this to allocate (if needed) and
        initialize the PCBV2 array, create the PCBV2 for process 0, and do
        any other initialization that is needed.
        */
        array[0].is_initialized = true;
        for (int i = 0; i < 16; i++) {
            array[i].next = i;
            array[i].prev = i;

        }
    }

    ~Version2() {
        /* Destructor. If you allocated anything with "new" during
        the lifetime of this object, and you haven't yet "delete"d
        it, "delete" it (using the "delete" keyword) here.
        */
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
                array[i].is_initialized = true;
                
                array[i].parent = parentPid;
                if (array[parentPid].firstChild == -1)
                {
                    array[parentPid].firstChild = i;
                }
                else {
                    int head = array[parentPid].firstChild;
                    int last = array[head].prev;
                    array[i].prev = last;
                    array[i].next = head;
                    array[head].prev = i;
                    array[last].next = i;

                }
                return i;
            }
        }
        // Assuming you've found the PCBV2 for parentPid in the PCBV2 array:
        // 1. Allocate and initialize a free PCBV2 object from the array
        //    of PCBV2 objects

        // 2. Connect the new PCBV2 object to its parent, its older
        //    sibling (if any), and its younger sibling (if any)

        // You can decide what the return value(s), if any, should be.
        return 0; // often means "success" or "terminated normally"
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
        // Assuming you've found the PCBV2 for targetPid in the PCBV2 array:
        // 1. Recursively destroy all descendants of targetPid, if it
        //    has any, and mark their PCBV2s as "free" in the PCBV2 array 
        //    (i.e., deallocate them)
        auto delete_value = [&](int i) {
                destroy(i);
                array[i].next = i;
                array[i].firstChild = -1;
                array[i].prev = i;
                array[i].parent = -1;
                array[i].is_initialized = false;
            };
        if (array[targetPid].firstChild != -1) {
            int head = array[targetPid].firstChild;
            int next;
            
            for (int i = array[head].next; i != head; i =next)
            {
                next = array[i].next;
                delete_value(i);
            }
            delete_value(head);
        }
        if(array[targetPid].parent != -1) {
            array[array[targetPid].prev].next = array[targetPid].next;
            array[array[targetPid].next].prev = array[targetPid].prev;
            if(array[array[targetPid].parent].firstChild == targetPid) {
                array[array[targetPid].parent].firstChild = -1;
            }
        }
        array[targetPid].next = targetPid;
        array[targetPid].firstChild = -1;
        array[targetPid].prev = targetPid;
        array[targetPid].parent = -1;
        array[targetPid].is_initialized = false;
        // 2. Adjust connections within the hierarchy graph as needed to
        //    re-connect the graph

        // 3. Deallocate targetPid's PCBV2 and mark its PCBV2 array entry
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
            std::cout << "Process " << i << ": parent is " << array[i].parent;
            if (array[i].firstChild == -1)
            {
                std::cout << " and has no children";
            }
            else {
                std::cout << " and children are ";
                int head = array[i].firstChild;
                auto print_value = [&](int j) {
                    std::cout << j;

                    if (head != array[j].next) {
                        std::cout << ' ';
                    }
                };
                print_value(head);
                for (int j = array[head].next; j != head; j = array[j].next)
                {
                    print_value(j);
                }
            }
            std::cout << std::endl;
        }
    }

    /* If you need or want more functions, feel free to add them. */

};

#endif  // VERSION2_H
