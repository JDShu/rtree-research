#include <stdio.h>
#include <stdlib.h>

#include "index.h"

struct DataEntry {
  int x;
  int y;
  char name[50];
};

struct DataEntry parseEntry(char *line) {
  struct DataEntry newEntry;
  sscanf(line, "%d:%d:%[^\t\n]", &newEntry.x, &newEntry.y, &newEntry.name);
  return newEntry;
  //printf("(%d, %d) for %s\n", newEntry.x, newEntry.y, newEntry.name);
  //get x value

  //get y value

  //get name
}

int MySearchCallback(int id, void* arg)
{
	// Note: -1 to make up for the +1 when data was inserted
	printf("Hit data rect %d\n", id-1);
	return 1; // keep going
}

int main() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int id = 1;

  struct Node* root = RTreeNewIndex();

  fp = fopen("points.txt", "r");

  if (fp == NULL)
    exit(EXIT_FAILURE);

  while((read=getline(&line, &len, fp)) != -1) {
    struct DataEntry entry = parseEntry(line);
    struct Rect rect = {entry.x, entry.y, entry.x, entry.y};
    RTreeInsertRect(&rect, id, &root, 0);
    id++;
  }

  free(line);

  //nhits = RTreeSearch(root, &search_rect, MySearchCallback, 0);

  RTreePrintNode(root, 0);
  exit(EXIT_SUCCESS);
}
