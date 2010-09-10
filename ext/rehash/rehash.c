#include <ruby.h>
#ifdef HAVE_RB_THREAD_BLOCKING_REGION
#define RUBY19
#include <rehash_19.h>
#else
#define RUBY18
#include <rehash_18.h>
#endif

#include <rehash.h>

static int
rb_hash_rekey_i(VALUE key, VALUE value, rehash_arg* arg)
{
    ID method;
    method = rb_to_id(arg->method);
    HASH_REHASH_METHOD(arg->tbl, rb_funcall(key, method, 0, 0), value)
}

static VALUE
rb_hash_rekey_bang(VALUE hash, VALUE method)
{
    HASH_REHASH_WITH(hash, method, rb_hash_rekey_i)
    return hash;
}

static int
rb_hash_revalue_i(VALUE key, VALUE value, rehash_arg* arg)
{
    ID method;
    method = rb_to_id(arg->method);
    HASH_REHASH_METHOD(arg->tbl, key, rb_funcall(value, method, 0, 0))
}

static VALUE
rb_hash_revalue_bang(VALUE hash, VALUE method)
{
    HASH_REHASH_WITH(hash, method, rb_hash_revalue_i)
    return hash;
}

void
Init_rehash()
{
    id_rekey_bang = rb_intern("rekey!");

    rb_define_method(rb_cHash, "rekey!", rb_hash_rekey_bang, 1);
    rb_define_method(rb_cHash, "revalue!", rb_hash_revalue_bang, 1);
}
