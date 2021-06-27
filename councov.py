import urllib.request,urllib.parse,urllib.error
import json
import csv

url='https://api.covid19api.com/summary'
print("Retrieving "+url)
data=urllib.request.urlopen(url)
us=data.read().decode()


js=json.loads(us)

for x in range(0,len(js['Countries'])):
	p=int(js['Countries'][x]['TotalConfirmed'])-int(js['Countries'][x]['TotalDeaths'])-int(js['Countries'][x]['TotalRecovered'])
	js['Countries'][x]['Active']=p

js['Global']['Active']=int(js['Global']['TotalConfirmed'])-int(js['Global']['TotalDeaths'])-int(js['Global']['TotalRecovered'])
js['Global']['Country']='Total'
#list1=['NewConfirmed','TotalConfirmed','NewDeaths','TotalDeaths','NewRecovered','TotalRecovered','Date']
with open("Countries.csv",'w',newline='') as csvfile:
	fieldnames=['Country','TotalConfirmed','TotalDeaths','TotalRecovered','Active']
	writer=csv.DictWriter(csvfile,fieldnames=fieldnames,extrasaction='ignore')
	writer.writeheader()

	#print(js['Countries'][2]['NewConfirmeds'])
	for x in range(0,len(js['Countries'])):
		
		writer.writerow(js['Countries'][x])
	writer.writerow(js['Global'])	
		
		#writer.writerow()
        #x=int(js['Countries'][x]['TotalConfirmed'])-int(js['Countries'][x]['TotalDeaths'])
    	#print(x)
    	    	#write.write({'Active':})    
	
		

    #js['data']['total']['state']='Total'    
    #writer.writerow(js['data']['total'])