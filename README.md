# Getting Started

**Language:** C

# Requirements

- gcc 9.3.0 or later
- make

# Compilation Instructions

Compilation can be done using the provided makefile and running
standard `make` command on the provided `makefile` or inspecting the
`makefile` for which compiler flags were used.

# Execution Instructions

The included executable was compiled on Ubuntu 20.04.2 LTS using
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0. The program accepts three command-line
arguments: the data file name, the page size, and the number of frames to
be used by the algorithms.

To run, call using

```
./vmemman "Data file-part2.dat" 512 4
./vmemman "Data file-part2.dat" 1024 4
./vmemman "Data file-part2.dat" 2048 4

./vmemman "Data file-part2.dat" 512 8
./vmemman "Data file-part2.dat" 1024 8
./vmemman "Data file-part2.dat" 2048 8

./vmemman "Data file-part2.dat" 512 12
./vmemman "Data file-part2.dat" 1024 12
./vmemman "Data file-part2.dat" 2048 12
```

# Pseudocode

## Optimal

```
if buffer not full:
  add new memory location to buffer.
  increment miss count
else if memory location in buffer:
  increment hit count
else:
  for each location in buffer:
    perform "look ahead" operation:
      look for next occurrence of location in remainder of input array
      if found, return how many entries ahead the next occurrence is,
      if not found, return INT_MAX.
    for each lookahead value:
      determine whether value is maximum in array
    replace the maximum with new value
    increment miss count

```

## First In First Out

```
if value already in buffer:
  increment hit count
else
  add value to buffer using a circular buffer method.
```

## Recently Used

```
if value already in array:
  reset use counter for value
  increment hit count
else:
  if buffer full:
    determine value to be replaced:
      for each use counter:
        determine if value is maximum (for LRU) or minimum (for MRU)
        return the index of the value
  else:
    add item to buffer at open position
    set the use counter to 0
    increment number of items in buffer
increment use counter for all items in buffer
```

## Main Program

```
open input file from command line argument
set page size from command line argument
set number of frames from command line argument.

for each line in file
  read line as integer
  floor divide by page size to get page number

for each algorithm
take page number
follow algorithm procedure to look for page in cache

    if page in cache
        move page in cache according to algorithm
    else
        increment page fault counter
        add page to cache according to algorithm

close file
print results
```

# Results

```
./vmemman "Data file-part2.dat" 512 4
Page Size    # of Pages    Algorithm    Fault Percentage
      512             4      Optimal              77.57%
      512             4         FIFO              80.37%
      512             4          LRU              80.00%
      512             4          MRU              93.07%

./vmemman "Data file-part2.dat" 1024 4
Page Size    # of Pages    Algorithm    Fault Percentage
     1024             4      Optimal              60.40%
     1024             4         FIFO              61.40%
     1024             4          LRU              60.47%
     1024             4          MRU              86.03%

./vmemman "Data file-part2.dat" 2048 4
Page Size    # of Pages    Algorithm    Fault Percentage
     2048             4      Optimal              24.93%
     2048             4         FIFO              26.47%
     2048             4          LRU              25.97%
     2048             4          MRU              74.70%


./vmemman "Data file-part2.dat" 512 8
Page Size    # of Pages    Algorithm    Fault Percentage
      512             8      Optimal              57.27%
      512             8         FIFO              61.00%
      512             8          LRU              60.10%
      512             8          MRU              90.93%

./vmemman "Data file-part2.dat" 1024 8
Page Size    # of Pages    Algorithm    Fault Percentage
     1024             8      Optimal              21.20%
     1024             8         FIFO              23.60%
     1024             8          LRU              22.80%
     1024             8          MRU              82.43%

./vmemman "Data file-part2.dat" 2048 8
Page Size    # of Pages    Algorithm    Fault Percentage
     2048             8      Optimal               1.70%
     2048             8         FIFO               1.87%
     2048             8          LRU               1.87%
     2048             8          MRU              64.67%


./vmemman "Data file-part2.dat" 512 12
Page Size    # of Pages    Algorithm    Fault Percentage
      512            12      Optimal              38.97%
      512            12         FIFO              42.97%
      512            12          LRU              42.07%
      512            12          MRU              88.70%

./vmemman "Data file-part2.dat" 1024 12
Page Size    # of Pages    Algorithm    Fault Percentage
     1024            12      Optimal               3.37%
     1024            12         FIFO               3.53%
     1024            12          LRU               3.53%
     1024            12          MRU              77.33%

./vmemman "Data file-part2.dat" 2048 12
Page Size    # of Pages    Algorithm    Fault Percentage
     2048            12      Optimal               1.60%
     2048            12         FIFO               1.80%
     2048            12          LRU               1.80%
     2048            12          MRU              58.60%
```

# Conclusions

- The page size has the greatest impact on reducing the page fault rate

- The best combination is large pages and high frame count

- The Optimal algorithm is used as a baseline for best possible performance of an
  a combination of page size and number of pages, since a realistic implementation
  is not achievable

- The performance of each algorithm is fairly consistent:

  1. LRU has the lowest fault percentage
  2. FIFO has comparable performance with LRU

     _A notable exception is running with a page size of 1024 and 6 pages, where FIFO performs better than LRU._

  3. MRU is consistently worse than all others

- LRU and FIFO have consistently similar performance

- FIFO is easier to implement and requires less overhead, making it a good choice.
