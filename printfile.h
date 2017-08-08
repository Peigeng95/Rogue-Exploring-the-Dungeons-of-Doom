#ifndef __PRINTFILE_H__
#define __PRINTFILE_H__

#include <fstream>
#include <iostream>
#include <string>
#include <ncurses.h>

class Print{
	public:
		static void printfile(std::string); // To print the whole file with height of 30 and width of 79
		static void printfrom(std::string file, int height); // To print the whole file with given height and width of 79
		static void printfile_easy(std::string);// Print function for easyplay.
};
#endif
