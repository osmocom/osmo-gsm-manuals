#!/bin/sh
# Pick a path, depending on where such path exists:
#   find_existing_path.sh "want/*.file" ./dir1 ../../dir2 /tmp/dir3
# prints the first existing match:
#   ../../dir2/want/foo.file
# or just the first argument if none is found:
#   want/*.file
path="$1"

shift 1
for dir in $@ ; do
	for f in "$dir"/$path ; do
		if [ ! -r "$f" ]; then
			continue
		fi
		echo "$f"
		exit 0
	done
done

echo "$path"
exit 1
