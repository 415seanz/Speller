This is a program written in C. Speller.c was written for me as part of a project. It calls methods from dictionary.h, which I wrote myself. The program allows users to upload a given txt file dictionary (from the /dictionaries folder in this repository), and store the dictionary in memory in a trie. Then, the user can import some other txt file (from the /texts folder in this repository). The program will check that txt file for spelling errors and return some statistics about the text along with any misspelled words. It will then offload the dictionary, freeing up any memory that was allocated to it.
