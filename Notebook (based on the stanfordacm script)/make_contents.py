import os
import shutil
import unidecode


def create_code_folder(directory):
    path = os.path.join(directory, 'code')
    if os.path.exists(path):
        shutil.rmtree(path)
    os.mkdir(path)


def normalize(s):
    return unidecode.unidecode(s)


def check(name):
    print(name)
    while name[-1] != '.':
        name = name[:-1]
    name = name[:-1]
    name = name.replace('_', ' ')
    return name

def dale(directory, foldername, id, path):
   curr_dir = directory + foldername

   if os.path.isdir(curr_dir):
    f.write('[' + path + ']\n')
    
    for filename in os.listdir(curr_dir):
        if not '.' in filename:
            continue

        name = check(filename)
        f.write( id + filename + '\t' + name + '\n')

        with open('code/' + id + filename, 'x') as f2:
            with open(curr_dir + '/' + filename) as f3:
                lines = f3.readlines()
                for l in lines:
                    f2.write(normalize(l))
    
    for filename in os.listdir(curr_dir):
        if not '.' in filename:
            dale(curr_dir + '/', filename, id + '_' + foldername + '_', path + '/' + filename)

    f.write('\n')

def write_folders_content(f):
    directory = os.getcwd()
    create_code_folder(directory)

    while directory[-1] != '/':
        directory = directory[:-1]

    banned = ['Notebook (based on the stanfordacm script)',
              '.git', 'Problem Solving']

    for foldername in os.listdir(directory):
        if foldername in banned:
            continue

        dale(directory, foldername, '', foldername)


def write_info(f):
    f.write('# Any line followed by a \'#\' character is ignored\n')
    f.write('# Section headings must be in square brackets\n')
    f.write('# Subsections within a section should follow the format:\n')
    f.write(
        '# [filename within code directory][tab character \\t][subsection title]\n')
    f.write('\n')


if __name__ == "__main__":
    f = open('contents.txt', 'w')
    write_info(f)
    write_folders_content(f)
    f.close()
