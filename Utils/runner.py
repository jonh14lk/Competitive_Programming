import os

naive = "brute.cpp"
code = "d.cpp"
generator = "g.cpp"

def compile_codes():
    os.system('g++ ' + generator + ' -o generator')
    os.system('g++ ' + naive + ' -o naive')
    os.system('g++ ' + code + ' -o code')

def generate_case():
    os.system('./generator > in');

def get_naive_output():
    output = os.popen('./naive <in').read()
    return output

def get_code_output():
    output = os.popen('./code <in').read()
    return output

def main():
    compile_codes()

    while True:
        generate_case()
        naive_output = get_naive_output()
        code_output = get_code_output()

        if naive_output == code_output:
            print('ACCEPTED')
        else : 
            print('FAILED\n')
            print('ANSWER:')
            print(naive_output)
            print('\nCODE OUTPUT:')
            print(code_output)
            break

if __name__ == '__main__':
    main()
