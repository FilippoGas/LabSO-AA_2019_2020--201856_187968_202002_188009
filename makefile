#Makefile


CC = gcc -std=gnu90
#Ground Path
GP = ./src/
PM = $(GP)Main/#Main Path
PR = $(GP)Report/#Report Path
PA = $(GP)Analizer/#Analizer Path
PP = $(GP)Pprocess/#P Path
PQ = $(GP)Qprocess/#Q Path
BN = /bin/
TM = /tmp/
#Compile for Main
OM = $(TM)main.o $(TM)mainfunc.o $(TM)messages.o
#Compile for Analizer
OA = $(TM)analizer.o $(TM)macro_libglob.o $(TM)pPreprocessing.o $(TM)inputcheck.o $(TM)onTheFlyHandlerA.o $(TM)messageHandler.o $(TM)messageToReport.o
#Compile for Report
OR = $(TM)report.o $(TM)print_report.o
#Compile for P
OP = $(TM)processP.o $(TM)processPfunc.o $(TM)onTheFlyHandlerP.o
#Compile for Q
OQ = $(TM)processQ.o $(TM)processQfunc.o $(TM)macro_libglob.o


build:
	@[ -d /bin/ ] || mkdir /bin/
	@make -s /bin/main
	@make -s /bin/report
	@make -s /bin/processP
	@make -s /bin/processQ
	@make -s /bin/analizer

/bin/main: $(OM)
	@$(CC) -o $@ $^
/bin/analizer: $(OA)
	@$(CC) -o $@ $^
/bin/report: $(OR)
	@$(CC) -o $@ $^
/bin/processP: $(OP)
	@$(CC) -o $@ $^
/bin/processQ: $(OQ)
	@$(CC) -o $@ $^

/tmp/analizer.o:
	@$(CC) -c $(PA)analizer.c -o $(TM)analizer.o
/tmp/macro_libglob.o:
	@$(CC) -c $(PA)macro_libglob.c -o $(TM)macro_libglob.o
/tmp/inputcheck.o:
	@$(CC) -c $(PA)CheckInput/inputcheck.c -o $(TM)inputcheck.o
/tmp/pPreprocessing.o:
	@$(CC) -c $(PA)CheckInput/pPreprocessing.c -o $(TM)pPreprocessing.o
/tmp/onTheFlyHandlerA.o:
	@$(CC) -c $(PA)OnTheFly/onTheFlyHandler.c -o $(TM)onTheFlyHandlerA.o
/tmp/messageHandler.o:
	@$(CC) -c $(PA)ReadMessage/messageHandler.c -o $(TM)messageHandler.o
/tmp/messageToReport.o:
	@$(CC) -c $(PA)WriteToReport/messageToReport.c -o $(TM)messageToReport.o



/tmp/main.o:
	@$(CC) -c $(PM)main.c -o $(TM)main.o
/tmp/messages.o:
	@$(CC) -c $(PM)messages.c -o $(TM)messages.o
/tmp/mainfunc.o:
	@$(CC) -c $(PM)mainfunc.c -o $(TM)mainfunc.o

/tmp/report.o:
	@$(CC) -c $(PR)report.c -o $(TM)report.o
/tmp/print_report.o:
	@$(CC) -c $(PR)print_report.c -o $(TM)print_report.o


/tmp/processP.o:
	@$(CC) -c $(PP)processP.c -o $(TM)processP.o
/tmp/processPfunc.o:
	@$(CC) -c $(PP)processPfunc.c -o $(TM)processPfunc.o
/tmp/onTheFlyHandlerP.o:
	@$(CC) -c $(PP)OnTheFly/onTheFlyHandler.c -o $(TM)onTheFlyHandlerP.o

/tmp/processQ.o:
	@$(CC) -c $(PQ)processQ.c -o processQ.o
/tmp/processQfunc.o:
	@$(CC) -c $(PQ)processQfunc.c -o processQfunc.o


clean:
	#@rm *.out
	#@rm file temporanei e il rBNort

start:
	./$(BN)M.out

help:
	@echo Comandi Makefile:
	@echo "\<make build\>: Compila tutto il programma;"
	@echo "\<make clean\>: Rimuove i file temporanei, nota bisogna ricompilare dopo aver usato questo comando."
	@echo "\<make start\>: Fa partire il Main"
	#@echo his is the \<Makefile\>, use \<make build\> to recompile everything and \<make clean\> to clean all the trash that you left behind
