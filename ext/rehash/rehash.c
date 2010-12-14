#include <ruby.h>
#ifdef HAVE_RB_THREAD_BLOCKING_REGION
#define RUBY19
#include <rehash_19.h>
#else
#define RUBY18
#include <rehash_18.h>
#endif

#include <rehash.h>

static inline int
rb_hash_rekey_i(VALUE key, VALUE value, rehash_arg* arg)
{
    HASH_REHASH_METHOD(arg->tbl, rb_funcall(key, arg->method, 0, 0), value)
}

static VALUE
rb_hash_rekey_bang(VALUE hash, VALUE method)
{
    rehash_arg arg;
    HASH_REHASH_WITH(hash, method, rb_hash_rekey_i)
}

static inline int
rb_hash_revalue_i(VALUE key, VALUE value, rehash_arg* arg)
{
    HASH_REHASH_METHOD(arg->tbl, key, rb_funcall(value, arg->method, 0, 0))
}

static VALUE
rb_hash_revalue_bang(VALUE hash, VALUE method)
{
    rehash_arg arg;
    HASH_REHASH_WITH(hash, method, rb_hash_revalue_i)
}

static VALUE
rb_hash_rekey(VALUE hash, VALUE method)
{
    rehash_arg arg;
    VALUE dup;
    dup = rb_obj_dup(hash);
    HASH_REHASH_WITH(dup, method, rb_hash_rekey_i)
}

static VALUE
rb_hash_revalue(VALUE hash, VALUE method)
{
    rehash_arg arg;
    VALUE dup;
    dup = rb_obj_dup(hash);
    HASH_REHASH_WITH(dup, method, rb_hash_revalue_i)
}

void
Init_rehash()
{
    rb_define_method(rb_cHash, "rekey!", rb_hash_rekey_bang, 1);
    rb_define_method(rb_cHash, "revalue!", rb_hash_revalue_bang, 1);
    rb_define_method(rb_cHash, "rekey", rb_hash_rekey, 1);
    rb_define_method(rb_cHash, "revalue", rb_hash_revalue, 1);
}
