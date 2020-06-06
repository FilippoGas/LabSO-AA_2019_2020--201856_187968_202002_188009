#Makefile


CC = gcc -std=gnu90

GP = src/ 						#Ground Path
PM = $(GP)Main/				#Main Path
PR = $(GP)Report/			#Report Path
PA = $(GP)Analizer/ 	#Analizer Path
PP = $(GP)Pprocess/ 	#P Path
PQ = $(GP)Qprocess/		#Q Path
EP = $(GP)Executable/	#Executable Path
#Compile for Main
OM = $(PM)main.c $(PM)mainfunc.c $(PM)messages.c
#Compile for Analizer
OA = $(PA)analizer.c $(GP)macro_libglob.c $(PA)CheckInput/pPreprocessing.c $(PA)CheckInput/inputcheck.c $(PA)OnTheFly/onTheFlyHandler.c $(PA)ReadMessage/messageHandler.c $(PA)WriteToReport/messageToReport.c
#Compile for Report
OR = $(PR)report.c $(PR)print_report.c
#Compile for P
OP = $(PP)processP.c $(PP)processPfunc.c $(PP)OnTheFly/onTheFlyHandler.c
#Compile for Q
OQ = $(PQ)processQ.c $(PQ)processQfunc.c $(GP)macro_libglob.c

build:
	@make main
	@make report
	@make processP
	@make processQ
	@make analizer

analizer: $(OA)
	@$(CC) -o $(EP)A.out $(OA)


main: $(OM)
	@$(CC) -o $(EP)M.out $(OM)


report: $(OR)
	@$(CC) -o $(EP)R.out $(OR)


processP: $(OP)
	@$(CC) -o $(EP)P.out $(OP)


processQ: $(OQ)
	@$(CC) -o $(EP)Q.out $(OQ)


clean:
  #@rm $(EP)*.out
	#@rm file temporanei e il report

start:
	./$(EP)M.out

help:
	@echo Comandi Makefile:
	@echo "\<make build\>: Compila tutto il programma;"
	@echo "\<make clean\>: Rimuove i file temporanei, nota bisogna ricompilare dopo aver usato questo comando."
	@echo "\<make start\>: Fa partire il Main"
	#@echo his is the \<Makefile\>, use \<make build\> to recompile everything and \<make clean\> to clean all the trash that you left behind
