#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(length);
  char **route = malloc(length * sizeof(char *));

  /* YOUR CODE HERE */
  // using the insert function we'll put the tickets into the hash table
  // we'll use the ticket source as the key and the ticket destination as the value
  for (int i = 0; i < length; i++) {
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }
  // per the instructions we'll start our trip with a source of NONE
  // using the retrieve function we'll find that ticket to start with
  // and assign it to the first position in our route
  route[0] = hash_table_retrieve(ht, "NONE");
  // then we'll loop through our route starting at the second index
  for (int i = 1; i < length; i++) {
    // setting the route index by using the destination of the previous ticket (i-1)
    // and the retrieve function to find it
    route[i] = hash_table_retrieve(ht, route[i-1]);
  }
  // to not have memory leaks we use the destroy function to kill the hash table
  //destroy_hash_table(ht);
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  for (int i = 0; i < 3; i++) {
    free(tickets[i]);
  }

  free(tickets);

  return 0;
}
#endif
