CXX_FLAGS=-std=c++11

all: temp-func temp-class temp-class2 temp-class3 template-temp template-un template-type template-inst template-spec template-ptr

temp-func: template-function.cpp
	$(CXX) $(CXX_FLAGS) template-function.cpp -o temp-func
temp-class: template-class.cpp
	$(CXX) $(CXX_FLAGS) template-class.cpp -o temp-class
temp-class2: template-class2.cpp
	$(CXX) $(CXX_FLAGS) template-class2.cpp -o temp-class2
temp-class3: template-class3.cpp
	$(CXX) $(CXX_FLAGS) template-class3.cpp -o temp-class3
template-temp: template-template.cpp
	$(CXX) $(CXX_FLAGS) template-template.cpp -o template-temp
template-un: template-union.cpp
	$(CXX) $(CXX_FLAGS) template-union.cpp -o template-un
template-type: template-type.cpp
	$(CXX) $(CXX_FLAGS) template-type.cpp -o template-type
template-inst: template-inst.cpp
	$(CXX) $(CXX_FLAGS) template-inst.cpp -o template-inst
template-spec: template-spec.cpp
	$(CXX) $(CXX_FLAGS) template-spec.cpp -o template-spec
template-ptr: template-pointer.cpp
	$(CXX) $(CXX_FLAGS) template-pointer.cpp -o template-ptr
clean:
	rm -f temp-func temp-class temp-class2 temp-class3 template-temp template-un template-type template-inst template-spec template-ptr

