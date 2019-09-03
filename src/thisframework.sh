# Source this script to set up the JPetFramework build that this script is part of.
#
# Based on thisframework.sh script from ROOT 6.16

drop_from_path()
{
   # Assert that we got enough arguments
   if test $# -ne 2 ; then
      echo "drop_from_path: needs 2 arguments"
      return 1
   fi

   local p=$1
   local drop=$2

   newpath=`echo $p | sed -e "s;:${drop}:;:;g" \
                          -e "s;:${drop}\$;;g"   \
                          -e "s;^${drop}:;;g"   \
                          -e "s;^${drop}\$;;g"`
}

#check if there is already setted some framework path
if [ -n "${FRAMEWORKSYS}" ] ; then
   old_frameworksys=${FRAMEWORKSYS}
fi

SOURCE=${BASH_ARGV[0]}
if [ "x$SOURCE" = "x" ]; then
    SOURCE=${(%):-%N} # for zsh
fi

if [ "x${SOURCE}" = "x" ]; then
    if [ -f bin/thisframework.sh ]; then
        FRAMEWORKSYS="$PWD"; export FRAMEWORKSYS
    elif [ -f ./thisframework.sh ]; then
        FRAMEWORKSYS=$(cd ..  > /dev/null; pwd); export FRAMEWORKSYS
    else
        echo ERROR: must "cd where/root/is" before calling ". bin/thisframework.sh" for this version of bash!
        FRAMEWORKSYS=; export FRAMEWORKSYS
        return 1
    fi
else
    # get param to "."
    thisframework=$(dirname ${SOURCE})
    FRAMEWORKSYS=$(cd ${thisframework}/.. > /dev/null;pwd); export FRAMEWORKSYS
fi

if [ -n "${old_frameworksys}" ] ; then
   if [ -n "${PATH}" ]; then
      drop_from_path "$PATH" "${old_frameworksys}/bin"
      PATH=$newpath
   fi
   if [ -n "${LD_LIBRARY_PATH}" ]; then
      drop_from_path "$LD_LIBRARY_PATH" "${old_frameworksys}/lib"
      LD_LIBRARY_PATH=$newpath
   fi
   if [ -n "${DYLD_LIBRARY_PATH}" ]; then
      drop_from_path "$DYLD_LIBRARY_PATH" "${old_frameworksys}/lib"
      DYLD_LIBRARY_PATH=$newpath
   fi
   if [ -n "${SHLIB_PATH}" ]; then
      drop_from_path "$SHLIB_PATH" "${old_frameworksys}/lib"
      SHLIB_PATH=$newpath
   fi
   if [ -n "${LIBPATH}" ]; then
      drop_from_path "$LIBPATH" "${old_frameworksys}/lib"
      LIBPATH=$newpath
   fi
   if [ -n "${PYTHONPATH}" ]; then
      drop_from_path "$PYTHONPATH" "${old_frameworksys}/lib"
      PYTHONPATH=$newpath
   fi
   if [ -n "${MANPATH}" ]; then
      drop_from_path "$MANPATH" "${old_frameworksys}/man"
      MANPATH=$newpath
   fi
   if [ -n "${CMAKE_PREFIX_PATH}" ]; then
      drop_from_path "$CMAKE_PREFIX_PATH" "${old_frameworksys}"
      CMAKE_PREFIX_PATH=$newpath
   fi
   if [ -n "${JUPYTER_PATH}" ]; then
      drop_from_path "$JUPYTER_PATH" "${old_frameworksys}/etc/notebook"
      JUPYTER_PATH=$newpath
   fi

fi

if [ -z "${PATH}" ]; then
   PATH=$FRAMEWORKSYS/bin; export PATH
else
   PATH=$FRAMEWORKSYS/bin:$PATH; export PATH
fi

if [ -z "${LD_LIBRARY_PATH}" ]; then
   LD_LIBRARY_PATH=$FRAMEWORKSYS/lib; export LD_LIBRARY_PATH       # Linux, ELF HP-UX
else
   LD_LIBRARY_PATH=$FRAMEWORKSYS/lib:$LD_LIBRARY_PATH; export LD_LIBRARY_PATH
fi

if [ -z "${CMAKE_PREFIX_PATH}" ]; then
   CMAKE_PREFIX_PATH=$FRAMEWORKSYS; export CMAKE_PREFIX_PATH       # Linux, ELF HP-UX
else
   CMAKE_PREFIX_PATH=$FRAMEWORKSYS:$CMAKE_PREFIX_PATH; export CMAKE_PREFIX_PATH
fi

unset old_frameworksys
unset thisframework
unset -f drop_from_path