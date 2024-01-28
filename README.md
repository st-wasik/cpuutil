### cpuutil
```
cpuutil - print CPU utilization percentage over time

Example: cpuutil [-AChs]

Parameters:
-A      do not calculate and do not print average utilization
-C      do not print current utilization
-h      print this message and exit
-s      sleep interval in seconds, default 1.0
```

#### Example output
```
   ALL   ALL   CPU00 CPU00   CPU01 CPU01   CPU02 CPU02   CPU03 CPU03
  CURR   AVG    CURR   AVG    CURR   AVG    CURR   AVG    CURR   AVG         STEP       TIME
  38.2  38.2    48.5  48.5    14.3  14.3    35.6  35.6    26.7  26.7            1       1.00
  24.1  31.1    16.7  32.6    33.0  23.6    41.6  38.6    25.5  26.1            2       2.00
  12.2  24.8    14.7  26.6    13.7  20.3     8.2  28.5    12.9  21.7            3       3.00
  17.7  23.0    12.2  23.0    33.0  23.5    32.0  29.4    12.5  19.4            4       4.00
  10.9  20.6    18.9  22.2    16.8  22.2     7.8  25.0    13.3  18.2            5       5.00
  17.2  20.0    14.9  21.0    41.7  25.4    23.8  24.8    14.6  17.6            6       6.00
   5.9  18.0     9.9  19.4     7.8  22.9    10.2  22.7     5.9  15.9            7       7.00
   5.5  16.5    10.1  18.2     8.7  21.1     5.0  20.5     4.0  14.4            8       8.00
  18.8  16.7    26.0  19.1    21.4  21.2    18.2  20.3    19.2  15.0            9       9.00
  10.8  16.1     7.4  17.9    16.0  20.6    16.3  19.9     8.0  14.3           10      10.00
   9.3  15.5     9.1  17.1    16.7  20.3    15.7  19.5     6.1  13.5           11      11.00
  21.0  16.0    18.2  17.2    18.0  20.1    23.0  19.8    17.6  13.9           12      12.00
   9.2  15.4    21.8  17.6    17.1  19.9     8.5  18.9     9.1  13.5           13      13.00
  13.1  15.3    23.5  18.0    16.0  19.6    11.0  18.3    11.0  13.3           14      14.00
  10.0  14.9    10.0  17.5    13.6  19.2     6.0  17.5    16.8  13.5           15      15.00
```
#### Build
`make`

#### Run
`./cpuutil`