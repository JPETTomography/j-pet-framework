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
my @tests = `ls *Test.x`;
my $path = cwd();
foreach my $test (@tests) {
  chomp $test;  
  my $test_name = $test;
  $test_name =~ s/\.x//g;
  print "\n".$test_name."\n";
  $test = "./".$test;
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
