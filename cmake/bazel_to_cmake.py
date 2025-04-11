import argparse
from pathlib import Path
import sys

calls = []


def convert_dep(dep):
    if dep == "//bazel:flex":
        return "command-file-lex-gen"
    if dep.startswith("//"):
        dep = dep[2:]
        parts = dep.split(":")
        if len(parts) == 2:
            before, target = parts
            before = before.replace("/", "::")
            return before + "::" + target
        else:
            return dep.replace("/", "::")
    if dep.startswith("@abseil-cpp"):
        dep = dep[13:]
        return dep.replace("/", "::")
    if dep.startswith("@googletest"):
        dep = dep.replace("@googletest//:", "GTest::")
        return dep
    if dep.startswith(":"):
        dep = dep[1:]
        return dep
    if dep.startswith("@re2"):
        return "re2::re2"
    return dep


def cc_library(**kwargs):
    calls.append(("cc_library", kwargs))


def cc_test(**kwargs):
    calls.append(("cc_test", kwargs))


def load(path, *symbols):
    return [None] * len(symbols)


def package(**kwargs):
    pass


def genlex(**kwargs):
    pass


def genrule(**kwargs):
    pass


def get_version_define_from_module():
    pass


def select(positional, **kwargs):
    pass


def main():
    parser = argparse.ArgumentParser(
        description="Convert a BUILD file to CMake style"
    )
    parser.add_argument("build_file", help="Path to the BUILD file")
    parser.add_argument("-o", "--output", help="The name of the file to be saved in the same folder")
    parser.add_argument("--verify", help="Path to the CMakeLists.txt to verify")
    args = parser.parse_args()

    if args.verify is not None:
        print(args.verify)
        print("Verify!")
        exit(0)

    with open(args.build_file, "r", encoding="utf-8") as f:
        content = f.read()
    exec(
        content,
        {
            "cc_library": cc_library,
            "cc_test": cc_test,
            "load": load,
            "package": package,
            "genlex": genlex,
            "select": select,
            "genrule": genrule,
            "get_version_define_from_module": get_version_define_from_module,
        },
    )

    p = Path(args.build_file)

    if args.output != "":
        f = open(p.parent / args.output, "w", encoding="utf-8")
        sys.stdout = f

    for func_name, kwargs in calls:
        print(f"{func_name}(")
        if "name" in kwargs:
            print("    NAME")
            print(f'    "{kwargs["name"]}"')
        if "srcs" in kwargs:
            print("    SRCS")
            for src in kwargs["srcs"]:
                print(f'    "{src}"')
        if "deps" in kwargs:
            print("    DEPS")
            for dep in kwargs["deps"]:
                print("    " + convert_dep(dep))
        print(")\n")


if __name__ == "__main__":
    main()
