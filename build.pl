#!/usr/bin/perl
use strict;
use warnings;
use File::Path qw(make_path);
use File::Basename;
use JSON;


my $test = 0;
foreach my $arg (@ARGV) {
    if ($arg eq '--test') {
        $test = 1;
    }
}

my $timestamp = `date +\%m_\%d_\%H\%M\%S`;
chomp($timestamp);

# Directories
my $src_dir     = 'src';
my $include_dir = 'include';
my $bin_dir     = 'bin';
my $log_dir     = 'logs/build';
my $log_file    = "$log_dir/build_$timestamp.log";
my $output_file = "$bin_dir/ChessPP";
my $test_dir    = "test";
my $test_bin    = "$test_dir/bin";

# Make sure bin/ and logs/ exist
make_path($bin_dir) unless -d $bin_dir;
make_path($log_dir) unless -d $log_dir;
make_path($test_bin) unless -d $test_bin;

# Collect all .cpp files from src/ and src/pieces/
my @cpp_files = glob("$src_dir/*.cpp");

# Compiler and flags
my $compiler = 'g++';
my $flags    = "-I $include_dir -std=c++17 -Wall -Wextra";

# Build command
my $cmd = "$compiler @cpp_files $flags -o $output_file";

print "Building...\n";
print "$cmd\n";

# Run the command and capture output
my $output = `$cmd 2>&1`;
my $exit_code = $? >> 8;

if ($exit_code != 0) {
    # Save errors to log file
    open(my $log_fh, '>', $log_file) or die "Can't open log file: $!";
    print $log_fh $output;
    close($log_fh);

    print "Build failed. See log: $log_file\n";
    exit 1;
}

print "Build successful. Binary is at $output_file\n";

if ($test) {
    my $testListPath = "$test_dir/tests.json";
    open (my $testList_fh, "<:encoding(UTF-8)", $testListPath)
        or die ("Can't open $testListPath");
    local $/;
    my $testList = <$testList_fh>;
    close($testList_fh);
    my $data = decode_json($testList);
    foreach my $test (keys %{$data}){
        my $cpp_files = $data->{$test}->{cpp};
        my $includes = $data->{$test}->{include};

        my $build_list = "";
        foreach my $cpp (@$cpp_files) {
            $build_list = "$build_list $cpp";
        }

        my $include_list = "";
        foreach my $include (@$includes) {
            $include_list = "$include_list -I$include";
        }
        my $cmd = "$compiler $build_list $include_list -std=c++17 -Wall -Wextra -o $test_dir/bin/$test.o";
        
        print "Building...\n";
        print "$cmd\n";

        my $output = `$cmd 2>&1`;
        my $exit_code = $? >> 8;

        if ($exit_code != 0) {
            open(my $log_fh, '>', $log_file) or die "Can't open log file: $!";
            print $log_fh $output;
            close($log_fh);

            print "Build failed. See log: $log_file\n";
            exit 1;
        }
        print "Build successful. Binary is at $test_dir/bin/$test.o\n";
    }
}
exit 0;

