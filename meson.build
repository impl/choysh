# SPDX-FileCopyrightText: 2022-2024 Noah Fontes
#
# SPDX-License-Identifier: Apache-2.0

project('choysh', 'c',
        version: '1.0.4',
        default_options: ['c_std=c11', 'warning_level=3', 'optimization=3'])
add_project_arguments('-D_POSIX_C_SOURCE=200809L', language: 'c')
executable('choysh', 'main.c', install: true)
