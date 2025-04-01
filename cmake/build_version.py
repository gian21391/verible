import subprocess
from datetime import datetime

def get_stdout(cmd):
    try:
        return subprocess.check_output(cmd, stderr=subprocess.DEVNULL).decode().strip()
    except subprocess.CalledProcessError:
        return ''


commit_timestamp = get_stdout(['git', 'log', '-n1', '--format=%cd', '--date=unix'])
git_describe = get_stdout(['git', 'describe', '--tags', '--match=v*'])
build_timestamp = int(datetime.now().timestamp())
formatted_date = datetime.now()

print("#define VERIBLE_BUILD_TIMESTAMP", build_timestamp)
print("#define VERIBLE_COMMIT_TIMESTAMP", commit_timestamp)
print('#define VERIBLE_FORMATTED_DATE "{}"'.format(formatted_date))
print('#define VERIBLE_GIT_DESCRIBE "{}"'.format(git_describe))