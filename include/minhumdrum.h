//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Aug  8 12:24:49 PDT 2015
// Last Modified: Sat Aug 15 22:21:28 PDT 2015
// Filename:      /include/minhumdrum.h
// URL:           https://github.com/craigsapp/minHumdrum/blob/master/include/minhumdrum.h
// Syntax:        C++11
// vim:           ts=3
//
// Description:   Include file for minHumdrum library.
//
/*
Copyright (c) 2015 Craig Stuart Sapp
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   and the following disclaimer in the documentation and/or other materials 
   provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef _MINHUMDRUM_H
#define _MINHUMDRUM_H

#include <math.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;
using std::istream;
using std::ifstream;
using std::ostream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::to_string;
using std::stringstream;

class Convert;
class HumNum;
class HumAddress;
class HumdrumToken;
class HumdrumLine;
class HumdrumFile;


class HumAddress {
	public:
		              HumAddress        (void);
		             ~HumAddress        ();

		int           getLineIndex      (void) const;
		int           getLineNumber     (void) const;
		int           getFieldIndex     (void) const;
		const HumdrumToken& getDataType (void) const;
		const string& getSpineInfo      (void) const;
		int           getTrack          (void) const;
		int           getSubtrack       (void) const;
		string        getTrackString    (void) const;
		HumdrumLine*  getLine           (void) const;
		HumdrumLine*  getOwner          (void) const { return getLine(); }
		bool          hasOwner          (void) const;

	protected:
		void          setOwner          (HumdrumLine* aLine);
		void          setFieldIndex     (int fieldlindex);
		void          setSpineInfo      (const string& spineinfo);
		void          setTrack          (int aTrack, int aSubtrack);
		void          setTrack          (int aTrack);
		void          setSubtrack       (int aSubtrack);

	private:

		// fieldindex: This is the index of the token in the HumdrumLine
		// which owns this token.
		int fieldindex;       // field index of token on line

		// spining: This is the spine position of the token. A simple spine
		// position is an integer, starting with "1" for the first spine
		// of the file (left-most spine).  When the spine splits, "(#)a"
		// is wrapped around the left-subspine's spine info, and "(#)b"
		// around the right-subspine's info. Merged spines will add a space
		// between the two or more merged spines information, such as
		// "(#)a (#)b" for two sub-spines merged into a single spine again.
		// But in this case there is a spine info simplification which will
		// convert "(#)a (#)b" into "#" where # is the original spine number.
		// Other more complicated mergers may be simplified in the future.
		string spining;

		// track: This is the track number of the spine.  It is the first
		// number found in the spineinfo string.
		int track;

		// subtrack: This is the subtrack number for the spine.  When a spine
		// is not split, it will be 0, if the spine has been split with *^,
		// then the left-subspine will be in subtrack 1 and the right-spine
		// will be subtrack 2.  If subspines are exchanged with *x, then their
		// subtrack assignments will also change.
		int subtrack;

		// owner: This is the line which manages the given token.
		HumdrumLine* owner;

// ggg still to process:

		// nullresolve: If the token is a null data token, then this variable
		// contains a pointer to the data token which continues the null.
		// If a null token comes before the first non-null token in the data spine,
		// this this value will be NULL.
		HumdrumToken* nullresolve;

	friend class HumdrumToken;
	friend class HumdrumLine;
	friend class HumdrumFile;
};


class HumNum {
	public:
		         HumNum             (void);
		         HumNum             (int value);
		         HumNum             (int numerator, int denominator);
		         HumNum             (const HumNum& rat);
		        ~HumNum             ();

		bool     isNegative         (void) const;
		bool     isPositive         (void) const;
		bool     isZero             (void) const;
		bool     isNonZero          (void) const;
		bool     isNonNegative      (void) const;
		bool     isNonPositive      (void) const;
		bool     isInfinite         (void) const;
		bool     isFinite           (void) const;
		bool     isNaN              (void) const;
		bool     isInteger          (void) const;
		double   getFloat           (void) const;
		int      getInteger         (double round = 0.0) const;
		int      getNumerator       (void) const;
		int      getDenominator     (void) const;
		void     setValue           (int numerator);
		void     setValue           (int numerator, int denominator);
		HumNum   getAbs             (void) const;
		HumNum&  makeAbs            (void);
		HumNum&  operator=          (const HumNum& value);
		HumNum&  operator=          (int value);
		HumNum&  operator+=         (const HumNum& value);
		HumNum&  operator+=         (int value);
		HumNum&  operator-=         (const HumNum& value);
		HumNum&  operator-=         (int value);
		HumNum&  operator*=         (const HumNum& value);
		HumNum&  operator*=         (int value);
		HumNum&  operator/=         (const HumNum& value);
		HumNum&  operator/=         (int value);
		HumNum   operator-          (void);
		HumNum   operator+          (const HumNum& value);
		HumNum   operator+          (int value);
		HumNum   operator-          (const HumNum& value);
		HumNum   operator-          (int value);
		HumNum   operator*          (const HumNum& value);
		HumNum   operator*          (int value);
		HumNum   operator/          (const HumNum& value);
		HumNum   operator/          (int value);
		bool     operator==         (const HumNum& value) const;
		bool     operator==         (double value) const;
		bool     operator==         (int value) const;
		bool     operator!=         (const HumNum& value) const;
		bool     operator!=         (double value) const;
		bool     operator!=         (int value) const;
		bool     operator<          (const HumNum& value) const;
		bool     operator<          (double value) const;
		bool     operator<          (int value) const;
		bool     operator<=         (const HumNum& value) const;
		bool     operator<=         (double value) const;
		bool     operator<=         (int value) const;
		bool     operator>          (const HumNum& value) const;
		bool     operator>          (double value) const;
		bool     operator>          (int value) const;
		bool     operator>=         (const HumNum& value) const;
		bool     operator>=         (double value) const;
		bool     operator>=         (int value) const;
		ostream& printFraction      (ostream& = cout) const;
		ostream& printMixedFraction (ostream& out = cout,
		                             string separator = "_") const;
		ostream& printList          (ostream& out) const;

	protected:
		void     reduce             (void);
		int      gcdIterative       (int a, int b);
		int      gcdRecursive       (int a, int b);

	private:
		int top;
		int bot;
};

ostream& operator<<(ostream& out, const HumNum& number);

template <typename A>
ostream& operator<<(ostream& out, const vector<A>& v);


class HumdrumFile {
	public:
		              HumdrumFile                  (void);
		             ~HumdrumFile                  ();

		bool          read                         (istream& infile);
		bool          read                         (const char*   contents);
		bool          read                         (const string& contents);
		bool          readString                   (const char*   contents);
		bool          readString                   (const string& contents);
		bool          readNoRhythm                 (istream& infile);
		bool          readNoRhythm                 (const char*   contents);
		bool          readNoRhythm                 (const string& contents);
		bool          readStringNoRhythm           (const char*   contents);
		bool          readStringNoRhythm           (const string& contents);
		HumdrumLine&  operator[]                   (int index);
		void          append                       (const char* line);
		void          append                       (const string& line);
		int           getLineCount                 (void) const;
		int           getMaxTrack                  (void) const;
		ostream&      printSpineInfo               (ostream& out = cout);
		ostream&      printDataTypeInfo            (ostream& out = cout);
		ostream&      printTrackInfo               (ostream& out = cout);
		ostream&      printDurationInfo            (ostream& out = cout);
		HumdrumToken* getTrackStart                (int track) const;
		int           getTrackEndCount             (int track) const;
		HumdrumToken* getTrackEnd                  (int track,
		                                            int subtrack) const;
		void          createLinesFromTokens        (void);
		HumNum        getScoreDuration             (void) const;

		// barline/measure functionality:
		int           getBarlineCount              (void) const;
		HumdrumLine*  getBarline                   (int index) const;
		HumNum        getBarlineDuration           (int index) const;
		HumNum        getBarlineDurationFromStart  (int index) const;
		HumNum        getBarlineDurationToEnd      (int index) const;

	protected:
		bool          analyzeTokens                (void);
		bool          analyzeSpines                (void);
		bool          analyzeRhythm                (void);
		bool          analyzeMeter                 (void);
		bool          analyzeLinks                 (void);
		bool          analyzeTokenDurations        (void);
		bool          analyzeTracks                (void);
		bool          analyzeLines                 (void);
		bool          analyzeDurationsOfNonRhythmicSpines(void);
		bool          adjustSpines                 (HumdrumLine& line,
		                                            vector<string>& datatype,
		                                            vector<string>& sinfo);
		string        getMergedSpineInfo           (vector<string>& info,
		                                            int starti, int extra);
		bool          stitchLinesTogether          (HumdrumLine& previous,
		                                            HumdrumLine& next);
		HumNum        getMinDur                    (vector<HumNum>& durs,
		                                            vector<HumNum>& durstate);
		bool          getTokenDurations            (vector<HumNum>& durs,
		                                            int line);
		bool          cleanDurs                    (vector<HumNum>& durs,
		                                            int line);
		bool          decrementDurStates           (vector<HumNum>& durs,
		                                            HumNum linedur, int line);
		bool          assignDurationsToTrack       (HumdrumToken* starttoken,
		                                            HumNum startdur);
		void          addToTrackStarts             (HumdrumToken* token);
		bool          prepareDurations             (HumdrumToken* token,
		                                            int state,
		                                            HumNum startdur);
		bool          setLineDurationFromStart     (HumdrumToken* token,
		                                            HumNum dursum);
		bool      analyzeRhythmOfFloatingSpine (HumdrumToken* spinestart);
		bool      analyzeNullLineRhythms       (void);
		void      fillInNegativeStartTimes     (void);
		void      assignLineDurations          (void);
		bool      assignDurationsToNonRhythmicTrack(HumdrumToken* starttoken);
		bool      analyzeNonNullDataTokens     (void);
		void      addUniqueTokens              (vector<HumdrumToken*>& target,
		                                        vector<HumdrumToken*>& source);
		bool      processNonNullDataTokensForTrackForward(
		                                        HumdrumToken* starttoken, 
		                                        vector<HumdrumToken*> ptokens);
		bool      processNonNullDataTokensForTrackBackward(
		                                        HumdrumToken* starttoken, 
		                                        vector<HumdrumToken*> ptokens);

	private:

		// lines: an array representing lines from the input file.
		vector<HumdrumLine*> lines;

		// trackstarts: list of addresses of the exclusive interpreations
		// in the file.  The first element in the list is reserved, so the
		// number of tracks (primary spines) is equal to one less than the
		// size of this list.
		vector<HumdrumToken*> trackstarts;

		// trackends: list of the addresses of the spine terminators in the file.
		// It is possible that spines can split and their subspines do not merge
		// before termination; therefore, the ends are stored in a 2d array.
		// The first dimension is the track number, and the second dimension
		// is the list of terminators.
		vector<vector<HumdrumToken*> > trackends;

		// barlines: list of barlines in the data.  If the first measures is
		// a pickup measure, then the first entry will not point to the first
		// starting exclusive interpretation line rather than to a barline.
		vector<HumdrumLine*> barlines;
		// Maybe also add "measures" which are complete metrical cycles.

};

ostream& operator<<(ostream& out, HumdrumFile& infile);



class HumdrumLine : public string {
	public:
		         HumdrumLine          (void);
		         HumdrumLine          (const string& aString);
		         HumdrumLine          (const char* aString);
		        ~HumdrumLine          ();

		bool     isComment              (void) const;
		bool     isCommentLocal         (void) const;
		bool     isCommentGlobal        (void) const;
		bool     isExclusive            (void) const;
		bool     isExclusiveInterpretation (void) const { return isExclusive(); }
		bool     isTerminator           (void) const;
		bool     isInterp               (void) const;
		bool     isInterpretation       (void) const { return isInterp(); }
		bool     isBarline              (void) const;
		bool     isData                 (void) const;
		bool     isAllNull              (void) const;
		bool     isAllRhythmicNull      (void) const;
		bool     isEmpty                (void) const;
		bool     isManipulator          (void) const;
		bool     hasSpines              (void) const;
		HumdrumToken& token             (int index) const;
		void     getTokens              (vector<HumdrumToken*>& list);
		int      getTokenCount          (void) const;
		int      getFieldCount          (void) const { return getTokenCount(); }
		string   getTokenString         (int index) const;
		bool     equalChar              (int index, char ch) const;
		char     getChar                (int index) const;
		ostream& printSpineInfo         (ostream& out = cout);
		ostream& printDataType          (ostream& out = cout);
		ostream& printTrackInfo         (ostream& out = cout);
		ostream& printDataTypeInfo      (ostream& out = cout);
		ostream& printDurationInfo      (ostream& out = cout);
		void     createLineFromTokens   (void);
		int      getLineIndex           (void) const;
		int      getLineNumber          (void) const;
		HumNum   getDuration            (void) const;
		HumNum   getDurationFromStart   (void) const;
		HumNum   getDurationToEnd       (void) const;
		HumNum   getDurationFromBarline (void) const;
		HumNum   getDurationToBarline   (void) const;
		HumNum   getBeat                (string beatrecip = "4") const;
		HumdrumToken* getTrackStart     (int track) const;

	protected:
		bool     analyzeTracks          (void);
		bool     analyzeTokenDurations  (void);
		void     setLineIndex           (int index);
		void     clear                  (void);
		void     setDuration            (HumNum aDur);
		void     setDurationFromStart   (HumNum dur);
		void     setDurationFromBarline (HumNum dur);
		void     setDurationToBarline   (HumNum dur);
		void     setOwner               (HumdrumFile* hfile);
		int      createTokensFromLine   (void);

	private:

		//
		// State variables managed by the HumdrumLine class:
		//

		// lineindex: Used to store the index number of the HumdrumLine in
		// the owning HumdrumFile object.
		// This variable is filled by HumdrumFile::analyzeLines().
		int lineindex;

		// tokens: Used to store the individual tab-separated token fields
		// on a line.  These are prepared automatically after reading in
		// a full line of text (which is accessed throught the string parent
		// class).  If the full line is changed, the tokens are not updated
		// automatically -- use createTokensFromLine().  Likewise the full
		// text line is not updated if any tokens are changed -- use
		// createLineFromTokens() in that case.  The second case is more
		// useful: you can read in a HumdrumFile, tweak the tokens, then
		// reconstruct the full line and print out again.
		// This variable is filled by HumdrumFile::read().
		vector<HumdrumToken*> tokens;

		// duration: This is the "duration" of a line.  The duration is
		// equal to the minimum time unit of all durational tokens on the
		// line.  This also includes null tokens when the duration of a
		// previous note in a previous spine is ending on the line, so it is
		// not just the minimum duration on the line.
		// This variable is filled by HumdrumFile::analyzeRhythm().
		HumNum duration;

		// durationFromStart: This is the cumulative duration of all lines
		// prior to this one in the owning HumdrumFile object.  For example,
		// the first notes in a score start at time 0, If the duration of the
		// first data line is 1 quarter note, then the durationFromStart for
		// the second line will be 1 quarter note.
		// This variable is filled by HumdrumFile::analyzeRhythm().
		HumNum durationFromStart;

		// durationFromBarline: This is the cumulative duration from the
		// last barline to the current data line.
		// This variable is filled by HumdrumFile::analyzeMeter().
		HumNum durationFromBarline;

		// durationToBarline: This is the duration from the start of the
		// current line to the next barline in the owning HumdrumFile object.
		// This variable is filled by HumdrumFile::analyzeMeter().
		HumNum durationToBarline;

		// owner: This is the HumdrumFile which manages the given line.
		HumdrumFile* owner;

	friend class HumdrumFile;
};

ostream& operator<< (ostream& out, HumdrumLine& line);



class HumdrumToken : public string {
	public:
		         HumdrumToken              (void);
		         HumdrumToken              (const char* token);
		         HumdrumToken              (const string& token);
		        ~HumdrumToken              ();

		bool     isNull                    (void) const;
		bool     isManipulator             (void) const;
		bool     isExclusive               (void) const;
		bool     isExclusiveInterpretation (void) const { return isExclusive(); }
		bool     isExInterp                (void) const { return isExclusive(); }
		bool     isSplitInterpretation     (void) const;
		bool     isMergeInterpretation     (void) const;
		bool     isExchangeInterpretation  (void) const;
		bool     isTerminateInterpretation (void) const;
		bool     isAddInterpretation       (void) const;
		bool     isBarline                 (void) const;
		bool     isData                    (void) const;
		bool     hasRhythm                 (void) const;
		HumNum   getDuration               (void) const;
		HumNum   getDurationFromStart      (void) const;
		HumdrumLine* getOwner              (void) const;
		HumdrumLine* getLine               (void) const { return getOwner(); }
		bool     equalChar                 (int index, char ch) const;

		int      getPreviousNonNullDataTokenCount(void);
		int      getPreviousNNDTCount(void) { return getPreviousNonNullDataTokenCount(); }
		HumdrumToken* getPreviousNonNullDataToken(int index);
		HumdrumToken* getPreviousNNDT(int index) { return getPreviousNonNullDataToken(index); }
		int      getNextNonNullDataTokenCount(void);
		int      getNextNNDTCount(void) { return getNextNonNullDataTokenCount(); }
		HumdrumToken* getNextNonNullDataToken(int index);
		HumdrumToken* getNextNNDT(int index) { return getNextNonNullDataToken(index); }

		int      getLineIndex              (void) const;
		int      getLineNumber             (void) const;
		int      getFieldIndex             (void) const;
		const string& getDataType          (void) const;
		string   getSpineInfo              (void) const;
		int      getTrack                  (void) const;
		int      getSubtrack               (void) const;
		string   getTrackString            (void) const;
		int      getSubtokenCount          (const string& separator = " ") const;
		string   getSubtoken               (int index,
		                                    const string& separator) const;

		// next/previous token functions:
		int           getNextTokenCount         (void) const;
		int           getPreviousTokenCount     (void) const;
		HumdrumToken* getNextToken              (int index = 0) const;
		HumdrumToken* getPreviousToken          (int index = 0) const;
		vector<HumdrumToken*> getNextTokens     (void) const;
		vector<HumdrumToken*> getPreviousTokens (void) const;

	protected:
		void     setLineIndex      (int lineindex);
		void     setFieldIndex     (int fieldlindex);
		void     setSpineInfo      (const string& spineinfo);
		void     setTrack          (int aTrack, int aSubtrack);
		void     setTrack          (int aTrack);
		void     setSubtrack       (int aSubtrack);
		void     setPreviousToken  (HumdrumToken* aToken);
		void     setNextToken      (HumdrumToken* aToken);
		void     makeForwardLink   (HumdrumToken& nextToken);
		void     makeBackwardLink  (HumdrumToken& previousToken);
		void     setOwner          (HumdrumLine* aLine);
		int      getState          (void) const;
		void     incrementState    (void);

		bool     analyzeDuration   (void);

	private:

		// address: The address contains information about the location of
		// the token on a HumdrumLine and in a HumdrumFile.
		HumAddress address;

		// duration: The duration of the token.  Non-rhythmic data types
		// will have a negative duration (which should be interpreted
		// as a zero duration--See HumdrumToken::hasRhythm()).
		// Grace note will have a zero duration, even if they have a duration
		// list in the token for a graphical display duration.
		HumNum duration;

		// nextTokens: This is a list of all previous tokens in the spine which
		// immediately precede this token. Typically there will be one
		// following token, but there can be two tokens if the current
		// token is *^, and there will be zero following tokens after a
		// spine terminating token (*-).
		vector<HumdrumToken*> nextTokens;     // link to next token(s) in spine

		// previousTokens: Simiar to nextTokens, but for the immediately
		// follow token(s) in the data.  Typically there will be one
		// preceding token, but there can be multiple tokens when the previous
		// line has *v merge tokens for the spine.  Exclusive interpretations
		// have no tokens preceding them.
		vector<HumdrumToken*> previousTokens; // link to last token(s) in spine

		// nextNonNullTokens: This is a list of non-tokens in the spine 
		// that follow this one.
		vector<HumdrumToken*> nextNonNullTokens;

		// previousNonNullTokens: This is a list of non-tokens in the spine 
		// that preced this one.
		vector<HumdrumToken*> previousNonNullTokens;

		// rhycheck: Used to perfrom HumdrumFile::analyzeRhythm recursively.
		int rhycheck;
		

	friend class HumdrumLine;
	friend class HumdrumFile;
};




class Convert {
	public:
		static HumNum  recipToDuration  (const string& recip, HumNum scale = 4,
		                                 string separator = " ");
};





#endif /* _MINHUMDRUM_H */

