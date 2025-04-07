#include <JTEncode.h>
#include <rs_common.h>
#include <int.h>
#include <string.h>
#include <cstdio>
#include <iostream>

// Mode defines
#define JT9_TONE_SPACING 174  // ~1.74 Hz
#define JT65_TONE_SPACING 269 // ~2.69 Hz
#define JT4_TONE_SPACING 437  // ~4.37 Hz
#define WSPR_TONE_SPACING 146 // ~1.46 Hz
#define FSQ_TONE_SPACING 879  // ~8.79 Hz
#define FT8_TONE_SPACING 625  // ~6.25 Hz

#define JT9_DELAY 576     // Delay value for JT9-1
#define JT65_DELAY 371    // Delay in ms for JT65A
#define JT4_DELAY 229     // Delay value for JT4A
#define WSPR_DELAY 683    // Delay value for WSPR
#define FSQ_2_DELAY 500   // Delay value for 2 baud FSQ
#define FSQ_3_DELAY 333   // Delay value for 3 baud FSQ
#define FSQ_4_5_DELAY 222 // Delay value for 4.5 baud FSQ
#define FSQ_6_DELAY 167   // Delay value for 6 baud FSQ
#define FT8_DELAY 159     // Delay value for FT8

#define JT9_DEFAULT_FREQ 14078700UL
#define JT65_DEFAULT_FREQ 14078300UL
#define JT4_DEFAULT_FREQ 14078500UL
#define WSPR_DEFAULT_FREQ 14097200UL
#define FSQ_DEFAULT_FREQ 7105350UL // Base freq is 1350 Hz higher than dial freq in USB
#define FT8_DEFAULT_FREQ 14075000UL

#define DEFAULT_MODE MODE_JT65

// Enumerations
enum mode
{
    MODE_JT9,
    MODE_JT65,
    MODE_JT4,
    MODE_WSPR,
    MODE_FSQ_2,
    MODE_FSQ_3,
    MODE_FSQ_4_5,
    MODE_FSQ_6,
    MODE_FT8
};

// Class instantiation
JTEncode jtencode;

// Global variables
unsigned long freq;
char message[] = "N0CALL AA00";
char call[] = "N0CALL";
char loc[] = "AA00";
uint8_t dbm = 27;
uint8_t tx_buffer[255];
enum mode cur_mode = DEFAULT_MODE;
uint8_t symbol_count;
uint16_t tone_delay, tone_spacing;

// Loop through the string, transmitting one character at a time.
void encode()
{
    uint8_t i;

    // Now print the channel symbols
    if (cur_mode == MODE_FSQ_2 || cur_mode == MODE_FSQ_3 || cur_mode == MODE_FSQ_4_5 || cur_mode == MODE_FSQ_6)
    {
        uint8_t j = 0;

        while (tx_buffer[j++] != 0xff)
            ;

        symbol_count = j - 1;
    }

    for (i = 0; i < symbol_count; i++)
    {
        std::cout << tx_buffer[i] << ", " << std::endl;
    }
}

void set_tx_buffer()
{
    // Clear out the transmit buffer
    memset(tx_buffer, 0, 255);

    // Set the proper frequency and timer CTC depending on mode
    switch (cur_mode)
    {
    case MODE_JT9:
        jtencode.jt9_encode(message, tx_buffer);
        break;
    case MODE_JT65:
        jtencode.jt65_encode(message, tx_buffer);
        break;
    case MODE_JT4:
        jtencode.jt4_encode(message, tx_buffer);
        break;
    case MODE_WSPR:
        jtencode.wspr_encode(call, loc, dbm, tx_buffer);
        break;
    case MODE_FT8:
        jtencode.ft8_encode(message, tx_buffer);
        break;
    case MODE_FSQ_2:
    case MODE_FSQ_3:
    case MODE_FSQ_4_5:
    case MODE_FSQ_6:
        jtencode.fsq_dir_encode(call, "n0call", ' ', "hello world", tx_buffer);
        break;
    }
}

void setup()
{
    // Set the mode to use
    cur_mode = MODE_JT65;

    // Set the proper frequency, tone spacing, symbol count, and
    // tone delay depending on mode
    switch (cur_mode)
    {
    case MODE_JT9:
        freq = JT9_DEFAULT_FREQ;
        symbol_count = JT9_SYMBOL_COUNT; // From the library defines
        tone_spacing = JT9_TONE_SPACING;
        tone_delay = JT9_DELAY;
        break;
    case MODE_JT65:
        freq = JT65_DEFAULT_FREQ;
        symbol_count = JT65_SYMBOL_COUNT; // From the library defines
        tone_spacing = JT65_TONE_SPACING;
        tone_delay = JT65_DELAY;
        break;
    case MODE_JT4:
        freq = JT4_DEFAULT_FREQ;
        symbol_count = JT4_SYMBOL_COUNT; // From the library defines
        tone_spacing = JT4_TONE_SPACING;
        tone_delay = JT4_DELAY;
        break;
    case MODE_WSPR:
        freq = WSPR_DEFAULT_FREQ;
        symbol_count = WSPR_SYMBOL_COUNT; // From the library defines
        tone_spacing = WSPR_TONE_SPACING;
        tone_delay = WSPR_DELAY;
        break;
    case MODE_FT8:
        freq = FT8_DEFAULT_FREQ;
        symbol_count = FT8_SYMBOL_COUNT; // From the library defines
        tone_spacing = FT8_TONE_SPACING;
        tone_delay = FT8_DELAY;
        break;
    case MODE_FSQ_2:
        freq = FSQ_DEFAULT_FREQ;
        tone_spacing = FSQ_TONE_SPACING;
        tone_delay = FSQ_2_DELAY;
        break;
    case MODE_FSQ_3:
        freq = FSQ_DEFAULT_FREQ;
        tone_spacing = FSQ_TONE_SPACING;
        tone_delay = FSQ_3_DELAY;
        break;
    case MODE_FSQ_4_5:
        freq = FSQ_DEFAULT_FREQ;
        tone_spacing = FSQ_TONE_SPACING;
        tone_delay = FSQ_4_5_DELAY;
        break;
    case MODE_FSQ_6:
        freq = FSQ_DEFAULT_FREQ;
        tone_spacing = FSQ_TONE_SPACING;
        tone_delay = FSQ_6_DELAY;
        break;
    }

    // Encode the message in the transmit buffer
    // This is RAM intensive and should be done separately from other subroutines
    set_tx_buffer();
}

int main()
{
    encode();
    return 0;
}
