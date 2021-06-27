import urllib.parse,urllib.request,urllib.error
import json
import csv
import pandas








url='https://api.covid19india.org/resources/resources.json'

	#print("Retrieving",
uh=urllib.request.urlopen(url)
print("Retrieving",url)
data=uh.read().decode()


js=json.loads(data)

#lestr=js['lastRefreshed']

with open('Testlab.csv', 'w', newline='') as csvfile:

	fieldnames=['state','city','nameoftheorganisation']
	writer=csv.DictWriter(csvfile,fieldnames=fieldnames,extrasaction='ignore')
	writer.writeheader() 


	for x in range(0,len(js['resources'])):
		#k=js[x]['state']	
		#for y in range(0,len(js[x]['districtData'])):
			#js[x]['districtData'][y]['state']=k;
			#writer.writerow(js[x]['districtData'][y])
		if(js['resources'][x]['category']=='CoVID-19 Testing Lab'):
			#print(js['resources'][x])
			writer.writerow(js['resources'][x])