#!/usr/bin/perl
use strict;
use warnings;
#my $level = "all";
#my $level = "error";
my $level = "";

if ( @ARGV > 0) {
  $level = $ARGV[0];
} else {
  $level="error";
}
my @tests = `ls -d *Test/`;
#my @testFiles = `ls *Test.exe`;
#foreach (@testFiles) {
foreach my $test_dir (@tests) {
  chomp $test_dir;  
  my $test =$test_dir;
  chop $test; #remove trailing /
  $test = $test.".exe";
  my $run_command = $test_dir.$test." --log_level=".$level;
  open my $handler, $run_command." |";
  while (<$handler>) {
    print $_;
  }
  close $handler;
#  print $run_command;
#  `$run_command`;

}

#system("cd ./ROOTExamples/; ./run_tests.sh")
