'''
Creates a file with specified number of letters
'''
import argparse
import random

MAX_CHAR_VALUE = 255

PARSER = argparse.ArgumentParser(description='Text generator', usage='%(prog)s [options]')
PARSER.add_argument('--mode', default='default', help='Mode')
PARSER.add_argument('--char', default='x', help='Character to fill')
PARSER.add_argument('--lines', default='1', help='Number of lines')
PARSER.add_argument('--dest', required=True, help='Destination location')
PARSER.add_argument('--length', required=True, help='Char length')

ARGS = PARSER.parse_args()

def get_random_ascii_char():
    '''
    Generates random ascii character
    '''
    return chr(random.randrange(0, MAX_CHAR_VALUE + 1))

def write_to_file(file, line_num, line_length, get_symbol):
    '''
    Generates a symbol to file based on predicate
    '''
    for i in range(line_num):
        for k in range(line_length):
            file.write(get_symbol())
        if line_num > 0:
            file.write('\n')

OUT = open(ARGS.dest, 'w')

if ARGS.mode is not 'r':
    write_to_file(OUT, int(ARGS.lines), int(ARGS.length), lambda: ARGS.char)
else:
    write_to_file(OUT, int(ARGS.lines), int(ARGS.length), get_random_ascii_char)
