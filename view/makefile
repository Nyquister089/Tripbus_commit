compile: 
	gcc  *.c -o program   ../model/trpdb.c ../utils/io.c ../utils/validation.c ../utils/db.c ../utils/dotenv.c `mysql_config --cflags --include --libs`

clean: 
	-rm program
