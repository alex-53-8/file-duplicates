# File duplicates
A simple util for searching for file duplicates in folders.
File duplicates can be search by:
- comparing files by a calculated hash of a file's content;
- by comparing files' names, content is ignored.

An util performs search in specified folders. A user can specify from 1 to N folders to be searched in.
Multiple folders are separated by colon when specified, for example:
```
fdups -f /test:/content:/tmp:/logs
```

Sample help output:
```
Usage:
  fdups [OPTION...]

  -h, --help              Print usage
  -f, --folders arg       folders where to look for duplicates; specify 
                          folders in format f1[:f2[:f3[:fn]]]; path of 
                          execution is used is used by default
  -m, --compare-mode arg  supports comparing by "hash" or by "name". "hash" 
                          is used by default
  -p, --pattern arg       regex for a file name, ".*" is used by default
```

Utility prints list of file duplicates to a standard output.
Sample output:
```
user@machine:/$ fdups -p .\* -m hash -f /test

Performing search by following arguments:
> folders: 
/test
> comparing method: hash
> pattern: .*

Same files for a hash: 7500f31bbb66e99a35498ba7799e3139d0756d2d8060973a304be71b867316f5
  /test/file.f1
  /test/file.f2
Same files for a hash: 94b306c8e7bf7f836da506b6c80297ecfead0481e6fe11086d8433d304a129eb
  /test/file.f3
  /test/inner/file.f3
  /test/inner/file.f4
```


# Build & install
Run following command for build and install an application

```
mkdir build && cd build
cmake ..
make
make install
```

