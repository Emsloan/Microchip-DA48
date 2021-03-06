/***********************************************************************|
| megaAVR Configurable Custom Logic library                             |
|                                                                       |
| Five_input_NOR.ino                                                    |
|                                                                       |
| A library for interfacing with the megaAVR Configurable Custom Logic. |
| Developed in 2019 by MCUdude.                                         |
| https://github.com/MCUdude/                                           |
|                                                                       |
| In this example we use two logic blocks to get five inputs.           |
| The output of block 1 is connected to one of the inputs of block 0.   |
| With the correct truth tables values we can make the output of        |
| block 0 go high when all inputs are low.                              |
|                                                                       |
| See Microchip's application note TB3218 for more information.         |
|***********************************************************************/

#include <Logic.h>

void setup() {
  // Initialize logic block 1
  // Logic block 1 has three inputs, PC0, PC1 and PC2 on ATmega parts
  // Logic block 1 inputs are PC3, PC4, and PC5 on ATtiny parts, but
  // only 24-pin parts have all three. 20-pin parts have PC3 only.
  // Because PA0 is not available on ATtiny under most situations
  // on megaTinyCore, we use input0 of logic block 0 as link from
  // other logic block. On the 20-pin parts, we also use the event system to
  // get the other two inputs from other pins.


  // Here, input2 is taken from the other
  // This example shows how this can be worked around for 20-pin parts
  // It's output is disabled because we connect the output signal to block 0 internally
  Logic1.enable = true;               // Enable logic block 1
  Logic1.input0 = in::input_pullup;   // Set PC0 as input with pullup
  Logic1.input1 = in::input_pullup;   // Set PC1 as input with pullup
  Logic1.input2 = in::input_pullup;   // Set PC2 as input with pullup
  Logic1.output = out::disable;       // Enable output pin
  Logic1.filter = filter::disable;    // No output filter enabled
  Logic1.truth = 0x01;                // Set truth table

  // Initialize logic block 0
  // Logic block 0 has three inputs, PA0, PA1 and PA2.
  // Block 0 output on PA3 on ATmega, PA5 on ATtiny.

  Logic0.enable = true;               // Enable logic block 0
  Logic0.input0 = in::link;           // Route output from block 1 to this input internally
  Logic0.input1 = in::input_pullup;   // Set PA1 as input with pullup
  Logic0.input2 = in::input_pullup;   // Set PA2 as input with pullup
  Logic0.output = out::enable;        // Enable logic block 0 output pin (PA3 (ATmega) or PA5 (ATtiny))
  Logic0.filter = filter::disable;    // No output filter enabled
  Logic0.truth = 0xFE;                // Set truth table

  // Initialize logic block 0 and 1
  Logic0.init();
  Logic1.init();

  // Start the AVR logic hardware
  Logic::start();
}

void loop() {
  // When using configurable custom logic the CPU isn't doing anything!
}
