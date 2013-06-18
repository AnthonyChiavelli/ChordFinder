#include "ChordFinder.h"
#include <boost/regex.hpp>

using namespace std;

set<string> findChords (string notes) {
  set<string> noteList = tokenize(notes);
  
  //Iterator over notes, assuming each is tonic
  for (set<string>::iterator tonic = noteList.begin(); tonic != noteList.end(); ++tonic) {
    //Pattern of intervals between tonic and other notes
    set<int> pattern;
    //Iterate over other notes, finding interval to current tonic
    for (set<string>::iterator note = noteList.begin(); note != noteList.end(); ++note) {
      int interval = ((chrIndexOf(*note) - chrIndexOf(*tonic)) + 12 ) % 12;
      cout << "Int between " + (*tonic) << " ("  << chrIndexOf(*tonic) << ")" << " and " << (*note) << " ( " << chrIndexOf(*note) << ") " <<" : " << interval << endl; 
      pattern.insert(interval);
    }
    for (set<int>::iterator intv = pattern.begin(); intv != pattern.end(); ++intv) {
      cout << *intv << " ";
    }
    cout << endl;
  }
  return noteList;
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

static string noteAtIndex(int index) {
  switch (index) {
    case 0:
      return string("a");
    case 1:
      return string("a#");
    case 2:
      return string("b");
    case 3:
      return string("c");
    case 4:
      return string("c#");
    case 5:
      return string("d");
    case 6:
      return string("d#");
    case 7:
      return string("e");
    case 8:
      return string("f");
    case 9:
      return string("f#");
    case 10:
      return string("g");
    case 11:
      return string("g#");
  }
}

int main() {
  findChords("cdg");
  return 0;
}


