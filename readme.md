This is a work in progress for an attempt to simplify use of timers on the Arduino Due.

For now this class enables a simple timer set, with interrupt on a regular interval, and the ability to attach a user-defined function to the interrupt handler.

Timer is declared either by its number (from 0 to 8) or by its TC (0 to 2) + channel (0 to 2) couple:

TimerDue firstTimer = TimerDue(TC0, 1) // Create a counter using Channel 1 of Timer Counter 0.
TimerDue secondTimer = TimerDue(5) // Create a coutner using Channel 2 of Timer Counter 1

Timer has to be inited, several functions are provided, so you can do the init using microsecond, millisecond or second delay, or give a frequency, or simply gives a numbre of CPU cycles.