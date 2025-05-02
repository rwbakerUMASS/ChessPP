#!/usr/bin/perl
use strict;
use warnings;
use File::Path qw(make_path);
use File::Basename;

my $timestamp = `date +\%m_\%d_\%H\%M\%S`;
chomp($timestamp);

# Directories
my $src_dir     = 'src';
my $pieces_dir  = 'src/pieces';
my $include_dir = 'include';
my $bin_dir     = 'bin';
my $log_dir     = 'logs/build';
my $log_file    = "$log_dir/build_$timestamp.log";
my $output_file = "$bin_dir/ChessPP";

# Make sure bin/ and logs/ exist
make_path($bin_dir) unless -d $bin_dir;
make_path($log_dir) unless -d $log_dir;

# Collect all .cpp files from src/ and src/pieces/
my @cpp_files = glob("$src_dir/*.cpp $pieces_dir/*.cpp");

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
exit 0;
