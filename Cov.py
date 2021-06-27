import urllib.parse,urllib.request,urllib.error
import json
import csv
import pandas
import matplotlib
import matplotlib.pyplot as plt
from PIL import Image

matplotlib.use('Agg')


url='https://api.rootnet.in/covid19-in/unofficial/covid19india.org/statewise'
print("Retrieving",url)
uh=urllib.request.urlopen(url)
data=uh.read().decode()



js=json.loads(data)

lestr=js['lastRefreshed']

with open('Sample.csv', 'w', newline='') as csvfile:

    fieldnames=['state','confirmed','recovered','deaths','active']
    writer=csv.DictWriter(csvfile,fieldnames=fieldnames)
    writer.writeheader() 




    for x in range(0,len(js['data']['statewise'])):
        writer.writerow(js['data']['statewise'][x])

    js['data']['total']['state']='Total'    
    writer.writerow(js['data']['total'])


fig1,fig2=plt.subplots()

df=pandas.read_csv("Sample.csv")
df['state'].replace({'Dadra and Nagar Haveli and Daman and Diu':'Dadra and Nagar Haveli','Andaman and Nicobar Islands':'Andaman and Nicobar'},inplace=True)
#df.columns(['sate','confirmed','recoverd','deaths','active'])
#df.set_index('state',inplace=True)



plt.xlabel('States')
plt.ylabel(' No of Confirmed cases')
plt.title('Confirmed cases comparison of different states ')
plt.xticks(rotation=90)
plt.subplots_adjust(bottom=0.43)
plt.bar(df['state'],df['confirmed'],label=" From Data Source")
plt.legend()

plt.savefig('Confirmedp.png')


img1=Image.open('Confirmedp.png')
img1 = img1.convert("RGB").save('Confirmed.jpg')

plt.close()


plt.xlabel('States')
plt.ylabel('No of Cases Recovered')
plt.title('Recovered cases comparison of different states ')
plt.xticks(rotation=90)
plt.subplots_adjust(bottom=0.43)
plt.bar(df['state'],df['recovered'],label="From Data Source")
plt.legend()
plt.savefig('Recoveredp.png')

img1=Image.open('Recoveredp.png')
img1 = img1.convert("RGB").save('Recovered.jpg')

plt.close()



plt.xlabel('States')
plt.ylabel('No of Death Cases')
plt.title('Death Cases comparison of different states ')
plt.xticks(rotation=90)
plt.subplots_adjust(bottom=0.43)
plt.bar(df['state'],df['deaths'],label="From Data Source")
plt.legend()
plt.savefig('Deathsp.png')
img1=Image.open('Deathsp.png')
img1 = img1.convert("RGB").save('Deaths.jpg')
plt.close()

plt.xlabel('States')
plt.ylabel('No of Active Cases')
plt.title('Active Cases comparison of different states ')
plt.xticks(rotation=90)
plt.subplots_adjust(bottom=0.43)
plt.bar(df['state'],df['active'],label="From Data Source")
plt.legend()
plt.savefig('Activep.png')
img1=Image.open('Activep.png')
img1 = img1.convert("RGB").save('Active.jpg')
plt.close()


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
plt.savefig('overallp.png')
img1=Image.open('overallp.png')
img1 = img1.convert("RGB").save('Overall.jpg')
plt.close()
#plt.show()

#plt.bar(x,y, label='Loaded from file!')
#plt.xlabel('x')
#plt.ylabel('y')
#plt.title('Interesting Graph\nCheck it out')
#plt.legend()
#plt.show()