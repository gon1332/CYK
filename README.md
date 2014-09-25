# CYK parsing algorithm.

## Implementation
The program takes as input
 - the grammar in CNF (symbols must be one-character wide) in an XML file
 - the string to be parsed

The algorithm is:
 - implemented with dynamic programming

Current version is *supposed* to work.


## Test
To build:

    $ make

To clean:

    $ make clean

To execute:

	$ ./cyk cnf_grammar.jff


## TODO
 - Implement a Sets Data Type
 - Support name of symbols larger than one character
 - Clean up memory leaks
