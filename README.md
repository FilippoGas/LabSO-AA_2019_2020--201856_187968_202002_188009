# LabSO-AA_2019_2020--201856_187968_202002_188009

mail gruppo: giacomo.fantoni@studenti.unitn.it

## Gruppo
Fantoni Giacomo	201856
Favari Ettore
Gastaldello Filippo
Lamorgese Giuseppe

Progetto del corso di Sistemi Operativi presso Università degli Studi di Trento per l'a.a. 2019-2020

## Usage:
	* The project offers three executable: 
		* main
		* analizer
		* report
	  To see how to use them launch them with the option -h: that will open the help page for the 
	  process. 
	* Main is a menu wrapper for report and analizer: communicates with analizer with a blocking
	  pipe at the beginning to receive the expanded list of files. There is another pipe non-blocking 
	  to analizer to modify its arguments on the fly. In main can exists only one running instance of 
	  analizer at any time. When requested main starts report and waits until it is closed.
	* Report is a menu that let the user see the data read with the last instance of analizer run. If
          analizer is running it will connect to it using a named pipe, if not it will read all the data 
	  from a file. The file contains the timstamp of the last update, the number of file and a list
	  of file followed by the data read. If the file is user modified report won't work.
	* Analizer is a process that communicates with report and main. Checks the input eliminating all
	  non existing file or directory and generates an n number of subfile "P" with a subsets of all
	  the files
	

## BUGS:

## Possibili migliorie:
