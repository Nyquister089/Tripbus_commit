compile: 
	gcc  *.c -o program `mysql_config --cflags --include --libs`  ../model/trpdb.c ../utils/io.c ../utils/validation.c ../utils/db.c ../utils/dotenv.c 

clean: 
	-rm run
