import matplotlib.pyplot as plt
import pandas
import sys

df=pandas.read_csv("Sample.csv")
df['state'].replace({'Dadra and Nagar Haveli and Daman and Diu':'Dadra and Nagar Haveli','Andaman and Nicobar Islands':'Andaman and Nicobar'},inplace=True)

#df.columns(['sate','confirmed','recoverd','deaths','active'])
#df.set_index('state',inplace=True)
def __confirm__():
	

	plt.xlabel('States')
	plt.ylabel(' No of Confirmed cases')
	plt.title('Confirmed cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.43)
	plt.bar(df['state'],df['confirmed'],label=" From Data Source")
	plt.legend()
	plt.show()

def __active__():
	plt.xlabel('States')
	plt.ylabel('No of Active Cases')
	plt.title('Active Cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.43)
	plt.bar(df['state'],df['active'],label="From Data Source")
	plt.legend()
	plt.show()
	return
def __recover__():
	plt.xlabel('States')
	plt.ylabel('No of Cases Recovered')
	plt.title('Recovered cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.43)
	plt.bar(df['state'],df['recovered'],label="From Data Source")
	plt.legend()
	plt.show()
	return

def __overall__():
	
	plt.xlabel('States')
	plt.ylabel('No of Cases')
	plt.title('Various Cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.43)
	plt.bar(df['state'],df['confirmed'],label=" Confirmed")
	plt.bar(df['state'],df['recovered'],label="Recovered")
	plt.bar(df['state'],df['deaths'],label="Deaths")
	plt.bar(df['state'],df['active'],label="Active")
	plt.legend()
	plt.show()
	return

def __deaths__():
	

	plt.xlabel('States')
	plt.ylabel('No of Death Cases')
	plt.title('Death Cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.43)
	plt.bar(df['state'],df['deaths'],label="From Data Source")
	plt.legend()
	plt.show()
	return



def main():
	choice=sys.argv[1]
	{
		'o':lambda:__overall__(),
		'r':lambda:__recover__(),
		'a':lambda:__active__(),
		'd':lambda:__deaths__(),
		'c':lambda:__confirm__(),
		
	}.get(choice)()

if __name__=='__main__':
	main()
#opt=sys.argv[1]
#print(opt)
#Call.get(opt)
#switcher.get(,-1)
