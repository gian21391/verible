import sys

if len(sys.argv) < 3:
    sys.exit("Usage: {} <input_file> <output_file>".format(sys.argv[0]))

inp, outp = sys.argv[1], sys.argv[2]

with open(outp, "w") as o, open(inp, "r") as i:
    o.write("#ifndef VERIBLE_VERILOG_TOKEN_ENUM_H_\n#define VERIBLE_VERILOG_TOKEN_ENUM_H_\n// DO NOT EDIT -- generated from {}\n".format(inp))
    flag = False
    for line in i:
        if not flag and "#ifndef VERILOG_TOKENTYPE" in line:
            flag = True
        if flag:
            o.write(line)
            if "#endif" in line:
                break
    o.write("#endif  // VERIBLE_VERILOG_TOKEN_ENUM_H_\n")
