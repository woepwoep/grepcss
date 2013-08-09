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
  https://github.com/Red-Seadog/grepcss
