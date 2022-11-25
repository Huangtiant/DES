#include<stdio.h>

void F(int R[32], int K[48]);
void S(int f[48]);
void replace(int *a, int *ans,int *biao, int m);

void lfMove(int *a, int n);
int Get(int r);
//DES
void shizhuaner(int *a,int x);
void S_box(int a[48],int b[32]);
void DES(int *m, int *k, int c[64]);

int IP[64] = { 58, 50, 42, 34, 26, 18, 10, 2, 
               60, 52, 44, 36, 28, 20, 12, 4, 
               62, 54, 46, 38, 30, 22, 14, 6, 
               64, 56, 48, 40, 32, 24, 16, 8, 
               57, 49, 41, 33, 25, 17, 9, 1, 
               59, 51, 43, 35, 27, 19, 11, 3, 
               61, 53, 45, 37, 29, 21, 13, 5, 
               63, 55, 47, 39, 31, 23, 15, 7 };
               
int IP_1[64] = { 40, 8, 48, 16, 56, 24, 64, 32, 
                 39, 7, 47, 15, 55, 23, 63, 31, 
                 38, 6, 46, 14, 54, 22, 62, 30, 
                 37, 5, 45, 13, 53, 21, 61, 29, 
                 36, 4, 44, 12, 52, 20, 60, 28, 
                 35, 3, 43, 11, 51, 19, 59, 27, 
                 34, 2, 42, 10, 50, 18, 58, 26, 
                 33, 1, 41, 9, 49, 17, 57, 25 };

int zhihuan1[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36, 
                     63, 55, 47, 39, 31, 23, 15, 
                     7, 62, 54, 46, 38, 30, 22, 
                     14, 6, 61, 53, 45, 37, 29, 
                     21, 13, 5, 28, 20, 12, 4 };
int	zhihuan2[48] = { 14, 17, 11, 24, 1, 5,
                     3, 28, 15, 6, 21, 10,
                     23, 19, 12, 4, 26, 8,
                     16, 7, 27, 20, 13, 2, 
                     41, 52, 31, 37, 47, 55, 
                     30, 40, 51, 45, 33, 48, 
                     44, 49, 39, 56, 34, 53, 
                     46, 42, 50, 36, 29, 32 }; 
int	e[48] = { 32, 1, 2, 3, 4, 5,
              4, 5, 6, 7, 8, 9,
              8, 9, 10, 11, 12, 13,
              12, 13, 14, 15, 16, 17,
              16, 17, 18, 19, 20, 21,
              20, 21, 22, 23, 24, 25,
              24, 25, 26, 27, 28, 29,
              28, 29, 30, 31, 32, 1 };

int	P[32] = { 16, 7, 20, 21, 29, 12, 28, 17,
              1, 15, 23, 26, 5, 18, 31, 10,
              2, 8, 24, 14, 32, 27, 3, 9, 
              19, 13, 30, 6, 22, 11, 4, 25 };


void replace(int *a, int *ans, int *biao, int m)
{
    int i;

    for(i = 0; i < m; i++) {
        ans[i] = a[biao[i] - 1];
    }
    return;
}

int Get(int r)
{
	int i;  	
	if (r==1||r==2||r==9||r==16) i=1;
	else i=2;
	return i;  
}

void lfMove(int a[28], int n) {
    int i, j;
    int temp;
    for(j = 0; j < n; j++) {
        temp = a[0];
        for(i = 0; i < 28; i++) {
            a[i] = a[i + 1];
        }
        a[27] = temp;
    }
    return;
}


void Nor48(int a[48], int b[48]) {
    int i;
    for(i = 0; i < 48; i++) {
        if(a[i] != b[i]) {
            a[i] = 1;
        } else {
            a[i] = 0;
        }
    }
    return;
}

void Nor32(int a[32], int b[32]) {
    int i;
    for(i = 0; i < 48; i++) {
        if(a[i] != b[i]) {
            a[i] = 1;
        } else {
            a[i] = 0;
        }
    }
    return;
}

void shizhuaner(int a[4], int x)
{
    int i;
    for(i = 3; i >= 0; i--) {
        a[i] = x % 2;
        x = x / 2;
    }
    return;
}

void S_box(int a[48],int b[32])
{ 
    int x, y;
    int temp, temp1[4];
	int s1[4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
                      { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
                      { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
                      { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 } };

	int s2[4][16] = { { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
                      { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
                      { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
                      { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 } };

    int s3[4][16] = { { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
                      { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
                      { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
                      { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 } };

	int s4[4][16] = { { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
                      { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
                      { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 3 },
                      { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 } };

	int s5[4][16] = { { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
                      { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
                      { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
                      { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 } };

	int s6[4][16] = { { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
                      { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
                      { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
                      { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 } };

	int s7[4][16] = { { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
                      { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
                      { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
                      { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 } };

	int s8[4][16] = { { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
                      { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
                      { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
                      { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
    int i;
	for(i = 0; i < 8; i++) { 
        x = 2 * a[i * 6] + a[i * 6 + 5];
        y = 8 * a[i * 6 + 1] + 4 * a[i * 6 + 2] + 2 * a[i * 6 + 3] + a[i * 6 + 4];
        switch(i)
        {
            case 0:temp = s1[x][y]; break;
		    case 1:temp = s2[x][y]; break;
		    case 2:temp = s3[x][y]; break;
		    case 3:temp = s4[x][y]; break;
		    case 4:temp = s5[x][y]; break;
		    case 5:temp = s6[x][y]; break;
		    case 6:temp = s7[x][y]; break;
		    case 7:temp = s8[x][y]; break;
        }
        shizhuaner(temp1, temp);//fault
        for(int j = 0; j < 4; j++) {
            b[(i * 4) + j] =  temp1[j];
        }
    }
}

void DES(int *m, int *k, int c[64]) {
    int m1[64];
    int left[32], right[32];
    int temp1[32];
    int temp2[32];
    int temp3[64];

    int k1[56];
    int C[28], D[28];
    int temp[48];
    int newk[48];

    int ans[64];
    int i;

    replace(k, k1, zhihuan1, 56);//zhihuan1 is right
    // for(i = 0; i < 56; i++) {
    //     printf("%3d", k1[i]);
    //     if((i + 1) % 8 == 0)    printf("\n");
    // }printf("\n");

    for(i = 0; i < 28; i++) {
        C[i] = k1[i];
        D[i] = k1[i + 28];
    }//correct
    // for(i = 0; i < 28; i++) {
    //     printf("%3d", D[i]);
    //     if((i + 1) % 8 == 0)    printf("\n");
    // }printf("\n");
    
    replace(m, m1, IP, 64);//ip is right

    for(i = 0; i < 32; i++) {
        left[i] = m1[i];
        right[i] = m1[i + 32];
    }


    for(i = 1; i < 17; i++) {
        int n = Get(i);

        lfMove(C, n);
        lfMove(D, n);//lfmove is correct

        for(int j = 0; j < 28; j++) {
            temp3[j] = C[j];
            temp3[j + 28] = D[j];
        }//correct
        

        replace(temp3, newk, zhihuan2, 48);//correct, k is always right
        
        if(i == 16) {
            printf("right:");
            for(int j = 0; j < 32; j++) {
                printf("%d", right[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }
        replace(right, temp, e, 48);//correct

        if(i == 16) {
            printf("temp :");
            for(int j = 0; j < 48; j++) {
                printf("%d", temp[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }
        if(i == 16) {
            printf("key :");
            for(int j = 0; j < 48; j++) {
                printf("%d", newk[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }
        Nor48(temp, newk);
        if(i == 16) {
            printf("after nor :");
            for(int j = 0; j < 48; j++) {
                printf("%d", temp[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }

        S_box(temp, temp1);//fault
        if(i == 16) {
            printf("after S :");
            for(int j = 0; j < 32; j++) {
                printf("%d", temp1[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }

        replace(temp1, temp2, P, 48);
        if(i == 16) {
            printf("P :");
            for(int j = 0; j < 32; j++) {
                printf("%d", temp2[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }

        Nor32(temp2, left);
        for(int j = 0; j < 32; j++) left[j] = right[j];
        for(int j = 0; j < 32; j++) right[j] = temp2[j];
        
        if(i == 16) {
            printf("left :");
            for(int j = 0; j < 32; j++) {
                printf("%d", left[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }
        if(i == 16) {
            printf("right :");
            for(int j = 0; j < 32; j++) {
                printf("%d", right[j]);
                if((j + 1) % 8 == 0) printf(" ");
            }printf("\n");
        }
    }
    for(int j = 0; j < 32; j++) {
        temp3[j] = right[j];
        temp3[j + 32] = left[j];
    }
    printf("temp3 :");
    for(int j = 0; j < 64; j++) {
        printf("%d", temp3[j]);
        if((j + 1) % 8 == 0) printf(" ");
    }printf("\n");
    replace(temp3, c, IP_1, 64);
    
    return;
}

int main() {
    int m[64] = {0, 0, 1, 1, 0, 0, 0, 0, 
                 0, 0, 1, 1, 0, 0, 0, 1, 
                 0, 0, 1, 1, 0, 0, 1, 0, 
                 0, 0, 1, 1, 0, 0, 1, 1, 
                 0, 0, 1, 1, 0, 1, 0, 0, 
                 0, 0, 1, 1, 0, 1, 0, 1, 
                 0, 0, 1, 1, 0, 1, 1, 0, 
                 0, 0, 1, 1, 0, 1, 1, 1};
    int k[64] =   {0, 0, 1, 1, 0, 0, 0, 1,
                   0, 0, 1, 1, 0, 0, 1, 0,
                   0, 0, 1, 1, 0, 0, 1, 1,
                   0, 0, 1, 1, 0, 1, 0, 0,
                   0, 0, 1, 1, 0, 1, 0, 1,
                   0, 0, 1, 1, 0, 1, 1, 0, 
                   0, 0, 1, 1, 0, 1, 1, 1,
                   0, 0, 1, 1, 1, 0, 0, 0};
    int c[64] = {0};

    DES(m, k, c);

    return 0;
}