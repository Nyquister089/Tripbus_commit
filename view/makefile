compile: 
	gcc -o run autista.c cliente.c hostess.c meccanico.c  ins.c upd.c login.c  ../model/trpdb.c ../utils/io.c ../utils/validation.c ../utils/db.c ../utils/dotenv.c $(mysql_config --libs)

clean: 
	-rm run
