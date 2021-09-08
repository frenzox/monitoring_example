project('monitoring_example',
        ['c'],
        default_options: ['warning_level=3'],
        meson_version: '>=0.56.0',
        version: '0.0.0',
)

keyval = import('keyval')
board_name = meson.get_cross_property('board_name')
temp_config_file = 'boards/@0@/@1@.config'
config_file = temp_config_file.format(board_name, board_name)
kconfig = keyval.load(config_file)

cc = meson.get_compiler('c')
cflags = meson.get_cross_property('cflags')
cflags = cc.get_supported_arguments(cflags)

c_args = []
c_link_args = []
source_files = []
linker_files = []
include_dirs = []

foreach key, value : kconfig
    if value == 'y'
        c_args += '-D' + key
    else
        c_args += '-D' + key + '=' + value
    endif
endforeach

include_dirs += include_directories('include')

subdir('application')
subdir('soc')
subdir('boards')
subdir('drivers')

foreach linker_file: linker_files
    c_link_args += ['-Wl,-T,@0@/@1@'.format(meson.current_source_dir(), linker_file)]
endforeach

c_args += cflags
if board_name != 'test'
    elf = executable('monitoring_example.elf',
                     source_files,
                     dependencies: [hal_stm32f3xx_dep],
                     c_args: c_args,
                     link_args: c_link_args,
                     include_directories: include_dirs)

    objcopy = find_program('objcopy')
    no_crc_bin = custom_target('monitoring-example-bin-without-crc.bin',
                        build_by_default: true,
                        depends: elf,
                        input: [elf],
                        output: ['monitoring-example-no-crc.bin'],
                        command: [objcopy, '-Obinary', '@INPUT@', '@OUTPUT@'])

    crc_appender = find_program('scripts/crc_appender.sh', required: true)
    bin = custom_target('monitoring-example.bin',
                        build_by_default: true,
                        depends: no_crc_bin,
                        input: [no_crc_bin],
                        output: ['monitoring-example.bin'],
                        command: [crc_appender, '@INPUT@', '@OUTPUT@'])
else
    add_project_arguments('--coverage', language: ['c'])
    add_project_link_arguments('--coverage', language: ['c'])
    c_link_args += ['-Wl,-undefined,dynamic_lookup']

    application_lib = static_library('application_lib',
                                     [application_files, application_generated_files],
                                     c_args: c_args,
                                     link_args: c_link_args,
                                     include_directories: include_dirs)

    application_dep = declare_dependency(link_with: application_lib,
                                         include_directories: include_dirs)

    unity_proj = subproject('unity')
    unity_dep = unity_proj.get_variable('unity_dep')

    cmock_proj = subproject('cmock')
    cmock_dep = cmock_proj.get_variable('cmock_dep')

    include_dirs += include_directories('include/drivers')
    subdir('test')
endif
