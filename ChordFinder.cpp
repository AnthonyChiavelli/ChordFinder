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
  //The index number of the note without accidental
  //int rootIndex = (note[0] <= 'e') ? 
  //                  ((note[0] - 'a') * 2):
  //                  ((note[0] - 'a') * 2) - 1;
  int rootIndex = ((note[0] - 'a') * 2) - ((note[0] >= 'c') + (note[0] >= 'f'));
  
  //Increment if there is a sharp sign in the string
  return rootIndex + (note.length() - 1);

}


int main() {
  string test("C# DDDbHHggG G#");
  set<string> notes = tokenize(test);
  for (set<string>::iterator iter = notes.begin(); iter != notes.end(); ++iter) {
    cout << *iter << endl;
  }

  cout << "Index of g#: " << chrIndexOf("g#") << endl;
  cout << "Index of a: " << chrIndexOf("a") << endl;
  cout << "Index of a#: " << chrIndexOf("a#") << endl;
  cout << "Index of b: " << chrIndexOf("b") << endl; 
  cout << "Index of c: " << chrIndexOf("c") << endl;
  cout << "Index of d: " << chrIndexOf("d") << endl;
  cout << "Index of d#: " << chrIndexOf("d#") << endl;
  return 0;
}


