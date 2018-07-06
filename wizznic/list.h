#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

struct listItemStruct
{
  void* data;
  struct listItemStruct* next;
};

typedef struct listItemStruct listItem;

void listAddData(listItem* start, void* data);
void listRemoveItem(listItem* start, listItem* item);
listItem* initList();
void freeList(listItem* start);
int listSize(listItem* start);

void* listGetItemData(listItem* start, int index);


#endif // LIST_H_INCLUDED
