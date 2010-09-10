class TestRehash < Test::Unit::TestCase
  def test_rekey_bang
    hash = { 'a' => 1, 'b' => 2 }
    hash.rekey!(:upcase)
    assert_rekeyed hash, %w(A B)
    hash.rekey!(:to_sym)
    assert_rekeyed hash, [:A, :B]
  end

  private
  def assert_rekeyed(hash, expected)
    assert_rehased(hash, :key?, expected)
  end

  def assert_rehased(hash, meth, expected)
    assert expected.all?{|k| hash.__send__(meth, k) }
  end
end