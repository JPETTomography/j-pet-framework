#!/usr/bin/perl
use strict;
use warnings;
use Cwd;
#my $level = "all";
#my $level = "error";
my $level = "";

if ( @ARGV > 0) {
  $level = $ARGV[0];
} else {
  $level="error";
}
my @tests = `ls -d *Test/`;
my $path = cwd();
foreach my $test_dir (@tests) {
  chdir($path);
  chomp $test_dir;  
  my $test =$test_dir;
  chop $test; #remove trailing /
  $test = "./".$test.".exe";
  print $test_dir."\n";
  chdir($test_dir);
  #my $run_command = $test_dir.$test." --log_level=".$level;
  my $run_command = $test." --log_level=".$level;
  open my $handler, $run_command." |";
  while (<$handler>) {
    print $_;
  }
  close $handler;
#  print $run_command;
#  `$run_command`;

}

#system("cd ./ROOTExamples/; ./run_tests.sh")
