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

OUT = open(ARGS.dest, 'w')

if ARGS.mode is not 'r':
    CHAR_CODE = ARGS.char
    for i in range(int(ARGS.lines)):
        for a in range(0, int(ARGS.length)):
            OUT.write(ARGS.char)
        if ARGS.lines > 0:
            OUT.write('\n')
else:
    for i in range(int(ARGS.lines)):
        for a in range(0, int(ARGS.length) + 1):
            OUT.write(get_random_ascii_char())
        if ARGS.lines > 0:
            OUT.write('\n')