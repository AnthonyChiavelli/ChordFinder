#include "ChordFinder.h"
#include <boost/regex.hpp>

using namespace std;

set<string> findChords (string notes) {
  

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
    validNotes->insert(*iter++);
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
      return string("A");
    case 1:
      return string("A#");
    case 2:
      return string("B");
    case 3:
      return string("C");
    case 4:
      return string("C#");
    case 5:
      return string("D");
    case 6:
      return string("D#");
    case 7:
      return string("E");
    case 8:
      return string("F");
    case 9:
      return string("F#");
    case 10:
      return string("G");
    case 11:
      return string("G#");
  }
}

int main() {

  return 0;
}


