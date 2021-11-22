import puzzle 
import sys
import searches

t=puzzle.TilePuzzle(int(sys.argv[1]))
t.permute(int(sys.argv[2]))
t.printPuzzle()
s=searches.Search(t)

print (f"Considering Best First: {s.bestFirst()}")
print (f"Considering Iterative Deepening Search: {s.iterativeDeepening()}") 
print (f"Considering Greedy 1 Search: {s.greedy(0)}") 
print (f"Considering Greedy 2 Search: {s.greedy(1)}") 
print (f"Considering A* 1 Search: {s.aSearch(0)}") 
print (f"Considering A* 2 Search: {s.aSearch(1)}") 