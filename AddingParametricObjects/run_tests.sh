#!/bin/bash

# test 1
echo "test1"
echo "Events and Parameters in the same file"
echo ""
cd test1
rm -f tree1.root
./gen1.x
./read1.x
cd ..
echo ""
echo "End test1"
echo ""

# test 2
echo "test2"
echo "Events and Parameters in separate files"
echo ""
cd test2
rm -f *.root
./gen2.x
./read2.x
cd ..
echo ""
echo "End test2"
echo ""

# test 3
echo "test3"
echo "Events and Parameters in separate files - \"Right\" method"
echo ""
cd test3
rm -f *.root
./gen3db.x
./gen3eve.x
./read3.x
cd ..
echo ""
echo "End test3"
echo ""

# test 4
echo "test4"
echo "Replacing orginal database with changed one"
echo ""
cd test4
rm -f *.root
./gen4db.x
./gen4eve.x
./regen4.x
#./inspect.x
./read4.x
cd ..
echo ""
echo "End test4"
echo ""
