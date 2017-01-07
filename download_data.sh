#!/bin/bash
#if the first argument is provided it is treated as the output path
#e.g. download_data.sh /blabla/path
#will write the output to /blabla/path 

#if there is an extra argument treat it as the output path 
#if the argument is empty set some default paths
BASE_PATH=.
if [ ! -z $1 ]; then
  BASE_PATH=$1
fi

CHECKSUM_COMMAND="shasum -c"

#for scp
CFG_DIR=/home/framework_configs
CFG_OUTPUT=$BASE_PATH/DBHandler/Config
declare -a CFG_FILES=("configDB.cfg" "configDB.cfg.koza" "ReadMe.txt")
CFG_SERVER=sphinx.if.uj.edu.pl

declare -a CFG_FILES_IN=()
for FILE in "${CFG_FILES[@]}"
do
  CFG_FILES_IN+=" ${CFG_DIR}/${FILE}"
done

declare -a CFG_FILES_OUT=()
for FILE in "${CFG_FILES[@]}"
do
  CFG_FILES_OUT+=" ${CFG_OUTPUT}/${FILE}"
done

#for wget
TEST_DATA_DIR="unitTestData"
TEST_CHECKSUM_FILE=$TEST_DATA_DIR.sha
TEST_BASE_URL="http://sphinx.if.uj.edu.pl/framework"
TEST_DATA_URL=$TEST_BASE_URL/$TEST_DATA_DIR
TEST_CHECKSUM_URL=$TEST_BASE_URL/$TEST_CHECKSUM_FILE
TEST_OUTPUT=$BASE_PATH
LOCAL_TEST_CHECKSUM_FILE=$TEST_OUTPUT/$TEST_CHECKSUM_FILE
# -r  means recursive,
# --cut-dirs=1 ignore given level of directories (e.g. remove framework from path)
# -nH  Disable generation of host-prefixed directories (so save only unitTestData and not full path)
# -np no parents
# --reject="index.html*" - do not store all index.html files
# -e robots=off - remove some robot generated files
declare -a WGET_FLAGS=(-r -nH -np --cut-dirs=1 --reject="index.html*" -e robots=off)

#downloading test data via wget
# first get and check the checksums
wget "${TEST_CHECKSUM_URL}" "${WGET_FLAGS[@]}" -P "${TEST_OUTPUT}"
if $CHECKSUM_COMMAND $LOCAL_TEST_CHECKSUM_FILE | grep 'FAIL'; then
  echo "Some unit test data files don't exist or are wrong."
  echo "Deleting the unit test data directory..."
  rm -rf $TEST_OUTPUT/$TEST_DATA_DIR
  echo "Downloading the unit test data..."
  wget "${TEST_DATA_URL}" "${WGET_FLAGS[@]}" -P "${TEST_OUTPUT}"
  if $CHECKSUM_COMMAND $LOCAL_TEST_CHECKSUM_FILE | grep 'FAIL'; then
    echo "The downloaded data does not match the checksum!"
    exit 1
  else
    echo "All unit test data OK."
  fi
else
  echo "All unit test data OK."
fi
rm $LOCAL_TEST_CHECKSUM_FILE

#check if scp files are already downloaded
#if at least one exists assume it was downloaded (because you usually overwrite one with the other)
DOWNLOADED=""
for FILE in ${CFG_FILES_OUT[@]}
do
  if [ -f $FILE ]; then
    DOWNLOADED="true"
    break
  fi
done
if [ ! -z $DOWNLOADED ] ; then
  echo "Config files seem to exist, not downloading them again."
else
  #downloading sensinble data via scp
  mkdir -p $CFG_OUTPUT
  echo "Fetching database config files."
  echo "To avoid downloading leave the username empty."
  read -p "username at ${CFG_SERVER}:" USERNM;
  if [ ! -z USERNM ]; then
    scp ${USERNM}@${CFG_SERVER}:"${CFG_FILES_IN}" ${CFG_OUTPUT}
  fi
fi
