
// TODO: function prototypes of vector and matrix operations
int ** mat_clone(int** mat, int col, int rows);
void add_mats(int** matrix1, int** matrix2, int rows, int cols, int** result_matrix);
void sub_mats(int** matrix1, int** matrix2, int rows, int cols, int** result_matrix);
int* vec_clone(int* vec, int length);
void add_vecs(int* vec1, int* vec2, int size, int* result_vec);
void sub_vecs(int* vec1, int* vec2, int size, int* result_vec);
int vec_comp(int* vec1, int* vec2, int size);
void print_mat(int** mat, int cols, int rows);
void print_vec(int* vec, int size);