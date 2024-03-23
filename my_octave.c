#include <stdio.h>
#include <stdlib.h>

//se aloca memoria pentru o matrice din vectorul de matrici

int** alloc_matrix(int *rows, int *colls, int index, int ***arr) {
    arr[index] = (int **)malloc(rows[index] * sizeof(int *));
    if (arr[index] == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE PENTRU MATRICE!1");
        free(arr[index]);
		return NULL;
    }
    for (int i = 0; i < rows[index]; i++) {
        arr[index][i] = (int *)malloc(colls[index] * sizeof(int));
        if (arr[index][i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE PENTRU MATRICE!2");
            for (int j = i; j >= 0; j--) {
                free(arr[index][j]);
            }
            free(arr[index]);
            return NULL;
        }
    }
    return arr[index];
}

//redimensionarea matricii

int** resize_matrix(int ***arr, int index, int *rows, int *colls) {
    arr[index] = (int**)realloc(arr[index], rows[index] * sizeof(int *));
    if (arr[index] == NULL) {
        fprintf(stderr, "NU S-A PUTUT REALOCA MEMORIE!3");
        free(arr[index]);
        return NULL;
    }
	for (int i = 0; i < rows[index]; i++) {
		arr[index][i] = (int *)calloc(1, sizeof(int));
	}
    for (int i = 0; i < rows[index]; i++) {
        arr[index][i] = (int*)realloc(arr[index][i], colls[index] * sizeof(int));
        if (arr[index][i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT REALOCA MEMORIE!4");
            for (int j = i; j >= 0; j--)
                free(arr[index][j]);
            free(arr[index]);
            return NULL;
        }
    }
    return arr[index];
}

//redimensionarea vectorului de matrici(pentru cand se citeste o noua matrice
//sau este eliminata una din colectie)

int*** realloc_array(int index, int ***arr) {
    arr = (int ***)realloc(arr, (index + 1) * sizeof(int **));
    if (arr == NULL) {
        fprintf(stderr, "NU S-A PUTUT REALOCA MEMORIE!5");
        free(arr);
        return NULL;
    }
    return arr;
}

//alocarea initiala pentru vectorul de matrici

int*** alloc_array(int ***arr) {
    arr = (int ***)malloc(sizeof(int **));
    if (arr == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!6");
        free(arr);
        return NULL;
    }
    return arr;
}

//alocarea initiala pentru vectorii care memoreaza dimensiunile matricilor

int* alloc_size(int *size) {
    size = (int *)malloc(sizeof(int));
    if (size == NULL) {
        fprintf(stderr, "NU S-A PUTU ALOCA MEMORIE!7");
        free(size);
        return NULL;
    }
    return size;
}

//redimensionarea vectorilor care retin dimensiunile matricilor (pentru cazul)
//in care se adauga sau se scot matrici

int* realloc_size(int *size, int index) {
    size = (int *)realloc(size, (index + 1) * sizeof(int));
    if (size == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!8");
        free(size);
        return NULL;
    }
    return size;
}

//citirea unei matrici de la tastatura

void read_matrix(int *rows, int *colls, int index, int ***arr) {
    for (int i = 0; i < rows[index]; i++) {
        for (int j = 0; j < colls[index]; j++) {
            scanf("%d ", &arr[index][i][j]);
        }
    }
}

//afisarea dimensiunilor matricei cu indexul mat

void opD(int mat, int *rows, int *colls) {
    printf("%d %d\n", rows[mat], colls[mat]);
}

//afisarea matricei cu indexul mat

void opP(int ***arr, int *rows, int *colls, int mat) {
    for (int i = 0; i < rows[mat]; i++) {
        for (int j = 0; j < colls[mat]; j++) {
            printf("%d ", arr[mat][i][j]);
        }
        printf("\n");
    }
}

//cropul pe matrice

int *** opC(int ***arr, int *rows, int *colls, int mat) { 
    int l, c;
    int *vc, *vl;
    scanf("%d", &l);
    vl = (int *)malloc(l * sizeof(int));
    if (vl == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!9");
        free(vl);
        return NULL;
    }
    for (int i = 0; i < l; i++) {
        scanf("%d ", &vl[i]);
    }
    scanf("%d", &c);
    vc = (int *)malloc(c * sizeof(int));
    if (vc == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!10");
        free(vc);
        return NULL;
    }
    for (int i = 0; i < c; i++) {
        scanf("%d ", &vc[i]);
    }
    int **au;
    au = (int **)malloc(l * sizeof(int *));
    if (au == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!11");
        free(au);
        return NULL;
    }
    for (int i = 0; i < l; i++) {
        au[i] = (int *)malloc(c * sizeof(int));
        if (au[i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!12");
            for (int j = i; j >= 0; j--)
                free(au[j]);
            free(au);
            return NULL;
        }
    }
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            au[i][j] = arr[mat][vl[i]][vc[j]];
        }
    }
    for (int i = 0; i < rows[mat]; i++)
        free(arr[mat][i]);
    free(arr[mat]);
    rows[mat] = l;
    colls[mat] = c;
    arr[mat] = alloc_matrix(rows, colls, mat, arr);
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            arr[mat][i][j] = au[i][j];
        }
    }
    for (int i = 0; i < l; i++)
        free(au[i]);
    free(au);
    free(vl);
    free(vc);
    return arr;
}

//inmultirea a doua matrici din multime

int*** opM(int ***arr, int *rows, int *colls, int index, int mat1, int mat2) {
    if (rows[mat2] == colls[mat1]) {
        arr[index] = alloc_matrix(rows, colls, index, arr);
        for (int i = 0; i < rows[mat1]; i++) {
            for (int j = 0 ; j < colls[mat2]; j++) {
                    arr[index][i][j] = 0;
            }
        }
        for (int i = 0; i < rows[mat1]; i++) {
            for (int j = 0 ; j < colls[mat2]; j++) {
                for (int k = 0; k < colls[mat1]; k++) {
                    arr[index][i][j] += arr[mat1][i][k] * arr[mat2][k][j];
					arr[index][i][j] = arr[index][i][j] % 10007;
                }
                if (arr[index][i][j] < 0)
                    arr[index][i][j] += 10007;
            }
        }
    } else {
        printf("Cannot perform matrix multiplication\n");
    }
    return arr;
}

//sortarea matricilor din multime

int*** opO(int ***arr, int *rows, int *colls, int index) {
    int *sort, aux;
	sort = (int *)calloc(index + 1, sizeof(int));
    if (sort == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!13");
        free(sort);
        return NULL;
    }
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < rows[i]; j++) {
            for (int k = 0; k < colls[i]; k++) {
                sort[i] = sort[i] + arr[i][j][k];
            }
        }
        sort[i] = sort[i] % 10007;
        if (sort[i] < 0) {
            sort[i] = sort[i] + 10007;
        }
    }
    int **au;
    for (int i = 0; i < index - 1; i++) {
        for (int j = i + 1; j < index; j++) {
            if (sort[i] > sort[j]) {
				au = (int **)malloc(rows[i] * sizeof(int *));
				if (au == NULL) {
					fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!14");
					free(au);
					return NULL;
				}
				for (int u = 0; u < rows[i]; u++) {
					au[u] = (int *)malloc(colls[i] * sizeof(int));
					if (au[u] == NULL) {
						fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!15");
						for (int k = u; k >= 0; k--) {
							free(au[k]);
						}
						free(au);
						return NULL;
					}
				}
				for (int k = 0; k < rows[i]; k++) {
					for (int u = 0; u < colls[i]; u++) {
						au[k][u] = arr[i][k][u];
					}
				}
				for (int k = 0; k < rows[i]; k++) {
					free(arr[i][k]);
				}
				free(arr[i]);
				arr[i] = (int **)malloc(rows[j] * sizeof(int *));
				if (arr[i] == NULL) {
					fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!16");
					free(arr[i]);
					return NULL;
				}
				for (int k = 0; k < rows[j]; k++) {
					arr[i][k] = (int *)malloc(colls[j] * sizeof(int));
					if (arr[i][k] == NULL) {
						fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!17");
						for (int u = k; u >= 0; u--) {
							free(arr[i][u]);
						}
						free(arr[i]);
						return NULL;
					}
				}
				for (int k = 0; k < rows[j]; k++) {
					for (int u = 0; u < colls[j]; u++) {
						arr[i][k][u] = arr[j][k][u];
					}
				}
				for (int k = 0; k < rows[j]; k++) {
					free(arr[j][k]);
				}
				free(arr[j]);
				arr[j] = (int **)malloc(rows[i] * sizeof(int *));
				if (arr[j] == NULL) {
					fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!18");
					free(arr[j]);
					return NULL;
				}
				for (int k = 0; k < rows[i]; k++) {
					arr[j][k] = (int *)malloc(colls[i] * sizeof(int));
					if (arr[j][k] == NULL) {
						fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!19");
						for (int u = k; u >= 0; u--) {
							free(arr[j][u]);
						}
						free(arr[j]);
						return NULL;
					}
				}
				for (int k = 0; k < rows[i]; k++) {
					for (int u = 0; u < colls[i]; u++) {
						arr[j][k][u] = au[k][u];
					}
				}
				for (int k = 0; k < rows[i]; k++) {
					free(au[k]);
				}
				free(au);
                aux = rows[i];
                rows[i] = rows[j];
                rows[j] = aux;
                aux = colls[i];
                colls[i] = colls[j];
                colls[j] = aux;
                aux = sort[i];
                sort[i] = sort[j];
                sort[j] = aux;
            }
        }
    }
    free(sort);
    return arr;
}

//transpunerea matricei cu indexul mat

int*** opT(int ***arr, int *rows, int *colls, int mat) {
    int **au, aux;
    au = (int **)malloc(colls[mat] * sizeof(int *));
    if (au == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!20");
        free(au);
        return NULL;
    }
    for (int i = 0; i < colls[mat]; i++) {
        au[i] = (int*)malloc(rows[mat] * sizeof(int));
        if (au[i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!21");
            for (int j = i; j >= 0; j--) {
                free(au[j]);
            }
            free(au);
            return NULL;
        }
    }
    aux = rows[mat];
    rows[mat] = colls[mat];
    colls[mat] = aux;
    for (int i = 0; i < rows[mat]; i++) {
        for (int j = 0; j < colls[mat]; j++) {
            au[i][j] = arr[mat][j][i];
        }
    }
    for (int  i = 0; i < colls[mat]; i++)
        free(arr[mat][i]);
    arr[mat] = resize_matrix(arr, mat, rows, colls);
    for (int i = 0; i < rows[mat]; i++)
        for (int j = 0; j < colls[mat]; j++)
            arr[mat][i][j] = au[i][j];
    for (int i = 0; i < rows[mat]; i++)
        free(au[i]);
    free(au);
    return arr;
}

//inmultirea a doua matrici, pentru ridicarea la putere

int** matrix_multiplication(int **au1, int **au2, int **mau, int *rows, int *colls, int mat) {
    for (int i = 0; i < rows[mat]; i++) {
        for (int j = 0; j < colls[mat]; j++) {
            for (int k = 0; k < colls[mat]; k++) {
                mau[i][j] += au1[i][k] * au2[k][j];
                mau[i][j] = mau[i][j] % 10007;
            }
            if (mau[i][j] < 0)
                mau[i][j] += 10007;
        }
    }
    return mau;
}

//ridicarea la putere a unei matrici

int*** opR(int ***arr, int *rows, int *colls, int mat, int pow) {
    if (pow == 0) {
        for (int i = 0; i < rows[mat]; i++) {
            for (int j = 0; j < colls[mat]; j++) {
                if (i == j)
                    arr[mat][i][j] = 1;
                else arr[mat][i][j] = 0;
            }
        }
        return arr;
    }
    if (pow == 1)
        return arr;
    int **mau, **au;
    mau = (int **)malloc(rows[mat] * sizeof(int *));
    if (mau == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!22");
        free(mau);
        return NULL;
    }
    for (int i = 0; i < rows[mat]; i++) {
        mau[i] = (int *)malloc(colls[mat] * sizeof(int));
        if (mau[i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!23");
            for (int j = i; j >= 0; j--) {
                free(mau[j]);
            }
            free(mau);
            return NULL;
        }
    }
    au = (int **)malloc(rows[mat] * sizeof(int *));
    if (au == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!24");
        free(au);
        return NULL;
    }
    for (int i = 0; i < rows[mat]; i++) {
        au[i] = (int *)malloc(colls[mat] * sizeof(int));
        if (au[i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!25");
            for (int j = i; j >= 0; j--) {
                free(au[j]);
            }
            free(au);
            return NULL;
        }
    }
    int **au1 = (int **)malloc(rows[mat] * sizeof(int *));
    if (au1 == NULL) {
        fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!24");
        free(au);
        return NULL;
    }
    for (int i = 0; i < rows[mat]; i++) {
        au1[i] = (int *)malloc(colls[mat] * sizeof(int));
        if (au1[i] == NULL) {
            fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!25");
            for (int j = i; j >= 0; j--) {
                free(au1[j]);
            }
            free(au1);
            return NULL;
        }
    }
    for (int i = 0; i < rows[mat]; i++)
        for (int j = 0; j < colls[mat]; j++) {
            mau[i][j] = 0;
        }
    int ok1 = 0, ok2 = 0;
    int cpow = pow;
    while (pow > 1) {
        if (pow % 2 == 0) {
            if (ok1 == 0) {
                for (int i = 0; i < rows[mat]; i++)
                    for (int j = 0; j < colls[mat]; j++) {
                        au[i][j] = arr[mat][i][j];
                    }
                ok1 = 1;
            }
            mau = matrix_multiplication(au, au, mau, rows, colls, mat);
            for (int i = 0; i < rows[mat]; i++)
                for (int j = 0; j < colls[mat]; j++) {
                    au[i][j] = mau[i][j];
                }
            pow = pow / 2;
        } else {
            if (ok2 == 0) {
                for (int i = 0; i < rows[mat]; i++)
                    for (int j = 0; j < colls[mat]; j++) {
                        if (i == j)
                            au1[i][j] = 1;
                        else au1[i][j] = 0;
                    }
                ok2 = 1;
            }
            if (cpow == pow) {
                mau = matrix_multiplication(au1, arr[mat], mau, rows, colls, mat);
            } else {
                mau = matrix_multiplication(mau, arr[mat], mau, rows, colls, mat);
            }
            
            pow--;
        }
    }
    for (int i = 0; i < rows[mat]; i++) {
        for (int j = 0; j < colls[mat]; j++) {
            arr[mat][i][j] = mau[i][j];
        }
    }
    for (int i = 0; i < rows[mat]; i++) {
        free(mau[i]);
        free(au[i]);
    }
    free(mau);
    free(au);
    return arr;
}

//eliminarea unei matrici din memorie

int*** opF(int ***arr, int *rows, int *colls, int mat, int index) {
	for (int i = mat; i < index - 1; i++) {
		for (int j = 0; j < rows[i]; j++) {
			free(arr[i][j]);
		}
        free(arr[i]);
		arr[i] = (int **)malloc(rows[i + 1] * sizeof(int *));
		if (arr[i] == NULL) {
			fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!26");
			free(arr[i]);
			return NULL;
		}
		for (int j = 0; j < rows[i + 1]; j++) {
			arr[i][j] = (int *)malloc(colls[i + 1] * sizeof(int));
			if (arr[i][j] == NULL) {
				fprintf(stderr, "NU S-A PUTUT ALOCA MEMORIE!27");
				for (int k = j; k >= 0; k--) {
					free(arr[i][k]);
				}
				free(arr[i]);
				return NULL;
			}
		}
		for (int j = 0; j < rows[i + 1]; j++) {
			for (int k = 0; k < colls[i + 1]; k++) {
				arr[i][j][k] = arr[i + 1][j][k];
			}
		}
		rows[i] = rows[i + 1];
		colls[i] = colls[i + 1];
	}
	for (int i = 0; i < rows[index - 1]; i++)
		free(arr[index - 1][i]);
	free(arr[index - 1]);
	rows[index - 1] = 0;
	colls[index - 1] = 0;
	return arr;
}

//eliberarea de memorie si finalizarea programului

void opQ(int ***arr, int *rows, int *colls, int index) {
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < rows[i]; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
    free(rows);
    free(colls);
}

//cand este citit un index gresit pt op C, valorile ce se citesc sunt
//preluate de acest program si ignorate

void trash(int l, int c) {
    int k;
    scanf("%d", &l);
    while (l) {
        scanf("%d ", &k);
        l--;
    }
    scanf("%d", &c);
    while (c) {
        scanf("%d", &k);
        c--;
    }
}

int main(void) {
    char s;
    int m, n, mat, mat1, mat2, ok = 1;
    int l, c, pow;
    int ***arr, *rows, *colls;
    arr = alloc_array(arr);
    rows = alloc_size(rows);
    colls = alloc_size(colls);
    int index = 0;
    do {
        scanf("%s", &s);
        switch (s) {
            case 'L':
                scanf("%d %d", &m, &n);
                rows[index] = m;
                colls[index] = n;
                arr[index] = alloc_matrix(rows, colls, index, arr);
                read_matrix(rows, colls, index, arr);
                index++;
                arr = realloc_array(index, arr);
                rows = realloc_size(rows, index);
                colls = realloc_size(colls, index);
            break;
            case 'D':
                scanf("%d", &mat);
                if (mat >= index || mat < 0) {
                    printf("No matrix with the given index\n");
                } else {
                    opD(mat, rows, colls);
                }
            break;
            case 'P':
                scanf("%d", &mat);
                if (mat >= index || mat < 0)
                    printf("No matrix with the given index\n");
                else opP(arr, rows, colls, mat);
            break;
            case 'C':
                scanf("%d", &mat);
                if (mat >= index || mat < 0) {
                    printf("No matrix with the given index\n");
                    trash(l, c);
                } else {
                    arr = opC(arr, rows, colls, mat);
                }
            break;
            case 'M':
                scanf("%d %d", &mat1, &mat2);
                if (mat1 >= index || mat1 < 0 || mat2 < 0 || mat2 >= index)
                    printf("No matrix with the given index\n");
                else {
                    if (rows[mat2] == colls[mat1]) {
                        rows = realloc_size(rows, index);
                    colls = realloc_size(colls, index);
                        rows[index] = rows[mat1];
                        colls[index] = colls[mat2];
                    
                    arr = realloc_array(index, arr);
                    arr = opM(arr, rows, colls, index, mat1, mat2);
                    index++;
                    } else {
                        printf("Cannot perform matrix multiplication\n");
                    }
                
                }
            break;
            case 'O':
                arr = opO(arr, rows, colls, index);
            break;
            case 'T':
                scanf("%d", &mat);
                if (mat >= index || mat < 0) {
                    printf("No matrix with the given index\n");
                } else {
                    arr = opT(arr, rows, colls, mat);
                }
            break;
            case 'R':
                scanf("%d %d", &mat, &pow);
                if (mat >= index || mat < 0)
                    printf("No matrix with the given index\n");
                else if (pow < 0)
                        printf("Power should be positive\n");
                    else if (rows[mat] != colls[mat]) 
                            printf("Cannot perform matrix multiplication\n");
                        else arr = opR(arr, rows, colls, mat, pow);
            break;
			case 'F':
				scanf("%d", &mat);
				if (mat >= index || mat < 0) {
					printf("No matrix with the given index\n");
				} else {
					arr = opF(arr, rows, colls, mat, index);
					index--;
					rows = realloc_size(rows, index);
					colls = realloc_size(colls, index);
					arr = realloc_array(index, arr);
				}
			break;
            case 'Q':
                opQ(arr, rows, colls, index);
            break;
			default:
				printf("Unrecognized command\n");
        }
    } while (s != 'Q');
}