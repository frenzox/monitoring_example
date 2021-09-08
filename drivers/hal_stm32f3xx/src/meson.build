file_list = run_command('grabber.sh')
hal_source_files = files(file_list.stdout().strip().split('\n'))

hal_stm32_c_args += '-w'
# In order to ignore all the warnings in these files, we have to compile them
# separately in a static library
hal_stm32f3xx_lib = static_library('hal_stm32f3xx',
                                   hal_source_files,
                                   pic: false,
                                   c_args: hal_stm32_c_args,
                                   include_directories: include_dirs)

hal_stm32f3xx_dep = declare_dependency(link_whole: hal_stm32f3xx_lib,
                                       include_directories: include_dirs)
