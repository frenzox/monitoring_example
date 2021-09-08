find = find_program('find', required: true)
mockgen = find_program('mockgen.sh', required: true)

mock_headers = run_command(find,
                           meson.project_source_root() + '/include/drivers/',
                           '-type', 'f',
                           '-name', '*.h').stdout().split()

mocks = []
cmock_headers = []
foreach mock : mock_headers
    mock_name = mock.split('/')
    mock_name = mock_name[mock_name.length() - 1]
    generated_mock = custom_target(mock_name,
                                   input: mock,
                                   output: ['mock_@BASENAME@.h',
                                            'mock_@BASENAME@.c'],
                                   command: [mockgen,
                                             meson.project_source_root() + '/subprojects/cmock/lib/cmock.rb',
                                             meson.current_build_dir(),
                                             '@INPUT@'])

    mocks += generated_mock
    cmock_headers += generated_mock[1]
endforeach

mocks_dep = declare_dependency(sources: mocks,
                               dependencies: [cmock_dep, unity_dep],
                               include_directories: include_dirs)

tests = [
    'test_temperature_monitor'
]

foreach _test : tests
    test_bin = executable(_test,
                          ['@0@.c'.format(_test), cmock_headers],
                          c_args: c_args,
                          include_directories: include_dirs,
                          dependencies: [application_dep,
                                         cmock_dep,
                                         mocks_dep,
                                         unity_dep])

    test(_test, test_bin)
endforeach
