"""
Command line tool which parses compilation options and passess it to the compiler.
Then it runs execution of compiled code.
"""

import argparse
import subprocess
import glob
import os
import signal

signal.signal(signal.SIGPIPE, signal.SIG_DFL)

PARSER = argparse.ArgumentParser(description='Arguments for compiler', usage='%(prog)s [options]')
PARSER.add_argument('-w', help='Show warnings', action="store_true")
PARSER.add_argument('-argv', help='Arguments mode', action="store_true")
PARSER.add_argument('-g', help='Prepare for debugging', action="store_true")
PARSER.add_argument('-l', help='Link libraries', action="store_true")
PARSER.add_argument('--i', nargs='*', help='Include directory')
PARSER.add_argument('--comp', default='cc', help='Compiler executable')
PARSER.add_argument('--sn', required=True, help='Solution number')
PARSER.add_argument('--out', nargs='?', default=None, help='Destination')
PARSER.add_argument('--opts', nargs='*', help='Parameters for executable')
PARSER.add_argument('--inc', nargs='*', help='Include files')


ARGS = PARSER.parse_args()

OPTION_LIST = []

# Add compiler
OPTION_LIST.append(ARGS.comp)

# Add warning mode
if ARGS.w:
    OPTION_LIST.append('-Wall')

if ARGS.g:
    OPTION_LIST.append('-g')

# Add include directory
if ARGS.i:
    OPTION_LIST.append('-I')
    for item in ARGS.i:
        item_found = glob.glob(item)[0]
        OPTION_LIST.append(item_found)

PATH = ARGS.sn.split('.')
FILES = glob.glob(os.path.join(PATH[0], '{0}_**.c'.format(PATH[1])))

# Add file to compile
OPTION_LIST.append(FILES[0])

# Add files to compile with
if ARGS.inc:
    for item in ARGS.inc:
        item_found = glob.glob(os.path.join(PATH[0], item))[0]
        OPTION_LIST.append(item_found)

# Add compiler output option
OPTION_LIST.append('-o')
if ARGS.out:
    OUT = ARGS.out
else:
    OUT = os.path.splitext(FILES[0])[0]

# Add output file
OPTION_LIST.append(OUT)

# Link libraries like math
if ARGS.l:
    OPTION_LIST.append('-lm')

# Executable command line arguments
EXEC_OPTIONS = []
EXEC_OPTIONS.append(OUT)

# Add options for compiled executable
if ARGS.opts:
    EXEC_OPTIONS.extend(ARGS.opts)

# Run compilation
print OPTION_LIST
EXIT_CODE = subprocess.call(OPTION_LIST, stdout=os.sys.stdout)

# Run execution
if EXIT_CODE == 0:
    subprocess.call(EXEC_OPTIONS, stdout=os.sys.stdout, shell=not ARGS.argv)
