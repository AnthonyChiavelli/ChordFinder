#include <set>
#include <string>

/* Returns a set of strings, each naming a chord formed
 * by combining the notes, given as a string
 */

std::set<std::string> findChords (std::string notes);

/* Takes a string of notes and produces a set of properly
 * formatted (i.e. sharps only) strings representing notes
 */

static std::set <std::string> tokenize (std::string notes);


/* Returns the distance in semitones from A up to the
 * parameter note
 */
static int chrIndexOf(std::string note);

/* Returns the note index number of semitones from A */
static std::string noteAtIndex(int index);
