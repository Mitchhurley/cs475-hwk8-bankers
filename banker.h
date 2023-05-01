/* declarations related to banker's algorithm */
void isSafe(int* available, int** alloc, int** need, int m, int n);
void print_schedules(int* finish, int** sequence, int num_schedules, int n); 
int ** subtractMatrices(int** matrix1, int** matrix2, int outerLength, int innerLength);
bool recursive_test(int* available, int** alloc, int** need, int m, int n, int depth, int* finished,  int* cur_seq);