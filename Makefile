compile:
	gcc -o run_test_validation test_validation.c  test_maker.c ../utils/validation.c
clean:
	-rm run_test_validation