//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sun Oct 16 16:08:05 PDT 2016
// Last Modified: Sun Oct 16 16:08:08 PDT 2016
// Filename:      GridCommon.h
// URL:           https://github.com/craigsapp/hum2ly/blob/master/include/GridCommon.h
// Syntax:        C++11; humlib
// vim:           ts=3 noexpandtab
//
// Description:   Enumerations shared between various classes in Grid system.
//

#ifndef _GRIDCOMMON_H
#define _GRIDCOMMON_H

namespace hum {

// START_MERGE

// SliceType is a list of various Humdrum line types.  Groupings are
// segmented by categories which are prefixed with an underscore.
// For example Notes are in the _Duration group, since they have
// non-zero durations.  Notes and Gracenotes are in the _Data group.
// The indentation shows the various types of groups.
//

enum class SliceType {
				Notes = 1,
			_Duration,
				GraceNotes,
		_Data,
			Measures,
		_Measure,
				Stria,
				Clefs,
				Transpositions,
				KeyDesignations,
				KeySigs,
				TimeSigs,
				MeterSigs,
				Tempos,
				Labels,
				LabelAbbrs,
				Ottavas,
			_RegularInterpretation,
				Exclusives,
				Terminators,
				Manipulators,
			_Manipulator,
		_Interpretation,
			Layouts,
			LocalComments,
	_Spined,
		GlobalComments,
		GlobalLayouts,
		ReferenceRecords,
	_Other,
		Invalid
};


// MeasureType is a list of the style types for a measure (ending type for now)

enum class MeasureStyle {
	Invisible,
	Plain,
	RepeatBackward,
	RepeatForward,
	RepeatBoth,
	Double,
	Final
};


// END_MERGE

} // end namespace hum

#endif /* _GRIDCOMMON_H */



