#!/bin/bash
#if the first argument is provided it is treated as the output path
#e.g. download_data.sh /blabla/path
#will write the output to /blabla/path 

#for scp
SCP_INPUT=/home/framework_configs
SCP_OUTPUT=./DBHandler/Config
declare -a CFG_FILES=("configDB.cfg" "configDB.cfg.koza" "ReadMe.txt")
SERVER=sphinx.if.uj.edu.pl

#for wget
WGET_DIR="unitTestData"
#WGET_INPUT="http://sphinx.if.uj.edu.pl/framework/"${WGET_DIR}
WGET_INPUT="http://koza.if.uj.edu.pl/framework/"${WGET_DIR}
WGET_OUTPUT="./"
# -r  means recursive, 
# --cut-dirs=1 ignore given level of directories (e.g. remove framework from path) 
# -nH  Disable generation of host-prefixed directories (so save only unitTestData and not full path)
# -np no parents
# --reject="index.html*" - do not store all index.html files
# -e robots=off - remove some robot generated files
declare -a WGET_FLAGS=(-r -nH -np --cut-dirs=1 --reject="index.html*" -e robots=off)

#if there is an extra argument treat it as the output path 
#if the argument is empty set some default paths
if [ -z $1 ]; then
  SCP_OUTPUT=.
  WGET_OUTPUT=.
else
  mkdir -p $1/DBHandler/Config
  SCP_OUTPUT=$1/DBHandler/Config
  WGET_OUTPUT=$1
fi

declare -a CFG_FILES_IN=()
for FILE in "${CFG_FILES[@]}"
do
  CFG_FILES_IN+=" ${SCP_INPUT}/${FILE}"
done

declare -a CFG_FILES_OUT=()
for FILE in "${CFG_FILES[@]}"
do
  CFG_FILES_OUT+=" ${SCP_OUTPUT}/${FILE}"
done

#downloading test data via wget
if [ ! -d "${WGET_OUTPUT}/${WGET_DIR}" ]; then
  wget "${WGET_INPUT}" "${WGET_FLAGS[@]}" -P "${WGET_OUTPUT}" 
else
  echo "directory ${WGET_OUTPUT}/${WGET_DIR} already exists !"
  echo "downloading interrupted!"
fi

#check if scp files are already downloaded
not_downloaded=false
for FILE in ${CFG_FILES_OUT[@]}
do
  if [ ! -f $FILE ]; then
    not_downloaded=true 
    break
  fi
done
echo ${not_downloaded}
if [ ${not_downloaded} = true ] ; then
  #downloading sensinble data via scp
  read -p "username at ${SERVER}:" USERNM;
  scp ${USERNM}@${SERVER}:"${CFG_FILES_IN}" ${SCP_OUTPUT}
else
  echo "config files seems to exist!"
  echo "downloading interrupted!"
fi
