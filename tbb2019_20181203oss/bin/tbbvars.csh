#!/bin/csh
#
# Copyright (c) 2005-2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
#
#

set LIBTBB_NAME="libtbb.dylib"

setenv TBBROOT "SUBSTITUTE_INSTALL_DIR_HERE"

set TBB_LIB_SUBDIR="lib"

while ( $# > 0 )
    switch ( $1 )
        case auto_tbbroot:
            # Argument 'auto_tbbroot' represents TBBROOT detection method.
            # If presented the environment variable TBBROOT is detected automatically by using the script directory path.
            set sourced=($_)
            if ("$sourced" != '') then # if the script was sourced
                set tmp="`dirname "$sourced[2]"`"
                set script_dir=`cd "$tmp"; pwd -P`
            else # if the script was run => "$_" is empty
                echo "ERROR: you have to source the script."
                exit 1
            endif
            setenv TBBROOT "$script_dir/.."
            breaksw
        case universal:
            # Argument 'universal' represents binary architecture.
            # If presented universal binaries will be sourced, otherwise (by default) - intel64 binaries.
            set TBB_LIB_SUBDIR="${TBB_LIB_SUBDIR}/universal"
            breaksw
        default:
            echo "WARNING: unexpected argument: $1"
    endsw
    shift
end

if (-e "${TBBROOT}/${TBB_LIB_SUBDIR}/${LIBTBB_NAME}") then
    if (! $?LIBRARY_PATH) then
        setenv LIBRARY_PATH "${TBBROOT}/${TBB_LIB_SUBDIR}"
    else
        setenv LIBRARY_PATH "${TBBROOT}/${TBB_LIB_SUBDIR}:$LIBRARY_PATH"
    endif
    if (! $?DYLD_LIBRARY_PATH) then
        setenv DYLD_LIBRARY_PATH "${TBBROOT}/${TBB_LIB_SUBDIR}"
    else
        setenv DYLD_LIBRARY_PATH "${TBBROOT}/${TBB_LIB_SUBDIR}:$DYLD_LIBRARY_PATH"
    endif
    if (! $?CPATH) then
        setenv CPATH "${TBBROOT}/include"
    else
        setenv CPATH "${TBBROOT}/include:$CPATH"
    endif
else
    echo "ERROR: ${LIBTBB_NAME} library does not exist in ${TBBROOT}/${TBB_LIB_SUBDIR}."
    unsetenv TBBROOT
    exit 1
endif
