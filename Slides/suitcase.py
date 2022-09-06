##Greedy Naive Solution

##Taking input for number of items
n = int(input('Enter number of items: '))

##Taking empty list for weights and values
weights = []
values = []

# Addind weights and values from user
print("Enter weights: ")
for i in range(0, n):
    ele = int(input())
    weights.append(ele) # adding the element

print("Enter values: ")
for i in range(0, n):
    ele = int(input())
    values.append(ele) # adding the element

#Taking input for Max Capacity
leftWeight = int(input('Enter max capacity: '))

def suitcase(leftWeight):
    curBest = 0;
    #weights = (5,4,2)
    #values = (150,100,10)
    
    for weight, value in zip(weights, values):
        if leftWeight >= weight :
            curBest = max(curBest , suitcase(leftWeight-weight) + value)
    return curBest

print(suitcase(leftWeight))