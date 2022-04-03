#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [Cho Daehyeon]  [2016039075] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return NULL;
    }
    /* 행렬 생성 */
    int** matrix = (int**)malloc(sizeof(int*) * row);   // 행렬의 행 생성하고 row의 수만큼의 주소를 저장하는 메모리 할당
    for(int r = 0; r < row; r++){
        matrix[r] = (int*)malloc(sizeof(int) * col);    // 행렬의 열 생성하고 col의 수만큼의 정수를 저장하는 메모리 할당
    }
    if(matrix == NULL){     // 행렬 생성에 실패했을 경우 실패 메시지 출력
        printf("Memory Allocation Failed.\n");
        return NULL;
    }
    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return;
    }
    for(int matrix_row = 0; matrix_row < row; matrix_row++){
        for(int matrix_col = 0; matrix_col < col; matrix_col++)
            printf("%3d", matrix[matrix_row][matrix_col]);          // 행에 먼저 접근하고 행에 저장된 열을 차례대로 출력
        printf("\n");
    }
    printf("\n");
    if(matrix == NULL){     // 출력할 행렬이 비어있을 경우 실패 메시지 출력
        printf("Memory Allocation Failed.\n");
        return;
    }
    return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row < 0; matrix_row++){
        free(matrix[matrix_row]);       // 행의 각 열에 할당된 메모리 해제
    }
    free(matrix);   // 행에 할당된 메모리 해제
    return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row < row; matrix_row++)
        for(int matrix_col = 0; matrix_col < col; matrix_col++)
            matrix[matrix_row][matrix_col] = rand() % 20;       // 행렬에 0~19의 정수를 랜덤으로 저장
    if(matrix == NULL){
        printf("Memory Allocation Failed.\n");      // 값을 저장할 행렬이 없을 경우 실패 메시지 출력
        return -1;
    }
    return 1;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row < row; matrix_row++){
        for(int matrix_col = 0; matrix_col < col; matrix_col++)
            matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];   // a행렬과 b행렬의 값을 더해 sum행렬에 저장
    }
    if(matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL){
        printf("Memory Allocation Failed.\n");      // 값을 저장할 행렬이 없을 경우 실패 메시지 출력
        return -1;
    }
    print_matrix(matrix_sum, row, col);
    free_matrix(matrix_sum, row, col);
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row < row; matrix_row++){
        for(int matrix_col = 0; matrix_col < col; matrix_col++)
            matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];   // a행렬과 b행렬의 값의 차를 구해 sub행렬에 저장
    }
    if(matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL){
        printf("Memory Allocation Failed.\n");      // 값을 저장할 행렬이 없을 경우 실패 메시지 출력
        return -1;
    }
    print_matrix(matrix_sub, row, col);
    free_matrix(matrix_sub, row, col);
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return -1;
    }
    for(int matrix_row = 0; matrix_row < row; matrix_row++){
        for(int matrix_col = 0; matrix_col < col; matrix_col++)
            matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];  // 행렬의 행과 열을 서로 바꾼 전치행렬 matrix_t 생성
    }
    if(matrix == NULL || matrix_t == NULL){
        printf("Memory Allocation Failed.\n");      // 값을 저장할 행렬이 없을 경우 실패 메시지 출력
        return -1;
    }
    return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);
    if(row <= 0 || col <= 0){       // row나 col가 0보다 작을 경우 상태를 확인하는 메시지 출력
        printf("Check the size of row and col\n");
        return -1;
    }
    for(int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++){          // 행렬 a의 모든 row에 대해 실행
        for(int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++){      // 행렬 a_t의 모든 row에 대해 실행
            int temp = 0;
            for(int matrix_col = 0; matrix_col < col; matrix_col++)
                temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];    // 행렬 a의 row * col 성분과 행렬 a_t의 col * row 성분을 곱해서 temp에 차례로 더하기
            matrix_axt[matrix_a_row][matrix_t_row] = temp;      // axt행렬의 각 성분에 temp 저장
        }
    }
    if(matrix_t == NULL || matrix_axt == NULL){
        printf("Memory Allocation Failed.\n");      // 값을 저장할 행렬이 없을 경우 실패 메시지 출력
        return -1;
    }
    print_matrix(matrix_axt, row, row);
    free_matrix(matrix_axt, row, col);
    return 1;
}
