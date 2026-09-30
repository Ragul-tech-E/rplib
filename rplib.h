#ifndef RPLIB_H
#define RPLIB_H

#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
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
    int x = 0;

    if (scanf("%d", &x) != 1)
        x = 0;

    return x;
}

static inline float ReadFloat(void)
{
    float x = 0;

    if (scanf("%f", &x) != 1)
        x = 0;

    return x;
}

static inline void ReadLine(char *s, int n)
{
    if (!s || n <= 0) return;

    if (fgets(s, n, stdin))
    {
        char *nl = strchr(s, '\n');

        if (nl)
            *nl = '\0';
        else
        {
            int c;

            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
    }
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

static inline int RpMaxInt(int x, int y) { return x > y ? x : y; }
static inline long RpMaxLong(long x, long y) { return x > y ? x : y; }
static inline long long RpMaxLL(long long x, long long y) { return x > y ? x : y; }
static inline double RpMaxDbl(double x, double y) { return x > y ? x : y; }

static inline int RpMinInt(int x, int y) { return x < y ? x : y; }
static inline long RpMinLong(long x, long y) { return x < y ? x : y; }
static inline long long RpMinLL(long long x, long long y) { return x < y ? x : y; }
static inline double RpMinDbl(double x, double y) { return x < y ? x : y; }

static inline int RpAbsInt(int x) { return x < 0 ? -x : x; }
static inline long RpAbsLong(long x) { return x < 0 ? -x : x; }
static inline long long RpAbsLL(long long x) { return x < 0 ? -x : x; }
static inline double RpAbsDbl(double x) { return fabs(x); }

#define Max(a,b) _Generic(((a)+(b)), \
    int: RpMaxInt, \
    long: RpMaxLong, \
    long long: RpMaxLL, \
    default: RpMaxDbl)((a),(b))

#define Min(a,b) _Generic(((a)+(b)), \
    int: RpMinInt, \
    long: RpMinLong, \
    long long: RpMinLL, \
    default: RpMinDbl)((a),(b))

#define Abs(x) _Generic(+(x), \
    int: RpAbsInt, \
    long: RpAbsLong, \
    long long: RpAbsLL, \
    default: RpAbsDbl)(x)

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
    if (n <= 1) return 0;

    long long sum = 1;

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

static inline int Digits(long long n)
{
    unsigned long long u = n < 0 ? 0ULL - (unsigned long long)n
                                 : (unsigned long long)n;
    int d = 1;

    while (u >= 10)
    {
        u /= 10;
        d++;
    }

    return d;
}

static inline int IsArmstrong(long long n)
{
    if (n < 0) return 0;

    int d = Digits(n);
    long long t = n;
    unsigned long long sum = 0;

    while (t)
    {
        int x = (int)(t % 10);
        unsigned long long p = 1;

        for (int k = 0; k < d; k++)
            p *= (unsigned int)x;

        sum += p;

        t /= 10;
    }

    return sum == (unsigned long long)n;
}

static inline int IsPalindrome(long long n)
{
    if (n < 0) return 0;

    unsigned long long t = (unsigned long long)n;
    unsigned long long r = 0;

    do
    {
        r = r * 10 + t % 10;
        t /= 10;

    } while (t);

    return r == (unsigned long long)n;
}


/* ================= ARRAYS ================= */

static inline void Read(int *a, int n)
{
    for (int i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            a[i] = 0;
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
        int swapped = 0;

        for (int j = 0; j < n-i-1; j++)
        {
            if (a[j] > a[j+1])
            {
                int t = a[j];

                a[j] = a[j+1];
                a[j+1] = t;

                swapped = 1;
            }
        }

        if (!swapped)
            break;
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
    __typeof__(a) rp_swap_tmp_ = (a); \
    (a) = (b); \
    (b) = rp_swap_tmp_; \
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
    if (n <= 0) return;

    memmove(a,b,(size_t)n*sizeof(int));
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
    if (n < 0) n = 0;
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

    if (k == 0) return;

    Rev(a, n);
    Rev(a, k);
    Rev(a + k, n - k);
}


/* ================= STRINGS ================= */

static inline size_t Len(const char *s)
{
    return s ? strlen(s) : 0;
}

static inline char *CopyStr(char *a, const char *b)
{
    if (!a || !b) return a;

    return strcpy(a,b);
}

static inline char *Cat(char *a, const char *b)
{
    if (!a || !b) return a;

    return strcat(a,b);
}

static inline int Cmp(const char *a, const char *b)
{
    if (!a || !b)
        return (a != NULL) - (b != NULL);

    return strcmp(a,b);
}

static inline void RevStr(char *s)
{
    if (!s) return;

    int i = 0;
    int j = (int)strlen(s) - 1;

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
        *s = (char)toupper((unsigned char)*s);
}

static inline void Lower(char *s)
{
    if (!s) return;

    for (; *s; s++)
        *s = (char)tolower((unsigned char)*s);
}

static inline void Trim(char *s)
{
    if (!s) return;

    char *p = s;

    while (isspace((unsigned char)*p))
        p++;

    if (p != s)
        memmove(s,p,strlen(p)+1);

    size_t n = strlen(s);

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

    const char *p = strchr(s,c);

    return p ? (int)(p-s) : -1;
}

static inline int FindStr(const char *s, const char *t)
{
    if (!s || !t) return -1;

    const char *p = strstr(s,t);

    return p ? (int)(p-s) : -1;
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
        sl-(size_t)(p-s)-ol+1
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
    for (int rp_i_=0; rp_i_<(n); rp_i_++)

#define Choose(c,a,b) \
    ((c) ? (a) : (b))


/* ================= MATRIX ================= */

static inline void ReadMat(int *a,int r,int c)
{
    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            if (scanf("%d",&a[i*c+j]) != 1)
                a[i*c+j]=0;
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

    int *t=(int *)malloc((size_t)n*sizeof(int));

    if(!t)
    {
        InsertSort(a,n);
        return;
    }

    for(long long w=1;w<n;w*=2)
    {
        for(long long l=0;l<n;l+=2*w)
        {
            long long m=l+w;
            long long r=l+2*w;

            if(m>n) m=n;
            if(r>n) r=n;

            long long i=l;
            long long j=m;
            long long k=l;

            while(i<m && j<r)
                t[k++]=(a[i]<=a[j])?a[i++]:a[j++];

            while(i<m)
                t[k++]=a[i++];

            while(j<r)
                t[k++]=a[j++];
        }

        memcpy(a,t,(size_t)n*sizeof(int));
    }

    free(t);
}

static inline void QuickSort(int *a,int n)
{
    while(n>1)
    {
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

        if(j+1 < n-i)
        {
            QuickSort(a,j+1);

            a+=i;
            n-=i;
        }
        else
        {
            QuickSort(a+i,n-i);

            n=j+1;
        }
    }
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

    for(int i=1;i<=n+1;i++)
        x^=i;

    for(int i=0;i<n;i++)
        x^=a[i];

    return x;
}


/* ================= UTILITIES ================= */

static inline void Clear(void)
{
#ifdef _WIN32
    (void)system("cls");
#else
    (void)system("clear");
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



/* ================= CASE-INSENSITIVE ALIASES ================= */

#ifndef RP_NO_ALIASES

#ifndef readint
#define readint() ReadInt()
#endif

#ifndef readInt
#define readInt() ReadInt()
#endif

#ifndef READINT
#define READINT() ReadInt()
#endif

#ifndef readfloat
#define readfloat() ReadFloat()
#endif

#ifndef readFloat
#define readFloat() ReadFloat()
#endif

#ifndef READFLOAT
#define READFLOAT() ReadFloat()
#endif

#ifndef readline
#define readline(...) ReadLine(__VA_ARGS__)
#endif

#ifndef readLine
#define readLine(...) ReadLine(__VA_ARGS__)
#endif

#ifndef READLINE
#define READLINE(...) ReadLine(__VA_ARGS__)
#endif

#ifndef readstr
#define readstr(...) ReadStr(__VA_ARGS__)
#endif

#ifndef readStr
#define readStr(...) ReadStr(__VA_ARGS__)
#endif

#ifndef READSTR
#define READSTR(...) ReadStr(__VA_ARGS__)
#endif

#ifndef printint
#define printint(...) PrintInt(__VA_ARGS__)
#endif

#ifndef printInt
#define printInt(...) PrintInt(__VA_ARGS__)
#endif

#ifndef PRINTINT
#define PRINTINT(...) PrintInt(__VA_ARGS__)
#endif

#ifndef printfloat
#define printfloat(...) PrintFloat(__VA_ARGS__)
#endif

#ifndef printFloat
#define printFloat(...) PrintFloat(__VA_ARGS__)
#endif

#ifndef PRINTFLOAT
#define PRINTFLOAT(...) PrintFloat(__VA_ARGS__)
#endif

#ifndef printstr
#define printstr(...) PrintStr(__VA_ARGS__)
#endif

#ifndef printStr
#define printStr(...) PrintStr(__VA_ARGS__)
#endif

#ifndef PRINTSTR
#define PRINTSTR(...) PrintStr(__VA_ARGS__)
#endif

#ifndef PAUSE
#define PAUSE() Pause()
#endif

#ifndef SQRT
#define SQRT(...) Sqrt(__VA_ARGS__)
#endif

#ifndef POW
#define POW(...) Pow(__VA_ARGS__)
#endif

#ifndef ROUND
#define ROUND(...) Round(__VA_ARGS__)
#endif

#ifndef FLOOR
#define FLOOR(...) Floor(__VA_ARGS__)
#endif

#ifndef CEIL
#define CEIL(...) Ceil(__VA_ARGS__)
#endif

#ifndef mod
#define mod(...) Mod(__VA_ARGS__)
#endif

#ifndef MOD
#define MOD(...) Mod(__VA_ARGS__)
#endif

#ifndef sign
#define sign(...) Sign(__VA_ARGS__)
#endif

#ifndef SIGN
#define SIGN(...) Sign(__VA_ARGS__)
#endif

#ifndef gcd
#define gcd(...) GCD(__VA_ARGS__)
#endif

#ifndef lcm
#define lcm(...) LCM(__VA_ARGS__)
#endif

#ifndef fact
#define fact(...) Fact(__VA_ARGS__)
#endif

#ifndef FACT
#define FACT(...) Fact(__VA_ARGS__)
#endif

#ifndef isprime
#define isprime(...) IsPrime(__VA_ARGS__)
#endif

#ifndef isPrime
#define isPrime(...) IsPrime(__VA_ARGS__)
#endif

#ifndef ISPRIME
#define ISPRIME(...) IsPrime(__VA_ARGS__)
#endif

#ifndef iseven
#define iseven(...) IsEven(__VA_ARGS__)
#endif

#ifndef isEven
#define isEven(...) IsEven(__VA_ARGS__)
#endif

#ifndef ISEVEN
#define ISEVEN(...) IsEven(__VA_ARGS__)
#endif

#ifndef isodd
#define isodd(...) IsOdd(__VA_ARGS__)
#endif

#ifndef isOdd
#define isOdd(...) IsOdd(__VA_ARGS__)
#endif

#ifndef ISODD
#define ISODD(...) IsOdd(__VA_ARGS__)
#endif

#ifndef isperfect
#define isperfect(...) IsPerfect(__VA_ARGS__)
#endif

#ifndef isPerfect
#define isPerfect(...) IsPerfect(__VA_ARGS__)
#endif

#ifndef ISPERFECT
#define ISPERFECT(...) IsPerfect(__VA_ARGS__)
#endif

#ifndef digits
#define digits(...) Digits(__VA_ARGS__)
#endif

#ifndef DIGITS
#define DIGITS(...) Digits(__VA_ARGS__)
#endif

#ifndef isarmstrong
#define isarmstrong(...) IsArmstrong(__VA_ARGS__)
#endif

#ifndef isArmstrong
#define isArmstrong(...) IsArmstrong(__VA_ARGS__)
#endif

#ifndef ISARMSTRONG
#define ISARMSTRONG(...) IsArmstrong(__VA_ARGS__)
#endif

#ifndef ispalindrome
#define ispalindrome(...) IsPalindrome(__VA_ARGS__)
#endif

#ifndef isPalindrome
#define isPalindrome(...) IsPalindrome(__VA_ARGS__)
#endif

#ifndef ISPALINDROME
#define ISPALINDROME(...) IsPalindrome(__VA_ARGS__)
#endif

#ifndef READ
#define READ(...) Read(__VA_ARGS__)
#endif

#ifndef print
#define print(...) Print(__VA_ARGS__)
#endif

#ifndef PRINT
#define PRINT(...) Print(__VA_ARGS__)
#endif

#ifndef sum
#define sum(...) Sum(__VA_ARGS__)
#endif

#ifndef SUM
#define SUM(...) Sum(__VA_ARGS__)
#endif

#ifndef avg
#define avg(...) Avg(__VA_ARGS__)
#endif

#ifndef AVG
#define AVG(...) Avg(__VA_ARGS__)
#endif

#ifndef maxa
#define maxa(...) MaxA(__VA_ARGS__)
#endif

#ifndef maxA
#define maxA(...) MaxA(__VA_ARGS__)
#endif

#ifndef MAXA
#define MAXA(...) MaxA(__VA_ARGS__)
#endif

#ifndef mina
#define mina(...) MinA(__VA_ARGS__)
#endif

#ifndef minA
#define minA(...) MinA(__VA_ARGS__)
#endif

#ifndef MINA
#define MINA(...) MinA(__VA_ARGS__)
#endif

#ifndef sort
#define sort(...) Sort(__VA_ARGS__)
#endif

#ifndef SORT
#define SORT(...) Sort(__VA_ARGS__)
#endif

#ifndef rev
#define rev(...) Rev(__VA_ARGS__)
#endif

#ifndef REV
#define REV(...) Rev(__VA_ARGS__)
#endif

#ifndef find
#define find(...) Find(__VA_ARGS__)
#endif

#ifndef FIND
#define FIND(...) Find(__VA_ARGS__)
#endif

#ifndef first
#define first(...) First(__VA_ARGS__)
#endif

#ifndef FIRST
#define FIRST(...) First(__VA_ARGS__)
#endif

#ifndef last
#define last(...) Last(__VA_ARGS__)
#endif

#ifndef LAST
#define LAST(...) Last(__VA_ARGS__)
#endif

#ifndef count
#define count(...) Count(__VA_ARGS__)
#endif

#ifndef COUNT
#define COUNT(...) Count(__VA_ARGS__)
#endif

#ifndef copy
#define copy(...) Copy(__VA_ARGS__)
#endif

#ifndef COPY
#define COPY(...) Copy(__VA_ARGS__)
#endif

#ifndef equal
#define equal(...) Equal(__VA_ARGS__)
#endif

#ifndef EQUAL
#define EQUAL(...) Equal(__VA_ARGS__)
#endif

#ifndef unique
#define unique(...) Unique(__VA_ARGS__)
#endif

#ifndef UNIQUE
#define UNIQUE(...) Unique(__VA_ARGS__)
#endif

#ifndef freq
#define freq(...) Freq(__VA_ARGS__)
#endif

#ifndef FREQ
#define FREQ(...) Freq(__VA_ARGS__)
#endif

#ifndef insert
#define insert(...) Insert(__VA_ARGS__)
#endif

#ifndef INSERT
#define INSERT(...) Insert(__VA_ARGS__)
#endif

#ifndef delete
#define delete(...) Delete(__VA_ARGS__)
#endif

#ifndef DELETE
#define DELETE(...) Delete(__VA_ARGS__)
#endif

#ifndef rotate
#define rotate(...) Rotate(__VA_ARGS__)
#endif

#ifndef ROTATE
#define ROTATE(...) Rotate(__VA_ARGS__)
#endif

#ifndef len
#define len(...) Len(__VA_ARGS__)
#endif

#ifndef LEN
#define LEN(...) Len(__VA_ARGS__)
#endif

#ifndef copystr
#define copystr(...) CopyStr(__VA_ARGS__)
#endif

#ifndef copyStr
#define copyStr(...) CopyStr(__VA_ARGS__)
#endif

#ifndef COPYSTR
#define COPYSTR(...) CopyStr(__VA_ARGS__)
#endif

#ifndef cat
#define cat(...) Cat(__VA_ARGS__)
#endif

#ifndef CAT
#define CAT(...) Cat(__VA_ARGS__)
#endif

#ifndef cmp
#define cmp(...) Cmp(__VA_ARGS__)
#endif

#ifndef CMP
#define CMP(...) Cmp(__VA_ARGS__)
#endif

#ifndef revstr
#define revstr(...) RevStr(__VA_ARGS__)
#endif

#ifndef revStr
#define revStr(...) RevStr(__VA_ARGS__)
#endif

#ifndef REVSTR
#define REVSTR(...) RevStr(__VA_ARGS__)
#endif

#ifndef upper
#define upper(...) Upper(__VA_ARGS__)
#endif

#ifndef UPPER
#define UPPER(...) Upper(__VA_ARGS__)
#endif

#ifndef lower
#define lower(...) Lower(__VA_ARGS__)
#endif

#ifndef LOWER
#define LOWER(...) Lower(__VA_ARGS__)
#endif

#ifndef trim
#define trim(...) Trim(__VA_ARGS__)
#endif

#ifndef TRIM
#define TRIM(...) Trim(__VA_ARGS__)
#endif

#ifndef countchar
#define countchar(...) CountChar(__VA_ARGS__)
#endif

#ifndef countChar
#define countChar(...) CountChar(__VA_ARGS__)
#endif

#ifndef COUNTCHAR
#define COUNTCHAR(...) CountChar(__VA_ARGS__)
#endif

#ifndef findchar
#define findchar(...) FindChar(__VA_ARGS__)
#endif

#ifndef findChar
#define findChar(...) FindChar(__VA_ARGS__)
#endif

#ifndef FINDCHAR
#define FINDCHAR(...) FindChar(__VA_ARGS__)
#endif

#ifndef findstr
#define findstr(...) FindStr(__VA_ARGS__)
#endif

#ifndef findStr
#define findStr(...) FindStr(__VA_ARGS__)
#endif

#ifndef FINDSTR
#define FINDSTR(...) FindStr(__VA_ARGS__)
#endif

#ifndef replace
#define replace(...) Replace(__VA_ARGS__)
#endif

#ifndef REPLACE
#define REPLACE(...) Replace(__VA_ARGS__)
#endif

#ifndef isDigit
#define isDigit(...) IsDigit(__VA_ARGS__)
#endif

#ifndef ISDIGIT
#define ISDIGIT(...) IsDigit(__VA_ARGS__)
#endif

#ifndef isAlpha
#define isAlpha(...) IsAlpha(__VA_ARGS__)
#endif

#ifndef ISALPHA
#define ISALPHA(...) IsAlpha(__VA_ARGS__)
#endif

#ifndef isSpace
#define isSpace(...) IsSpace(__VA_ARGS__)
#endif

#ifndef ISSPACE
#define ISSPACE(...) IsSpace(__VA_ARGS__)
#endif

#ifndef readmat
#define readmat(...) ReadMat(__VA_ARGS__)
#endif

#ifndef readMat
#define readMat(...) ReadMat(__VA_ARGS__)
#endif

#ifndef READMAT
#define READMAT(...) ReadMat(__VA_ARGS__)
#endif

#ifndef printmat
#define printmat(...) PrintMat(__VA_ARGS__)
#endif

#ifndef printMat
#define printMat(...) PrintMat(__VA_ARGS__)
#endif

#ifndef PRINTMAT
#define PRINTMAT(...) PrintMat(__VA_ARGS__)
#endif

#ifndef matadd
#define matadd(...) MatAdd(__VA_ARGS__)
#endif

#ifndef matAdd
#define matAdd(...) MatAdd(__VA_ARGS__)
#endif

#ifndef MATADD
#define MATADD(...) MatAdd(__VA_ARGS__)
#endif

#ifndef matsub
#define matsub(...) MatSub(__VA_ARGS__)
#endif

#ifndef matSub
#define matSub(...) MatSub(__VA_ARGS__)
#endif

#ifndef MATSUB
#define MATSUB(...) MatSub(__VA_ARGS__)
#endif

#ifndef matmul
#define matmul(...) MatMul(__VA_ARGS__)
#endif

#ifndef matMul
#define matMul(...) MatMul(__VA_ARGS__)
#endif

#ifndef MATMUL
#define MATMUL(...) MatMul(__VA_ARGS__)
#endif

#ifndef transpose
#define transpose(...) Transpose(__VA_ARGS__)
#endif

#ifndef TRANSPOSE
#define TRANSPOSE(...) Transpose(__VA_ARGS__)
#endif

#ifndef trace
#define trace(...) Trace(__VA_ARGS__)
#endif

#ifndef TRACE
#define TRACE(...) Trace(__VA_ARGS__)
#endif

#ifndef diag
#define diag(...) Diag(__VA_ARGS__)
#endif

#ifndef DIAG
#define DIAG(...) Diag(__VA_ARGS__)
#endif

#ifndef matequal
#define matequal(...) MatEqual(__VA_ARGS__)
#endif

#ifndef matEqual
#define matEqual(...) MatEqual(__VA_ARGS__)
#endif

#ifndef MATEQUAL
#define MATEQUAL(...) MatEqual(__VA_ARGS__)
#endif

#ifndef identity
#define identity(...) Identity(__VA_ARGS__)
#endif

#ifndef IDENTITY
#define IDENTITY(...) Identity(__VA_ARGS__)
#endif

#ifndef linear
#define linear(...) Linear(__VA_ARGS__)
#endif

#ifndef LINEAR
#define LINEAR(...) Linear(__VA_ARGS__)
#endif

#ifndef binary
#define binary(...) Binary(__VA_ARGS__)
#endif

#ifndef BINARY
#define BINARY(...) Binary(__VA_ARGS__)
#endif

#ifndef bubble
#define bubble(...) Bubble(__VA_ARGS__)
#endif

#ifndef BUBBLE
#define BUBBLE(...) Bubble(__VA_ARGS__)
#endif

#ifndef SELECT
#define SELECT(...) Select(__VA_ARGS__)
#endif

#ifndef insertsort
#define insertsort(...) InsertSort(__VA_ARGS__)
#endif

#ifndef insertSort
#define insertSort(...) InsertSort(__VA_ARGS__)
#endif

#ifndef INSERTSORT
#define INSERTSORT(...) InsertSort(__VA_ARGS__)
#endif

#ifndef mergesort
#define mergesort(...) MergeSort(__VA_ARGS__)
#endif

#ifndef mergeSort
#define mergeSort(...) MergeSort(__VA_ARGS__)
#endif

#ifndef MERGESORT
#define MERGESORT(...) MergeSort(__VA_ARGS__)
#endif

#ifndef quicksort
#define quicksort(...) QuickSort(__VA_ARGS__)
#endif

#ifndef quickSort
#define quickSort(...) QuickSort(__VA_ARGS__)
#endif

#ifndef QUICKSORT
#define QUICKSORT(...) QuickSort(__VA_ARGS__)
#endif

#ifndef secondmax
#define secondmax(...) SecondMax(__VA_ARGS__)
#endif

#ifndef secondMax
#define secondMax(...) SecondMax(__VA_ARGS__)
#endif

#ifndef SECONDMAX
#define SECONDMAX(...) SecondMax(__VA_ARGS__)
#endif

#ifndef secondmin
#define secondmin(...) SecondMin(__VA_ARGS__)
#endif

#ifndef secondMin
#define secondMin(...) SecondMin(__VA_ARGS__)
#endif

#ifndef SECONDMIN
#define SECONDMIN(...) SecondMin(__VA_ARGS__)
#endif

#ifndef missing
#define missing(...) Missing(__VA_ARGS__)
#endif

#ifndef MISSING
#define MISSING(...) Missing(__VA_ARGS__)
#endif

#ifndef clear
#define clear() Clear()
#endif

#ifndef CLEAR
#define CLEAR() Clear()
#endif

#ifndef delay
#define delay(...) Delay(__VA_ARGS__)
#endif

#ifndef DELAY
#define DELAY(...) Delay(__VA_ARGS__)
#endif

#ifndef RANDOM
#define RANDOM(...) Random(__VA_ARGS__)
#endif

#ifndef seed
#define seed() Seed()
#endif

#ifndef SEED
#define SEED() Seed()
#endif

#ifndef MALLOC
#define MALLOC(...) Malloc(__VA_ARGS__)
#endif

#ifndef FREE
#define FREE(...) Free(__VA_ARGS__)
#endif

#ifndef timerstart
#define timerstart() TimerStart()
#endif

#ifndef timerStart
#define timerStart() TimerStart()
#endif

#ifndef TIMERSTART
#define TIMERSTART() TimerStart()
#endif

#ifndef timerstop
#define timerstop(...) TimerStop(__VA_ARGS__)
#endif

#ifndef timerStop
#define timerStop(...) TimerStop(__VA_ARGS__)
#endif

#ifndef TIMERSTOP
#define TIMERSTOP(...) TimerStop(__VA_ARGS__)
#endif

#ifndef TIME
#define TIME() Time()
#endif

#ifndef in
#define in(...) In(__VA_ARGS__)
#endif

#ifndef IN
#define IN(...) In(__VA_ARGS__)
#endif

#ifndef out
#define out(...) Out(__VA_ARGS__)
#endif

#ifndef OUT
#define OUT(...) Out(__VA_ARGS__)
#endif

#ifndef nl
#define nl() NL()
#endif

#ifndef swap
#define swap(...) Swap(__VA_ARGS__)
#endif

#ifndef SWAP
#define SWAP(...) Swap(__VA_ARGS__)
#endif

#ifndef repeat
#define repeat(...) Repeat(__VA_ARGS__)
#endif

#ifndef REPEAT
#define REPEAT(...) Repeat(__VA_ARGS__)
#endif

#ifndef choose
#define choose(...) Choose(__VA_ARGS__)
#endif

#ifndef CHOOSE
#define CHOOSE(...) Choose(__VA_ARGS__)
#endif

#ifndef max
#define max(...) Max(__VA_ARGS__)
#endif

#ifndef MAX
#define MAX(...) Max(__VA_ARGS__)
#endif

#ifndef min
#define min(...) Min(__VA_ARGS__)
#endif

#ifndef MIN
#define MIN(...) Min(__VA_ARGS__)
#endif

#ifndef ABS
#define ABS(...) Abs(__VA_ARGS__)
#endif

#endif

#endif
