# avr-t85-adc-dump

This small projects configures the attiny85 ADC to collect samples at its maximum nominal rate and write them all to the output UART pin. This is useful e.g. to analyze its noise properties or for calibration. 

Two modes supported, see the FREE_RUNNING definition: 

- free running, in which the ADC start the next conversion immediately after the previous one. In this mode the overall output rate is the highest.
- low noise, in which the ADC is enabled while the MCU is in the sleep mode, to reduce digitally induced noise.

Every 256 samples, the ADC rotates between measuring the input, temperature sensor, and zero. Note that the very first samples are not guaranteed to be accurate, there may also be some transient noise immediately after switching inputs. In a real program these samples should be disarded, but the purpose of this tool to look at these artifacts too. 

The UART is a transmit-only software UART written in assembly, and working at a fixed baud rate of 921600, using PB1.
