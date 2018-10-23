/* 
* Exercise 8-6. The standard library function calloc(n,size) returns a pointer to n 
* objects of size 'size', with the storage initialized to zero. Write calloc, by calling 
* malloc or by modifying it.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 8.6

#include <stdio.h>

typedef long _align;

union memunit {
    struct
    {
        union memunit *ptr;
        unsigned size;
    } s;
    _align x;
};

typedef union memunit Header;

static Header base;
static Header *freep = NULL;
static Header *morecore(unsigned);
void _free(void *ap);

void *_malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(union memunit) + 1;

    if ((prevp = freep) == NULL)
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

#define NALLOC 1024

static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;
    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *)-1)
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    _free((void *)(up + 1));
    return freep;
}

void _free(void *ap)
{
    Header *bp, *p;
    bp = (Header *)ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

    if (bp + bp->s.size == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;
}

void *_calloc(int n, unsigned size)
{
    return _malloc(n * size);
}

int main(int argc, char *argv[])
{

    int *a = _malloc(sizeof(int));
    *a = 123;
    long *b = _malloc(sizeof(long));
    *b = 100;
    char *s = _calloc(5, sizeof(char));
    char *t = "test";
    if (a && b && s)
    {
        printf("%d\n", *a);
        printf("%ld\n", *b);
        for (int i = 0; i < 5; i++)
        {
            s[i] = t[i];
        }
        printf("%s\n", s);
        _free(a);
        _free(b);
        _free(s);
    }

    return 0;
}
