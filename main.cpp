#include <Windows.h> // include the Windows API library
#include <iostream>  // include the input/output stream library

using namespace std; // use the standard namespace

int main(int argc, char** argv) { // the main function takes command line arguments and returns an integer
    // Check if the user provided the correct number of arguments
    if (argc != 3) { // if the number of arguments is not 3
        cout << "Usage: injector.exe <pid> <path_to_dll>" << endl; // print a usage message
        return 1; // return with an error code
    }

    // Parse the process ID and DLL path from the command line arguments
    DWORD pid = atoi(argv[1]); // convert the first argument to a DWORD integer and store it in the 'pid' variable
    char* dllPath = argv[2]; // store the second argument as a string in the 'dllPath' variable

    // Open a handle to the target process
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); // call the OpenProcess function to open a handle to the process with the specified ID
    if (process == NULL) { // if the handle is NULL
        cout << "Failed to open process with PID " << pid << ": " << GetLastError() << endl; // print an error message
        return 1; // return with an error code
    }

    // Allocate memory in the target process for the DLL path
    LPVOID dllPathAddr = VirtualAllocEx(process, NULL, strlen(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); // call the VirtualAllocEx function to allocate memory in the target process for the DLL path string
    if (dllPathAddr == NULL) { // if the allocation fails
        cout << "Failed to allocate memory in process with PID " << pid << ": " << GetLastError() << endl; // print an error message
        return 1; // return with an error code
    }

    // Write the DLL path to the allocated memory in the target process
    if (!WriteProcessMemory(process, dllPathAddr, dllPath, strlen(dllPath), NULL)) { // call the WriteProcessMemory function to write the DLL path string to the allocated memory in the target process
        cout << "Failed to write to memory in process with PID " << pid << ": " << GetLastError() << endl; // print an error message
        return 1; // return with an error code
    }

    // Get the address of the LoadLibraryA function
    LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"); // call the GetProcAddress function to get the address of the LoadLibraryA function from the kernel32.dll library
    if (loadLibraryAddr == NULL) { // if the address is NULL
        cout << "Failed to get address of LoadLibraryA function: " << GetLastError() << endl; // print an error message
        return 1; // return with an error code
    }

    // Create a remote thread in the target process to
