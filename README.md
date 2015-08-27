minHumdrum
==========

The minHumdrum library is a set of C++ classes for parsing 
[Humdrum](http://www.humdrum.org) file data.  The library is designed
to be portable, consisting of two files that can be copied into
your project:

1. An include file [minhumdrum.h](/include/minhumdrum.h)
2. and a source file [minhumdrum.cpp](/src/minhumdrum.cpp)

The classes use some C++11-specific features, so you must add the
`-stc=c++11` option when compiling with GNU g++ or clang++ compiler.
Also include the `-stdlib=libc++` when compiling with clang.  See the
[Makefile](Makefile) for compiling the library and 
[Makefile.examples](Makefile.examples) for linking to create executables.

More information and documentation for the library can be found at http://min.humdrum.org.


Downloading
===========

To download using git, type:
```bash
git clone https://github.com/craigsapp/minHumdrum
```
To update to the most recent version of minHumdrum, type in the minHumdrum directory:
```bash
git pull
```

 
Compiling
==========

If you download the git repository or a zip/tarball of the repository, you can
compile the library with the command
```bash
make
```
This should create the file `lib/libminhumdrum.a`, which can be used to
link to other program code.

For testing purposes, another form of the library can be compiled from the individual source files for each class:
```bash
make lib
```
This will create the file `lib/libhumdrum.a`.


Class overview
==============

Here are the classes defined in the minHumdrum library:

* [HumdrumFile](https://github.com/craigsapp/minHumdrum/blob/master/include/HumdrumFile.h): primary interface for working with Humdrum file data. <img title="class-organization" align="right" width="250" src="https://cdn.rawgit.com/craigsapp/minHumdrum/gh-pages/images/class-organization.svg">
* [HumdrumFileContent](https://github.com/craigsapp/minHumdrum/blob/master/include/HumdrumFileContent.h): manages analysis of data content (particularly of **kern data) beyond basic rhythmic analysis done in HumdrumFileStructure.
* [HumdrumFileStructure](https://github.com/craigsapp/minHumdrum/blob/master/include/HumdrumFileStructure.h): manages rhythmic analysis of the data and extra parameters for data tokens.
* [HumdrumFileBase](https://github.com/craigsapp/minHumdrum/blob/master/include/HumdrumFileBase.h): manages data storage and reading/writing of Humdrum file data.
(particularly from token strings) into other formats.
* [HumdrumLine](https://github.com/craigsapp/minHumdrum/blob/master/include/HumdrumLine.h): manages the content of a line (data record) in a Humdrum file.
* [HumdrumToken](https://github.com/craigsapp/minHumdrum/blob/master/include/HumdrumToken.h): manages tokens (data elements on a line) for HumdrumLine.
* [HumAddress](https://github.com/craigsapp/minHumdrum/blob/master/include/HumAddress.h): location information for a HumdrumToken on a HumdrumLine and in a HumdrumFile.
* [HumNum](https://github.com/craigsapp/minHumdrum/blob/master/include/HumNum.h): rational number class for working with durations. 
* [HumHash](https://github.com/craigsapp/minHumdrum/blob/master/include/HumHash.h): associative array for HumdrumLine and HumdrumToken parameters.
* [HumMultiHash](https://github.com/craigsapp/minHumdrum/blob/master/include/HumMultiHash.h): associative array for HumdrumFile reference records and parameters.
* [Convert](https://github.com/craigsapp/minHumdrum/blob/master/include/Convert.h): utility functions for converting data (primarily for processing HumdrumToken strings).

The following figure shows some sample Humdrum file for a musical score with overlays illustrating how the class structure of a HumdrumFile interacts with the data.  The blue area represents a HumdrumFile.  The file primarily consists of an array of HumdrumLines, indexed from 0.  The HumdrumLine in turn contains a list of HumdrumTokens, indexed by a field number on the line, which is also indexed from 0.

<img title="class-organization" width="600" src="https://cdn.rawgit.com/craigsapp/minHumdrum/gh-pages/images/humdrum-file.svg">

The bottom right portion of the above figure shows the organization of the file in terms of parts (or staves) in the data.  The parts are contained in "spines" which start with a data type, such as `**kern` and end with a data terminator, `*-` (star-dash, not star-underscore).  Humdrum spines can split into two subspines (and the subspines can split into sub-subspines) as shown in the second spine.  A spine is split using the `*^` spine manipulator and can be merged again with the merge manipulator `*v`.  A related concept to spines are "tracks".  Tracks are identical to spines if spines do not split; otherwise, subspines and subtracks are described slighly differently.  Subspines are described by strings which indicate the spine manipulator history of the spine.  For example when spine `2` splits into two subspines, the first subspine on the line is labeled `(2)a` and the second subspine is `(2)b`.  Likewise if the `(2)b` subspine splits again, the two sub-subspines would be labeled `((2)b)a` and `((2)b)b`.  Subtracks are enumerated in the order of their left-to-right occurence on the line regardless of subspine manipulations, so in this example subspine `(2)a` is called subtrack `2.1` and subspine `(2)b` is called subtrack `2.2`.  If the two subspines were to switch their order on the line with the exchange manipulator `*x`, then the subtrack assignments would reverse such that `(2)b` would be subtrack `2.1` and `(2)a` would be subtrack `2.2`.  Note that spine and track labels are indexed from 1 rather than 0.

Code snippets
==============

Here are examples of how to access data in a Humdrum score using the 
minHumdrum classes:


1: Read Humdrum data from a file, string or istream:
```cpp
HumdrumFile infile;
infile.read(char* filename);
infile.read(string filename);
infile.read(std::cin);
```
To read content from a char* or string:
```cpp
infile.parse(stringstream content);
infile.parse(char* content);
infile.parse(string content);
```

2: Access the token in the second field of the fourth line (`12e` in the above example). This can be done in two ways: either address the HumdrumLine by the [] operator of HumdrumClass and then the data files with HumdrumLine::token, or access the HumdrumToken directly from the HumdrumFile::token function, giving the line and field index as arguments.
```cpp
infile[3].token(1);
infile.token(3, 1);
```

3: HumdrumTokens inherit from std::string, so you can access the text of the token in several ways:
```cpp
(std::string)infile.token(3, 1);
infile.token(3, 1).c_str();
```

4: To access the parsed duration of the token, use the HumdrumToken::getDuration function.  The return value of getDuration() is a "HumNum" which is a rational number, or fraction, consisting of an integer numerator and denominator.  The HumNum::getFloat() function will return the duration as a double:
```cpp
infile.token(3, 1).getDuration();              // 1/3 for "12e"
infile.token(3, 1).getDuration().getFloat();   // 0.3333 for "12e"
```
5: HumdrumLines also possess duration:
```cpp
infile[i].getDuration();  // 1/6 (1/6th of a quarter note, due to the polyrhythm between the parts)
```
6: HumdrumFiles also possess duration:
```cpp
infile.getDuration();    // 3 (one measure of 3/4)
```
7: When converting Humdrum files into MIDI, MuseData, MusicXML or SKINI, the function HumdrumFile::tpq (ticks per quarter note) will return the minimum number of fractional time units necessary to describe all rhythms in the file as integer durations.
```cpp
infile.tpq();           // 6 = minimum time unit is a triplet sixteenth note for example
```
8: Durations can be expressed in ticks by giving the tpq value as an argument to the duration functions:
```cpp
int tpq = infile.tpq();                           // 6 ticks per quarter note
infile.token(3, 1).getDuration(tpq).toInteger();  // 2 ticks for a triplet eighth note
infile[3].getDuration(tpq).toInteger();           // 1 tick for a triplet sixteenth note
infile.getDuration(tpq).toInteger();              // 18 ticks for three quarter notes
```
9: Get the total number of HumdrumLines in a HumdrumFile:
```cpp
infile.getLineCount();
```
10: Get the total number of token fields on a HumdrumLine:
```cpp
infile[3].getTokenCount();
infile[3].getFieldCount();
```
11: Get the track number for a token:
```cpp
infile[3].getTrack(1);   // 2nd track in file.
```
12: Get the total number of spines/tracks in a HumdrumFile:
```cpp
infile.getMaxTrack();
```
13: Get the first token in the seocond spine/track (second `**kern` token on the first line):
```cpp
infile.getTrackStart(2);
```
Note that this will return a pointer rather than a reference to the token.

14:  Ask the starting token how many tokens precede/follow it in the spine:
```cpp
HumdrumToken* tok = infile.getTrackStart(2);
tok->getNextTokenCount();           // 1 token following in the spine
tok->getPreviousTokenCount();       // 0 tokens preceding in the spine
tok->getNextToken();                // returns pointer to `*M3/4`, using default value of 0 for argument.
tok->getPreviousToken();            // returns NULL
```

Code example
=============

Here is an example program that uses the minHumdrum library to convert a Humdrum file into a MIDI-like listing of notes in the Humdrum score:


```cpp
#include "minhumdrum.h"

using namespace std;
using namespace minHumdrum;

void printNoteInformation(HumdrumFile& infile, int line, int field, int tpq) {
   int starttime = infile[line].getDurationFromStart(tpq).getInteger();
   int duration  = infile.token(line, field).getDuration(tpq).getInteger();;
   cout << Convert::kernToSciPitch(infile.token(line, field))
        << '\t' << infile.token(line, field).getTrackString()
        << '\t' << starttime << '\t' << duration << endl;
}

int main(int argc, char** argv) {
   if (argc != 2) {
      return 1;
   }
   HumdrumFile infile;
   if (!infile.read(argv[1])) {
      return 1;
   }
   int tpq = infile.tpq();
   cout << "TPQ: " << tpq << endl;
   cout << "PITCH\tTRACK\tSTART\tDURATION" << endl;

   for (int i=0; i<infile.getLineCount(); i++) {
      if (!infile[i].isData()) {
         continue;
      }
      for (int j=0; j<infile[i].getTokenCount(); j++) {
         if (infile.token(i, j).isNull()) {
            continue;
         }
         if (infile.token(i, j).isDataType("kern")) {
            printNoteInformation(infile, i, j, tpq);
         }
      }
   }
   return 0;
}
```

Notice that all minHumdrum code is placed into the minHumdrum namespace.

Test data for use with the above program:

![Example music](https://cdn.rawgit.com/craigsapp/minHumdrum/gh-pages/images/hum2notelist.svg)

<table style="border-collapse: separate; margin-left:auto; margin-right:auto">
<tr><td style="border:0">
Example input:<br>
<pre style="tab-stop: 12; font-family: Courier; text-align:left">
**kern  **kern
*M3/4   *M3/4
8C      12d
.       12e
8B      .
.       12f
*       *^
4A      2g      4d
4G      .       4c
*       *v      *v
=       =
*-      *-
</pre>
</td><td style="border:0">
Example output:<br>
<pre style="font-family: Courier; text-align:left">
TPQ: 6
PITCH   TRACK   START   DURATION
C3      1       0       3
D4      2       0       2
E4      2       2       2
B3      1       3       3
F4      2       4       2
A3      1       6       6
G4      2.1     6       12
D4      2.2     6       6
G3      1       12      6
C4      2.2     12      6
</pre>
</td></tr></table>
</center>

If you are using the minHumdrum project directory, you can place
programs into a subdirectory called `myprograms` and then to compile,
go to the base directory of the minHumdrum code and type `make myprogram`
if the program is called `myprograms/myprogram.cpp`.  The compiled program
will be created as `bin/myprogram`.
