// Description: Print the duration from the start of the Humdrum file to the
// start of the current line.

#include "humlib.h"

int main(int argc, char** argv) {
   if (argc != 2) {
      return 1;
   }
   hum::HumdrumFile infile;
   if (!infile.read(argv[1])) {
      return 1;
   }
   for (int i=0; i<infile.size(); i++) {
      cout << infile[i].getDurationFromBarline() << "\t";
      cout << infile[i].getDurationToBarline() << "\t";
      cout << infile[i].getBeat() << "\t";
      cout << infile[i].getBeat().getFloat() << "\t";
      cout << infile[i] << endl;
   }
   return 0;
}


