#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  HashTable *ht = create_hash_table(16);
  
  /* YOUR CODE HERE */
  Answer *answer = malloc(sizeof(Answer));
  // put the weight into the hash table as the key, using the insert function
  // and the value will be their index in the hash table 
  for (int i = 0; i < length; i++) {
    hash_table_insert(ht, weights[i], i);
  }
  // using the retrieve function we'll try to find the correct weights that add up to the limit
  for (int i = 0; i < length; i++) {
    // subtract the limit weight from the weight stored as the key to get the difference
    // or the key we are looking for
    // save the retrieved value as an int so we can use it later
    int retrieved_value = hash_table_retrieve(ht, limit - weights[i]);
    // check to make sure that the key was found
    // and that the retrieved_value is not the same as the current i value 
    if (retrieved_value != -1 && retrieved_value != i) {
      // check to see which value is bigger to put them in the correct index field
      if (retrieved_value <= i) {
        answer->index_1 = i;
        answer->index_2 = retrieved_value;
        return answer;
      } else {
        answer->index_1 = retrieved_value;
        answer->index_2 = i;
        return answer;
      }
    }
  }
  // use destroy_hash_table function to combat memory leaks
  destroy_hash_table(ht);
  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{
  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}

#endif
