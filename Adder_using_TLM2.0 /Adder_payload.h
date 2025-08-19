#ifndef ADDER_PAYLOAD_H   // Header guard start: prevents multiple inclusion of this file
#define ADDER_PAYLOAD_H

// -----------------------------
// Custom Payload
// -----------------------------
// This struct defines the data structure that will be carried inside TLM transactions.
// It holds the inputs (a, b) and the result (sum) for the adder operation.
struct AdderPayload {
    int a;    // first operand
    int b;    // second operand
    int sum;  // result (computed by target)
};

#endif // ADDER_PAYLOAD_H   // Header guard end

