import urllib.parse,urllib.request,urllib.error
import json
import csv

url='https://api.rootnet.in/covid19-in/unofficial/covid19india.org/statewise'
print("Retrieving",url)
uh=urllib.request.urlopen(url)
data=uh.read().decode()

print(type(data))

js=json.loads(data)

lestr=js['lastRefreshed']
print(lestr)
#ilen=lestr+'.csv'
with open('Sample.csv', 'w', newline='') as csvfile:

	fieldnames=['state','confirmed','recovered','deaths','active']
	writer=csv.DictWriter(csvfile,fieldnames=fieldnames)
	writer.writeheader() 




	for x in range(0,len(js['data']['statewise'])):
		writer.writerow(js['data']['statewise'][x])

	js['data']['total']['state']='Total'	
	writer.writerow(js['data']['total'])
