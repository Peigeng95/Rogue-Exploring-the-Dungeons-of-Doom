#include "printfile.h"

using namespace std;


// To print the whole file with height of 30 and width of 79
void Print::printfile(string file){
	fstream pri(file.c_str());
   string s;
   for(;;){
      for(int i = 0; i < 30; i++){
         getline(pri,s);
         if(pri.eof()) break;
         for(int j = 0; j < 79; j++){
            cout << s.at(j); // Print every char
         }
	 		cout << endl; // \n at each line-end.
      }
      break;
   }
}

// To print the whole file with given height and width of 79
void Print::printfrom(string file, int h){
	fstream pri(file.c_str());
   string s;
   for(;;){
      for(int i = 0; i < h; i++){
         getline(pri,s);
         if(pri.eof()) break;
         for(int j = 0; j < 79; j++){
            cout << s.at(j);// Print every char
         }
	 		cout << endl;// \n at each line-end
      }
      break;
   }
}

void Print::printfile_easy(string file){
	fstream pri(file.c_str());
   string s;
      for(int i = 0; i < 30; i++){
         getline(pri,s);
         if(pri.eof()) break;
         for(int j = 0; j < 79; j++){
         	mvaddch(i, j, s.at(j)); // Print every char
         }
      }
	refresh();
}
