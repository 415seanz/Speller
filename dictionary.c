// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Create trie structure
typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

node *root;
unsigned int dict_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char checkchar;
    node *check_cursor = root;
    int word_length = strlen(word);

    // Iterate through the word comparing to trie
    for (int i = 0; i < word_length; i++)
    {
        // Convert each char to lower case
        checkchar = tolower(word[i]);

        // Convert apostrophes
        if (checkchar == '\'')
        {
            checkchar = 'z' + 1;
        }

        // Look for checkchar in children of cursor. If null return a misspelling
        if (check_cursor->children[checkchar - 'a'] == NULL)
        {
            return false;
        }
        // Follow children if entry exists
        else
        {
            check_cursor = check_cursor->children[checkchar - 'a'];
        }

        // If end of word, check whether cursor is word
        if (i == word_length - 1 && check_cursor->is_word == false)
        {
            return false;
        }
    }
    return true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }

    // Create root node and initialize it
    root = malloc(sizeof(node));
    if (!root)
    {
        fprintf(stderr, "Failed to allocate root\n");
        unload();
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }

    // Create load_cursor node and initially set it equal to root
    node *load_cursor = root;

    // Iterate through each dictionary character and place it in the trie
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // Check for apostrophes
        if (c == '\'')
        {
            c = 'z' + 1;
        }

        // Set is_word true for each endline and set load_cursor node back to root
        if (c == 0 || c == 10)
        {
            load_cursor->is_word = true;
            load_cursor = root;
            dict_count++;
        }

        // Create new node if it doesn't exist and go to it
        else if (load_cursor->children[c - 'a'] == NULL)
        {
            node *newnode = malloc(sizeof(node));
            if (!newnode)
            {
                fprintf(stderr, "Failed to allocate newnode\n");
                unload();
                return false;
            }
            newnode->is_word = false;
            for (int i = 0; i < 27; i++)
            {
                newnode->children[i] = NULL;
            }
            load_cursor->children[c - 'a'] = newnode;
            load_cursor = load_cursor->children[c - 'a'];
        }

        // Go to node if it exists
        else if (load_cursor->children[c - 'a'] != NULL)
        {
            load_cursor = load_cursor->children[c - 'a'];
        }
    }

    fclose(dict);

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_count;
}

// Recursive function to unload nodes. Returns true if it completes successfully
bool unloadnode(node *unload_cursor, node *unload_cursor_child)
{
    // Loop through each position in the child node
    for (int i = 0; i < 27; i++)
    {
        // Free node if all of its children are NULL
        if (unload_cursor_child->children[i] == NULL)
        {
            if (i == 26)
            {
                free(unload_cursor_child);
                unload_cursor_child = unload_cursor;
            }
        }

        // If children aren't null, go to child and call self recursively
        else
        {
            node *new_unload_cursor = unload_cursor_child;
            node *new_unload_cursor_child = unload_cursor_child->children[i];
            unloadnode(new_unload_cursor, new_unload_cursor_child);
            // Free last node after unloading its children
            if (i == 26)
            {
                free(new_unload_cursor);
            }
        }


    }
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *unload_root = root;
    bool success = unloadnode(unload_root, unload_root);
    return success;
}