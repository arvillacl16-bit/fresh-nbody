project('FreshNBody', 'cpp', version : '0.1.0', default_options : ['cpp_std=c++17', 'warning_level=3'])

source_files = files('src/particle.cpp')

inc = include_directories('include')

lib_freshnbody = static_library('freshnbody', source_files, include_directories : inc, install : true)

executable('test_', sources : 'test.cpp', include_directories : inc, link_with : lib_freshnbody)