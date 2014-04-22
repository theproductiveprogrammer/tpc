/**
 * To implement a double-linked list with only a single pointer.
 *
 * There are two ways I can think off:
 * 1) Make the pointer a decomposible operation of the previous
 *    and next pointers. These would mean any reversible operations like
 *      - addition
 *      - subtraction
 *      - multiplication
 *      - xor
 * 2) Partition the pointer into two parts that contain the previous
 *    and next links.
 *
 *
 * Analysis of approaches
 * 1) In this case, a pointer is recoverable as long as it's 'pair' is
 *    available. This is implementable, for instance, by using the head
 *    of the list and walking to the current node, utilizing the fact that
 *    the we know the previous of the head pointer (to be NULL) or by
 *    utilizing the tail of the list (whose next will be NULL).
 *    The disadvantage of this approach is that we now have a doubly linked
 *    list whose performance in insertion and deletion is O(n) which is
 *    _worse_ than a singly linked-list. Hence I am not using this approach.
 * 2) In this case, in order for a pointer to be able to partition itself
 *    we can make use of the fact that the entire pointer space is enormous
 *    while the space allocated to a given program is normally much smaller.
 *    Since the space is so much smaller, the pointers can be 'compressed'
 *    by representing them as the _offsets_ between the current node and
 *    the next.
 *    I belive approach gives us all the benefits of the double-linked list
 *    for most cases and so I am using this approach. The tricky bit is only
 *    to ensure that pointer sizes are correctly handled for various
 *    architectures (32-bit and 64-bit). I have coded a sample below.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct dbl_ll {
    union {
        struct DBL_LL* ptr;
#ifdef 32_BIT
        uint16_t prv;
        uint16_t nxt;
#endif
#ifdef 64_BIT
        uint32_t prv;
        uint32_t nxt;
#endif
    };

    int value;
};

struct dbl_ll* insert (struct dbl_ll* cur, int value)
{
        struct dbl_ll *n, *nxt;

    n = malloc (sizeof *n);
    n->ptr   = 0;
    n->value = value;

    if (!cur) return n;

    nxt = cur + cur->nxt;
    cur->nxt = n - cur;
    n->prv = cur->nxt;
    n->nxt = nxt - n;

    return n;
}

struct dbl_ll* delete (struct dbl_ll* cur)
{
    ...
}

