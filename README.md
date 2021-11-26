# 8-Puzzle Solver using IDS and A\* Search

This program is a C++ implementation to the 8-Puzzle problem which uses A\* Search
and Iterative Deepening Search (**_IDS_**). IDS is a blind search strategy whilst A\* is an
informed search strategy which uses a heuristic function.

A given goal state is declared where the following input states should reach the said
goal using both search strategies.The program returns the number of nodes expanded, cost
of the solution path, the path taken from the initial state to the goal state, and
the runtime of the program in milliseconds.

## About the 8-Puzzle Problem

The 8-Puzzle problem is being played on a 3-by-3 grid with 8 square blocks labeled 1
through 8 and a blank square. The goal is to rearrange the blocks so that they are in
order. In this iteration of the problem, there are different initial states for the puzzle to
start from and there is a given goal state for the puzzle to achieve.

A puzzle configuration is considered as solvable, if there exists a sequence of actions,
which leads to the goal configuration. This holds true for exactly half of all possible puzzle
configurations as stated on this [paper](https://mediatum.ub.tum.de/doc/1283911/1283911.pdf) and from MathWorld's [explanation](https://mathworld.wolfram.com/15Puzzle.html) on n-puzzles.

## Test States

These are the input states used during our execution of the program. The preferred initial
state can be any desired input as long as it follows the [rules](https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/) for initial state selection.

> In the source code, "0" is used as the representation for the blank tile.

**INITIAL STATES**:

<table>
  <tr>
    <td>
      <table>
        <caption>EASY</caption>
        <tr>
          <td>1</td>
          <td>3</td>
          <td>4</td>
        </tr>
        <tr>
          <td>8</td>
          <td>6</td>
          <td>2</td>
        </tr>
        <tr>
          <td>7</td>
          <td> </td>
          <td>5</td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <caption>MEDIUM</caption>
        <tr>
          <td>2</td>
          <td>8</td>
          <td>1</td>
        </tr>
        <tr>
          <td> </td>
          <td>4</td>
          <td>3</td>
        </tr>
        <tr>
          <td>7</td>
          <td>6</td>
          <td>5</td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <caption>HARD</caption>
        <tr>
          <td>2</td>
          <td>8</td>
          <td>1</td>
        </tr>
        <tr>
          <td>4</td>
          <td>6</td>
          <td>3</td>
        </tr>
        <tr>
          <td>7</td>
          <td>5</td>
          <td> </td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <caption>WORST</caption>
        <tr>
          <td>5</td>
          <td>6</td>
          <td>7</td>
        </tr>
        <tr>
          <td>4</td>
          <td> </td>
          <td>8</td>
        </tr>
        <tr>
          <td>3</td>
          <td>2</td>
          <td>1</td>
        </tr>
      </table>
    </td>
    <td>
    <table>
        <caption>PREFERRED INITIAL 
          STATE</caption>
        <tr>
          <td>3</td>
          <td>6</td>
          <td>4</td>
        </tr>
        <tr>
          <td> </td>
          <td>1</td>
          <td>2</td>
        </tr>
        <tr>
          <td>8</td>
          <td>7</td>
          <td>5</td>
        </tr>
      </table>
    </td>
  </tr>
</table>

**GOAL STATE**:

<table>
  <tr>
    <td>1</td>
    <td>2</td>
    <td>3</td>
  </tr>
  <tr>
    <td>8</td>
    <td> </td>
    <td>4</td>
  </tr>
  <tr>
    <td>7</td>
    <td>6</td>
    <td>5</td>
  </tr>
</table>

### Notes

The result proves that A* Search is faster compared to IDS which is true with the stated
time complexities, where A* time complexity is exponential to the heuristics given whilst
IDS time complexity is O(bd ). On given occasions, A\* gives the most optimized solution
path compared to IDS.

The only drawback to A\* Search is its memory usage(**_O(|V|) = O(b^d)_**). Meanwhile IDS' memory
usage depends on the depth of the goal node(**_O(d)_**).

> This test is executed on a 64-bit Windows 10 OS with an AMD Ryzen 5 3600
> processor and 16 GB of RAM set at 3200hz
> Coded and documented by @Lester105, @nibiru-rada, @raffittee, and @luminacht for a class
> in Artificial Intelligence.
