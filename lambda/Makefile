
FLAGS= -Wall -std=c++11 
all: lambda_test1 lambda_test2 lambda_test3 lambda_test4 lambda_test5 lambda_test6 lambda-test7

lambda_test1: lambda.cc
	$(CXX) lambda.cc -o lambda_test1 $(FLAGS)
lambda_test2: lambda2.cc
	$(CXX) lambda2.cc -o lambda_test2  $(FLAGS)
lambda_test3: lambda_capture.cc
	$(CXX) lambda_capture.cc -o lambda_test3 $(FLAGS)
lambda_test4: main.cc
	$(CXX) main.cc -o lambda_test4 $(FLAGS)
lambda_test5: source.cc
	$(CXX) source.cc -o lambda_test5 $(FLAGS)
lambda_test6: test.cc
	$(CXX) test.cc -o lambda_test6 $(FLAGS)
lambda-test7: lambda-test.cpp
	$(CXX) lambda-test.cpp -o lambda-test7 $(FLAGS)
clean:
	rm -f lambda_test1 lambda_test2 lambda_test3 lambda_test4 lambda_test5 lambda_test6 lambda-test7
