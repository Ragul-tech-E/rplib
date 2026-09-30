#ifndef RPLIB_H
#define RPLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* =========================================================
   RPLIB.H
   Simple C library for shorter, Python-like C programming
   ========================================================= */


/* ================= INPUT / OUTPUT ================= */

#define In(...)   scanf(__VA_ARGS__)
#define Out(...)  printf(__VA_ARGS__)
#define NL()      putchar('\n')

static inline int ReadInt(void)
{
    int x;
    scanf("%d", &x);
    return x;
}

static inline float ReadFloat(void)
{
    float x;
    scanf("%f", &x);
    return x;
}

static inline void ReadLine(char *s, int n)
{
    if (!s || n <= 0) return;

    if (fgets(s, n, stdin))
        s[strcspn(s, "\n")] = '\0';
    else
        s[0] = '\0';
}

static inline void ReadStr(char *s, int n)
{
    ReadLine(s, n);
}

static inline void PrintInt(int x)
{
    printf("%d", x);
}

static inline void PrintFloat(double x)
{
    printf("%g", x);
}

static inline void PrintStr(const char *s)
{
    if (s) printf("%s", s);
}

static inline void Pause(void)
{
    getchar();
}


/* ================= MATH ================= */

static inline double Sqrt(double x)
{
    return sqrt(x);
}

static inline double Pow(double x, double y)
{
    return pow(x, y);
}

static inline double Abs(double x)
{
    return fabs(x);
}

static inline double Max(double x, double y)
{
    return x > y ? x : y;
}

static inline double Min(double x, double y)
{
    return x < y ? x : y;
}

static inline double Round(double x)
{
    return round(x);
}

static inline double Floor(double x)
{
    return floor(x);
}

static inline double Ceil(double x)
{
    return ceil(x);
}

static inline long long Mod(long long x, long long y)
{
    return y ? x % y : 0;
}

static inline int Sign(double x)
{
    return (x > 0) - (x < 0);
}

static inline long long GCD(long long a, long long b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b)
    {
        long long t = a % b;
        a = b;
        b = t;
    }

    return a;
}

static inline long long LCM(long long a, long long b)
{
    if (!a || !b) return 0;

    return llabs((a / GCD(a,b)) * b);
}

static inline unsigned long long Fact(unsigned int n)
{
    unsigned long long r = 1;

    for (unsigned int i = 2; i <= n; i++)
        r *= i;

    return r;
}

static inline int IsPrime(long long n)
{
    if (n < 2) return 0;

    if (n % 2 == 0)
        return n == 2;

    for (long long i = 3; i <= n/i; i += 2)
        if (n % i == 0)
            return 0;

    return 1;
}

static inline int IsEven(long long n)
{
    return n % 2 == 0;
}

static inline int IsOdd(long long n)
{
    return n % 2 != 0;
}

static inline int IsPerfect(long long n)
{
    if (n <= 0) return 0;

    long long sum = 1;

    if (n == 1) return 0;

    for (long long i = 2; i <= n/i; i++)
    {
        if (n % i == 0)
        {
            sum += i;

            if (i != n/i)
                sum += n/i;
        }
    }

    return sum == n;
}

static inline int IsArmstrong(long long n)
{
    if (n < 0) return 0;

    long long t = n;
    long long sum = 0;

    int d = (n == 0) ? 1 : 0;

    while (t)
    {
        d++;
        t /= 10;
    }

    t = n;

    while (t)
    {
        int x = t % 10;

        sum += (long long)llround(pow(x,d));

        t /= 10;
    }

    return sum == n;
}

static inline int IsPalindrome(long long n)
{
    if (n < 0) return 0;

    long long t = n;
    long long r = 0;

    do
    {
        r = r * 10 + t % 10;
        t /= 10;

    } while (t);

    return r == n;
}

static inline int Digits(long long n)
{
    int d = 1;

    if (n < 0)
        n = -n;

    while (n >= 10)
    {
        n /= 10;
        d++;
    }

    return d;
}


/* ================= ARRAYS ================= */

static inline void Read(int *a, int n)
{
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

static inline void Print(const int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i) putchar(' ');

        printf("%d", a[i]);
    }
}

static inline long long Sum(const int *a, int n)
{
    long long s = 0;

    for (int i = 0; i < n; i++)
        s += a[i];

    return s;
}

static inline double Avg(const int *a, int n)
{
    return n > 0 ? (double)Sum(a,n)/n : 0;
}

static inline int MaxA(const int *a, int n)
{
    if (n <= 0) return 0;

    int m = a[0];

    for (int i = 1; i < n; i++)
        if (a[i] > m)
            m = a[i];

    return m;
}

static inline int MinA(const int *a, int n)
{
    if (n <= 0) return 0;

    int m = a[0];

    for (int i = 1; i < n; i++)
        if (a[i] < m)
            m = a[i];

    return m;
}

static inline void Sort(int *a, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (a[j] > a[j+1])
            {
                int t = a[j];

                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

static inline void Rev(int *a, int n)
{
    for (int i = 0, j = n-1; i < j; i++, j--)
    {
        int t = a[i];

        a[i] = a[j];
        a[j] = t;
    }
}

#define Swap(a,b) \
do { \
    __typeof__(a) t = (a); \
    (a) = (b); \
    (b) = t; \
} while(0)

static inline int Find(const int *a, int n, int x)
{
    for (int i = 0; i < n; i++)
        if (a[i] == x)
            return i;

    return -1;
}

static inline int First(const int *a, int n, int x)
{
    return Find(a,n,x);
}

static inline int Last(const int *a, int n, int x)
{
    for (int i = n-1; i >= 0; i--)
        if (a[i] == x)
            return i;

    return -1;
}

static inline int Count(const int *a, int n, int x)
{
    int c = 0;

    for (int i = 0; i < n; i++)
        if (a[i] == x)
            c++;

    return c;
}

static inline void Copy(int *a, const int *b, int n)
{
    memmove(a,b,n*sizeof(int));
}

static inline int Equal(const int *a, const int *b, int n)
{
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;

    return 1;
}

static inline int Unique(int *a, int n)
{
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (Find(a,k,a[i]) == -1)
            a[k++] = a[i];
    }

    return k;
}

static inline int Freq(const int *a, int n, int x)
{
    return Count(a,n,x);
}

static inline int Insert(int *a, int n, int pos, int x)
{
    if (pos < 0) pos = 0;
    if (pos > n) pos = n;

    for (int i = n; i > pos; i--)
        a[i] = a[i-1];

    a[pos] = x;

    return n+1;
}

static inline int Delete(int *a, int n, int pos)
{
    if (pos < 0 || pos >= n)
        return n;

    for (int i = pos; i < n-1; i++)
        a[i] = a[i+1];

    return n-1;
}

static inline void Rotate(int *a, int n, int k)
{
    if (n <= 0) return;

    k %= n;

    if (k < 0)
        k += n;

    while (k--)
    {
        int t = a[n-1];

        for (int i = n-1; i > 0; i--)
            a[i] = a[i-1];

        a[0] = t;
    }
}


/* ================= STRINGS ================= */

static inline size_t Len(const char *s)
{
    return s ? strlen(s) : 0;
}

static inline char *CopyStr(char *a, const char *b)
{
    return strcpy(a,b);
}

static inline char *Cat(char *a, const char *b)
{
    return strcat(a,b);
}

static inline int Cmp(const char *a, const char *b)
{
    return strcmp(a,b);
}

static inline void RevStr(char *s)
{
    if (!s) return;

    int i = 0;
    int j = strlen(s)-1;

    while (i < j)
    {
        char t = s[i];

        s[i] = s[j];
        s[j] = t;

        i++;
        j--;
    }
}

static inline void Upper(char *s)
{
    if (!s) return;

    for (; *s; s++)
        *s = toupper((unsigned char)*s);
}

static inline void Lower(char *s)
{
    if (!s) return;

    for (; *s; s++)
        *s = tolower((unsigned char)*s);
}

static inline void Trim(char *s)
{
    if (!s) return;

    char *p = s;

    while (isspace((unsigned char)*p))
        p++;

    if (p != s)
        memmove(s,p,strlen(p)+1);

    int n = strlen(s);

    while (n && isspace((unsigned char)s[n-1]))
        s[--n] = '\0';
}

static inline int CountChar(const char *s, int c)
{
    int n = 0;

    if (!s) return 0;

    for (; *s; s++)
        if (*s == c)
            n++;

    return n;
}

static inline int FindChar(const char *s, int c)
{
    if (!s) return -1;

    char *p = strchr(s,c);

    return p ? p-s : -1;
}

static inline int FindStr(const char *s, const char *t)
{
    if (!s || !t) return -1;

    char *p = strstr(s,t);

    return p ? p-s : -1;
}

static inline int Replace(char *s, size_t cap,
                          const char *old, const char *nw)
{
    if (!s || !old || !nw || !cap || !*old)
        return 0;

    char *p = strstr(s,old);

    if (!p)
        return 0;

    size_t sl = strlen(s);
    size_t ol = strlen(old);
    size_t nl = strlen(nw);

    if (sl-ol+nl+1 > cap)
        return 0;

    memmove(
        p+nl,
        p+ol,
        sl-(p-s)-ol+1
    );

    memcpy(p,nw,nl);

    return 1;
}

static inline int IsDigit(int c)
{
    return isdigit((unsigned char)c);
}

static inline int IsAlpha(int c)
{
    return isalpha((unsigned char)c);
}

static inline int IsSpace(int c)
{
    return isspace((unsigned char)c);
}


/* ================= LOOP HELPERS ================= */

#define F(i,n) \
    for ((i)=0; (i)<(n); (i)++)

#define R(i,n) \
    for ((i)=(n)-1; (i)>=0; (i)--)

#define Repeat(n) \
    for (int _i=0; _i<(n); _i++)

#define Choose(c,a,b) \
    ((c) ? (a) : (b))


/* ================= MATRIX ================= */

static inline void ReadMat(int *a,int r,int c)
{
    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            scanf("%d",&a[i*c+j]);
}

static inline void PrintMat(const int *a,int r,int c)
{
    for (int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
            printf("%d ",a[i*c+j]);

        NL();
    }
}

static inline void MatAdd(
    const int *a,
    const int *b,
    int *out,
    int r,
    int c)
{
    for (int i=0;i<r*c;i++)
        out[i]=a[i]+b[i];
}

static inline void MatSub(
    const int *a,
    const int *b,
    int *out,
    int r,
    int c)
{
    for (int i=0;i<r*c;i++)
        out[i]=a[i]-b[i];
}

static inline void MatMul(
    const int *a,
    const int *b,
    int *out,
    int r1,
    int c1,
    int c2)
{
    for (int i=0;i<r1;i++)
    {
        for (int j=0;j<c2;j++)
        {
            int s=0;

            for (int k=0;k<c1;k++)
                s += a[i*c1+k] * b[k*c2+j];

            out[i*c2+j]=s;
        }
    }
}

static inline void Transpose(
    const int *a,
    int *out,
    int r,
    int c)
{
    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            out[j*r+i]=a[i*c+j];
}

static inline long long Trace(
    const int *a,
    int n)
{
    long long s=0;

    for (int i=0;i<n;i++)
        s += a[i*n+i];

    return s;
}

static inline void Diag(
    const int *a,
    int n)
{
    for (int i=0;i<n;i++)
        printf("%d ",a[i*n+i]);
}

static inline int MatEqual(
    const int *a,
    const int *b,
    int r,
    int c)
{
    return Equal(a,b,r*c);
}

static inline void Identity(
    int *a,
    int n)
{
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            a[i*n+j]=(i==j);
}


/* ================= SEARCH / SORT ================= */

static inline int Linear(
    const int *a,
    int n,
    int x)
{
    return Find(a,n,x);
}

static inline int Binary(
    const int *a,
    int n,
    int x)
{
    int l=0;
    int r=n-1;

    while(l<=r)
    {
        int m=l+(r-l)/2;

        if(a[m]==x)
            return m;

        if(a[m]<x)
            l=m+1;
        else
            r=m-1;
    }

    return -1;
}

static inline void Bubble(int *a,int n)
{
    Sort(a,n);
}

static inline void Select(int *a,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int p=i;

        for(int j=i+1;j<n;j++)
            if(a[j]<a[p])
                p=j;

        if(p!=i)
            Swap(a[i],a[p]);
    }
}

static inline void InsertSort(int *a,int n)
{
    for(int i=1;i<n;i++)
    {
        int x=a[i];
        int j=i-1;

        while(j>=0 && a[j]>x)
        {
            a[j+1]=a[j];
            j--;
        }

        a[j+1]=x;
    }
}

static inline void MergeSort(int *a,int n)
{
    if(n<2) return;

    int *t=malloc(n*sizeof(int));

    if(!t) return;

    for(int w=1;w<n;w*=2)
    {
        for(int l=0;l<n;l+=2*w)
        {
            int m=l+w;
            int r=l+2*w;

            if(m>n) m=n;
            if(r>n) r=n;

            int i=l;
            int j=m;
            int k=l;

            while(i<m && j<r)
                t[k++]=(a[i]<=a[j])?a[i++]:a[j++];

            while(i<m)
                t[k++]=a[i++];

            while(j<r)
                t[k++]=a[j++];
        }

        memcpy(a,t,n*sizeof(int));

        if(w>n/2)
            break;
    }

    free(t);
}

static inline void QuickSort(int *a,int n)
{
    if(n<=1) return;

    int i=0;
    int j=n-1;
    int p=a[n/2];

    while(i<=j)
    {
        while(a[i]<p) i++;
        while(a[j]>p) j--;

        if(i<=j)
        {
            int t=a[i];
            a[i]=a[j];
            a[j]=t;

            i++;
            j--;
        }
    }

    if(j>0)
        QuickSort(a,j+1);

    if(i<n)
        QuickSort(a+i,n-i);
}

static inline int SecondMax(
    const int *a,
    int n)
{
    if(n<2) return 0;

    int m=MaxA(a,n);
    int found=0;
    int s=0;

    for(int i=0;i<n;i++)
    {
        if(a[i]!=m &&
           (!found || a[i]>s))
        {
            s=a[i];
            found=1;
        }
    }

    return found?s:m;
}

static inline int SecondMin(
    const int *a,
    int n)
{
    if(n<2) return 0;

    int m=MinA(a,n);
    int found=0;
    int s=0;

    for(int i=0;i<n;i++)
    {
        if(a[i]!=m &&
           (!found || a[i]<s))
        {
            s=a[i];
            found=1;
        }
    }

    return found?s:m;
}

static inline int Missing(
    const int *a,
    int n)
{
    int x=0;

    for(int i=1;i<=n;i++)
        x^=i;

    for(int i=0;i<n;i++)
        x^=a[i];

    return x;
}


/* ================= UTILITIES ================= */

static inline void Clear(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static inline void Delay(unsigned int seconds)
{
#ifdef _WIN32
    Sleep(seconds*1000);
#else
    sleep(seconds);
#endif
}

static inline int Random(int n)
{
    if(n<=0) return 0;

    return rand()%n;
}

static inline void Seed(void)
{
    srand((unsigned int)time(NULL));
}

static inline void *Malloc(size_t n)
{
    return malloc(n);
}

static inline void Free(void *p)
{
    free(p);
}

static inline clock_t TimerStart(void)
{
    return clock();
}

static inline double TimerStop(clock_t start)
{
    return (double)(clock()-start)
           / CLOCKS_PER_SEC;
}

static inline time_t Time(void)
{
    return time(NULL);
}

#endif