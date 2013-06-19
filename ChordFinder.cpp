#include "ChordFinder.h"
#include <boost/regex.hpp>

using namespace std;

set<string> findChords (string notes) {
  set<string> noteList = tokenize(notes);
  set<string> chordNames;
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
        chordNames.insert(*tonic + string(" ") + string(pairs->second)); 
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
    //If capitalized, make lower case
    if ((note)[0] < 'a') {
      (note)[0] += ('a' - 'A');
    }
    validNotes->insert(note);
  }
  return *validNotes;
}

static int chrIndexOf(string note) {
  //Find the index of the note without any accidentals
  int rootIndex = ((note[0] - 'a') * 2) - ((note[0] >= 'c') + (note[0] >= 'f'));
  
  //Increment if there is a sharp sign in the string
  return rootIndex + (note.length() - 1);

}


int initPatternData() {
  set<int> major = {0, 4, 7};
  patternMap[major] = "major";
  
  set<int> minor = {0, 3, 7};
  patternMap[minor] = "minor";

  set<int> sus2 = {0, 2, 7};
  patternMap[sus2] = "sus2";
  
  set<int> sus4 = {0, 5, 7};
  patternMap[sus4] = "sus4";

  set<int> augmented = {0, 4, 8};
  patternMap[augmented] = "augmented";

  set<int> major7 = {0, 4, 7, 11};
  patternMap[major7] = "major7";

  set<int> minor7 = {0, 3, 7, 10};
  patternMap[minor7] = "minor7";
  
  set<int> dominant7 = {0, 4, 7, 10};
  patternMap[dominant7] = "dominant7";

  set<int> major6 = {0, 4, 7, 9};
  patternMap[major6] = "major6";
  
  set<int> minor6 = {0, 3, 7, 8};
  patternMap[minor6] = "minor6";



  //TODO: add more

 
  return 0; //TODO: fix
}

static bool patternsEqual(const set<int> &a, const set<int> &b) {
  if (a.size() != b.size())
    return false;
  return equal(a.begin(), a.end(), b.begin());
}

int main() {
  initPatternData();
  
  //set<string> chords = findChords("cbebgb bb");
  for (int i = 0; i < 1000000; i++) 
    findChords("cbebgb bb");

  //for (set<string>::iterator iter = chords.begin(); iter != chords.end(); ++iter) {
  //  cout << *iter << endl;
  //}
  return 0;
}


