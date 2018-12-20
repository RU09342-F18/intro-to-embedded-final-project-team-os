#include <msp430.h> 
#include <stdint.h>
#include <stdbool.h>

volatile float light = 0;
volatile int move = 0;
volatile int temp = 0;
int TensChar = 0;           // Sets the 10's place of the temperature value in degrees Celsius
int OnesChar = 0;

void UARTSetup(void)
{
    P4SEL |= (BIT4+BIT5);                   // Allows BIT4 to become the TXD output and BIT5 to become the RXD input
    UCA1CTL1 |= UCSWRST;                    // State Machine Reset + Small Clock Initialization
    UCA1CTL1 |= UCSSEL_2;                   // Sets USCI Clock Source to SMCLK
    UCA1BR0 = 9;			    // Sets Baud Rate to 115200
    UCA1BR1 = 0;
    UCA1MCTL = UCBRS_1+UCBRF_0;               // Modulation UCBRSx=1, UCBRFx=0
    UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**                  // Initialize USCI State Machine
    UCA1IE |= UCRXIE;                       // Enable USCI_A0 RX interrupt
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    ADC12CTL0 = ADC12SHT03 + ADC12ON;         // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP + ADC12DIV_7 + ADC12SSEL_1;                     // Use sampling timer

    ADC12IE |= 0x01 | BIT1;                           // Enable interrupt
    ADC12CTL0 |= ADC12ENC;
    P6SEL |= 0x01 | BIT1;                              // P6.0 ADC option select

    UARTSetup();

    P1IE |= BIT5;
    P1IES |= BIT5;			// Detects a low to high transition at P1.5
    P2IE |= BIT0;
    P2IES |= BIT0;			// Detects a low to high transition at P2.0
    P2IFG &= ~BIT0;

	while(1)
	{
	    P2IES ^= BIT0;
	    ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
	    P1IES ^= BIT5;
	    __bis_SR_register(GIE);     // Global Interrupt Enable
	    __no_operation();                       // For debugger

	    __delay_cycles(750000);
	    if ((light == 1) | (move == 1))		// If the light is on or motion is detected, the room is occupied
	    {
	        while(!(UCA1IFG & UCTXIFG));
	       UCA1TXBUF = 'R';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'o';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'o';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'm';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = ' ';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'O';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'c';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'c';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'u';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'p';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'i';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'e';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'd';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = '.';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = ' ';
            while(!(UCA1IFG & UCTXIFG));
            UCA1TXBUF = '\n';
	    }
	    else		// Else the room is inoccupied
	    {
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'R';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'o';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'o';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'm';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = ' ';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'N';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'o';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 't';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = ' ';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'O';
	        while(!(UCA1IFG & UCTXIFG));
            UCA1TXBUF = 'c';
            while(!(UCA1IFG & UCTXIFG));
            UCA1TXBUF = 'c';
            while(!(UCA1IFG & UCTXIFG));
            UCA1TXBUF = 'u';
            while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'p';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'i';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'e';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = 'd';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = '.';
	        while(!(UCA1IFG & UCTXIFG));
	        UCA1TXBUF = ' ';
            while(!(UCA1IFG & UCTXIFG));
            UCA1TXBUF = '\n';
	    }
	}
}
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC12_VECTOR))) ADC12_ISR (void)
#else
#error Compiler not supported!
#endif
{
    __delay_cycles(750000);
    ADC12CTL0 &= ~ADC12SC; // End Sampling / Conversion
    switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:                                  // Vector  6:  ADC12IFG0
      temp = (ADC12MEM0) * ((5-0.5)/4096) * (1/.01) - 79; // Bits * (Volts/Bits) * (Celsius/Volts) Converts ADC output from bits to degrees Celsius

       TensChar = temp / 10;           // Sets the 10's place of the temperature value in degrees Celsius
       OnesChar = temp - TensChar*10;  // Sets the 1's place of the temperature value in degrees Celsius

       while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'T';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'e';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'm';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'p';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'e';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'r';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'a';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 't';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'u';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'r';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'e';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = ':';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = ' ';

             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = TensChar + 48;         // Sends the 10's place value over UART
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = OnesChar + 48;         // Sends the 1's place value over UART
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = 'C';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = ' ';
             while(!(UCA1IFG & UCTXIFG));
             UCA1TXBUF = '\n';

       __bic_SR_register_on_exit(LPM0_bits);   // Exit active CPU
  case 8:  break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                           // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1 (void)
{
    while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 'L';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 'i';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 'g';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 'h';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 't';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = ' ';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 'i';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = 's';
                while(!(UCA1IFG & UCTXIFG));
                UCA1TXBUF = ' ';

    if ((P1IES & BIT5) == !BIT5) 		// Detects low to high transition stating that a light is on
    {
                  light = 1;
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = 'O';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = 'N';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = ' ';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = '.';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = '\n';

    }
    else if ((P1IES & BIT5) == BIT5)		// Detects high to low transition stating that a light is off
    {
                  light = 0;
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = 'O';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = 'F';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = 'F';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = '.';
                  while(!(UCA1IFG & UCTXIFG));
                  UCA1TXBUF = '\n';
    }
    P1IFG &= 0;

}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2 (void)
{
                       if ((P2IES & BIT0) == !BIT0)			// Detects a high to low transition stating that motion is detected
                       {
                       move = 1;
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'M';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'o';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 't';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'i';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'o';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'n';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = ' ';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'D';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'e';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 't';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'e';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'c';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 't';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'e';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = 'd';    // Enter
                       while(!(UCA1IFG & UCTXIFG));
                       UCA1TXBUF = '\n';    // Enter
                       }
                       else if ((P2IES & BIT0) == BIT0)			// Detects a low to high transition stating that motion is not detected
                       {
                           move = 0;
                       }
                       P2IFG &= ~BIT0;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A1_VECTOR))) USCI_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(UCA1IV,4))
    {
    case 0:break;                             // Vector 0 - no interrupt
    case 2:break;                                  // Vector 2 - RXIFG
    case 4:break;                             // Vector 4 - TXIFG
    default: break;
    }
}
