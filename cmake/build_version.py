import argparse
import subprocess
from datetime import datetime

def get_stdout(cmd):
    try:
        return subprocess.check_output(cmd, stderr=subprocess.DEVNULL).decode().strip()
    except subprocess.CalledProcessError:
        return ''

def main():
    parser = argparse.ArgumentParser(description='Parser symbol modification utility')
    parser.add_argument("-c", "--commit", help="Commit timestamp")
    parser.add_argument("-v", "--version", help="Git describe")
    args = parser.parse_args()

    if args.commit is not None:
        commit_timestamp = args.commit
    else:
        commit_timestamp = get_stdout(['git', 'log', '-n1', '--format=%cd', '--date=unix'])

    if commit_timestamp == "":
        commit_timestamp = "0"


    if args.version is not None:
        git_describe = args.version
    else:
        git_describe = get_stdout(['git', 'describe', '--tags', '--match=v*'])

    if git_describe == "":
        git_describe = "No git info"

    build_timestamp = int(datetime.now().timestamp())
    formatted_date = datetime.now()

    print("#define VERIBLE_BUILD_TIMESTAMP", build_timestamp)
    print("#define VERIBLE_COMMIT_TIMESTAMP", commit_timestamp)
    print('#define VERIBLE_FORMATTED_DATE "{}"'.format(formatted_date))
    print('#define VERIBLE_GIT_DESCRIBE "{}"'.format(git_describe))

if __name__ == "__main__":
    main()