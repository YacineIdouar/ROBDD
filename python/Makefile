
test_tools:
	python3 Test_tools.py

test_tree:
	python3 Test_tree.py

exec_main :
	python3 Main.py 

exec_experimentation :
	python3 Experimentations.py

define experim =
	k=(500003 400003 486892 56343 94999 17975)
	for i in 5 6 7 8 9 10
	do
		python3 Experimentations.py $i ${k[$i - 5]}
	done;
endef
exec_experimentations_var_10: SHELL:=/bin/bash
exec_experimentations_var_10: ;$(value experim)
	
.ONESHELL:



clean: 
	rm -rf "./__pycache__" ./dot/* ./code/__pycache__  ./experimentations/gnuplot_data/*.dat ./experimentations/*.md ./experimentations/gnuplot_diagrammes/*
	clear
