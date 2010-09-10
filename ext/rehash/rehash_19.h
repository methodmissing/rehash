#include "ruby/st.h"
#define HASH_TBL(hash) RHASH(hash)->ntbl
#define HASH_SIZE(hash) RHASH(hash)->ntbl->num_entries
#define HASH_TYPE(hash) RHASH(hash)->ntbl->type
#define HASH_MOD_CHECK(hash) \
    if (RHASH(hash)->iter_lev > 0) { \
    rb_raise(rb_eRuntimeError, "rehash during iteration"); \
    } \
    rb_hash_modify_check(hash); \
    if (!RHASH(hash)->ntbl) \
        return hash;

/* leeched from core hash.c - would be nice to have these not be static and exposed via intern.h */

static void
rb_hash_modify_check(VALUE hash)
{
    if (OBJ_FROZEN(hash)) rb_error_frozen("hash");
    if (!OBJ_UNTRUSTED(hash) && rb_safe_level() >= 4)
    rb_raise(rb_eSecurityError, "Insecure: can't modify hash");
}
