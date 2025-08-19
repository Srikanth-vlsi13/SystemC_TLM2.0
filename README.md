# SystemC_TLM2.0
Collection of SystemC &amp; TLM 2.0 examples for learning and projects
# SystemC Repository

SystemC TLM 2.0 (Transaction-Level Modeling)

SystemC TLM 2.0 (Transaction-Level Modeling) is a modeling methodology for high-level simulation of hardware/software systems. It allows modeling of communication between modules using transactions rather than pin-level signals, improving simulation speed and abstraction.

TLM-2.0 is widely used in SoC design, verification, and early software development, enabling fast functional simulation and architectural exploration.

Key Concepts

1. Transaction
  A transaction represents a data transfer between modules (e.g., read/write).

  Carried by tlm_generic_payload in TLM-2.0.
  
  Can include data, address, command type, and response status.
  

3. Modules
   Initiator: Generates transactions (e.g., processor sending a request).
   Target: Responds to transactions (e.g., memory or peripheral).
   Sockets: Connect initiator and target:
    tlm_utils::simple_initiator_socket
    tlm_utils::simple_target_socket

4. Transport Methods
  1.Blocking Transport (b_transport):
    Simple method where initiator waits until the target completes the transaction.
    Can include delays for timing accuracy.
  
  2.Non-Blocking Transport (nb_transport_fw / nb_transport_bw):
    Supports pipelining and temporal decoupling for higher simulation efficiency.


Features:
  1.High-level modeling abstraction (ignore pin-level signals).
  
  2.Supports temporal decoupling with simulation delays.
  
  3.Allows easy verification of module interactions and functional correctness.
  
  4.Compatible with both C++ software simulation and hardware prototyping.

Example Structure
project/
│
├── adder_payload.h       # Defines transaction payload
├── initiator.h           # Initiator module
├── target.h              # Target module
├── main.cpp              # sc_main, bind modules, start simulation
└── README.md             # Project documentation

How to Run:
  1.Install SystemC library.
  2.Compile using a C++ compiler:
      g++ -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux main.cpp -lsystemc -o tlm_sim
  3.Run the simulation:
      ./tlm_sim
