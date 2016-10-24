#!/usr/bin/perl
use warnings;
use strict;
use IPC::Cmd qw[can_run];

my $numArgs = $#ARGV + 1;
if ($numArgs != 1) {
  die "usage: ./fix_style.pl filename\n";
}
my $gitRoot = `git rev-parse --show-toplevel`;
chomp $gitRoot;
my $astyle = can_run('astyle') or die "astyle not found, please install it!\n";
my $astyleConfig = $gitRoot."/extras/_astylerc";
my $command = $astyle." --options=".$astyleConfig;
my $fullCommand = $command." $ARGV[0]";
`$fullCommand`;
