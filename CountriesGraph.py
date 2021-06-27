import matplotlib.pyplot as plt
import pandas
import sys

df=pandas.read_csv("Countries.csv",engine='python')
#df['state'].replace({'Dadra and Nagar Haveli and Daman and Diu':'Dadra and Nagar Haveli','Andaman and Nicobar Islands':'Andaman and Nicobar'},inplace=True)


def __confirm__():
	
	#plt.figure(1)
	plt.xlabel('Countries')
	plt.ylabel(' No of Confirmed cases')
	plt.title('Confirmed cases comparison of different Countries ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.33,left=0.04,right=0.99,top=0.97)
	plt.bar(df['Country'],df['TotalConfirmed'],label=" From Data Source")
	plt.legend()
	figManager = plt.get_current_fig_manager()
	figManager.window.state('zoomed')
	plt.show()

def __active__():
	plt.xlabel('Countries')
	plt.ylabel('No of Active Cases')
	plt.title('Active Cases comparison of different Countries ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.33,left=0.04,right=0.99,top=0.97)
	plt.bar(df['Country'],df['Active'],label="From Data Source")
	plt.legend()
	figManager = plt.get_current_fig_manager()
	figManager.window.state('zoomed')
	plt.show()
	return
def __recover__():
	plt.xlabel('Countries')
	plt.ylabel('No of Cases Recovered')
	plt.title('Recovered cases comparison of different Countries ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.33,left=0.04,right=0.99,top=0.97)
	plt.bar(df['Country'],df['TotalRecovered'],label="From Data Source")
	plt.legend()
	figManager = plt.get_current_fig_manager()
	figManager.window.state('zoomed')
	plt.show()
	return

def __overall__():
	
	plt.xlabel('States')
	plt.ylabel('No of Cases')
	plt.title('Various Cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.33,left=0.04,right=0.99,top=0.97)
	plt.bar(df['Country'],df['TotalConfirmed'],label=" Confirmed")
	plt.bar(df['Country'],df['TotalRecovered'],label="Recovered")
	plt.bar(df['Country'],df['TotalDeaths'],label="Deaths")
	plt.bar(df['Country'],df['Active'],label="Active")
	plt.legend()
	figManager = plt.get_current_fig_manager()
	figManager.window.state('zoomed')
	plt.show()
	return

def __deaths__():
	

	plt.xlabel('States')
	plt.ylabel('No of Death Cases')
	plt.title('Death Cases comparison of different states ')
	plt.xticks(rotation=90)
	plt.subplots_adjust(bottom=0.33,left=0.04,right=0.99,top=0.97)
	plt.bar(df['Country'],df['TotalDeaths'],label="From Data Source")
	plt.legend()
	figManager = plt.get_current_fig_manager()
	figManager.window.state('zoomed')
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
#opt=sys.argv[1A]
#print(opt)
#Call.get(opt)
#switcher.get(,-1)
