#!/bin/bash
CHECKSUMS_FILE="all_data.sha"
DATA_DIRECTORY="unitTestData"

# Ignore hidden files and directories. For all files contained in a subdirectory compute a SHA256 checksum.
find $DATA_DIRECTORY -mindepth 1 -type f -print0 | xargs -0 shasum -a 256 > $CHECKSUMS_FILE
chgrp users $CHECKSUMS_FILE
