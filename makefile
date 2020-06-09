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


build: /bin/main /bin/analizer /bin/report /bin/processP /bin/processQ
	@[ -d /bin/ ] || mkdir /bin/
	@[ -d /.help/ ] || mkdir /.help/
	@cp ./src/ManFiles/analizer_usage.txt /.help/
	@cp ./src/ManFiles/report_usage.txt /.help/
	@cp ./src/ManFiles/main_usage.txt /.help/

clean:	/tmp/analizer.o /tmp/macro_libglob.o /tmp/inputcheck.o /tmp/pPreprocessing.o /tmp/onTheFlyHandlerA.o /tmp/messageHandler.o /tmp/messageToReport.o /tmp/main.o /tmp/messages.o /tmp/mainfunc.o /tmp/report.o /tmp/print_report.o /tmp/report.o /tmp/print_report.o /tmp/processP.o /tmp/processPfunc.o /tmp/onTheFlyHandlerP.o /tmp/processQ.o /tmp/processQfunc.o
	@rm -f $^

help:
	@echo Commands Makefile:
	@echo "\<make build\>: Install the programs"
	@echo "\<make clean\>: Remove temporary files."
	@echo "\<make start\>: Start main."


/bin/main: $(OM)
	@$(CC) -o $@ $^
/bin/analizer: $(OA)
	@$(CC) -o $@ $^ -lm
/bin/report: $(OR)
	@$(CC) -o $@ $^
/bin/processP: $(OP)
	@$(CC) -o $@ $^
/bin/processQ: $(OQ)
	@$(CC) -o $@ $^

/tmp/analizer.o:
	@$(CC) -c $(PA)analizer.c -o $(TM)analizer.o
/tmp/macro_libglob.o:
	@$(CC) -c $(GP)macro_libglob.c -o $(TM)macro_libglob.o
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
	@$(CC) -c $(PQ)processQ.c -o $(TM)processQ.o
/tmp/processQfunc.o:
	@$(CC) -c $(PQ)processQfunc.c -o $(TM)processQfunc.o



