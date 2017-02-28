#!/usr/bin/perl
use strict;
use warnings;
use Cwd;
use Getopt::Std;

my $level = "";
my $format = "";
our $opt_f = "HRF";
our $opt_l;
my $reportLevel = "no";

# process command-line options
getopts('f:l:');

if( ! defined $opt_l ){
    $level = "error";
}else{
    $level = $opt_l;
}

if( $opt_f eq "xml" ){
    $level = "all";
    $format = "XML";
}else{
    $format = "HRF";
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
  $run_command = $run_command." --log_format=".$format;
  if( $format eq "XML" ){
      $run_command = $run_command." --log_sink=".$test_name.".xml";
      $run_command = $run_command." --report_level=".$reportLevel;
  }
  open my $handler, $run_command." |";
  while (<$handler>) {
    print $_;
  }
  close $handler;
  print $run_command;
#  `$run_command`;

}

#system("cd ./ROOTExamples/; ./run_tests.sh")
