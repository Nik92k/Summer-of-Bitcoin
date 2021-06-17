
Summer of bitcoin Submission 

Table of content 

 •	Reasoning behind logic

 •	Tradeoffs 

Reasoning behind logic
 
Went with Fractional knapsack (greedy) approach to the problem statement 

 •	First made the CSV file readable to C++ language 

 •	Created a map of the transactions, key being Index of transaction

 •	Created a "set" of all transactions, with parameters, Ratio = fee/weight, and mapped key of the transaction as the second parameter. 

 •	Once obtained transaction with highest ratio->fee, checked if the parents of the transaction exist before jotting down the transaction-id.

 •	If all flags came in favor of the transaction, added the transaction to the final block. 


Complexity of Code O(n^3) 

Total weight of the final Block: 3999936 

Total fee earned by miner (objective): 4803570

Total transactions considered: 2668

References
//https://en.wikipedia.org/wiki/Knapsack_problem

//https://en.wikipedia.org/wiki/Topological_sorting
