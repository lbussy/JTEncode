JT65/JT9/JT4/FT8/WSPR/FSQ Encoder Library for C++
=====================================================

This library very simply generates a set of channel symbols for JT65, JT9, JT4, FT8, or WSPR based on the user providing a properly formatted Type 6 message for JT65, JT9, or JT4 (which is 13 valid characters), Type 0.0 or 0.5 message for FT8 (v2.0.0 protocol) or a Type 1, Type 2, or Type 3 message for WSPR. It will also generate an arbitrary FSQ message of up to 200 characters in both directed and non-directed format.

WSPR Messages
-------------
JTEncode includes support for all three WSPR message types. A brief listing of the three types is given below:

| Message Type | Fields | Example |
|--------------|--------|---------|
| Type 1 | Callsign, Grid (4 digit), Power | NT7S CN85 30 |
| Type 2 | Callsign with prefix or suffix, Power | NT7S/P 30 |
| Type 3 | Callsign Hash, Grid (6 digit), Power | \<NT7S\> CN85NM 30 |

Most WSPR messages are type 1, however sometimes type 2 and 3 messages are needed. Type 2 messages allow you to send a callsign with a prefix of up to three characters, a suffix of a single character, or a suffix consisting of two numerical digits. Type 3 messages are typically used in conjunction with type 2 messages since type 2 messages don't include a grid locator. The type 3 message sends a 15-bit hash of the included callsign, along with a 6 digit grid locator and the power.

Type 2 messages can be sent in JTEncode simply by including the slashed prefix or suffix in the callsign field. A type 3 message can be sent by enclosing a callsign with angle brackets (as seen in the example above).

Example
-------

The message to be transmitted is passed to the JTEncode method corresponding to the desired mode, along with a pointer to an array which holds the returned channel symbols.

An instance of the JTEncode object is created:

    JTEncode jtencode;

On sketch startup, the mode parameters are set based on which mode is currently selected (by the DEFAULT_MODE define):

    // Set the proper frequency, tone spacing, symbol count, and
    // tone delay depending on mode
    switch(cur_mode)
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

Note that the number of channel symbols for each mode is defined in the library, so you can use those defines to initialize your own symbol array sizes.

Before transmit, the proper class method is chosen based on the desired mode, then the transmit symbol buffer and the other mode information is set:

    // Set the proper frequency and timer CTC depending on mode
    switch(cur_mode)
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
      jtencode.ft_encode(message, tx_buffer);
      break;
    case MODE_FSQ_2:
    case MODE_FSQ_3:
    case MODE_FSQ_4_5:
    case MODE_FSQ_6:
      jtencode.fsq_dir_encode(call, "n0call", " ", "hello world", tx_buffer);
      break;
    }

As mentioned above, it is best if the message encoding functions are called only when needed, in its own subroutine.

Once the channel symbols have been generated, it is a simple matter of transmitting them in sequence, each the correct amount of time:

    // Now transmit the channel symbols
    for(i = 0; i < symbol_count; i++)
    {
        // Do something with the symbol
    }

Public Methods
------------------
### jt65_encode()
```
/*
 * jt65_encode(const char * message, uint8_t * symbols)
 *
 * Takes an arbitrary message of up to 13 allowable characters and returns
 * a channel symbol table.
 *
 * message - Plaintext Type 6 message.
 * symbols - Array of channel symbols to transmit returned by the method.
 *  Ensure that you pass a uint8_t array of at least size JT65_SYMBOL_COUNT to the method.
 *
 */
```
### jt9_encode()
```
/*
 * jt9_encode(const char * message, uint8_t * symbols)
 *
 * Takes an arbitrary message of up to 13 allowable characters and returns
 * a channel symbol table.
 *
 * message - Plaintext Type 6 message.
 * symbols - Array of channel symbols to transmit returned by the method.
 *  Ensure that you pass a uint8_t array of at least size JT9_SYMBOL_COUNT to the method.
 *
 */
```

### jt4_encode()
```
/*
 * jt4_encode(const char * message, uint8_t * symbols)
 *
 * Takes an arbitrary message of up to 13 allowable characters and returns
 * a channel symbol table.
 *
 * message - Plaintext Type 6 message.
 * symbols - Array of channel symbols to transmit returned by the method.
 *  Ensure that you pass a uint8_t array of at least size JT9_SYMBOL_COUNT to the method.
 *
 */
 ```

### wspr_encode()
```
/*
 * wspr_encode(const char * call, const char * loc, const uint8_t dbm, uint8_t * symbols)
 *
 * Takes a callsign, grid locator, and power level and returns a WSPR symbol
 * table for a Type 1, 2, or 3 message.
 *
 * call - Callsign (12 characters maximum).
 * loc - Maidenhead grid locator (6 characters maximum).
 * dbm - Output power in dBm.
 * symbols - Array of channel symbols to transmit returned by the method.
 *  Ensure that you pass a uint8_t array of at least size WSPR_SYMBOL_COUNT to the method.
 *
 */
```

### ft8_encode()
```
/*
 * ft8_encode(const char * message, uint8_t * symbols)
 *
 * Takes an arbitrary message of up to 13 allowable characters or a telemetry message
 * of up to 18 hexadecimal digit (in string format) and returns a channel symbol table.
 * Encoded for the FT8 protocol used in WSJT-X v2.0 and beyond (79 channel symbols).
 *
 * message - Type 0.0 free text message or Type 0.5 telemetry message.
 * symbols - Array of channel symbols to transmit returned by the method.
 *  Ensure that you pass a uint8_t array of at least size FT8_SYMBOL_COUNT to the method.
 *
 */
 ```

### fsq_encode()
```
/*
 * fsq_encode(const char * from_call, const char * message, uint8_t * symbols)
 *
 * Takes an arbitrary message and returns a FSQ channel symbol table.
 *
 * from_call - Callsign of issuing station (maximum size: 20)
 * message - Null-terminated message string, no greater than 130 chars in length
 * symbols - Array of channel symbols to transmit returned by the method.
 *  Ensure that you pass a uint8_t array of at least the size of the message
 *  plus 5 characters to the method. Terminated in 0xFF.
 *
 */
```

### fsq_dir_encode()
 ```
/*
* fsq_dir_encode(const char * from_call, const char * to_call, const char cmd, const char * message, uint8_t * symbols)
*
* Takes an arbitrary message and returns a FSQ channel symbol table.
*
* from_call - Callsign from which message is directed (maximum size: 20)
* to_call - Callsign to which message is directed (maximum size: 20)
* cmd - Directed command
* message - Null-terminated message string, no greater than 100 chars in length
* symbols - Array of channel symbols to transmit returned by the method.
*  Ensure that you pass a uint8_t array of at least the size of the message
*  plus 5 characters to the method. Terminated in 0xFF.
*
*/
```

### latlon_to_grid()
```
/*
 * latlon_to_grid(float lat, float lon, char* ret_grid)
 *
 * Takes a station latitude and longitude provided in decimal degrees format and
 * returns a string with the 6-digit Maidenhead grid designator.
 *
 * lat - Latitude in decimal degrees format.
 * lon - Longitude in decimal degrees format.
 * ret_grid - Derived Maidenhead grid square. A pointer to a character array of
 *   at least 7 bytes must be provided here for the function return value.
 *
 */
 ```

Tokens
------
Here are the defines, structs, and enumerations you will find handy to use with the library.

Defines:

    JT65_SYMBOL_COUNT, JT9_SYMBOL_COUNT, JT4_SYMBOL_COUNT, WSPR_SYMBOL_COUNT, FT8_SYMBOL_COUNT

Acknowledgements
----------------

JTEncode was originally developed and released by Jason Milldrum, [NT7S](https://github.com/NT7S) in his [JTEncode](https://github.com/etherkit/JTEncode) Arduino library.  It was Arduino-centric, and having earned my own scars coding for an Uno, I can appreciate his tenacity working in a resource-constrained environment.

I've un-Arduino'd this code to use in modern C++ applications, and I hope I never have to worry about coding within the constraints of the ATmega328P again.

Many thanks to  for his innovative work in amateur radio. We are lucky to have him. The algorithms in this program were derived from the Joe Taylor K1JT's source code in the [WSJT-X](https://sourceforge.net/p/wsjt/) suite of applications.

License
-------
JTEncode is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

JTEncode is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with JTEncode.  If not, see <http://www.gnu.org/licenses/>.
