Gem::Specification.new do |s|
  s.name = 'rehash'
  s.version = '0.1'
  s.date = '2010-09-10'
  s.authors = ['Lourens Naudé', 'James Tucker']
  s.email = ['lourens@methodmissing.com', 'jftucker@gmail.com']
  s.description = 'This gem provides basic rehashing abilities.'
  s.homepage = 'http://github.com/methodmissing/rehash'
  s.summary = 'This gem provides basic rehashing abilities.'
  s.extensions = 'ext/rehash/extconf.rb'
  s.files = Dir.glob("{ext,test}/**/*") + %w[README Rakefile rehash.gemspec]
  s.has_rdoc = true
  s.extra_rdoc_files = Dir['ext/rehash/*.c']
end