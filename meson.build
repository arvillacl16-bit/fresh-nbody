project('FreshNBody', 'cpp', version : '0.1.0', default_options : ['cpp_std=c++17', 'warning_level=3'])

gtest_dep = dependency('gtest', fallback : ['gtest', 'gtest_dep'])
gtest_main_dep = dependency('gtest_main', fallback : ['gtest', 'gtest_main_dep'])

source_files = files('src/particle.cpp')

inc = include_directories('include')

lib_freshnbody = static_library('freshnbody', source_files, include_directories : inc, install : true)

test_files = {
  'test1': 'test1.cpp'
}

foreach test_name, test_file : test_files
  test_file = 'unit-tests' / test_file
  test_exe = executable(test_name,
    sources : test_file,
    include_directories : inc,
    link_with : lib_freshnbody,
    dependencies : gtest_main_dep,
    install : false
  )

  test(test_name, test_exe)
endforeach