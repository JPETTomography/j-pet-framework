#!/usr/bin/perl
use warnings;
use strict;
use Data::Dumper;

my $numArgs = $#ARGV + 1;
if ($numArgs != 1) {
  print "usage: ./check_style.pl filename";
  exit;
}
my $flags = " --filter=-legal/copyright,-readability/streams,-build/header_guard";
my $command = "python cpplint.py";
my $fullCommand = $command.$flags." $ARGV[0]";
`$fullCommand`;
