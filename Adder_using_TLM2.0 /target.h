#ifndef TARGET_H
#define TARGET_H

#include <systemc>   // SystemC core
#include <tlm>       // TLM definitions
#include <tlm_utils/simple_target_socket.h>  // Utility for target sockets
#include "adder_payload.h" // Custom payload

using namespace sc_core; 
using namespace tlm;     
using namespace std;     

// -----------------------------
// Target Module
// -----------------------------
struct Target : sc_module {
    tlm_utils::simple_target_socket<Target> socket;  
    // Target socket for receiving TLM transactions

    SC_CTOR(Target) {
        // Register blocking transport callback
        socket.register_b_transport(this, &Target::b_transport);
        // b_transport will be called whenever the initiator sends a transaction
    }

    void b_transport(tlm_generic_payload& trans, sc_time& delay) {
        // Called when a transaction arrives

        AdderPayload* payload =
            reinterpret_cast<AdderPayload*>(trans.get_data_ptr());  
        // Get the original payload from generic payload

        int a = payload->a; // Read input a
        int b = payload->b; // Read input b
        payload->sum = a + b;   // Compute sum

        // Print the computation with simulation time
        cout << "[Target] Received: " << a << " + " << b
             << " = " << payload->sum
             << " at time " << sc_time_stamp() << endl;

        trans.set_response_status(TLM_OK_RESPONSE); 
        // Mark transaction as successfully handled

        delay += sc_time(5, SC_NS);  
        // Add artificial processing delay for realism
    }
};

#endif // TARGET_H
