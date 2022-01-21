import random
workfile = "C:\\Users\\Vova\\OneDrive\\Desktop\\keywords_youtube.txt"
outfile = "C:\\Users\\Vova\\OneDrive\\Desktop\\keywords_youtube_shuffled.txt"
with open(workfile, 'r', encoding='utf-8') as f:
    read_data = f.read()
f.close()
content_list = read_data.split("\n")
random.shuffle(content_list)
with open(outfile, 'w', encoding='utf-8') as f2:
    f2.write('\r'.join(content_list))
    
f2.close()

print(content_list)
