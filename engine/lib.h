#pragma once

/**
 * @file
 * @brief Configuration file for the graphics engine library.
 */

 // Generic info:
#ifdef _DEBUG

#define LIB_NAME      "Chessboard - SUPSI Graphics Course Project (a.a. 2024/25) [DEBUG] \n" \
                        "A. Cantoni (C) SUPSI - alessandro.cantoni@student.supsi.ch \n" \
                        "F. Fasola (C) SUPSI - francesco.fasola@student.supsi.ch \n" \
                        "M. Verdolin(C) SUPSI - mattia.verdolin@student.supsi.ch \n"    ///< Library credits
#else
#define LIB_NAME      "Chessboard - SUPSI Graphics Course Project (a.a. 2024/25) \n" \
                        "A. Cantoni (C) SUPSI - alessandro.cantoni@student.supsi.ch \n" \
                        "F. Fasola (C) SUPSI - francesco.fasola@student.supsi.ch \n" \
                        "M. Verdolin(C) SUPSI - mattia.verdolin@student.supsi.ch \n"   ///< Library credits
#endif

#define LIB_VERSION   10                           ///< Library version (divide by 10)

      // Export API:
#ifdef _WINDOWS

#ifdef ENGINE_EXPORTS
#define ENG_API __declspec(dllexport)
#else
#define ENG_API __declspec(dllimport)
#endif      

#pragma warning(disable : 4251) 

#else // Under linux

#define ENG_API
#endif
