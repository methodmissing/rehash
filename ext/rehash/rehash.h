typedef struct {
  st_table *tbl;
  ID method;
} rehash_arg;

static ID id_rekey_bang, id_revalue_bang;

#define HASH_REHASH_METHOD(tbl, k, v) \
  if ((k) != Qundef) st_insert(tbl, (k), (v)); \
  return ST_CONTINUE;

#define HASH_REHASH_WITH(hash, method, func) \
    rehash_arg arg; \
    HASH_MOD_CHECK(hash) \
    arg.method = rb_to_id(method); \
    arg.tbl = st_init_table_with_size(HASH_TYPE(hash), HASH_SIZE(hash)); \
    rb_hash_foreach(hash, func, (rehash_arg*)&arg); \
    st_free_table(HASH_TBL(hash)); \
    HASH_TBL(hash) = arg.tbl; \
    return hash;
