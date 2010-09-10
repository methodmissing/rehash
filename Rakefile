#!/usr/bin/env rake
require 'rake/testtask'
require 'rake/clean'
$:.unshift(File.expand_path('lib'))
REHASH_ROOT = 'ext/rehash'

desc 'Default: test'
task :default => :test

desc 'Run rehash tests.'
Rake::TestTask.new(:test) do |t|
  t.libs = [REHASH_ROOT]
  t.pattern = 'test/test_*.rb'
  t.ruby_opts << '-rtest'
  t.libs << 'test'
  t.warning = true
  t.verbose = true
end
task :test => :build

namespace :build do
  file "#{REHASH_ROOT}/rehash.c"
  file "#{REHASH_ROOT}/extconf.rb"
  file "#{REHASH_ROOT}/Makefile" => %W(#{REHASH_ROOT}/rehash.c #{REHASH_ROOT}/extconf.rb) do
    Dir.chdir(REHASH_ROOT) do
      ruby 'extconf.rb'
    end
  end

  desc "generate makefile"
  task :makefile => %W(#{REHASH_ROOT}/Makefile #{REHASH_ROOT}/rehash.c)

  dlext = Config::CONFIG['DLEXT']
  file "#{REHASH_ROOT}/rehash.#{dlext}" => %W(#{REHASH_ROOT}/Makefile #{REHASH_ROOT}/rehash.c) do
    Dir.chdir(REHASH_ROOT) do
      sh 'make' # TODO - is there a config for which make somewhere?
    end
  end

  desc "compile rehash extension"
  task :compile => "#{REHASH_ROOT}/rehash.#{dlext}"

  task :clean do
    Dir.chdir(REHASH_ROOT) do
      sh 'make clean'
    end if File.exists?("#{REHASH_ROOT}/Makefile")
  end

  CLEAN.include("#{REHASH_ROOT}/Makefile")
  CLEAN.include("#{REHASH_ROOT}/rehash.#{dlext}")
end

task :clean => %w(build:clean)

desc "compile"
task :build => %w(build:compile)

task :install do |t|
  Dir.chdir(REHASH_ROOT) do
    sh 'sudo make install'
  end
end

desc "clean build install"
task :setup => %w(clean build install)