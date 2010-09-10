#include "st.h"
#define HASH_TBL(hash) RHASH(hash)->tbl
#define HASH_SIZE(hash) RHASH(hash)->tbl->num_entries
#define HASH_TYPE(hash) &objhash
#define HASH_MOD_CHECK(hash) rb_hash_modify(hash);

/* leeched from core hash.c - would be nice to have these not be static and exposed via intern.h */

static void
rb_hash_modify(hash)
    VALUE hash;
{
    if (!RHASH(hash)->tbl) rb_raise(rb_eTypeError, "uninitialized Hash");
    if (OBJ_FROZEN(hash)) rb_error_frozen("hash");
    if (!OBJ_TAINTED(hash) && rb_safe_level() >= 4)
    rb_raise(rb_eSecurityError, "Insecure: can't modify hash");
}

static VALUE
eql(args)
    VALUE *args;
{
    return (VALUE)rb_eql(args[0], args[1]);
}

static int
rb_any_cmp(a, b)
    VALUE a, b;
{
    VALUE args[2];

    if (a == b) return 0;
    if (FIXNUM_P(a) && FIXNUM_P(b)) {
    return a != b;
    }
    if (TYPE(a) == T_STRING && RBASIC(a)->klass == rb_cString &&
    TYPE(b) == T_STRING && RBASIC(b)->klass == rb_cString) {
    return rb_str_cmp(a, b);
    }
    if (a == Qundef || b == Qundef) return -1;
    if (SYMBOL_P(a) && SYMBOL_P(b)) {
    return a != b;
    }

    args[0] = a;
    args[1] = b;
    return !rb_with_disable_interrupt(eql, (VALUE)args);
}

static int
rb_any_hash(a)
    VALUE a;
{
    VALUE hval;
    int hnum;

    switch (TYPE(a)) {
      case T_FIXNUM:
      case T_SYMBOL:
    hnum = (int)a;
    break;

      case T_STRING:
    hnum = rb_str_hash(a);
    break;

      default:
        hval = rb_hash(a);
    hnum = (int)FIX2LONG(hval);
    }
    hnum <<= 1;
    return RSHIFT(hnum, 1);
}

static struct st_hash_type objhash = {
    rb_any_cmp,
    rb_any_hash,
};