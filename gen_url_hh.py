import subprocess
import random

def copy2clip(txt):
    cmd='echo '+'"'+txt.strip()+'"'+'|clip'
    return subprocess.check_call(cmd, shell=True)

page_number =  random.randint(1,10)   
url = "https://hh.ru/search/vacancy?resume=170669dfff0865af3b0039ed1f6b6d3752674b&page={}".format(page_number)  
print(url)
copy2clip(url)