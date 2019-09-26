# serial-bus-servo

An Arduino library for controlling serial bus servo specially designed for
ZX361S / ZX01S / ZX01D.

## What is Serial Bus Servo

A serial bus servo is a digital servo, unlike the traditional PWM analog servos, the
serial bus servo can be controlled by digital commands via serial ports (UART), and you
can link several servos together, and control them individually and simultaneously.

Like most of the digital servos, the serial bus servos can be controlled
asynchronously while providing feedbacks including angle, temperature, voltage,
etc.

Most serial bus servos use special half-duplex UART bus as input source. This
means you only need one pin for both reading and writing.
