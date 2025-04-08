#include "JTEncode.h"
#include "rs_common.h"
#include "int.h"

#include <cstdio>
#include <iomanip>
#include <iostream>

#include <string.h>

// Enumerations
enum wspr_type
{
    TYPE1 = 1,
    TYPE2,
    TYPE3
};

// Class instantiation
JTEncode jtencode;

int main()
{
    uint8_t dbm = 20;
    uint8_t tx_buffer[255];

    for (int type = 1; type <= 3; ++type)
    {
        // Clear out the transmit buffer
        memset(tx_buffer, 0, 255);

        if (type == 1)
        {
            char call[] = "AA0NT";
            char loc[] = "EM18";
            jtencode.wspr_encode(call, loc, dbm, tx_buffer);
            std::cout << "[Encoding] ";
            std::cout << "Call: " << call << ", ";
            std::cout << "Loc: " << loc << ", ";
            std::cout << "dBm: " << std::to_string(dbm) << ".";
            std::cout << std::endl;
        }
        else if (type == 2)
        {
            char call[] = "AA0NT/P";
            char loc[] = "EM18";
            jtencode.wspr_encode(call, loc, dbm, tx_buffer);
            std::cout << "[Encoding] ";
            std::cout << "Call: " << call << ", ";
            std::cout << "Loc: " << loc << ", ";
            std::cout << "dBm: " << std::to_string(dbm) << ".";
            std::cout << std::endl;
        }
        else if (type == 3)
        {
            char call[] = "<AA0NT>";
            char loc[] = "EM18IG";
            jtencode.wspr_encode(call, loc, dbm, tx_buffer);
            std::cout << "[Encoding] ";
            std::cout << "Call: " << call << ", ";
            std::cout << "Loc: " << loc << ", ";
            std::cout << "dBm: " << std::to_string(dbm) << ".";
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Incorrect mode selected," << std::endl;
        }

        // Iterate through the symbols and print them.
        std::cout << "WSPR Block:" << std::endl;
        for (int i = 0; i < WSPR_SYMBOL_COUNT; ++i)
        {
            // Print each symbol as an integer.
            std::cout << std::setw(3) << static_cast<int>(tx_buffer[i]) << " ";

            // Optionally, insert a newline every 16 symbols for readability.
            if ((i + 1) % 16 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
