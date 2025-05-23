#!/usr/bin/perl

my $test_bins = `ls test/bin`;
my @test_bins_list =  split /\n/, $test_bins;

my $pass = 1;
foreach $test (@test_bins_list) {
    system("test/bin/$test");
    if($?) {
        $pass = 0;
    } 
}

if ($pass) {
    print "All Tests Passed!\n";
    exit 0;
}
exit 1;