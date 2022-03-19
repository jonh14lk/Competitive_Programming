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
    while name[-1] != '.':
        name = name[:-1]
    name = name[:-1]
    name = name.replace('_', ' ')
    return name


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

        curr_dir = directory + foldername

        if os.path.isdir(curr_dir):
            f.write('[' + foldername + ']\n')

            for filename in os.listdir(curr_dir):
                name = check(filename)
                f.write(filename + '\t' + name + '\n')

                with open('code/' + filename, 'x') as f2:
                    with open(curr_dir + '/' + filename) as f3:
                        lines = f3.readlines()
                        for l in lines:
                            f2.write(normalize(l))

            f.write('\n')


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
