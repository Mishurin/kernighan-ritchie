/*
* Exercise 8-7. malloc accepts a size request without checking its plausibility; free 
* believes that the block it is asked to free contains a valid size field. Improve
* these routines so they make more pains with error checking.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 8.7

#include <stdio.h>
#include <limits.h>

#define NALLOC 1024
#define MAX(a,b) (((a)>(b))?(a):(b))

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

// According to the UINT_MAX malloc can acquire up to 4 Gb of memory...
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

    // ... but
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
        return; // points to null
    Header *bp, *p;
    bp = (Header *)ap - 1;
    if(bp->s.size == 0)
        return; // request to something that even haven't been freed.
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

int lim(Header *fp)
{
    int maxunits = MAX(fp? fp->s.size : 0, NALLOC);

    return sizeof(Header) * (maxunits - 1) + 1;
}

int main(int argc, char *argv[])
{

    int maxbytes;

    maxbytes = lim(freep);
    printf("Max request:%d\n", maxbytes);
    
    char *s1 = _malloc(maxbytes);
    char *s2 = _malloc(maxbytes - 1);
    char *s3 = _malloc(maxbytes - 1);
    printf("Address 1:%p\n", s1);
    printf("Address 2:%p\n", s2);
    printf("Address 3:%p\n", s3);

    Header *s2h = (Header *) s2 - 1;
    Header *s3h = (Header *) s3 - 1;
    printf("Mem unit size 1:%u\n", s2h->s.size);
    printf("Mem unit size 2:%u\n", s3h->s.size);

    _free(s1); // nothing to free
    _free(s2);
    _free(s3);
    
    maxbytes = lim(freep);
    printf("Merged mem unit size:%u\n", freep->s.size);
    printf("Max request:%d\n", maxbytes);
    char *s4 = _malloc(maxbytes - 1); // no
    printf("Address 4:%p\n", s4);
    s4 = _malloc(sizeof(Header) * (NALLOC - 1) + 1);
    printf("Address 4:%p\n", s4); // still no

    _free(s4); // nothing to free

    return 0;
}