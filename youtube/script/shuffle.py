import random
workfile = "current.txt"
outfile = "keywords_youtube_shuffled.txt"
with open(workfile, 'r', encoding='utf-8') as f:
    read_data = f.read()
f.close()
content_list = read_data.split("\n")
#print(content_list)

ignore_list = ['apocaliptoLIB_booklist.txt',
'file.pdf',
'ideas_apocaliptoLIB.txt',
'map.txt',
'The_Charcoal_Foundry_by_David_J.._Gingery_(z-lib.org)[',
'youtube.txt',
'books.txt',
'.~lock.',
'f.txt']
random.shuffle(content_list)
with open(outfile, 'w', encoding='utf-8') as f2:
    f2.write('\r'.join(content_list))
    
f2.close()

print(content_list)
