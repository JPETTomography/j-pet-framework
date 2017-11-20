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


function check_sums {
	local CUR_DIR=$PWD
	cd $BASE_PATH
	shasum -c $1
	cd $CUR_DIR
}
CHECKSUM_COMMAND="check_sums"

#for wget
TEST_CHECKSUM_FILE="all_data.sha"
TEST_BASE_URL="http://sphinx.if.uj.edu.pl/framework"
TEST_CHECKSUM_URL=$TEST_BASE_URL/$TEST_CHECKSUM_FILE
TEST_OUTPUT=$BASE_PATH
LOCAL_TEST_CHECKSUM_FILE=$TEST_OUTPUT/$TEST_CHECKSUM_FILE
# -x create subdirectories,
# -nH  Disable generation of host-prefixed directories (so save only unitTestData and not full path)
# --cut-dirs=1 ignore given level of directories (e.g. remove framework from path)
declare -a WGET_FLAGS=(-x -nH --cut-dirs=1)

#downloading test data via wget
# first get and check the checksums
wget "${TEST_CHECKSUM_URL}" "${WGET_FLAGS[@]}" -P "${TEST_OUTPUT}"
for FILE in $($CHECKSUM_COMMAND $LOCAL_TEST_CHECKSUM_FILE | grep 'FAIL' | sed 's/:.*//'); do
  TEST_FILE_URL=$TEST_BASE_URL/$FILE
  wget "${TEST_FILE_URL}" "${WGET_FLAGS[@]}" -P "${TEST_OUTPUT}"
done
if $CHECKSUM_COMMAND $LOCAL_TEST_CHECKSUM_FILE | grep 'FAIL'; then
  echo "The downloaded data does not match the checksum!"
  exit 1
else
  echo "All unit test data OK."
fi
rm $LOCAL_TEST_CHECKSUM_FILE
