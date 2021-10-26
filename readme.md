***
# this README file covers:

- documentation of program

- documentation of refactoring
***

# PROGRAM DOCUMENTATION

## Simple console application, for processing text files with predefined structure;

### what program does:

	- reads data from structured text file and loads it to list of structures

	- allows user to append to the list, and it sorts appended cell to already sorted list

	- allows user to print the content from list into console

	- allows user to print out palindromes (from car plates) and it also prints name (does not have to be palindrome)

	- prints monthly reward for officer

	- prints offences from given year

### types of inputs:

	- alpha numeric values from console

	- text file:  'priestupky.txt'

### structure of an input file ('priestupky.txt'):

 	- every line holds one type of information

	- one data chunk consists of 7 LINES

	- those data clusters are divided by '\n', empty char

	- it is alphabetically sorted by name

### console commands
```
o- loads data from 'priestupky.txt' and puts the data into newly created list of structures

v- prints out the content of list

x- prints out offences from desired month

r- prints out month revenue/reward for police officer out of data from list

p- prints out palindromes (from car plates)

a- appends to the list (one record), and it sorts appended record to already sorted list

k- deallocs memory, closes file, and points pointers back to null
```

***

# REFACTORING, DOCUMENTATION OF CHANGES:


1. deletion of duplicate/repeating code (commit on GitHub is called: 'simplified addChunk...')

2. changed variable names (in numerous commits within branch 'change_variable_names') into more meaning full names, e.g. from chunk to list

3. changed function names into more meaning full names (inside branch 'change_variable_names')

4. encapsulation, - creation of two new functions (fillList, fillCell), out of loadFromTxtFile, and by that function loadFromTxtFile has been shortened

5. using newly created function fillCell inside of function appendToList, thus making function appendToList much shorter

6. deletion of code that was not necessary, e.g. unnecessary if statements

7. Updating error messages, when file was not loaded or when memory was not allocated

8. deletion of magical numbers- creation of constants

9. comment at beginning that explains the functionality of a program + deletion of Slovak comments

10. changing if statements into switch

11. cosmetic changes, deletion of spaces and other visual adjustments

12. function comments, every function has its own comment that declares its functionality, parameters and its return type if it returns anything
