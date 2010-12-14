class TestRehash < Test::Unit::TestCase
  def test_rekey
    hash = { 'a' => 1, 'b' => 2 }
    rekeyed = hash.rekey(:upcase)
    assert_not_equal hash.object_id, rekeyed.object_id
    assert_rekeyed rekeyed, %w(A B)
  end

  def test_rekey_bang
    hash = { 'a' => 1, 'b' => 2 }
    hash.rekey!(:upcase)
    assert_rekeyed hash, %w(A B)
    hash.rekey!(:to_sym)
    assert_rekeyed hash, [:A, :B]
  end

  def test_revalue
    hash = { 1 => 'a', 2 => 'b' }
    revalued = hash.revalue(:upcase)
    assert_not_equal hash.object_id, revalued.object_id
    assert_revalued revalued, %w(A B)
  end

  def test_revalue_bang
    hash = { 1 => 'a', 2 => 'b' }
    hash.revalue!(:upcase)
    assert_revalued hash, %w(A B)
    hash.revalue!(:to_sym)
    assert_revalued hash, [:A, :B]
  end

  private
  def assert_revalued(hash, expected)
    assert_rehased(hash, :value?, expected)
  end

  def assert_rekeyed(hash, expected)
    assert_rehased(hash, :key?, expected)
  end

  def assert_rehased(hash, meth, expected)
    assert expected.all?{|k| hash.__send__(meth, k) }
  end
end