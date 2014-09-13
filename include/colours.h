/**
 * @file colours.h
 * @author Mario Román
 * @date 11 Aug 2014
 * @brief Color definitions.
 * Macros defining colour strings for ptinting in the terminal.
 */

// Avoids redefinition
#ifndef COLOURS_H_
#define COLOURS_H_

/** @brief \b Red colour string for printing in the terminal*/
#define KRED	"\033[31m"    
/** @brief \b Light \b red colour string for printing in the terminal*/
#define KLRE	"\033[1;31m"  
/** @brief \b Green colour string for printing in the terminal*/
#define KGRN	"\033[32m"    
/** @brief \b Yellow colour string for printing in the terminal*/
#define KYEL	"\033[33m"    
/** @brief \b Blue colour string for printing in the terminal*/
#define KBLU	"\033[34m"    
/** @brief \b Magenta colour string for printing in the terminal*/
#define KMAG	"\033[35m"    
/** @brief \b Cyan colour string for printing in the terminal*/
#define KCYN	"\033[36m"    
/** @brief \b White colour string for printing in the terminal*/
#define KWHT	"\033[37m"    
/** @brief \b Reset \b colour string for printing in the terminal*/
#define KRES	"\033[0m"     

#endif
