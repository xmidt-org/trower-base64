# Meson build file
#
# SPDX-FileCopyrightText: 2021 Comcast Cable Communications Management, LLC
# SPDX-License-Identifier: Apache-2.0

project('trower-base64', 'c',
        version: '1.2.4',
        license: ['Apache-2.0'],
        default_options: ['c_std=c99',
                          'b_coverage=true'])

if not meson.is_subproject()
  # We want strict flags
  warning_level = 3   # -Wall
  werror = true
endif

################################################################################
# Common variable definitions
################################################################################

inc_base = 'include/'+meson.project_name()

################################################################################
# Generate the version header file
################################################################################

subdir('include/'+meson.project_name())

################################################################################
# Define the libraries
################################################################################

inc = include_directories(inc_base)

install_headers([inc_base+'/base64.h', ver_h], subdir: meson.project_name())

sources = ['src/base64.c']

libtrower = library(meson.project_name(),
                    sources,
                    include_directories: inc,
                    install: true)

################################################################################
# Define the tests
################################################################################

if not meson.is_subproject()
  test_args = ['-fprofile-arcs', '-ftest-coverage', '-O0']

  cunit_dep = dependency('cunit')

  test('simple test',
       executable('simple', ['tests/simple.c'],
                  include_directories: inc,
                  dependencies: cunit_dep,
                  install: false,
                  link_args: test_args,
                  link_with: libtrower))

  add_test_setup('valgrind',
                 is_default: true,
                 exe_wrapper: [ 'valgrind',
                                '--leak-check=full',
                                '--error-exitcode=1' ],
                 timeout_multiplier: 2)
endif

################################################################################
# Add the license check target
################################################################################

reuse_bin = find_program('reuse', required: false)
if reuse_bin.found()
  custom_target('license',
                command: [reuse_bin, 'lint'],
                build_always_stale: true,
                output: ['license'])
endif

libtrower_base64_dep = declare_dependency(include_directories: ['include'],
                                          link_with: libtrower)

if meson.version().version_compare('>=0.54.0')
  meson.override_dependency(meson.project_name(), libtrower_base64_dep)
endif
