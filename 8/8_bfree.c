/*
* Exercise 8-8. Write a routine bfree(p,n) that will free any arbitrary block p of n 
* characters into the free list maintained by malloc and free. By using bfree, a user 
* can add a static or external array to the free list at any time.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 8.8

#include <stdio.h>
#include <limits.h>

#define NALLOC 1024

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

    if (nunits > NALLOC)
        return NULL;

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
    if(ap == NULL)
        return;
    Header *bp, *p;
    bp = (Header *)ap - 1;
    if(bp->s.size == 0)
        return;
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

void bfree(char *p, int n)
{
    if (freep == NULL)
    {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }
    int nunits = (n * sizeof(char) + sizeof(Header) - 1) / sizeof(union memunit);
    Header *hp = (Header *)p;
    hp->s.size = nunits;
    _free(hp + 1);
}

void *_calloc(int n, unsigned size)
{
    return _malloc(n * size);
}

int main(int argc, char *argv[])
{
    
    int hlen = sizeof(Header); // bytes used to setup header attributes
    int arrlen = 1;
    char arr[hlen + arrlen];

    bfree(arr, hlen + arrlen);
    char *pt = (char *)_malloc(arrlen);
    printf("Test:%d\n", pt == &arr[hlen]);

    _free(pt);
    pt = (char *)_malloc(arrlen);
    printf("Test:%d\n", pt == &arr[hlen]);

    char *pt1 = _malloc(3);
    _free(pt);
    _free(pt1);

    printf("%u\n", freep->s.size);
    printf("%u\n", freep->s.ptr->s.size);

    return 0;
}