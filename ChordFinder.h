#include <map>
#include <set>
#include <string>
using namespace std;

/* A mapping from sets of note patterns to chord
 * type names
 */
map<set<int>, string> patternMap;

/* Returns a set of strings, each naming a chord formed
 * by combining the notes, given as a string
 */
set<string> findChords (string notes);

/* Takes a string of notes and produces a set of properly
 * formatted (i.e. sharps only) strings representing notes
 */
static set <string> tokenize (string notes);

/* Returns the distance in semitones from A up to the
 * parameter note
 */
static int chrIndexOf(string note);

/* Returns the note index number of semitones from A */
static string noteAtIndex(int index);

/* Initializes the chord type patterns */
static int initPatternData();

/* Tests two note patterns for equality */
static bool patternsEqual(const set<int>&, const set<int>&);

