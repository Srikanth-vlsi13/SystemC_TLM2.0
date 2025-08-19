#include <systemc>   // SystemC core
#include "initiator.h"  // Initiator module
#include "target.h"     // Target module

int sc_main(int argc, char* argv[]) {
    // Instantiate initiator and target
    Initiator initiator("initiator");  
    Target target("target");

    // Bind initiator socket to target socket
    // This connects the TLM communication channel
    initiator.socket.bind(target.socket);

    // Start the simulation
    sc_start();  
    // Simulation runs until all processes (SC_THREAD) are complete

    return 0; // Return 0 → normal exit
}
