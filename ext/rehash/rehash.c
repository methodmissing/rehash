#include <ruby.h>
#ifdef HAVE_RB_THREAD_BLOCKING_REGION
#define RUBY19
#include <rehash_19.h>
#else
#define RUBY18
#include <rehash_18.h>
#endif

typedef struct {
  st_table *tbl;
  VALUE method;
} rehash_arg;

static ID id_rekey_bang;

#define HASH_REHASH_METHOD(tbl, k, v) \
  if ((k) != Qundef) st_insert(tbl, (k), (v)); \
  return ST_CONTINUE;

static int
rb_hash_rekey_i(VALUE key, VALUE value, rehash_arg* arg)
{
    ID method;
    method = rb_to_id(arg->method);
    HASH_REHASH_METHOD(arg->tbl, rb_funcall(key, method, 0, 0), value)
}

#define HASH_REHASH_WITH(hash, method, func) \
    rehash_arg arg; \
    HASH_MOD_CHECK(hash) \
    arg.method = method; \
    arg.tbl = st_init_table_with_size(HASH_TYPE(hash), HASH_SIZE(hash)); \
    rb_hash_foreach(hash, func, (rehash_arg*)&arg); \
    st_free_table(HASH_TBL(hash)); \
    HASH_TBL(hash) = arg.tbl;

static VALUE
rb_hash_rekey_bang(VALUE hash, VALUE method)
{
    HASH_REHASH_WITH(hash, method, rb_hash_rekey_i)
    return hash;
}

void
Init_rehash()
{
    id_rekey_bang = rb_intern("rekey!");

    rb_define_method(rb_cHash, "rekey!", rb_hash_rekey_bang, 1);
}
