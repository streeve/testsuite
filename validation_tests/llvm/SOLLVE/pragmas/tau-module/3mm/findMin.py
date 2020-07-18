import pandas
from sklearn import model_selection
from sklearn.linear_model import LogisticRegression

dataframe = pandas.read_csv("results.csv")
array = dataframe.values
x = array[:,-1]

print("Performance summary based on", len(array), "evaluations:")
print("Min: ", str( x.min() ), "s")
print("Max: ", str( x.max() ), "s")
print("Mean: ", str( x.mean() ), "s")
print("The best configurations (for the smallest time) of P0, P1, P2, P3, P4 and P5 is:\n")
print("P0     P1	P2 	P3 	P4    P5	execution time	     elapsed time\n")
mn = x.min()
for i in range(len(array)): 
   if x[i] == mn:
    print (array[i,:])
