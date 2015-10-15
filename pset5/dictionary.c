/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

 // trie struct
typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

// function to create new node
node* getNode();

//function to get position in array
int array_pos(int c);

// keep track of number of words loaded into dictionary
int dict_size = 0;

// create root node of trie
node* root = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
 

    
bool check(const char* word)
{
    // initialize index of word letters and set current node to root
    int index = 0;
    node* curr = root;
    int pos;
    
    // check for end of word
    while (word[index] != '\0')
    {
        // get position of letter in array
        int letter = tolower(word[index]);
        pos = array_pos(letter);
        
        // check to see if it exists in the array
        if(curr->children[pos] != NULL)
        {
            curr = curr->children[pos];
            index++;
        }
        
        else
        {
            return false;
        }
    }
    
    if(curr->is_word == true)
    {    
        return true;
    }
    
    return false;  
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //create current node and set to root
    root = getNode();
    node* curr = root;
    
    //open file
    FILE* fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }
    
    //initialize c
    int c = 0;
       
    // iterate through until end of file
    while ((c = fgetc(fp)) != EOF)
    {
        // iterate through word
        if (c != '\n')
        {
            // get position of letter in the trie array
            int pos = array_pos(c);
            
            //if the trie node is null, create a new node
            if(!curr->children[pos])
            {
                node* new = getNode();
                curr->children[pos] = new;
            }
        
        // place the current node at the next level down    
        curr = curr->children[pos];
        }
        
        else
        {    
            // once a newline is detected, change bool to true and increase dicitonary size
            curr->is_word = true;
            curr = root;
            dict_size++;
        }
    }
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dict_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 
void freeNode(node* current)
{
    for (int i = 0; i < 27; i++)
    {
        if(current->children[i] != NULL)
        {
            freeNode(current->children[i]);
        }
    }
    free(current);
}  
 
bool unload(void)
{
    freeNode(root);  
    return true;
}

// function to create new node
node* getNode()
{
    node* new_node = NULL;
    new_node = malloc(sizeof(node));
    new_node->is_word = false;
    
    for(int i = 0; i < 27; i++)
    {
        new_node->children[i] = NULL;
    }
    
    return new_node;
}

//function to get position in array
int array_pos(int c)
{
    if(c == '\'')
    {
       int n = 26;
       return n;
    }
    else
    {
        int n = (tolower(c) - 'a');
        return n;
    }
}
