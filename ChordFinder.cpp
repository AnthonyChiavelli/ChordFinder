#include "ChordFinder.h"
#include <boost/regex.hpp>
using namespace std;

set<string> *findChords (string notes) {
  //Get note tokens
  set<string> noteList = tokenize(notes);
  set<string> *chordNames = new set<string>;
  //Iterator over notes, assuming each is tonic
  for (set<string>::iterator tonic = noteList.begin(); tonic != noteList.end(); ++tonic) {
    //Pattern of intervals between tonic and other notes
    set<int> pattern;
    //Iterate over other notes, finding interval to current tonic
    for (set<string>::iterator note = noteList.begin(); note != noteList.end(); ++note) {
      int interval = ((chrIndexOf(*note) - chrIndexOf(*tonic)) + 12 ) % 12;
      pattern.insert(interval);
    }
    //Match to chord pattern library
    for (map<set<int>, string>::iterator pairs = patternMap.begin(); pairs != patternMap.end(); ++pairs) {
      if (patternsEqual(pairs->first, pattern)) 
        chordNames->insert(*tonic + string(" ") + string(pairs->second)); 
    }
  }
  return chordNames;
}

static set<string> tokenize (string notes) {
  set<string> *validNotes = new set<string>; 
  //Matches chromatic scale notes
  static boost::regex validNotesRE("[A-Ga-g][b#]{0,2}"); 
  //End of sequence iterator for later comparison
  boost::regex_token_iterator<string::iterator> eos;
  boost::regex_token_iterator<string::iterator> iter (notes.begin(), notes.end(), validNotesRE, 0);
  //Add all matches to a set
  while (iter != eos) {
    string note = *iter++;
    //If lowercase, make uppercase
    if ((note)[0] > 'Z') 
      (note)[0] -= ('a' - 'A');
    validNotes->insert(note);
  }
  return *validNotes;
}

static int chrIndexOf(string note) {
  //Find the index of the note without any accidentals
  int rootIndex = ((note[0] - 'A') * 2) - ((note[0] >= 'C') + (note[0] >= 'F'));
  //Increment if there is a sharp sign in the string
  return rootIndex + (note.length() - 1);
}

int initPatternData() {
  //Triads
  set<int> major = {0, 4, 7};
  patternMap[major] = "major";
  set<int> minor = {0, 3, 7};
  patternMap[minor] = "minor";
  set<int> augmented = {0, 4, 8};
  patternMap[augmented] = "augmented";
  set<int> diminished = {0, 3, 6};
  patternMap[diminished] = "diminshed";
  
  //Triads with suspensions
  set<int> add9 = {0, 2, 4, 7};
  patternMap[add9] = "add 9";
  set<int> sus2 = {0, 2, 7};
  patternMap[sus2] = "sus 2";
  set<int> sus4 = {0, 5, 7};
  patternMap[sus4] = "sus 4";

  //Sixth chords
  set<int> major6 = {0, 4, 7, 10};
  patternMap[major6] = "major 6";
  set<int> minor6 = {0, 3, 7, 10};
  patternMap[minor6] = "minor 6";


  //Seventh chords
  set<int> major7 = {0, 4, 7, 11};
  patternMap[major7] = "major 7";
  set<int> minor7 = {0, 3, 7, 10};
  patternMap[minor7] = "minor 7";
  set<int> dominant7 = {0, 4, 7, 10};
  patternMap[dominant7] = "dominant 7";
  set<int> diminished7 = {0, 3, 6, 9};
  patternMap[diminshed] = "diminished 7";
  set<int> halfdiminished7 = {0, 3, 6, 10};
  patternMap[halfdiminshed7] = "half-diminished 7";
  set<int> minorMajor7 = {0, 3, 7, 11};
  patternMap[minorMajor7] = "minor major 7";
  set<int> augmented7= {0, 4, 8, 10};
  patternMap[augmented7] = "augmented 7";
  set<int> augmentedMajor7 = {0, 4, 8, 11};
  patternMap[augmentedMajor7] = "augmented major 7";

  return 0; 
}

static bool patternsEqual(const set<int> &a, const set<int> &b) {
  if (a.size() != b.size())
    return false;
  return equal(a.begin(), a.end(), b.begin());
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: ChordFinder note1 [note2] [note3] ..." << endl;
    return 1;
  }
  string chordString;
  //Flatten command line args into a single string
  for (int i = 1; i < argc; i++) 
    chordString += string(argv[i]) + " ";
  //Initialize chord data
  initPatternData();
  //Find and print
  set<string> *notes = findChords(chordString);
  for (set<string>::iterator iter = notes->begin(); iter != notes->end(); ++iter) 
    cout << *iter << endl;
  return 0;
}
