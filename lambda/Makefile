CXX=c++
FLAGS= -Wall -std=c++11 
all:
	$(CXX) lambda.cc -o lambda_test1 $(FLAGS)
	$(CXX) lambda2.cc -o lambda_test2  $(FLAGS)
	$(CXX) lambda_capture.cc -o lambda_test3 $(FLAGS)
	$(CXX) main.cc -o lambda_test4 $(FLAGS)
	$(CXX) source.cc -o lambda_test5 $(FLAGS)
	$(CXX) test.cc -o lambda_test6 $(FLAGS)
	$(CXX) lambda-test.cpp -o lambda-test7 $(FLAGS)
clean:
	rm -f lambda_test1 lambda_test2 lambda_test3 lambda_test4 lambda_test5 lambda_test6 lambda-test7
