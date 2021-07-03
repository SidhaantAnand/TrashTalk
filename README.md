# Problem Formulation - Q4
- *Problem*: Minimize the cost for the vehicle routing problem with number of cities as 39, one depot and number of vehicles as 6
- *State Representation*: State representation used here will be a list of size m where each element is a list in itself and displays the order of the visited cities for a particular vehicle. For example: [[a1,a2],[b1,b2,b3]] means that vehicle a visited depot->a1->a2->depot and vehicle b visited depot->b1->b2->b3->depot.
- *State Space*: Any combination of the state representation such that no city is repeated and union of all sublists covers all the cities
- *cost function* : 
	- Cost function returns the bottleneck path with the highest duration, thus it is defined as the maximum of the total duration of the path undertaken by each truck. 
	- Total duration for the path traversed by a truck is defined as the euclidean sum of distances/70 + total service time, where 70 is the average speed of the trucks
	- For state [[a1,a2],[b1,b2,b3]], we can say
		- duration for truck1 = ( euc(depot,a1) + euc(a1,a2) + euc(a2,depot) )/70 + serv(a1) + serv(a2)
		- duration for truck2 = ( euc(depot,b1) + euc(b1,b2) + euc(b2,b3) + euc(b3,depot) )/70 + serv(b1) + serv(b2) + serv(b3)
		- Cost function would return the max(duration for truck1, duration for truck2)
	- Note: In the above example, serv(x) returns the service time for city x, euc(x,y) returns the euclidean distance between city x and city y
- *neighbouring function* : The neighbouring function can be defined in 3 ways
	- Swap cities within a vehicle's path. For eg [[a1,a2],[b1,b2,b3]] -> [[a1,a2],[b1,b3,b2]]
	- Swap cities between two vehicle's paths: For eg [[a1,a2],[b1,b2,b3]] -> [[b1,a2],[a1,b2,b3]]
	- Remove city from the end of one path and append into another: For eg [[a1,a2],[b1,b2,b3]] -> [[a1,a2,b3],[b1,b2]]
- *initial state* : Shuffle all cities and divide them into m sublists of approximately equal lengths

# Algorithm 
optimal_paths <- initial state <br /> 

current_paths <- initial state <br /> 

Loop while current_temperature > minimum_temperature <br /> 

&nbsp; Loop for a predefined number of iterations <br /> 

&nbsp;&nbsp;  Define new_paths using the above defined neighbouring function <br /> 

 &nbsp;&nbsp; Get cost using the cost function <br /> 
 
 &nbsp;&nbsp; If the cost of new_paths is lesser than cost of current_paths  then current_paths  is updated to new_paths <br /> 
 
 &nbsp;&nbsp; Else, a random number is generated and if it is less than exp(-difference in cost/current_temperature) then current_paths  is updated to new_paths <br /> 
 
 &nbsp; update current_temperature <- current_temperature - alpha <br /> 


# Complexity Analysis
- Time and Space complexity is dependent on the input parameters like the following
	- initial temperature,alpha,min temperature : These determine the number of iterations the outer loop of above described SA algorithm take. They decide the number of iterations after which the temperature drops below the minimum temperature (say this number is denoted by t)
	- max iterations per  temp: These determine the number of iterations the inner loop of above described SA algorithm take. This is predetermined number of iterations for every temperature (say this number is denoted by i)
	- Initial state - it is a 2D space structure, does not impact time complexity
- Time Complexity:
	- Outer loop has t iterations
	- Inner loop has i iterations
	- The rest of the operations inside the nested loops take an average O(1) time complexity.
	- Thus the timecomplexity of the program is O(t*i) 
- Space Complexity:
	- Key data structures used in this program are as follows:
	- A 2D list to store the current path. It has number of rows as m and a variable number of columns such that number of elements in the 2D list is n=number of cities. Space complexity - O(n)
	- A Similar 2D list is also used to store the optimal path
	- A 1D list to store all costs - Since a cost is stored at all iterations, the size of this list will be t*i 
	- Thus the Space complexity of this algorithm is O(t*i). This is only because the costs at each step where stored because of the graphing requirment of this question. Otherwise the space complexity is O(n) 

# Total Duration shouldnt exceed T

There are two ways of handling this
 - Define feasibilty and apply death penalty: In this case we will define a feasible candidate or state to be such that its cost function returns a total duration less than T. In case the value is greater than T, the state or candidate is deemed infeasible and ignored. To implement this, we can make changes to our neighbour function as follows:
 
return_neighbours(current_state,T) {

&nbsp; &nbsp; neighbour = get_neighbours(current_state)

&nbsp; &nbsp; while (cost(neighbour) > T) {

&nbsp; &nbsp; &nbsp; &nbsp; neighbour = get_neighbours(current_state)

&nbsp; &nbsp; }

&nbsp; &nbsp; return neighbour

 - Update the cost function to include a penalty: This can be done to discourage the selecting of solutions for which total duration is greater than T by adding a penalty. One ways this can be done is as follows
	 - Update Cost function from max(all truck durations) to max(durations) > T ? max(durations) + penalty : max(durations). Thus what this means is that if the total duration is greater than T then we would add a penalty to the cost such that the delta c becomes very high and the probability of the candidate being selected becomes marginal
