import sys
from pathlib import Path
from typing import List

out_file_scheme = \
"""#ifndef [MODULE_DEF]
#define [MODULE_DEF]


[DATA]

#endif
"""

def check_args():
    args = sys.argv[1:]
    if len(args) < 2:
        print('Usage example: python BinToC Resources.h ./img/img1.png ./img/img2.png ./img/img3.png')
        print("Or in windows powershell: python ./scripts/BinToC.py Resources.txt ((dir  -Path ./img/*.png).fullname)")
        exit(0)
    return args

def read_bytes(filename:str):
    file = open(filename, "rb")
    bytes = file.read()
    file.close()
    return bytes
def bytes_to_hex_str(bytes):
    return ', '.join('0x%02x' % i for i in bytes)

def filename_to_name(filename:str, with_extention):
    if not with_extention:
        res = Path(filename).stem
    else:
        res = Path(filename).name
    res = res.replace(' ', '_') \
             .replace('-', '_') \
             .replace('.', '_')
    return res.upper()

each_file_scheme = \
"""
//region [NAME]
#define [NAME]_SIZE [SIZE]
static const unsigned char [NAME][[NAME]_SIZE] = { 
    [DATA]
};
// endregion



"""


def file_to_code(filename:str) -> str:
    bytes = read_bytes(filename)
    hex_bytes = bytes_to_hex_str(bytes)
    name = filename_to_name(filename, True)
    res = each_file_scheme\
            .replace('[NAME]', name) \
            .replace('[DATA]', hex_bytes) \
            .replace('[SIZE]', str(len(bytes)))
    return res

def files_to_code(files:List[str]) -> str:
    return ''.join([file_to_code(file) for file in files])

if __name__ == '__main__':
    args = check_args()
    out_filename = args[0]
    module_name = filename_to_name(out_filename, True)
    data = files_to_code(args[1:])
    res = out_file_scheme\
            .replace('[MODULE_DEF]', module_name) \
            .replace('[DATA]', data)

    out_file = open(out_filename, "wt")
    out_file.write(res)
    out_file.close()
