import re
import argparse
import sys

def std_move_parser_symbols(src, out):
    with open(src, 'r') as file:
        content = file.read()

    content = re.sub(r"= yylval;", r"= std::move(yylval);", content)
    content = re.sub(r"= yyval;", r"= std::move(yyval);", content)
    content = re.sub(r"\(= yyval_default\)", r"(= std::move(yyval_default))", content)
    content = re.sub(r"yyval = yyvsp\[1-yylen\];", r"// yyval = yyvsp[1-yylen];", content)

    with open(out, 'w') as file:
        file.write(content)


def record_recovered_syntax_errors(src, out):
    with open(src, 'r') as file:
        content = file.read()

    content = re.sub(
        r"\+\+yynerrs;",
        r"++yynerrs;\n          // Automatically patched by >>record_recovered_syntax_errors<< rule:\n          param->RecordSyntaxError(yylval);\n          // end of automatic patch",
        content
    )

    with open(out, 'w') as file:
        file.write(content)


def main():
    parser = argparse.ArgumentParser(description='Parser symbol modification utility')

    subparsers = parser.add_subparsers(dest='function', help='Function to invoke')

    move_parser = subparsers.add_parser('std_move_parser_symbols', help='Modify parser symbols with std::move')
    move_parser.add_argument('--src', required=True, help='Source file path')
    move_parser.add_argument('--out', required=True, help='Output file path')

    record_parser = subparsers.add_parser('record_recovered_syntax_errors', help='Record recovered syntax errors')
    record_parser.add_argument('--src', required=True, help='Source file path')
    record_parser.add_argument('--out', required=True, help='Output file path')

    args = parser.parse_args()

    if args.function == 'std_move_parser_symbols':
        std_move_parser_symbols(args.src, args.out)
        print(f"Processed {args.src} to {args.out} with '{args.function}'")
    elif args.function == 'record_recovered_syntax_errors':
        record_recovered_syntax_errors(args.src, args.out)
        print(f"Processed {args.src} to {args.out} with name '{args.function}'")
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()