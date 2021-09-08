models = files('fsm_tripper.xml')

gsl = find_program('gsl')
gen_fsm = generator(gsl,
                    output: ['@BASENAME@.h',
                             '@BASENAME@.c',
                             '@BASENAME@_handlers.h',
                             '@BASENAME@_default_handlers.c'],
                    arguments: ['-a',
                                '-q',
                                '-script:' + meson.project_source_root() + '/scripts/fsm_code.gsl',
                                '@INPUT@',
                                '@BUILD_DIR@'])

foreach file : models
    source_files += gen_fsm.process(file)
endforeach
