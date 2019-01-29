#!/bin/bash

## Script downloading test data for J-PET Framework build
# Files are on sphinx server and listed together with their checksums.
# If some file has been already downloaded, its checksum is compared with the one
# from the list. If equal, file is not downloaded again.
# Download is performed with wget.
# If the script is provided with one argument, it is treated as the output path
# i.e. download_data.sh /somedir/path
##

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

TEST_CHECKSUM_FILE="all_data.sha"
TEST_BASE_URL="http://sphinx.if.uj.edu.pl/framework"
TEST_CHECKSUM_URL=$TEST_BASE_URL/$TEST_CHECKSUM_FILE
TEST_OUTPUT=$BASE_PATH
LOCAL_TEST_CHECKSUM_FILE=$TEST_OUTPUT/$TEST_CHECKSUM_FILE

# -x create subdirectories,
# -nH  Disable generation of host-prefixed directories (so save only unitTestData and not full path)
# --cut-dirs=1 ignore given level of directories (e.g. remove framework from path)
# -nv not verbose
declare -a WGET_FLAGS=(-x -nH -nv --cut-dirs=1)

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
