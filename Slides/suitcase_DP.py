##Greedy DP Solution
##For taking 10000 as input we set the recursion limit to higher number
import sys
sys.setrecursionlimit(10001)
# print(sys.getrecursionlimit())

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

#Taking empty list for ans and initializing it ti -1
ans = []
for i in range(leftWeight+1):
    ans.append(-1)

def suitcase_DP(leftWeight):
    curBest = 0;
    if ans[leftWeight] != -1:   ##added for DP
        return ans[leftWeight]
    for weight, value in zip(weights, values):
        if leftWeight >= weight :
            curBest = max(curBest , suitcase_DP(leftWeight-weight) + value)
    ans[leftWeight] = curBest
    return ans[leftWeight]      ##added for DP

print(suitcase_DP(leftWeight))