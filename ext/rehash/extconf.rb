require 'mkmf'

dir_config('rehash')
have_func('rb_thread_blocking_region')
$defs.push("-pedantic")
create_makefile('rehash')