
test_tools:
	python3 Test_tools.py

test_tree:
	python3 Test_tree.py

exec_main :
	python3 Main.py 

clean: 
	rm -rf "./__pycache__" ./dot/* ./code/__pycache__ ./test/__pycache__
	clear