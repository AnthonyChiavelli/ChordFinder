ChordFinder
===========

Trying to figure out the harmony of your favorite song and you can't remember what
chord A C# E F# is? Don't want to use some clunky flash app with a flame-pattern 
guitar in the background? ChordFinder fulfills its titular prophecy with simplicity 
and ease. Simply invoke ChordFinder from the command line with each argument as a  
note. Notes contain a letter from a - g followed by 0-2 sharp signs (#) or 0-2 flat
(b) signs. Examples of valid notes include: A a# bbb c## E#. In this release, only
exact matches are returned, and note ordering is not significant.

**Usage**

ChordFinder note1 [note2] [note3] ...

Example:

$ ChordFinder c eb gb bb
>> C half-diminished 7
>> Eb minor 6
