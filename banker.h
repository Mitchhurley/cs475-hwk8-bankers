/* declarations related to banker's algorithm */
int isSafe(int* available, int** alloc, int** need, int m, int n);
void print_schedules(int* finish, int** sequence, int num_schedules, int n); 
int ** subtractMatrices(int** matrix1, int** matrix2, int outerLength, int innerLength);
int recursive_test(int* available, int** alloc, int** need, int m, int n, int depth, int* finished,  int* cur_seq,int* safe_threads);
// void isSafe2(int* available, int** alloc, int** need, int m, int n);