# Compile q7.c
q7: q7.c
	gcc q7.c -o q7

# Run the C program with a value of N (example: make run_c N=100)
run_c: q7
	./q7 $(N)

# Run the Python script
run_py:
	python3 time-barchart.py

# Clean generated files
clean:
	rm -f q7
