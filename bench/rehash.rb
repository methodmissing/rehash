$:.unshift "."
require 'benchmark'
require File.dirname(__FILE__) + '/../ext/rehash/rehash'

TESTS = 100_000
key_hash = { 'a' => 1, 'b' => 2, 'c' => 3, 'd' => 4, 'e' => 5, 'f' => 6 }
value_hash = key_hash.invert

puts "#{TESTS} iterations ..."

class Hash
  def ruby_rekey!(m)
    keys.each{|k| self[k.__send__(m)] = delete(k) }
  end

  def ruby_revalue!(m)
    keys.each{|k| self[k] = self[k].__send__(m) }
  end
end

Benchmark.bmbm do |results|
  results.report("key_hash.dup.rekey!(:upcase)") { TESTS.times{ key_hash.dup.rekey!(:upcase) } }
  results.report("key_hash.dup.ruby_rekey!(:upcase)") { TESTS.times{ key_hash.dup.ruby_rekey!(:upcase) } }
  results.report("value_hash.dup.revalue!(:upcase)") { TESTS.times{ value_hash.dup.revalue!(:upcase) } }
  results.report("value_hash.dup.ruby_revalue!(:upcase)") { TESTS.times{ value_hash.dup.ruby_revalue!(:upcase) } }
end