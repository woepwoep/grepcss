NAME
  grepcss - print CSS lines matching a pattern


SYNOPSIS
  grepcss [-c] [-s selector] [-p property] [-v value] cssfile(s)
  grepcss [-b] [-c] cssfile(s)


OPTIONS
  -c
    appends the count ("aantal=") of each CSS expression found in the input stream/file

  -s selector
  -p property
  -v value
    a "grep"-like function to get a subset of CSS expressions found in the input stream/file

  -b
    indented output of the input stream


SEE ALSO
  grep(1)


NOTES
  grepcss is also valid with other commands,
  for example: grepcss -c *.css | sort -u | grepcss -b > alphabeticallySorted.css

repository at: https://github.com/Red-Seadog/grepcss
  contributed by http://www.red-seadog.com
