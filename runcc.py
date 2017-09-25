"""
Command line tool which parses compilation options and passess it to the compiler.
Then it runs execution of compiled code.
"""

import argparse
import subprocess
import glob
import os

PARSER = argparse.ArgumentParser(description='Arguments for compiler', usage='%(prog)s [options]')
PARSER.add_argument('w', nargs='?', help='Show warnings')
PARSER.add_argument('--comp', default='cc', help='Compiler executable')
PARSER.add_argument('--sn', required=True, help='Solution number')
PARSER.add_argument('--out', nargs='?', default=None, help='Destination')
PARSER.add_argument('--opts', nargs='*', help='Parameters for executable')

ARGS = PARSER.parse_args()

OPTION_LIST = []

# Add compiler
OPTION_LIST.append(ARGS.comp)

# Add warning mode
if ARGS.w:
    OPTION_LIST.append('-Wall')

PATH = ARGS.sn.split('.')
FILES = glob.glob(os.path.join(PATH[0], '{0}_**.c'.format(PATH[1])))

# Add file to compile
OPTION_LIST.append(FILES[0])

# Add compiler output option
OPTION_LIST.append('-o')
if ARGS.out:
    OUT = ARGS.out
else:
    OUT = os.path.splitext(FILES[0])[0]

# Add output file
OPTION_LIST.append(OUT)

# Executable command line arguments
EXEC_OPTIONS = []
EXEC_OPTIONS.append(OUT)

# Add options for compiled executable
if ARGS.opts:
    EXEC_OPTIONS.extend(ARGS.opts)

# Run compilation
EXIT_CODE = subprocess.call(OPTION_LIST, stdout=os.sys.stdout)

# Run execution
if EXIT_CODE == 0:
    subprocess.call(EXEC_OPTIONS, stdout=os.sys.stdout, shell=True)
