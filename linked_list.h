
// Bismillah

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

struct Node {
  int data;
  struct Node* next_node;
};

struct LinkedList {
  int num_of_nodes;
  struct Node* head;
};

/**
* Allocates and initializes the LinkedList.
* 
* @return Initialized LinkedList. NULL if function failed.
*/
struct LinkedList* linked_list_alloc() {
  
  struct LinkedList* ptr_to_list = (struct LinkedList*)malloc(sizeof(struct LinkedList)*1); 
  ptr_to_list->num_of_nodes = 0;  
  ptr_to_list->head = NULL;      

  return ptr_to_list;             


}


/**
  * Returns the amount of elements in the LinkedList.
  *
  * @param linked_list  LinkedList that we want to know how many elements are in
  *
  * @return number of elements
  */
int linked_list_get_size(struct LinkedList* linked_list){
  
  return linked_list->num_of_nodes;


}





/**
* Get the data at the given index of the LinkedList.
*
* @param linked_list the LinkedList to fetch data from
*
* @param index  index of element to fetch
*
* @return the data at the index requested
*/
int linked_list_get_element_at(struct LinkedList* linked_list, int index){

  if (index >= linked_list->num_of_nodes || index < 0) {
    return -1;
  }


  struct Node* temporary_ptr = linked_list->head;   
                                                    

  for (int i = 0; i < index ; i++) {                
                                                     
    temporary_ptr = temporary_ptr->next_node;
  }

  return temporary_ptr->data;
  
}




/**
* Insert an element at the beginning of the LinkedList.
*
* @param linked_list the LinkedList to insert into
*
* @param data the element to insert
*/
void linked_list_prepend(struct LinkedList* linked_list, int data){      
                                                                   
  struct Node* prepended_node = (struct Node*)malloc(sizeof(struct Node));
  prepended_node->data = data;                                        
  prepended_node->next_node = linked_list->head;    
  linked_list->head = prepended_node;    
  linked_list->num_of_nodes++;                     
}


/**
* Insert an element at the end of the LinkedList.
*
* @param linked_list the LinkedList to insert into
*
* @param data the element to insert
*/
void linked_list_append(struct LinkedList* linked_list, int data){
  

  struct Node* appended_node = (struct Node*)malloc(sizeof(struct Node));
 
  if (linked_list->head != NULL){
  struct Node* temporary_ptr = linked_list->head;

  while (temporary_ptr->next_node != NULL) {
    temporary_ptr = temporary_ptr->next_node;
  }
  
  
  appended_node->data = data;
  temporary_ptr->next_node = appended_node;
  appended_node->next_node = NULL;
  }

  else {
    linked_list->head = appended_node;
    appended_node->next_node = NULL;
  }
  

linked_list->num_of_nodes++;


}




/**
* Insert an element at a certain index into the LinkedList. If there is an existing element,
* then it may be moved to the right.
*
* @param linked_list the LinkedList to insert into
* 
* @param data data to insert
*
* @param index index of where to insert element
*/
void linked_list_insert_element_at(struct LinkedList* linked_list, int data, int index){

 
  if (index > linked_list->num_of_nodes || index < 0) {
    raise(SIGSEGV);
    
    exit(0);
  } 

  if (index == 0){
    linked_list_prepend(linked_list, data);

    return;
  }

  else if (index == linked_list->num_of_nodes){

    linked_list_append(linked_list, data);

    return;
  }


  
  struct Node* inserted_node = (struct Node*)malloc(sizeof(struct Node));
 

  struct Node* temporary_ptr = linked_list->head;

  for (int i = 1; i < index; i++) {
    temporary_ptr = temporary_ptr->next_node;
  }
  
  
  inserted_node->data = data;
  inserted_node->next_node=temporary_ptr->next_node;
  temporary_ptr->next_node = inserted_node; 
  

linked_list->num_of_nodes++;

}



/**
* Remove an element at a certain index of the LinkedList.
*
* @param linked_list the LinkedList to remove from
*
* @param index index of element to remove
*
* @return the data of the element removed
*/
int linked_list_remove_element_at(struct LinkedList* linked_list, int index){


  if (index > linked_list->num_of_nodes || index < 0) {
    return -1;
  }

  if (index == 0){
    
    int removed = linked_list->head->data;

    linked_list->head = linked_list->head->next_node;
    
    linked_list->num_of_nodes--;

    return removed;
  }

  struct Node* temporary_ptr = linked_list->head;
       
  for (int i = 1; i < index; i++){
    temporary_ptr = temporary_ptr->next_node;
  }
  int removed_element = temporary_ptr->next_node->data;


  temporary_ptr->next_node = temporary_ptr->next_node->next_node;
  linked_list->num_of_nodes--;
  return removed_element;
}

/**
  * Deallocating the LinkedList.
  *
  * @param linked_list the LinkedList to deallocate
  */
void linked_list_free(struct LinkedList* linked_list){
  
  struct Node* temporary_ptr = linked_list->head;

 while (temporary_ptr != NULL) {

    struct Node* to_delete = temporary_ptr;
    temporary_ptr = temporary_ptr->next_node;

    free(to_delete);
   
}

  free(linked_list);
}
