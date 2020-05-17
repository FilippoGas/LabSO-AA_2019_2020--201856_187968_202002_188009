import sys
from subprocess import Popen, PIPE, call
import random

def executeCommand(command):
    p = Popen(command, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    output, err = p.communicate(b"input data that is passed to subprocess' stdin")
    return output, err

def initTestArea():
    res = {}
    res["Easy"] = initTestDir("Easy", 20, 5, 3, 160, 30)
    res["Medium"] = initTestDir("Medium", 80, 30, 8, 1000, 30)
    res["Hard"] = initTestDir("Hard", 300, 100, 2, 200000, 30)
    res["Nested"] = initTestDir("Nested", 100, 90, 60, 200, 30)
    #res["BigFiles"] = initTestDir("BigFiles", 40, 5, 2, 10000000, 100)
    #res["BigVariance"] = initTestDir("BigVariance", 40, 5, 2, 1000000, 555000)
    return res


def initTestDir(name, n_files, n_dir, dir_height, dim_files, file_dim_variation):
    if name[-1] != '/':
        name += '/'
    name = './' + name
    out, err = executeCommand(["ls", name])
    if not err:
        executeCommand(["rm", "-r", name])
    call(["mkdir", name])
    paths = []
    paths.append(name)
    i = 0
    for i in range(0, n_dir):
        new_dir = str()
        if i < dir_height:
            new_dir = paths[-1] + "dirtest" + str(i) + '/'
            paths.append(new_dir)
        else:
            j = random.randint(0, len(paths) - 1)
            new_dir = paths[j] + "dirtest" + str(i) + '/'
        call(["mkdir", new_dir])
    res = []
    for i in range(0, n_files):
        namefile = paths[random.randint(0, len(paths) - 1)] + "filetest" + str(i)
        content = createFile(namefile, dim_files, file_dim_variation)
        content = [namefile, content]
        res.append(content)
    return res

def createFile(namefile, dim_file, file_dim_variation):
    dim_file = random.randint(dim_file - file_dim_variation, dim_file + file_dim_variation)
    while dim_file < 0:
        dim_file = random.randint(dim_file - file_dim_variation, dim_file + file_dim_variation)
    res = [0] * 256
    with open(namefile, 'w') as new_file:
        content = ''.join([chr(random.randint(0, 255)) for value in range(0, dim_file)])
        for i in content:
            res[ord(i)] += 1
        new_file.write(content)
    return res

def compile():
    prefix = "/LabSO-AA_2019_2020--201856_187968_202002_188009/src/"
    call(["gcc", "-std=gnu90", prefix + "Report/report.c", prefix + "Report/print_report.c", prefix + "macro_libglob.c", "-o", "/TestArea/Executable/Report.out"])
    call(["gcc", "-std=gnu90", prefix + "Qprocess/processQ.c", prefix + "Qprocess/processQfunc.c", prefix + "macro_libglob.c", "-o", "/TestArea/Executable/Q.out"])
    call(["gcc", "-std=gnu90", prefix + "Pprocess/processP.c", prefix + "Pprocess/processPfunc.c", prefix + "Debug/utility.c", prefix + "macro_libglob.c", "-o", "/TestArea/Executable/P.out"])
    call(["gcc", "-std=gnu90", prefix + "Analizer/analizer.c", prefix + "Debug/utility.c", prefix + "Analizer/CheckInput/inputcheck.c", prefix + "Analizer/CheckInput/pPreprocessing.c", prefix + "Analizer/ReadMessage/messageHandler.c", prefix + "Analizer/WriteToReport/messageToReport.c", prefix + "macro_libglob.c", "-lm", "-o", "/TestArea/Executable/A.out"])

if __name__ == "__main__":
    print("Press 1 to init test area\nPress 2 to compile all")
    menu = input()
    if menu == "1":
        content = initTestArea()
    else:
        compile()

