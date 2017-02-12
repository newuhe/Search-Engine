# encoding=utf-8
import re
import jieba  #分词库
from bs4 import BeautifulSoup
import urllib.request


#链接获取函数
def get_links(url):
    response = urllib.request.urlopen(url,timeout=10)
    html = response.read()
    soup = BeautifulSoup(html)
    urls=[]
    for link in soup.find_all('a'): 
        url=link.get('href')
        if url is None:
            continue        
        if  'pdf' in url:
            return urls
        if 'http' not in url:
            if url=='/':
                print('already in')
            elif url=='#':
                print('already in')
            else:
                urls.append('http://stuex.nju.edu.cn'+url)
                print('http://stuex.nju.edu.cn'+url)
    return urls
  

  
seed_url='http://stuex.nju.edu.cn'         #首页地址
response = urllib.request.urlopen(seed_url)
html = response.read()
soup = BeautifulSoup(html)	
crawl=[seed_url]
seen=set(crawl)              #链接存放集合
while crawl: 
    url=crawl.pop()
    urls=get_links(url)
    if len(urls)==0:
        break
    for link in urls:
       if link not in seen:
            seen.add(link)
            crawl.append(link)

#主网页地址爬取
f=open('links.txt','a',encoding='gb18030')
for link in seen:
    f.write(link+'\n')
f.close()

#主网页内的所有链接爬取
i=0
for link in seen:
    if('void') in link:
        continue
    f=open(str(i)+'.txt','a',encoding='gb18030')
    i=i+1
    f.write(link+'\n\n\n')
    response = urllib.request.urlopen(link)
    html = response.read()
    soup = BeautifulSoup(html)	
    for lin in soup.find_all('a'): 
        url1=lin.get('href')
        if url1 is None:
            continue
        if 'admin' in url1:
            print('admin')
        if  'pdf' in url1:
            print('pdf')       
        if 'http' not in url1:   #排除重复链接
            if url1=='/':
                f.write('http://stuex.nju.edu.cn'+'\n')       
            elif url1=='#':
                f.write(link+'\n')       
            else:
                f.write('http://stuex.nju.edu.cn'+url1+'\n')       
                
########网页文字内容爬取#########         
    s=soup.text
    blank_line=re.compile('\n+')  #数据清洗
    s=blank_line.sub('',s)  
    blank_line_l=re.compile('\n')  
    s=blank_line_l.sub('',s)  
    blank_kon=re.compile('\t')  
    s=blank_kon.sub('',s)  
    blank_one=re.compile('\r\n')  
    s=blank_one.sub('',s)  
    blank_two=re.compile('\r')  
    s=blank_two.sub('',s)  
    blank_three=re.compile(' ')  
    s=blank_three.sub('',s)
    seg_list = jieba.cut_for_search(s)  # 搜索引擎模式
    ss="  ".join(seg_list)
    f.write(ss)
    f.close()    

