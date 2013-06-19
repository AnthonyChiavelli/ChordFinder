#include "ChordFinder.h"
#include <boost/regex.hpp>
using namespace std;

void printSet(set<int> s) {
  for (auto i = s.begin(); i !=s.end(); cout << *i++);
}

void printSetS(set<string> s) {
  for (auto i = s.begin(); i !=s.end(); cout << *i++ << " ");
}
set<string> *findChords (string notes) {
  //Get note tokens
  set<string> noteList = tokenize(notes);
  cout << "note set is ";
  printSetS(noteList);
  cout << endl;
  set<string> *chordNames = new set<string>;
  //Iterate over notes, assuming each is tonic
  for (set<string>::iterator tonic = noteList.begin(); tonic != noteList.end(); ++tonic) {
    //Pattern of intervals between tonic and other notes
    set<int> pattern;
    //Iterate over other notes, finding interval to current tonic
    for (set<string>::iterator note = noteList.begin(); note != noteList.end(); ++note) {
      int interval = ((chrIndexOf(*note) - chrIndexOf(*tonic)) + 12 ) % 12;
      pattern.insert(interval);
    }
    cout << "pattern is ";
    printSet(pattern);
    cout << endl;
    //Match to chord pattern library
    for (map<set<int>, string>::iterator pairs = patternMap.begin(); pairs != patternMap.end(); ++pairs) {
      if (patternsEqual(pairs->first, pattern))  {
        cout << "Match between ";
        printSet(pairs->first);
        cout << " and ";
        printSet(pattern);
        cout << endl;
        chordNames->insert(*tonic + string(" ") + string(pairs->second)); 
      }
    }
  }
  return chordNames;
}

static set<string> tokenize (string notes) {
  set<string> *validNotes = new set<string>; 
  //Matches chromatic scale notes
  static boost::regex validNotesRE("[A-Ga-g][#b]{0,2}"); 
  //End of sequence iterator for later comparison
  boost::regex_token_iterator<string::iterator> eos;
  boost::regex_token_iterator<string::iterator> iter (notes.begin(), notes.end(), validNotesRE, 0);
  //Add all matches to a set
  while (iter != eos) {
    cout << *iter <<endl;
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
  int index = ((note[0] - 'A') * 2) - ((note[0] >= 'C') + (note[0] >= 'F'));
  //No accidentals
  if (note.length() == 1)
    return index;
  for (int i = 1; i < note.length(); i++) {
    //Add or subtract for each accidental
    if (note[i] == '#') index++;
    else if (note[i] == 'b') index--;
  }
  return index;
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
  set<int> major6 = {0, 4, 7, 9};
  patternMap[major6] = "major 6";
  set<int> minor6 = {0, 3, 7, 9};
  patternMap[minor6] = "minor 6";

  //Seventh chords
  set<int> major7 = {0, 4, 7, 11};
  patternMap[major7] = "major 7";
  set<int> minor7 = {0, 3, 7, 10};
  patternMap[minor7] = "minor 7";
  set<int> dominant7 = {0, 4, 7, 10};
  patternMap[dominant7] = "dominant 7";
  set<int> diminished7 = {0, 3, 6, 9};
  patternMap[diminished7] = "diminished 7";
  set<int> halfdiminished7 = {0, 3, 6, 10};
  patternMap[halfdiminished7] = "half-diminished 7";
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
