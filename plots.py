import numpy as np
import matplotlib.pyplot as plt

files = ["sc","searchc","su"]

def make_plots (filename):
	for file in files:
		if file == "sc":
			with open("sc_"+filename+".txt","r+") as f:
			    content = f.readlines()

			content = [x.strip() for x in content]
			content = map(int, content)

			with open("records_"+filename+".txt","r+") as f:
			    records = f.readlines()

			records = [x.strip() for x in records]

			x = records
			y = content

			plt.plot(x,y, lw=0.2)
			plt.title("Splitting Cost")
			plt.xlabel("Records")
			plt.ylabel("Cost")
			plt.xticks(range(0,100000,10000))
			plt.savefig("linear_splitting_cost_" +filename_+".png")

		elif file=="searchc":
			with open("searchc_"+filename+".txt","r+") as f:
			    content = f.readlines()

			content = [x.strip() for x in content] 

			x = range(0,20)
			y = content

			plt.plot(x,y)
			plt.title("Search Cost")
			plt.xlabel("Records")
			plt.ylabel("Cost")
			plt.savefig("linear_search_cost_" +filename_+".png")
		else:
			with open("su_"+filename+".txt","r+") as f:
			    content = f.readlines()

			content = [x.strip() for x in content] 

			x = range(0,100000)
			y = content

			plt.plot(x,y)
			plt.title("Space Utilization")
			plt.xlabel("Records")
			plt.ylabel("Cost")
			plt.savefig("linear_space_utilization_" +filename_+".png")


make_plots("db_a")
make_plots("db_b")


