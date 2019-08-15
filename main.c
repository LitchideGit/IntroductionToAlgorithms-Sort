#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ShowRe(const int n, int *A);
int GenRandom(const int n, int* R);
void InsertSort(const int n, const int *A, int *R);
void BubbleSort(const int n, const int *A, int *R);
int Merge(int *A, const int s, const int m, const int e);
int MergeSort(const int s, const int e, int *R);

int MaxHEAP(int *A, const int cIdx, const int length);
int BuildMaxHEAP(int *A, const int length);
int HEAPSort(int *A, const int length);

int Partition(int *A, const int st, const int ed);
int QuickSort(int *A, const int st, const int ed);

int main() {
    int n = 1<<10;
    int *A, *R;
    A = (int *)malloc(n * sizeof(int));
    R = (int *)malloc(n * sizeof(int));

    GenRandom(n, A);
    ShowRe(n, A);

    InsertSort(n, A, R);
    printf("\n1. Insert Sort:\n");
    ShowRe(n, R);

    BubbleSort(n, A, R);
    printf("\n2. Bubble Sort:\n");
    ShowRe(n, R);

    memcpy(R, A, n * sizeof(int));
    MergeSort(0, n, R);
    printf("\n3. Merge Sort:\n");
    ShowRe(n, R);

    memcpy(R, A, n * sizeof(int));
    HEAPSort(R, n);
    printf("\n4. HEAP Sort:\n");
    ShowRe(n, R);

    memcpy(R, A, n * sizeof(int));
    QuickSort(R, 0, n);
    printf("\n5. Quick Sort:\n");
    ShowRe(n, R);


    free(A); free(R);
//    printf("Hello, World!\n");
    return 0;
}

void ShowRe(const int n, int *A)
{
    printf("A(%d) = [", n);
    for (int i = 0; i < n - 1; ++i)
    {
        printf("%d, ", A[i]);
    }
    printf("%d]\n", A[n - 1]);
}

int GenRandom(const int n, int *R)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; ++i)
    {
        R[i] = rand()%100;
    }

    return 0;
}

// 1. Insert Sort
void InsertSort(const int n, const int *A, int *R)
{
    memcpy(R, A, n * sizeof(int));

    int cv;

    for (int i = 1; i < n; ++i)
    {
        cv = R[i];
        int ci = i - 1;

        while(ci >= 0 && R[ci] > cv)
        {
            R[ci + 1] = R[ci];
            --ci;
        }
        R[ci+1] = cv;
    }
}

// 2. Bubble Sort
void BubbleSort(const int n, const int *A, int *R)
{
    memcpy(R, A, n * sizeof(int));

    for (int i = 0; i < (n - 1); ++i)
    {
        for (int j = (n - 1); j > i; --j)
        {
            if (R[j] < R[j - 1])
            {
                int cache;
                cache       = R[j - 1];
                R[j - 1]    = R[j];
                R[j]        = cache;
            }
        }
    }
}

// 3. Merge Sort
int Merge(int *A, const int s, const int m, const int e)
{
    int LenLeft     = m - s + 1;
    int LenRight    = e - m + 1;

    int *Left, *Right;
    Left    = (int *) malloc(LenLeft * sizeof(int));
    Right   = (int *) malloc(LenRight * sizeof(int));

    for (int i = 0; i < (LenLeft - 1); ++i)
    {
        Left[i] = A[s + i];
    }
    Left[LenLeft - 1] = 1024;

    for (int i = 0; i < (LenRight - 1); ++i)
    {
        Right[i] = A[m + i];
    }
    Right[LenRight - 1] = 1024;

    int LeftIdx     = 0;
    int RightIdx    = 0;

    for (int i = s; i < e; ++i)
    {
        if (Left[LeftIdx] <= Right[RightIdx])
        {
            A[i] = Left[LeftIdx];
            ++LeftIdx;
        }
        else
        {
            A[i] = Right[RightIdx];
            ++RightIdx;
        }
    }

    free(Left); free(Right);

    return 0;
}

int MergeSort(const int s, const int e, int *R)
{
    if (s < (e - 1))
    {
        int MidIdx;
        MidIdx = (s + e)/2;

        MergeSort(s, MidIdx, R);
        MergeSort(MidIdx, e, R);

        Merge(R, s, MidIdx, e);
    }

    return 0;
}

// 4. HEAP Sort
int MaxHEAP(int *A, const int cIdx, const int length)
{
    int left    = 2 * (cIdx + 1) - 1;
    int right   = 2 * (cIdx + 1);
    int largest = cIdx;

    if (left < length && A[left] > A[cIdx])
    {
        largest = left;
    }

    if (right < length && A[right] > A[largest])
    {
        largest = right;
    }

    if (largest != cIdx)
    {
        int cache;
        cache       = A[cIdx];
        A[cIdx]     = A[largest];
        A[largest]  = cache;

        MaxHEAP(A, largest, length);
    }

    return 0;
}

int BuildMaxHEAP(int *A, const int length)
{
    for (int i = (length/2 - 1); i >= 0; --i)
    {
        MaxHEAP(A, i, length);
    }

    return 0;
}

int HEAPSort(int *A, const int length)
{
    int cache;

    BuildMaxHEAP(A, length);
    for (int i = length; i > 1; --i)
    {
        cache   = A[0];
        A[0]    = A[i - 1];
        A[i - 1]= cache;
        MaxHEAP(A, 0, (i - 1));
    }

    return 0;
}

// 5. Quick Sort
int Partition(int *A, const int st, const int ed)
{
    int T       = A[ed - 1];
    int cIdx    = (st - 1);
    int cache;

    for (int i = st; i < (ed - 1); ++i)
    {
        if (A[i] <= T)
        {
            ++cIdx;
            cache = A[cIdx];
            A[cIdx] = A[i];
            A[i] = cache;
        }
    }

    ++cIdx;
    cache = A[cIdx];
    A[cIdx]     = A[ed - 1];
    A[ed - 1]   = cache;

    return cIdx;
}

int QuickSort(int *A, const int st, const int ed)
{
    if (st < (ed - 1))
    {
        int cIdx;
        cIdx = Partition(A, st, ed);
        QuickSort(A, st, cIdx);
        QuickSort(A, (cIdx + 1), ed);
    }

    return 0;
}
