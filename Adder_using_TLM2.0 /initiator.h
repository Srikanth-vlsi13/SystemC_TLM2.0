#ifndef INITIATOR_H
#define INITIATOR_H

#include <systemc>   // Include SystemC core definitions
#include <tlm>       // Include TLM-2.0 definitions
#include <tlm_utils/simple_initiator_socket.h>  // Include utility for initiator sockets
#include "adder_payload.h"  // Include custom payload structure

using namespace sc_core;  // SystemC core namespace
using namespace tlm;      // TLM namespace
using namespace std;      // C++ standard library

// -----------------------------
// Initiator Module
// -----------------------------
struct Initiator : sc_module {
    tlm_utils::simple_initiator_socket<Initiator> socket;  
    // Initiator socket to communicate with the target using TLM-2.0

    SC_CTOR(Initiator) { 
        SC_THREAD(process);   
        // Use SC_THREAD so that we can use wait() to simulate delays between transactions
    }

    void process() {  
        // Process thread: generates and sends transactions to the target

        // 5 testcases: pairs of numbers to send
        int testcases[5][2] = {
            {7, 5}, {10, 20}, {3, 9}, {15, -4}, {100, 200}
        };

        for (int i = 0; i < 5; i++) {  // Loop through all testcases
            tlm_generic_payload trans;    // TLM generic payload for this transaction
            sc_time delay = SC_ZERO_TIME; // Initialize delay to zero

            // Create custom payload for this transaction
            AdderPayload* payload = new AdderPayload;
            payload->a = testcases[i][0]; // Set input a
            payload->b = testcases[i][1]; // Set input b
            payload->sum = 0;             // Initialize sum (target will compute)

            // -----------------------------
            // Setup generic payload fields
            // -----------------------------
            trans.set_command(TLM_WRITE_COMMAND); // Command type: write (initiator → target)
            trans.set_address(0);                 // Address (not used here, but required)
            trans.set_data_ptr(reinterpret_cast<unsigned char*>(payload));  
            // Pointer to the payload, cast to unsigned char* as TLM expects bytes
            trans.set_data_length(sizeof(AdderPayload)); // Number of bytes in the payload
            trans.set_streaming_width(sizeof(AdderPayload)); // Width for streaming (full payload)
            trans.set_byte_enable_ptr(0);   // No byte-enable mask
            trans.set_dmi_allowed(false);   // Disable direct memory interface (not used here)
            trans.set_response_status(TLM_INCOMPLETE_RESPONSE);  
            // Initialize response status to incomplete

            // Print sending information with current simulation time
            cout << "\n[Initiator] Sending a = " << payload->a
                 << ", b = " << payload->b
                 << " at time " << sc_time_stamp() << endl;

            // -----------------------------
            // Call TLM blocking transport
            // -----------------------------
            socket->b_transport(trans, delay); 
            // Sends transaction to target and waits until target returns

            // Check transaction status returned by target
            if (trans.is_response_error()) {
                cout << "[Initiator] Transaction Error: "
                     << trans.get_response_string() << endl;
            } else {
                cout << "[Initiator] Transaction OK: "
                     << trans.get_response_string()
                     << ", Result sum = " << payload->sum << endl;
            }

            wait(10, SC_NS); // Wait 10 ns before sending next transaction
        }
    }
};

#endif // INITIATOR_H
