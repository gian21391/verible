import argparse
import sys
import re

def main():
    parser = argparse.ArgumentParser(description="Generate foreach list for nonterminal enums")
    parser.add_argument("infile")
    parser.add_argument("outfile")
    args = parser.parse_args()

    infile = args.infile
    outfile = args.outfile

    in_generate = False
    with open(infile) as fin:
        lines = fin.readlines()
    processed = []
    for line in lines:
        if "BEGIN GENERATE" in line:
            in_generate = True; continue
        if "END GENERATE" in line:
            in_generate = False; continue
        if in_generate:
            if "GENERATE" in line: continue
            newline = re.sub(r'^ *', 'CONSIDER(', line)
            newline = re.sub(r' =.*?,', ',', newline, count=1)
            newline = re.sub(r',', ')', newline, count=1)
            processed.append(newline)
    with open(outfile, 'w') as fout:
        fout.writelines(processed)


if __name__ == "__main__":
    main()