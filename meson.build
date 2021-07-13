# Meson build file
#
# SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC
# SPDX-License-Identifier: Apache-2.0

project('trower-base64', 'c',
        version: '1.2.0',
        license: ['Apache-2.0'],
        default_options: ['c_std=c99',
                          'b_coverage=true'])

# We want strict flags
warning_level = 3   # -Wall
werror = true

################################################################################
# Generate the version values
################################################################################

version = meson.project_version()
version_arr = version.split('.')
major = version_arr[0].to_int()
minor = version_arr[1].to_int()
patch = version_arr[2].to_int()

hex = '0123456789abcdef'
ver = '0x@0@@1@@2@@3@@4@@5@'
bitwise = ver.format(hex[major / 16], hex[major % 16],
                     hex[minor / 16], hex[minor % 16],
                     hex[patch / 16], hex[patch % 16])

cfg = configuration_data()
cfg.set( meson.project_name()+'_VERSION', version)
cfg.set( meson.project_name()+'_VERSION_MAJOR', major)
cfg.set( meson.project_name()+'_VERSION_MINOR', minor)
cfg.set( meson.project_name()+'_VERSION_PATCH', patch)
cfg.set( meson.project_name()+'_BITWISE_VERSION', bitwise)

ver_h = configure_file(input:  'src/ver.h.in',
                       output: 'ver.h',
                       configuration: cfg)

################################################################################
# Define the libraries
################################################################################

inc = include_directories('src')

install_headers(['src/base64.h', ver_h])

the_sources = ['src/base64.c']

the_libs = both_libraries(meson.project_name(),
                          the_sources,
                          include_directories: inc,
                          install: true)

################################################################################
# Define the tests
################################################################################

test_args = ['-fprofile-arcs', '-ftest-coverage', '-O0']

cunit_dep = dependency('cunit')

test('simple test',
     executable('simple', ['tests/simple.c'],
                include_directories: inc,
                dependencies: cunit_dep,
                link_args: test_args,
                link_with: the_libs))

################################################################################
# Configure valgrind
################################################################################

add_test_setup('valgrind',
               is_default: true,
               exe_wrapper: [ 'valgrind',
                              '--leak-check=full',
                              '--error-exitcode=1' ],
               timeout_multiplier: 2)

################################################################################
# Add the license check target
################################################################################

reuse_bin = find_program('reuse')
if reuse_bin.found()
  custom_target('license',
                command: [reuse_bin, 'lint'],
                build_always_stale: true,
                output: ['license'])
endif

