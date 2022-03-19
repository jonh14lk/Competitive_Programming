# This script does the following:
# 1 - Run a code with all inputs files from a folder
# 2 - Compare the output for each test case with the answer
import os

code = "a.cpp" # Path to your code
input_folder = "input" # Path to folder which the input files are
output_folder = "output" # Path to folder which the output files are
input_prefix = "L_" # prefix of all input files names
output_prefix = "L_" # prefix of all input files names
tests = 56 # Number of test cases

def compile_code():
    os.system('g++ ' + code + ' -o code -O2')

def get_ans(output):
    out = open(output, "r")
    ret = out.read()
    out.close()
    return ret

def get_code_output(input):
    output = os.popen('./code <' + input).read()
    return output

def main():
    compile_code()
    # tests indexed from 1
    for i in range (1, tests + 1):
        ans = get_ans(output_folder + '/' + output_prefix + str(i))
        code_output = get_code_output(input_folder + '/' + input_prefix + str(i))
        print('Case' + str(i) + ': ')
        if ans == code_output:
            print('ACCEPTED')
        else : 
            print('FAILED\n')
            print('ANSWER:')
            print(ans)
            print('\nCODE OUTPUT:')
            print(code_output)
        print()

if __name__ == '__main__':
    main()