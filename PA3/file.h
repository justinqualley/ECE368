#include"path.h"

void fastest_path(Node* vertices, char* filename);
short** read_graph(char*, short*, short*);
void graph_to_txt(short**, char*, short, short);
void path_to_txt(short**);
void fastest_times(int* times, char* filename, short n);
