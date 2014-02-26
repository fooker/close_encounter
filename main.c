#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>


int main() {
  // Configure output pins
  DDRB = (1 << PB1)
       | (1 << PB2)
       | (1 << PB3)
       | (1 << PB4)
       | (1 << PB5)
       ;
  PORTB = ~( (0 << PB1)
           | (0 << PB2)
           | (0 << PB3)
           | (0 << PB4)
           | (0 << PB5))
           ;

  for (;;) {
    // Loop over the rounds
    for (uint8_t i = 0; i < 6; i++) {
      // Build channel mask with exactly two bits set
      uint8_t b1 = rand() % 5;
      uint8_t b2 = rand() % 4;
      if (b2 == b1) b2 = 4;

      uint8_t m1 = (uint8_t[]) { (1 << PB1),
                                 (1 << PB2),
                                 (1 << PB3),
                                 (1 << PB4),
                                 (1 << PB5) }[b1];
      uint8_t m2 = (uint8_t[]) { (1 << PB1),
                                 (1 << PB2),
                                 (1 << PB3),
                                 (1 << PB4),
                                 (1 << PB5) }[b2];

      PORTB = ~(m1 | m2);
      _delay_ms(600);

      // Turn of channels
      PORTB = ~( (0 << PB1)
               | (0 << PB2)
               | (0 << PB3)
               | (0 << PB4)
               | (0 << PB5) )
               ;
      _delay_ms(300);
    }

    // Delay a random time until next set of rounds (30..60] sendonds
    uint8_t s = 30 + (rand() % 30);
    for (uint8_t i = 0; i < s; i++) {
      _delay_ms(100);
    }
  }
}

